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

#pragma once

#include <mongocxx/options/bulk_write-fwd.hpp>

#include <bsoncxx/document/view_or_value.hpp>
#include <bsoncxx/stdx/optional.hpp>
#include <bsoncxx/types/bson_value/view_or_value.hpp>

#include <mongocxx/write_concern.hpp>

#include <mongocxx/config/prelude.hpp>

namespace mongocxx {
namespace v_noabi {
namespace options {

///
/// Used by @ref mongocxx::v_noabi::collection.
///
class bulk_write {
   public:
    ///
    /// Constructs a new bulk_write object. By default, bulk writes are considered ordered
    /// as this is the only safe choice. If you want an unordered update, you must call
    /// ordered(false) to switch to unordered mode.
    ///
    MONGOCXX_ABI_EXPORT_CDECL() bulk_write();

    ///
    /// Sets whether the writes must be executed in order by the server.
    ///
    /// The server-side default is @c true.
    ///
    /// @param ordered
    ///   If @c true all write operations will be executed serially in the order they were appended,
    ///   and the entire bulk operation will abort on the first error. If @c false operations will
    ///   be executed in arbitrary order (possibly in parallel on the server) and any errors will be
    ///   reported after attempting all operations.
    ///
    /// @return
    ///   A reference to the object on which this member function is being called.  This facilitates
    ///   method chaining.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(bulk_write&) ordered(bool ordered);

    ///
    /// Gets the current value of the ordered option.
    ///
    /// @return The value of the ordered option.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(bool) ordered() const;

    ///
    /// Sets the write_concern for this operation.
    ///
    /// @param wc
    ///   The new write_concern.
    ///
    /// @return
    ///   A reference to the object on which this member function is being called.  This facilitates
    ///   method chaining.
    ///
    /// @see
    /// - https://www.mongodb.com/docs/manual/core/write-concern/
    ///
    MONGOCXX_ABI_EXPORT_CDECL(bulk_write&) write_concern(mongocxx::v_noabi::write_concern wc);

    ///
    /// The current write_concern for this operation.
    ///
    /// @return
    ///   The current write_concern.
    ///
    /// @see
    /// - https://www.mongodb.com/docs/manual/core/write-concern/
    ///
    MONGOCXX_ABI_EXPORT_CDECL(bsoncxx::v_noabi::stdx::optional<mongocxx::v_noabi::write_concern> const&)
    write_concern() const;

    ///
    /// Set whether or not to bypass document validation for this operation.
    ///
    /// @param bypass_document_validation
    ///   Whether or not to bypass document validation.
    ///
    /// @return
    ///   A reference to the object on which this member function is being called.  This facilitates
    ///   method chaining.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(bulk_write&)
    bypass_document_validation(bool bypass_document_validation);

    ///
    /// The current setting for bypassing document validation for this operation.
    ///
    /// @return
    ///  The current document validation bypass setting.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(bsoncxx::v_noabi::stdx::optional<bool> const)
    bypass_document_validation() const;

    ///
    /// Set the value of the let option.
    ///
    /// @param let
    ///   The new let option.
    ///
    /// @return
    ///   A reference to the object on which this member function is being called.  This facilitates
    ///   method chaining.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(bulk_write&) let(bsoncxx::v_noabi::document::view_or_value let);

    ///
    /// Gets the current value of the let option.
    ///
    /// @return
    ///  The current let option.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(bsoncxx::v_noabi::stdx::optional<bsoncxx::v_noabi::document::view_or_value> const)
    let() const;

    ///
    /// Set the value of the comment option.
    ///
    /// @param comment
    ///   The new comment option.
    ///
    /// @return
    ///   A reference to the object on which this member function is being called.  This facilitates
    ///   method chaining.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(bulk_write&)
    comment(bsoncxx::v_noabi::types::bson_value::view_or_value comment);

    ///
    /// Gets the current value of the comment option.
    ///
    /// @return
    ///  The current comment option.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(bsoncxx::v_noabi::stdx::optional<bsoncxx::v_noabi::types::bson_value::view_or_value> const)
    comment() const;

   private:
    bool _ordered;
    bsoncxx::v_noabi::stdx::optional<mongocxx::v_noabi::write_concern> _write_concern;
    bsoncxx::v_noabi::stdx::optional<bool> _bypass_document_validation;
    bsoncxx::v_noabi::stdx::optional<bsoncxx::v_noabi::document::view_or_value> _let;
    bsoncxx::v_noabi::stdx::optional<bsoncxx::v_noabi::types::bson_value::view_or_value> _comment;
};

} // namespace options
} // namespace v_noabi
} // namespace mongocxx

#include <mongocxx/config/postlude.hpp>

///
/// @file
/// Provides @ref mongocxx::v_noabi::options::bulk_write.
///
