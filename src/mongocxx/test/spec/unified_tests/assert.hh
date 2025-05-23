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

#include "entity.hh"

#include <bsoncxx/types/bson_value/view_or_value.hpp>

namespace mongocxx {
namespace assert {

void matches(
    bsoncxx::types::bson_value::view actual,
    bsoncxx::types::bson_value::view expected,
    mongocxx::entity::map& map,
    bool is_root = true,
    bool is_array_of_root_docs = false);

} // namespace assert
} // namespace mongocxx
