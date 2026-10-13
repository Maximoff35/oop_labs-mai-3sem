cmake_minimum_required(VERSION 3.16)

project(lab2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(matrix
    src/matrix.cpp
)

target_include_directories(matrix PUBLIC
    include
)

add_executable(lab2
    src/main.cpp
)

target_link_libraries(lab2 PRIVATE
    matrix
)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(lab2_tests
    tests/test_variant.cpp
)

target_link_libraries(lab2_tests PRIVATE
    matrix
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(lab2_tests)