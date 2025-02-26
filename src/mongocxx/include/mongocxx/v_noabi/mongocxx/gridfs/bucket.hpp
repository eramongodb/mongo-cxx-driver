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

#include <istream>
#include <memory>
#include <ostream>

#include <mongocxx/database-fwd.hpp>
#include <mongocxx/gridfs/bucket-fwd.hpp>

#include <bsoncxx/document/view_or_value.hpp>
#include <bsoncxx/stdx/optional.hpp>
#include <bsoncxx/stdx/string_view.hpp>
#include <bsoncxx/types/bson_value/view.hpp>

#include <mongocxx/cursor.hpp>
#include <mongocxx/gridfs/downloader.hpp>
#include <mongocxx/gridfs/uploader.hpp>
#include <mongocxx/options/find.hpp>
#include <mongocxx/options/gridfs/bucket.hpp>
#include <mongocxx/options/gridfs/upload.hpp>
#include <mongocxx/result/gridfs/upload.hpp>

#include <mongocxx/config/prelude.hpp>

namespace mongocxx {
namespace v_noabi {
namespace gridfs {

///
/// A GridFS bucket.
///
/// A GridFS bucket is used to store files that may be too large to store in a single document due
/// to the 16 MB limit. The bucket comprises of two collections, `<bucketname>.files` and
/// `<bucketname>.chunks.` A file written to a GridFS bucket will be serialized into zero or more
/// chunk documents stored in the `<bucketname>.chunks` collection, and one document will be stored
/// in the `<bucketname>.files` collection containing the information about the file. Users should
/// not modify these collections directly.
///
/// @par Example
/// ```cpp
/// mongocxx::v_noabi::client mongo_client{mongocxx::v_noabi::uri{}};
///
/// // Obtain the default GridFS bucket for a given database.
/// auto gridfs_bucket = mongo_client["database"].gridfs_bucket();
/// ```
///
/// See also the method documentation for `mongocxx::v_noabi::database::gridfs_bucket()`.
///
/// @see
/// - https://www.mongodb.com/display/DOCS/GridFS
///
class bucket {
   public:
    ///
    /// Default constructs a bucket object. The bucket is equivalent to the state of a moved from
    /// bucket. The only valid actions to take with a default constructed bucket are to assign to
    /// it, or destroy it.
    ///
    MONGOCXX_ABI_EXPORT_CDECL() bucket() noexcept;

    ///
    /// Move constructs a bucket.
    ///
    MONGOCXX_ABI_EXPORT_CDECL() bucket(bucket&&) noexcept;

    ///
    /// Move assigns a bucket.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(bucket&) operator=(bucket&&) noexcept;

    ///
    /// Copy constructs a bucket.
    ///
    MONGOCXX_ABI_EXPORT_CDECL() bucket(bucket const&);

    ///
    /// Copy assigns a bucket.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(bucket&) operator=(bucket const&);

    ///
    /// Destroys a bucket.
    ///
    MONGOCXX_ABI_EXPORT_CDECL() ~bucket();

    ///
    /// Returns true if the bucket is valid, meaning it was not default constructed or moved from.
    ///
    explicit MONGOCXX_ABI_EXPORT_CDECL() operator bool() const noexcept;

    ///
    /// Opens a gridfs::uploader to create a new GridFS file. The id of the file will be
    /// automatically generated as an ObjectId.
    ///
    /// @param filename
    ///   The name of the file to be uploaded. A bucket can contain multiple files with the same
    ///   name.
    ///
    /// @param options
    ///   Optional arguments; see options::gridfs::upload.
    ///
    /// @return
    ///   A stream for writing to the GridFS file.
    ///
    /// @note
    ///   If this GridFS bucket does not already exist in the database, it will be implicitly
    ///   created and initialized with GridFS indexes.
    ///
    /// @throws mongocxx::v_noabi::logic_error if `options` are invalid.
    ///
    /// @throws mongocxx::v_noabi::query_exception
    ///   if an error occurs when reading from the files collection for this bucket.
    ///
    /// @throws mongocxx::v_noabi::operation_exception if an error occurs when building GridFS
    /// indexes.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(uploader)
    open_upload_stream(bsoncxx::v_noabi::stdx::string_view filename, options::gridfs::upload const& options = {});

