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

namespace bsoncxx {
namespace v_noabi {
namespace builder {

struct concatenate_doc;
struct concatenate_array;

} // namespace builder
} // namespace v_noabi
} // namespace bsoncxx

namespace bsoncxx {
namespace builder {

using ::bsoncxx::v_noabi::builder::concatenate_array;
using ::bsoncxx::v_noabi::builder::concatenate_doc;

} // namespace builder
} // namespace bsoncxx

///
/// @file
/// Provides concatenators for use with "streaming" BSON builder syntax.
///
