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

#include <bsoncxx/document/element.hpp>

//

#include <bsoncxx/v1/detail/macros.hpp>

#include <cstdlib>
#include <string>

#include <bsoncxx/exception/error_code.hpp>
#include <bsoncxx/exception/exception.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/types/bson_value/value.hpp>
#include <bsoncxx/types/bson_value/view.hpp>

#include <bsoncxx/private/bson.hh>
#include <bsoncxx/private/suppress_deprecation_warnings.hh>

#define BSONCXX_CITER                                                           \
    bson_iter_t iter;                                                           \
    bson_iter_init_from_data_at_offset(&iter, _raw, _length, _offset, _keylen); \
    ((void)0)

namespace bsoncxx {
namespace v_noabi {
namespace document {

element::element() : element(nullptr, 0, 0, 0) {}

element::element(std::uint8_t const* raw, std::uint32_t length, std::uint32_t offset, std::uint32_t keylen)
    : _raw(raw), _length(length), _offset(offset), _keylen(keylen) {}

element::element(stdx::string_view const key) : _raw(nullptr), _length(0), _offset(0), _keylen(0), _key(key) {}

std::uint8_t const* element::raw() const {
    return _raw;
}

std::uint32_t element::length() const {
    return _length;
}
std::uint32_t element::offset() const {
    return _offset;
}

std::uint32_t element::keylen() const {
    return _keylen;
}

bsoncxx::v_noabi::type element::type() const {
    if (_raw == nullptr) {
        throw bsoncxx::v_noabi::exception{
            error_code::k_unset_element,
            "cannot return the type of uninitialized element" +
                std::string(_key ? " with key \"" + std::string(_key.value().data()) + "\"" : "")};
    }

    BSONCXX_CITER;
    return static_cast<bsoncxx::v_noabi::type>(bson_iter_type(&iter));
}

stdx::string_view element::key() const {
    if (_raw == nullptr) {
        throw bsoncxx::v_noabi::exception{
            error_code::k_unset_element,
            "cannot return the key from an uninitialized element" +
                std::string(_key ? " with key \"" + std::string(_key.value().data()) + "\"" : "")};
    }

    BSONCXX_CITER;

    char const* key = bson_iter_key(&iter);

    return stdx::string_view{key};
}

#define BSONCXX_ENUM(name, val)                                                                         \
    types::b_##name element::get_##name() const {                                                       \
        if (_raw == nullptr) {                                                                          \
            throw bsoncxx::v_noabi::exception{                                                          \
                error_code::k_unset_element,                                                            \
                "cannot get " #name " from an uninitialized element" +                                  \
                    std::string(_key ? " with key \"" + std::string(_key.value().data()) + "\"" : "")}; \
        }                                                                                               \
        types::bson_value::view v{_raw, _length, _offset, _keylen};                                     \
        return v.get_##name();                                                                          \
    }
#include <bsoncxx/enums/type.hpp>
#undef BSONCXX_ENUM

types::bson_value::view element::get_value() const {
    switch (static_cast<int>(type())) {
#define BSONCXX_ENUM(type, val) \
    case val:                   \
        return types::bson_value::view{get_##type()};
#include <bsoncxx/enums/type.hpp>
#undef BSONCXX_ENUM
    }

    BSONCXX_PRIVATE_UNREACHABLE;
}

types::bson_value::value element::get_owning_value() const {
    return types::bson_value::value{_raw, _length, _offset, _keylen};
}

element element::operator[](stdx::string_view key) const {
    if (_raw == nullptr || type() != bsoncxx::v_noabi::type::k_document)
        return element();
    document::view doc = get_document();
    return doc[key];
}

array::element element::operator[](std::uint32_t i) const {
    if (_raw == nullptr || type() != bsoncxx::v_noabi::type::k_array)
        return array::element();
    array::view arr = get_array();
    return arr[i];
}

element::operator bool() const {
    return _raw != nullptr;
}

bool operator==(element const& elem, types::bson_value::view const& v) {
    return elem.get_value() == v;
}

bool operator==(types::bson_value::view const& v, element const& elem) {
    return elem == v;
}

bool operator!=(element const& elem, types::bson_value::view const& v) {
    return !(elem == v);
}

bool operator!=(types::bson_value::view const& v, element const& elem) {
    return !(elem == v);
}

} // namespace document
} // namespace v_noabi
} // namespace bsoncxx
