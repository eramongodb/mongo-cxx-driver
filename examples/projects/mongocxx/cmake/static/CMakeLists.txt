# Copyright 2009-present MongoDB, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Demonstrates how to use the CMake 'find_package' mechanism to locate build against the libmongocxx
# static library.

cmake_minimum_required(VERSION 3.15...4.0)

project(HELLO_WORLD LANGUAGES C CXX)

# Enforce the C++ standard, and disable extensions.
if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 11)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
endif()

# NOTE: For this to work, the CMAKE_PREFIX_PATH variable must be set to point to the directory that
# was used as the argument to CMAKE_INSTALL_PREFIX when building libmongocxx.
find_package(mongocxx REQUIRED)

add_executable(hello_mongocxx ../../hello_mongocxx.cpp)

target_link_libraries(hello_mongocxx
  PRIVATE mongo::mongocxx_static
)

add_custom_target(run
    COMMAND hello_mongocxx
    DEPENDS hello_mongocxx
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

# Sanity-check that static library macros are set when building against the static library.  Users
# don't need to include this section in their projects.
get_target_property(LIBBSONCXX_STATIC_DEFINITIONS mongo::bsoncxx_static INTERFACE_COMPILE_DEFINITIONS)
list(FIND LIBBSONCXX_STATIC_DEFINITIONS "BSONCXX_STATIC" LIST_IDX)
if (${LIST_IDX} EQUAL -1)
    message(FATAL_ERROR "Expected BSONCXX_STATIC to be defined")
endif()
get_target_property(LIBMONGOCXX_STATIC_DEFINITIONS mongo::mongocxx_static INTERFACE_COMPILE_DEFINITIONS)
list(FIND LIBMONGOCXX_STATIC_DEFINITIONS "MONGOCXX_STATIC" LIST_IDX)
if (${LIST_IDX} EQUAL -1)
    message(FATAL_ERROR "Expected MONGOCXX_STATIC to be defined")
endif()
