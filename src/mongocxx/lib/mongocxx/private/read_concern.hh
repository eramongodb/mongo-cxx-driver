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

#include <mongocxx/read_concern.hpp>

#include <mongocxx/private/mongoc.hh>

namespace mongocxx {
namespace v_noabi {

class read_concern::impl {
   public:
    impl(::mongoc_read_concern_t* read_concern) : read_concern_t{read_concern} {}

    ~impl() {
        libmongoc::read_concern_destroy(read_concern_t);
    }

    impl(impl&&) = delete;
    impl& operator=(impl&&) = delete;

    impl(impl const&) = delete;
    impl& operator=(impl const&) = delete;

    ::mongoc_read_concern_t* read_concern_t;
};

} // namespace v_noabi
} // namespace mongocxx