    ///
    /// Opens a gridfs::uploader to create a new GridFS file. The id of the file will be
    /// automatically generated as an ObjectId.
    ///
    /// @param session
    ///   The mongocxx::v_noabi::client_session with which to perform the upload. The client session
    ///   must remain valid for the lifetime of the uploader.
    ///
    /// @param filename
    ///   The name of the file to be uploaded. A bucket can contain multiple files with the same
    ///   name.
    ///
    /// @param options
    ///   Optional arguments; see options::gridfs::upload.
    ///
    /// @return
    ///   A stream for writing to the GridFS file.
    ///
    /// @note
    ///   If this GridFS bucket does not already exist in the database, it will be implicitly
    ///   created and initialized with GridFS indexes.
    ///
    /// @throws mongocxx::v_noabi::logic_error if `options` are invalid.
    ///
    /// @throws mongocxx::v_noabi::query_exception
    ///   if an error occurs when reading from the files collection for this bucket.
    ///
    /// @throws mongocxx::v_noabi::operation_exception if an error occurs when building GridFS
    /// indexes.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(uploader)
    open_upload_stream(
        client_session const& session,
        bsoncxx::v_noabi::stdx::string_view filename,
        options::gridfs::upload const& options = {});

    ///
    /// Opens a gridfs::uploader to create a new GridFS file.
    ///
    /// @param id
    ///   The unique id of the file being uploaded.
    ///
    /// @param filename
    ///   The name of the file to be uploaded. A bucket can contain multiple files with the same
    ///   name.
    ///
    /// @param options
    ///   Optional arguments; see options::gridfs::upload.
    ///
    /// @return
    ///   The gridfs::uploader to which the GridFS file should be written.
    ///
    /// @note
    ///   If this GridFS bucket does not already exist in the database, it will be implicitly
    ///   created and initialized with GridFS indexes.
    ///
    /// @throws mongocxx::v_noabi::logic_error if `options` are invalid.
    ///
    /// @throws mongocxx::v_noabi::query_exception
    ///   if an error occurs when reading from the files collection for this bucket.
    ///
    /// @throws mongocxx::v_noabi::operation_exception if an error occurs when building GridFS
    /// indexes.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(uploader)
    open_upload_stream_with_id(
        bsoncxx::v_noabi::types::bson_value::view id,
        bsoncxx::v_noabi::stdx::string_view filename,
        options::gridfs::upload const& options = {});

    ///
    /// Opens a gridfs::uploader to create a new GridFS file.
    ///
    /// @param session
    ///   The mongocxx::v_noabi::client_session with which to perform the upload. The client session
    ///   must remain valid for the lifetime of the uploader.
    ///
    /// @param id
    ///   The unique id of the file being uploaded.
    ///
    /// @param filename
    ///   The name of the file to be uploaded. A bucket can contain multiple files with the same
    ///   name.
    ///
    /// @param options
    ///   Optional arguments; see options::gridfs::upload.
    ///
    /// @return
    ///   The gridfs::uploader to which the GridFS file should be written.
    ///
    /// @note
    ///   If this GridFS bucket does not already exist in the database, it will be implicitly
    ///   created and initialized with GridFS indexes.
    ///
    /// @throws mongocxx::v_noabi::logic_error if `options` are invalid.
    ///
    /// @throws mongocxx::v_noabi::query_exception
    ///   if an error occurs when reading from the files collection for this bucket.
    ///
    /// @throws mongocxx::v_noabi::operation_exception if an error occurs when building GridFS
    /// indexes.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(uploader)
    open_upload_stream_with_id(
        client_session const& session,
        bsoncxx::v_noabi::types::bson_value::view id,
        bsoncxx::v_noabi::stdx::string_view filename,
        options::gridfs::upload const& options = {});

