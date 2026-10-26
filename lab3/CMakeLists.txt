cmake_minimum_required(VERSION 3.20)

project(lab3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(temperature
    src/temperature.cpp
    src/temperature_set.cpp
)

target_include_directories(temperature PUBLIC
    include
)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(lab3_tests
    tests/test_temperature.cpp
    tests/test_temperature_set.cpp
)

target_link_libraries(lab3_tests PRIVATE
    temperature
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(lab3_tests)