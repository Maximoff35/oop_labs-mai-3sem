cmake_minimum_required(VERSION 3.16)

project(lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(str_ops
    src/str_ops.cpp
)

target_include_directories(str_ops PUBLIC
    include
)

add_executable(lab1
    src/main.cpp
)

target_link_libraries(lab1 PRIVATE
    str_ops
)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(lab1_tests
    tests/test_variant.cpp
)

target_link_libraries(lab1_tests PRIVATE
    str_ops
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(lab1_tests)