    ///
    /// Creates a new GridFS file by uploading bytes from an input stream. The id of the file will
    /// be automatically generated as an ObjectId.
    ///
    /// @param filename
    ///   The name of the file to be uploaded. A bucket can contain multiple files with the same
    ///   name.
    ///
    /// @param source
    ///    The non-null stream from which the GridFS file should be read. The exception mask on
    ///    `source` will be cleared of `eofbit` and set for `failbit` and `badbit`.
    ///
    /// @param options
    ///   Optional arguments; see options::gridfs::upload.
    ///
    /// @return
    ///   The id of the uploaded file.
    ///
    /// @note
    ///   If this GridFS bucket does not already exist in the database, it will be implicitly
    ///   created and initialized with GridFS indexes.
    ///
    /// @throws mongocxx::v_noabi::logic_error if `options` are invalid.
    ///
    /// @throws mongocxx::v_noabi::bulk_write_exception
    ///   if an error occurs when writing chunk data or file metadata to the database.
    ///
    /// @throws std::ios_base::failure
    ///   if reading from `source` fails. Any exception thrown during the execution of
    ///   `source::read()` will be re-thrown.
    ///
    /// @throws mongocxx::v_noabi::gridfs_exception
    ///   if the uploader requires more than 2^31-1 chunks to store the file at the requested chunk
    ///   size.
    ///
    /// @throws mongocxx::v_noabi::query_exception
    ///   if an error occurs when reading from the files collection for this bucket.
    ///
    /// @throws mongocxx::v_noabi::operation_exception if an error occurs when building GridFS
    /// indexes.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(result::gridfs::upload)
    upload_from_stream(
        bsoncxx::v_noabi::stdx::string_view filename,
        std::istream* source,
        options::gridfs::upload const& options = {});

    ///
    /// Creates a new GridFS file by uploading bytes from an input stream. The id of the file will
    /// be automatically generated as an ObjectId.
    ///
    /// @param session
    ///   The mongocxx::v_noabi::client_session with which to perform the upload.
    ///
    /// @param filename
    ///   The name of the file to be uploaded. A bucket can contain multiple files with the same
    ///   name.
    ///
    /// @param source
    ///    The non-null stream from which the GridFS file should be read. The exception mask on
    ///    `source` will be cleared of `eofbit` and set for `failbit` and `badbit`.
    ///
    /// @param options
    ///   Optional arguments; see options::gridfs::upload.
    ///
    /// @return
    ///   The id of the uploaded file.
    ///
    /// @note
    ///   If this GridFS bucket does not already exist in the database, it will be implicitly
    ///   created and initialized with GridFS indexes.
    ///
    /// @throws mongocxx::v_noabi::logic_error if `options` are invalid.
    ///
    /// @throws mongocxx::v_noabi::bulk_write_exception
    ///   if an error occurs when writing chunk data or file metadata to the database.
    ///
    /// @throws std::ios_base::failure
    ///   if reading from `source` fails. Any exception thrown during the execution of
    ///   `source::read()` will be re-thrown.
    ///
    /// @throws mongocxx::v_noabi::gridfs_exception
    ///   if the uploader requires more than 2^31-1 chunks to store the file at the requested chunk
    ///   size.
    ///
    /// @throws mongocxx::v_noabi::query_exception
    ///   if an error occurs when reading from the files collection for this bucket.
    ///
    /// @throws mongocxx::v_noabi::operation_exception if an error occurs when building GridFS
    /// indexes.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(result::gridfs::upload)
    upload_from_stream(
        client_session const& session,
        bsoncxx::v_noabi::stdx::string_view filename,
        std::istream* source,
        options::gridfs::upload const& options = {});

