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

#include <bsoncxx/config/config.hpp>

#if !defined(BSONCXX_POLY_USE_IMPLS) && !defined(BSONCXX_POLY_USE_STD)
#error "bsoncxx/v_noabi/bsoncxx/config/config.hpp should define a polyfill library macro"
#endif