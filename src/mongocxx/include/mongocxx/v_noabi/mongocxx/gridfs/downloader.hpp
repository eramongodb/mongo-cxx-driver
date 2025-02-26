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

#include <cstddef>
#include <cstdint>
#include <memory>

#include <mongocxx/gridfs/bucket-fwd.hpp>
#include <mongocxx/gridfs/downloader-fwd.hpp>

#include <bsoncxx/document/value.hpp>
#include <bsoncxx/document/view.hpp>
#include <bsoncxx/stdx/optional.hpp>
#include <bsoncxx/types/bson_value/view.hpp>

#include <mongocxx/cursor.hpp>

#include <mongocxx/config/prelude.hpp>

namespace mongocxx {
namespace v_noabi {
namespace gridfs {

///
/// Used to specify the offset from which to start reading the chunks of the file.
///
struct chunks_and_bytes_offset {
    std::int32_t chunks_offset = 0;
    std::int32_t bytes_offset = 0;
};

///
/// Used to download a GridFS file.
///
class downloader {
   public:
    ///
    /// Default constructs a downloader object. The downloader is equivalent to the state of a moved
    /// from downloader. The only valid actions to take with a default constructed downloader are to
    /// assign to it, or destroy it.
    ///
    MONGOCXX_ABI_EXPORT_CDECL() downloader() noexcept;

    ///
    /// Move constructs a downloader.
    ///
    MONGOCXX_ABI_EXPORT_CDECL() downloader(downloader&&) noexcept;

    ///
    /// Move assigns a downloader.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(downloader&) operator=(downloader&&) noexcept;

    downloader(downloader const&) = delete;

    downloader& operator=(downloader const&) = delete;

    ///
    /// Destroys a downloader.
    ///
    MONGOCXX_ABI_EXPORT_CDECL() ~downloader();

    ///
    /// Returns true if the downloader is valid, meaning it was not default constructed or moved
    /// from.
    ///
    explicit MONGOCXX_ABI_EXPORT_CDECL() operator bool() const noexcept;

    ///
    /// Reads a specified number of bytes from the GridFS file being downloaded.
    ///
    /// @param buffer
    ///   A pointer to a buffer to store the bytes read from the file.
    ///
    /// @param length
    ///   The number of bytes to read from the file.
    ///
    /// @return
    ///   The number of bytes actually read. If zero, the downloader has reached the end of the
    ///   file.
    ///
    /// @throws mongocxx::v_noabi::logic_error if the download stream was already closed.
    ///
    /// @throws mongocxx::v_noabi::gridfs_exception if the requested file has been corrupted.
    ///
    /// @throws mongocxx::v_noabi::query_exception
    ///   if an error occurs when reading chunk data from the database for the requested file.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(std::size_t) read(std::uint8_t* buffer, std::size_t length);

    ///
    /// Closes the downloader stream.
    ///
    /// @throws mongocxx::v_noabi::logic_error if the download stream was already closed.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(void) close();

    ///
    /// Gets the chunk size of the file being downloaded.
    ///
    /// @return
    ///   The chunk size in bytes.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(std::int32_t) chunk_size() const;

    ///
    /// Gets the length of the file being downloaded.
    ///
    /// @return
    ///   The length in bytes.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(std::int64_t) file_length() const;

    ///
    /// Gets the files collection document of the file being downloaded.
    ///
    /// @return
    ///    A view to the files collection document of the file being downloaded.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(bsoncxx::v_noabi::document::view) files_document() const;

   private:
    friend ::mongocxx::v_noabi::gridfs::bucket;

    //
    // Constructs a new downloader stream.
    //
    // @param chunks
    //   The cursor to read the chunks of the file from. It must have a value if the length of the
    //   file is non-zero.
    //
    // @param start
    //   The offset from which to start reading the chunks of the file.
    //
    // @param chunk_size
    //   The expected size of a chunk in bytes.
    //
    // @param file_len
    //   The expected size of the file in bytes.
    //
    // @param files_doc
    //   The files collection document of the file being downloaded.
    //
    downloader(
        bsoncxx::v_noabi::stdx::optional<cursor> chunks,
        chunks_and_bytes_offset start,
        std::int32_t chunk_size,
        std::int64_t file_len,
        bsoncxx::v_noabi::document::value files_doc);

    void fetch_chunk();

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
/// Provides utilities to download GridFS files.
///