    ///
    /// Creates a new GridFS file with a user-supplied unique id by uploading bytes from an input
    /// stream.
    ///
    /// @param id
    ///   A unique id for the file being uploaded.
    ///
    /// @param filename
    ///   The name of the file to be uploaded. A bucket can contain multiple files with the same
    ///   name.
    ///
    /// @param source
    ///    The non-null stream from which the GridFS file should be read. The exception mask on
    ///    `source` will be cleared of `eofbit` and set for `failbit` and `badbit`.
    ///
    /// @param options
    ///   Optional arguments; see options::gridfs::upload.
    ///
    /// @note
    ///   If this GridFS bucket does not already exist in the database, it will be implicitly
    ///   created and initialized with GridFS indexes.
    ///
    /// @throws mongocxx::v_noabi::logic_error if `options` are invalid.
    ///
    /// @throws mongocxx::v_noabi::bulk_write_exception
    ///   if an error occurs when writing chunk data or file metadata to the database.
    ///
    /// @throws std::ios_base::failure
    ///   if reading from `source` fails. Any exception thrown during the execution of
    ///   `source::read()` will be re-thrown.
    ///
    /// @throws mongocxx::v_noabi::gridfs_exception
    ///   if the uploader requires more than 2^31-1 chunks to store the file at the requested chunk
    ///   size.
    ///
    /// @throws mongocxx::v_noabi::query_exception
    ///   if an error occurs when reading from the files collection for this bucket.
    ///
    /// @throws mongocxx::v_noabi::operation_exception if an error occurs when building GridFS
    /// indexes.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(void)
    upload_from_stream_with_id(
        bsoncxx::v_noabi::types::bson_value::view id,
        bsoncxx::v_noabi::stdx::string_view filename,
        std::istream* source,
        options::gridfs::upload const& options = {});

    ///
    /// Creates a new GridFS file with a user-supplied unique id by uploading bytes from an input
    /// stream.
    ///
    /// @param session
    ///   The mongocxx::v_noabi::client_session with which to perform the upload.
    ///
    /// @param id
    ///   A unique id for the file being uploaded.
    ///
    /// @param filename
    ///   The name of the file to be uploaded. A bucket can contain multiple files with the same
    ///   name.
    ///
    /// @param source
    ///    The non-null stream from which the GridFS file should be read. The exception mask on
    ///    `source` will be cleared of `eofbit` and set for `failbit` and `badbit`.
    ///
    /// @param options
    ///   Optional arguments; see options::gridfs::upload.
    ///
    /// @note
    ///   If this GridFS bucket does not already exist in the database, it will be implicitly
    ///   created and initialized with GridFS indexes.
    ///
    /// @throws mongocxx::v_noabi::logic_error if `options` are invalid.
    ///
    /// @throws mongocxx::v_noabi::bulk_write_exception
    ///   if an error occurs when writing chunk data or file metadata to the database.
    ///
    /// @throws std::ios_base::failure
    ///   if reading from `source` fails. Any exception thrown during the execution of
    ///   `source::read()` will be re-thrown.
    ///
    /// @throws mongocxx::v_noabi::gridfs_exception
    ///   if the uploader requires more than 2^31-1 chunks to store the file at the requested chunk
    ///   size.
    ///
    /// @throws mongocxx::v_noabi::query_exception
    ///   if an error occurs when reading from the files collection for this bucket.
    ///
    /// @throws mongocxx::v_noabi::operation_exception if an error occurs when building GridFS
    /// indexes.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(void)
    upload_from_stream_with_id(
        client_session const& session,
        bsoncxx::v_noabi::types::bson_value::view id,
        bsoncxx::v_noabi::stdx::string_view filename,
        std::istream* source,
        options::gridfs::upload const& options = {});

    ///
    /// Opens a gridfs::downloader to read a GridFS file.
    ///
    /// @param id
    ///   The id of the file to read.
    ///
    /// @return
    ///   The gridfs::downloader from which the GridFS file should be read.
    ///
    /// @throws mongocxx::v_noabi::gridfs_exception
    ///   if the requested file does not exist, or if the requested file has been corrupted.
    ///
    /// @throws mongocxx::v_noabi::query_exception
    ///   if an error occurs when reading from the files collection for this bucket.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(downloader)
    open_download_stream(bsoncxx::v_noabi::types::bson_value::view id);

