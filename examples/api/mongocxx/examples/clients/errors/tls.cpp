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

#include <mongocxx/client.hpp>
#include <mongocxx/exception/error_code.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/options/client.hpp>
#include <mongocxx/options/tls.hpp>
#include <mongocxx/uri.hpp>

#include <examples/api/runner.hh>
#include <examples/macros.hh>

namespace {

// [Example]
void example() {
    try {
        mongocxx::client client{
            mongocxx::uri{},
            mongocxx::options::client{}.tls_opts(mongocxx::options::tls{})};  // Throws.

        EXPECT(false && "should not reach this point");
    } catch (const mongocxx::exception& ex) {
        EXPECT(
            // When TLS/SSL is enabled for both mongocxx and libmongoc.
            ex.code() == mongocxx::error_code::k_invalid_parameter ||

            // When TLS/SSL is not enabled for either mongocxx or libmongoc.
            ex.code() == mongocxx::error_code::k_ssl_not_supported ||

            false);
    }
}
// [Example]

}  // namespace

RUNNER_REGISTER_COMPONENT_WITH_INSTANCE() {
    example();
}