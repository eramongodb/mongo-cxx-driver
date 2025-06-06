#pragma once

#include <string>

#include <mongocxx/search_index_model-fwd.hpp>

#include <bsoncxx/document/value.hpp>
#include <bsoncxx/document/view_or_value.hpp>
#include <bsoncxx/stdx/optional.hpp>
#include <bsoncxx/string/view_or_value.hpp>

#include <mongocxx/config/prelude.hpp>

namespace mongocxx {
namespace v_noabi {

///
/// Used by @ref mongocxx::v_noabi::search_index_view.
///
class search_index_model {
   public:
    ///
    /// Initializes a new search_index_model over a mongocxx::v_noabi::collection.
    ///
    MONGOCXX_ABI_EXPORT_CDECL()
    search_index_model(bsoncxx::v_noabi::document::view_or_value definition);

    MONGOCXX_ABI_EXPORT_CDECL()
    search_index_model(
        bsoncxx::v_noabi::string::view_or_value name,
        bsoncxx::v_noabi::document::view_or_value definition);

    search_index_model() = delete;

    ///
    /// Move constructs a search_index_model.
    ///
    MONGOCXX_ABI_EXPORT_CDECL() search_index_model(search_index_model&&) noexcept;

    ///
    /// Move assigns a search_index_model.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(search_index_model&) operator=(search_index_model&&) noexcept;

    ///
    /// Copy constructs a search_index_model.
    ///
    MONGOCXX_ABI_EXPORT_CDECL() search_index_model(search_index_model const&);

    ///
    /// Copy assigns a search_index_model.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(search_index_model&) operator=(search_index_model const&);

    ///
    /// Destroys a search_index_model.
    ///
    MONGOCXX_ABI_EXPORT_CDECL() ~search_index_model();

    ///
    /// Retrieves name of a search_index_model.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(bsoncxx::v_noabi::stdx::optional<bsoncxx::v_noabi::string::view_or_value>)
    name() const;

    ///
    /// Retrieves definition of a search_index_model.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(bsoncxx::v_noabi::document::view) definition() const;

    ///
    /// Retrieves type of a search_index_model.
    ///
    MONGOCXX_ABI_EXPORT_CDECL(bsoncxx::v_noabi::stdx::optional<bsoncxx::v_noabi::string::view_or_value>)
    type() const;

    ///
    /// Sets type of a search_index_model.
    ///
    /// @param type The type for this index. Can be either "search" or "vectorSearch".
    ///
    /// @return A reference to this object to facilitate method chaining.
    MONGOCXX_ABI_EXPORT_CDECL(search_index_model&)
    type(bsoncxx::v_noabi::string::view_or_value type);

   private:
    class impl;

    impl const& _get_impl() const;

    impl& _get_impl();

   private:
    std::unique_ptr<impl> _impl;
};

} // namespace v_noabi
} // namespace mongocxx

#include <mongocxx/config/postlude.hpp>

///
/// @file
/// Provides @ref mongocxx::v_noabi::search_index_model.
///