    ///
    /// Opens a gridfs::downloader to read a GridFS file.
    ///
    /// @param session
    ///   The mongocxx::v_noabi::client_session with which to perform the download. The client
    ///   session must remain valid for the lifetime of the downloader.
    ///
    /// @param id
    ///   The id of the file to read.
    ///
    /// @return
    ///   The gridfs::downloader from which the GridFS file should be read.
    ///
    /// @throws mongocxx::v_noabi::gridfs_exception
    ///   if the requested file does not exist, or if the requested file has been corrupted.
    ///
    /// @throws mongocxx::v_noabi::query_exception
    ///   if an error occurs when reading from the files collection for this bucket.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(downloader)
    open_download_stream(client_session const& session, bsoncxx::v_noabi::types::bson_value::view id);

    ///
    /// Downloads the contents of a stored GridFS file from the bucket and writes it to a stream.
    ///
    /// @param id
    ///   The id of the file to read.
    ///
    /// @param destination
    ///   The non-null stream to which the GridFS file should be written.
    ///
    /// @throws mongocxx::v_noabi::gridfs_exception
    ///   if the requested file does not exist, or if the requested file has been corrupted.
    ///
    /// @throws mongocxx::v_noabi::query_exception
    ///   if an error occurs when reading from the files or chunks collections for this bucket.
    ///
    /// @throws std::ios_base::failure
    ///   if writing to `destination` fails.  In addition, if `destination::exceptions()` is set for
    ///   `badbit`, any exception thrown during execution of `destination::write()` will be
    ///   re-thrown.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(void)
    download_to_stream(bsoncxx::v_noabi::types::bson_value::view id, std::ostream* destination);

    ///
    /// @copydoc download_to_stream(bsoncxx::v_noabi::types::bson_value::view id, std::ostream* destination)
    ///
    /// @param start The byte offset to the beginning of content to download.
    /// @param end The byte offset to the end of content to download.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(void)
    download_to_stream(
        bsoncxx::v_noabi::types::bson_value::view id,
        std::ostream* destination,
        std::size_t start,
        std::size_t end);

    ///
    /// Downloads the contents of a stored GridFS file from the bucket and writes it to a stream.
    ///
    /// @param session
    ///   The mongocxx::v_noabi::client_session with which to perform the download.
    ///
    /// @param id
    ///   The id of the file to read.
    ///
    /// @param destination
    ///   The non-null stream to which the GridFS file should be written.
    ///
    /// @throws mongocxx::v_noabi::gridfs_exception
    ///   if the requested file does not exist, or if the requested file has been corrupted.
    ///
    /// @throws mongocxx::v_noabi::query_exception
    ///   if an error occurs when reading from the files or chunks collections for this bucket.
    ///
    /// @throws std::ios_base::failure
    ///   if writing to `destination` fails.  In addition, if `destination::exceptions()` is set for
    ///   `badbit`, any exception thrown during execution of `destination::write()` will be
    ///   re-thrown.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(void)
    download_to_stream(
        client_session const& session,
        bsoncxx::v_noabi::types::bson_value::view id,
        std::ostream* destination);

    ///
    /// @copydoc download_to_stream(client_session const& session, bsoncxx::v_noabi::types::bson_value::view id, std::ostream* destination)
    ///
    /// @param start The byte offset to the beginning of content to download.
    /// @param end The byte offset to the end of content to download.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(void)
    download_to_stream(
        client_session const& session,
        bsoncxx::v_noabi::types::bson_value::view id,
        std::ostream* destination,
        std::size_t start,
        std::size_t end);

    ///
    /// Deletes a GridFS file from the bucket.
    ///
    /// @param id
    ///   The id of the file to be deleted.
    ///
    /// @throws mongocxx::v_noabi::gridfs_exception if the requested file does not exist.
    ///
    /// @throws mongocxx::v_noabi::bulk_write_exception
    ///   if an error occurs when removing file data or chunk data from the database.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(void) delete_file(bsoncxx::v_noabi::types::bson_value::view id);

