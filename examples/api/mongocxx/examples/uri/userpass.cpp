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

#include <vector>

#include <mongocxx/uri.hpp>

#include <examples/api/runner.hh>
#include <examples/macros.hh>

namespace {

// [Example]
void example() {
    {
        mongocxx::uri uri{"mongodb://localhost:27017/"};

        EXPECT(uri.username().empty());
        EXPECT(uri.password().empty());

        EXPECT(uri.tls() == false);
    }

    {
        mongocxx::uri uri{"mongodb://bob:pwd123@localhost:27017/?tls=true"};

        EXPECT(uri.username() == "bob");
        EXPECT(uri.password() == "pwd123");

        EXPECT(uri.tls() == true);
    }
}
// [Example]

} // namespace

RUNNER_REGISTER_COMPONENT_WITH_INSTANCE() {
    example();
}
