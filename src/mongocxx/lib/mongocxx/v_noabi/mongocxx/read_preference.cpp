// Copyright 2009-present MongoDB, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <bsoncxx/types.hpp>

#include <mongocxx/exception/error_code.hpp>
#include <mongocxx/exception/logic_error.hpp>
#include <mongocxx/read_preference.hpp>

#include <bsoncxx/private/make_unique.hh>

#include <mongocxx/private/bson.hh>
#include <mongocxx/private/conversions.hh>
#include <mongocxx/private/mongoc.hh>
#include <mongocxx/private/read_preference.hh>

namespace mongocxx {
namespace v_noabi {

read_preference::read_preference(read_preference&&) noexcept = default;
read_preference& read_preference::operator=(read_preference&&) noexcept = default;

read_preference::read_preference(read_preference const& other)
    : _impl(bsoncxx::make_unique<impl>(libmongoc::read_prefs_copy(other._impl->read_preference_t))) {}

read_preference& read_preference::operator=(read_preference const& other) {
    _impl.reset(bsoncxx::make_unique<impl>(libmongoc::read_prefs_copy(other._impl->read_preference_t)).release());
    return *this;
}

read_preference::read_preference(std::unique_ptr<impl>&& implementation) {
    _impl.reset(implementation.release());
}

read_preference::read_preference()
    : _impl(
          bsoncxx::make_unique<impl>(
              libmongoc::read_prefs_new(libmongoc::conversions::read_mode_t_from_read_mode(read_mode::k_primary)))) {}

read_preference::read_preference(read_mode mode) : read_preference(mode, deprecated_tag{}) {}

read_preference::read_preference(read_mode mode, deprecated_tag)
    : _impl(
          bsoncxx::make_unique<impl>(
              libmongoc::read_prefs_new(libmongoc::conversions::read_mode_t_from_read_mode(mode)))) {}

read_preference::read_preference(read_mode mode, bsoncxx::v_noabi::document::view_or_value tags)
    : read_preference(mode, std::move(tags), deprecated_tag{}) {}

read_preference::read_preference(read_mode mode, bsoncxx::v_noabi::document::view_or_value tags, deprecated_tag)
    : read_preference(mode, deprecated_tag{}) {
    read_preference::tags(std::move(tags));
}

read_preference::~read_preference() = default;

read_preference& read_preference::mode(read_mode mode) {
    libmongoc::read_prefs_set_mode(_impl->read_preference_t, libmongoc::conversions::read_mode_t_from_read_mode(mode));

    return *this;
}

read_preference& read_preference::tags(bsoncxx::v_noabi::document::view_or_value tag_set_list) {
    libbson::scoped_bson_t scoped_bson_tags(std::move(tag_set_list));
    libmongoc::read_prefs_set_tags(_impl->read_preference_t, scoped_bson_tags.bson());

    return *this;
}

read_preference& read_preference::tags(bsoncxx::v_noabi::array::view_or_value tag_set_list) {
    libbson::scoped_bson_t scoped_bson_tags(bsoncxx::v_noabi::document::view(tag_set_list.view()));
    libmongoc::read_prefs_set_tags(_impl->read_preference_t, scoped_bson_tags.bson());

    return *this;
}

read_preference::read_mode read_preference::mode() const {
    return libmongoc::conversions::read_mode_from_read_mode_t(libmongoc::read_prefs_get_mode(_impl->read_preference_t));
}

bsoncxx::v_noabi::stdx::optional<bsoncxx::v_noabi::document::view> read_preference::tags() const {
    bson_t const* bson_tags = libmongoc::read_prefs_get_tags(_impl->read_preference_t);

    if (bson_count_keys(bson_tags))
        return bsoncxx::v_noabi::document::view(bson_get_data(bson_tags), bson_tags->len);

    return bsoncxx::v_noabi::stdx::optional<bsoncxx::v_noabi::document::view>{};
}

read_preference& read_preference::max_staleness(std::chrono::seconds max_staleness) {
    auto max_staleness_sec = max_staleness.count();
    if (max_staleness_sec < -1 || max_staleness_sec == 0) {
        throw logic_error{error_code::k_invalid_parameter};
    }
    libmongoc::read_prefs_set_max_staleness_seconds(_impl->read_preference_t, max_staleness_sec);

    return *this;
}

bsoncxx::v_noabi::stdx::optional<std::chrono::seconds> read_preference::max_staleness() const {
    auto staleness = libmongoc::read_prefs_get_max_staleness_seconds(_impl->read_preference_t);

    // libmongoc signals "disabled" with the value -1.
    if (staleness == -1) {
        return bsoncxx::v_noabi::stdx::nullopt;
    }

    return std::chrono::seconds{staleness};
}

read_preference& read_preference::hedge(bsoncxx::v_noabi::document::view_or_value hedge) {
    libbson::scoped_bson_t hedge_bson{std::move(hedge)};
    BSONCXX_SUPPRESS_DEPRECATION_WARNINGS_BEGIN
    libmongoc::read_prefs_set_hedge(_impl->read_preference_t, hedge_bson.bson());
    BSONCXX_SUPPRESS_DEPRECATION_WARNINGS_END
    return *this;
}

bsoncxx::v_noabi::stdx::optional<bsoncxx::v_noabi::document::view> const read_preference::hedge() const {
    BSONCXX_SUPPRESS_DEPRECATION_WARNINGS_BEGIN
    bson_t const* hedge_bson = libmongoc::read_prefs_get_hedge(_impl->read_preference_t);
    BSONCXX_SUPPRESS_DEPRECATION_WARNINGS_END

    if (!bson_empty(hedge_bson)) {
        return bsoncxx::v_noabi::document::view(bson_get_data(hedge_bson), hedge_bson->len);
    }

    return bsoncxx::v_noabi::stdx::optional<bsoncxx::v_noabi::document::view>{};
}

bool operator==(read_preference const& lhs, read_preference const& rhs) {
    return (lhs.mode() == rhs.mode()) && (lhs.tags() == rhs.tags()) && (lhs.max_staleness() == rhs.max_staleness());
}

bool operator!=(read_preference const& lhs, read_preference const& rhs) {
    return !(lhs == rhs);
}

} // namespace v_noabi
} // namespace mongocxx
