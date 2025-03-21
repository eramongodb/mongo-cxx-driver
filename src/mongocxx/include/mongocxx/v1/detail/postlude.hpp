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

// mongocxx/v1/config/export.hpp (generated by CMake)
#pragma pop_macro("MONGOCXX_ABI_EXPORT_H")
#if !defined(MONGOCXX_ABI_EXPORT_H)
#pragma pop_macro("MONGOCXX_ABI_EXPORT")
#pragma pop_macro("MONGOCXX_ABI_NO_EXPORT")
#pragma pop_macro("MONGOCXX_ABI_CDECL")
#pragma pop_macro("MONGOCXX_ABI_EXPORT_CDECL")
#pragma pop_macro("MONGOCXX_DEPRECATED")
#endif

// mongocxx/v1/config/version.hpp (generated by CMake)
#pragma pop_macro("MONGOCXX_V1_CONFIG_VERSION_HPP")
#if !defined(MONGOCXX_V1_CONFIG_VERSION_HPP)
#pragma pop_macro("MONGOCXX_VERSION_STRING")
#pragma pop_macro("MONGOCXX_VERSION_EXTRA")
#pragma pop_macro("MONGOCXX_VERSION_MAJOR")
#pragma pop_macro("MONGOCXX_VERSION_MINOR")
#pragma pop_macro("MONGOCXX_VERSION_PATCH")
#endif

// mongocxx/v1/detail/macros.hpp
#pragma push_macro("MONGOCXX_V1_DETAIL_MACROS_HPP")
#if !defined(MONGOCXX_V1_DETAIL_MACROS_HPP)
#pragma pop_macro("MONGOCXX_PRIVATE_UNREACHABLE")
#endif

#if !defined(MONGOCXX_PRIVATE_V1_INSIDE_MACRO_GUARD_SCOPE)
#error "postlude header included without a matching prelude header"
#endif
#pragma pop_macro("MONGOCXX_PRIVATE_V1_INSIDE_MACRO_GUARD_SCOPE")

///
/// @file
/// The mongocxx v1 macro guard postlude header.
///
/// @warning For internal use only!
///
/// This header uses macro pragmas to guard macros defined by the mongocxx library for internal use
/// by "popping" their prior definition onto the stack after use by mongocxx headers.
///
/// @see
/// - @ref mongocxx/v1/detail/prelude.hpp
///
