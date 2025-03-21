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

#include <mongocxx/v1/detail/macros.hpp>

#include <string>

#include <bsoncxx/builder/basic/document.hpp>

#include <mongocxx/validation_criteria.hpp>

namespace {

using bsoncxx::v_noabi::builder::basic::kvp;

// Convert validation levels to strings.
std::string validation_level_to_string(mongocxx::v_noabi::validation_criteria::validation_level level) {
    switch (level) {
        case mongocxx::v_noabi::validation_criteria::validation_level::k_off:
            return "off";
        case mongocxx::v_noabi::validation_criteria::validation_level::k_moderate:
            return "moderate";
        case mongocxx::v_noabi::validation_criteria::validation_level::k_strict:
            return "strict";
    }

    MONGOCXX_PRIVATE_UNREACHABLE;
}

// Convert validation actions to strings.
std::string validation_action_to_string(mongocxx::v_noabi::validation_criteria::validation_action action) {
    switch (action) {
        case mongocxx::v_noabi::validation_criteria::validation_action::k_warn:
            return "warn";
        case mongocxx::v_noabi::validation_criteria::validation_action::k_error:
            return "error";
    }

    MONGOCXX_PRIVATE_UNREACHABLE;
}

} // namespace

namespace mongocxx {
namespace v_noabi {

validation_criteria& validation_criteria::rule(bsoncxx::v_noabi::document::view_or_value rule) {
    _rule = std::move(rule);
    return *this;
}

validation_criteria& validation_criteria::level(validation_criteria::validation_level level) {
    _level = level;
    return *this;
}

validation_criteria& validation_criteria::action(validation_criteria::validation_action action) {
    _action = action;
    return *this;
}

bsoncxx::v_noabi::stdx::optional<bsoncxx::v_noabi::document::view_or_value> const& validation_criteria::rule() const {
    return _rule;
}

bsoncxx::v_noabi::stdx::optional<validation_criteria::validation_level> const& validation_criteria::level() const {
    return _level;
}

bsoncxx::v_noabi::stdx::optional<validation_criteria::validation_action> const& validation_criteria::action() const {
    return _action;
}

bsoncxx::v_noabi::document::value validation_criteria::to_document_deprecated() const {
    bsoncxx::v_noabi::builder::basic::document doc;

    if (_rule) {
        doc.append(kvp("validator", bsoncxx::v_noabi::types::b_document{*_rule}));
    }

    if (_level) {
        doc.append(kvp("validationLevel", validation_level_to_string(*_level)));
    }

    if (_action) {
        doc.append(kvp("validationAction", validation_action_to_string(*_action)));
    }

    return doc.extract();
}

bsoncxx::v_noabi::document::value validation_criteria::to_document() const {
    return to_document_deprecated();
}

bool operator==(validation_criteria const& lhs, validation_criteria const& rhs) {
    return ((lhs.rule() == rhs.rule()) && (lhs.level() == rhs.level()) && (lhs.action() == rhs.action()));
}
bool operator!=(validation_criteria const& lhs, validation_criteria const& rhs) {
    return !(lhs == rhs);
}

} // namespace v_noabi
} // namespace mongocxx