    ///
    /// Deletes a GridFS file from the bucket.
    ///
    /// @param session
    ///   The mongocxx::v_noabi::client_session with which to perform the delete.
    ///
    /// @param id
    ///   The id of the file to be deleted.
    ///
    /// @throws mongocxx::v_noabi::gridfs_exception if the requested file does not exist.
    ///
    /// @throws mongocxx::v_noabi::bulk_write_exception
    ///   if an error occurs when removing file data or chunk data from the database.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(void)
    delete_file(client_session const& session, bsoncxx::v_noabi::types::bson_value::view id);

    ///
    /// Finds the documents in the files collection of the bucket which match the provided filter.
    ///
    /// @param filter
    ///   Document view representing a document that should match the query.
    ///
    /// @param options
    ///   Optional arguments; see options::find.
    ///
    /// @return
    ///   A mongocxx::v_noabi::cursor with the results. If the query fails, the cursor throws
    ///   mongocxx::v_noabi::query_exception when the returned cursor is iterated.
    ///
    /// @throws mongocxx::v_noabi::logic_error if the options are invalid, or if the unsupported
    /// option modifiers "$query" or "$explain" are used.
    ///
    /// @see
    /// - @ref mongocxx::v_noabi::collection::find.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(cursor)
    find(bsoncxx::v_noabi::document::view_or_value filter, options::find const& options = {});

    ///
    /// Finds the documents in the files collection of the bucket which match the provided filter.
    ///
    /// @param session
    ///   The mongocxx::v_noabi::client_session with which to perform the query. The client session
    ///   must remain valid for the lifetime of the cursor.
    ///
    /// @param filter
    ///   Document view representing a document that should match the query.
    ///
    /// @param options
    ///   Optional arguments; see options::find.
    ///
    /// @return
    ///   A mongocxx::v_noabi::cursor with the results. If the query fails, the cursor throws
    ///   mongocxx::v_noabi::query_exception when the returned cursor is iterated.
    ///
    /// @throws mongocxx::v_noabi::logic_error if the options are invalid, or if the unsupported
    /// option modifiers "$query" or "$explain" are used.
    ///
    /// @see
    /// - @ref mongocxx::v_noabi::collection::find.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(cursor)
    find(
        client_session const& session,
        bsoncxx::v_noabi::document::view_or_value filter,
        options::find const& options = {});

    ///
    /// Gets the name of the GridFS bucket.
    ///
    /// @return
    ///   The name of the GridFS bucket.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(bsoncxx::v_noabi::stdx::string_view) bucket_name() const;

   private:
    friend ::mongocxx::v_noabi::database;

    // Constructs a new GridFS bucket.  Throws if options are invalid.
    bucket(database const& db, options::gridfs::bucket const& options);

    void create_indexes_if_nonexistent(client_session const* session);

    uploader _open_upload_stream_with_id(
        client_session const* session,
        bsoncxx::v_noabi::types::bson_value::view id,
        bsoncxx::v_noabi::stdx::string_view filename,
        options::gridfs::upload const& options);

    void _upload_from_stream_with_id(
        client_session const* session,
        bsoncxx::v_noabi::types::bson_value::view id,
        bsoncxx::v_noabi::stdx::string_view filename,
        std::istream* source,
        options::gridfs::upload const& options);

    downloader _open_download_stream(
        client_session const* session,
        bsoncxx::v_noabi::types::bson_value::view id,
        bsoncxx::v_noabi::stdx::optional<std::size_t> start,
        bsoncxx::v_noabi::stdx::optional<std::size_t> end);

    void _download_to_stream(
        client_session const* session,
        bsoncxx::v_noabi::types::bson_value::view id,
        std::ostream* destination,
        bsoncxx::v_noabi::stdx::optional<std::size_t> start,
        bsoncxx::v_noabi::stdx::optional<std::size_t> end);

    void _delete_file(client_session const* session, bsoncxx::v_noabi::types::bson_value::view id);

    class impl;

    impl& _get_impl();
    impl const& _get_impl() const;

    std::unique_ptr<impl> _impl;
};

} // namespace gridfs
} // namespace v_noabi
} // namespace mongocxx

#include <mongocxx/config/postlude.hpp>

///
/// @file
/// Provides @ref mongocxx::v_noabi::gridfs::bucket.
///
