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

#include <cstdint>
#include <system_error>

#include <mongocxx/exception/error_code-fwd.hpp>

#include <mongocxx/config/prelude.hpp>

namespace mongocxx {
namespace v_noabi {

///
/// Errors which may occur during mongocxx library usage.
///
/// @note `std::is_error_code_enum` is specialized for this type.
///
enum class error_code : std::int32_t {
    /// More than one mongocxx::v_noabi::instance has been created.
    k_cannot_recreate_instance = 1,

    /// A default-constructed or moved-from mongocxx::v_noabi::client object has been used.
    k_invalid_client_object,

    /// A default-constructed or moved-from mongocxx::v_noabi::collection object has been used.
    k_invalid_collection_object,

    /// A default-constructed or moved-from mongocxx::v_noabi::database object has been used.
    k_invalid_database_object,

    /// An invalid or out-of-bounds parameter was provided.
    k_invalid_parameter,

    /// An SSL operation was used without SSL support being built.
    k_ssl_not_supported,

    /// An unknown read concern level was set.
    k_unknown_read_concern,

    /// An unknown write concern level was set.
    k_unknown_write_concern,

    /// The server returned a malformed response.
    k_server_response_malformed,

    /// An invalid MongoDB URI was provided.
    k_invalid_uri,

    /// A default-constructed or moved-from mongocxx::v_noabi::gridfs::bucket object has been used.
    k_invalid_gridfs_bucket_object,

    /// A default-constructed or moved-from mongocxx::v_noabi::gridfs::uploader object has been
    /// used.
    k_invalid_gridfs_uploader_object,

    /// A default-constructed or moved-from mongocxx::v_noabi::gridfs::downloader object has been
    /// used.
    k_invalid_gridfs_downloader_object,

    /// A mongocxx::v_noabi::gridfs::uploader object was not open for writing, or a
    /// mongocxx::v_noabi::gridfs::downloader object was not open for reading.
    k_gridfs_stream_not_open,

    /// A mongocxx::v_noabi::gridfs::uploader object has exceeded the maximum number of allowable
    /// GridFS
    /// chunks when attempting to upload the requested file.
    k_gridfs_upload_requires_too_many_chunks,

    /// The requested GridFS file was not found.
    k_gridfs_file_not_found,

    /// A GridFS file being operated on was discovered to be corrupted.
    k_gridfs_file_corrupted,

    /// The mongocxx::v_noabi::instance has been destroyed.
    k_instance_destroyed,

    /// mongocxx::v_noabi::client.create_session failed to create a
    /// mongocxx::v_noabi::client_session.
    k_cannot_create_session,

    /// A failure attempting to pass a mongocxx::v_noabi::client_session to a method.
    k_invalid_session,

    /// A moved-from mongocxx::v_noabi::options::transaction object has been used.
    k_invalid_transaction_options_object,

    /// A resource (server API handle, etc.) could not be created:
    k_create_resource_fail,

    /// A default-constructed or moved-from mongocxx::v_noabi::search_index_model object has been
    /// used.
    k_invalid_search_index_model,

    /// A default-constructed or moved-from mongocxx::v_noabi::search_index_view object has been
    /// used.
    k_invalid_search_index_view,

    /// Timed out while waiting for a client to be returned to the pool
    k_pool_wait_queue_timeout,

    // Add new constant string message to error_code.cpp as well!
};

///
/// Get the error_category for mongocxx library exceptions.
///
/// @return The mongocxx error_category
///
MONGOCXX_ABI_EXPORT_CDECL(std::error_category const&) error_category();

///
/// Translate a mongocxx::v_noabi::error_code into a std::error_code.
///
/// @param error A mongocxx::v_noabi::error_code
///
/// @return A std::error_code
///
inline std::error_code make_error_code(error_code error) {
    return {static_cast<int>(error), error_category()};
}

} // namespace v_noabi
} // namespace mongocxx

namespace mongocxx {

using ::mongocxx::v_noabi::error_category;
using ::mongocxx::v_noabi::make_error_code;

} // namespace mongocxx

#include <mongocxx/config/postlude.hpp>

namespace std {

// @cond DOXYGEN_DISABLE
template <>
struct is_error_code_enum<::mongocxx::v_noabi::error_code> : std::true_type {};
// @endcond

} // namespace std

///
/// @file
/// Provides @ref mongocxx::v_noabi::error_code.
///
