cmake_minimum_required(VERSION 3.20)

project(lab4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(polygon
    src/polygon.cpp
    src/triangle.cpp
    src/geometry_utils.cpp
    src/pentagon.cpp
    src/polygon_collection.cpp
    src/square.cpp
)

target_include_directories(polygon PUBLIC
    include
)

add_executable(lab4
    src/main.cpp
)

target_link_libraries(lab4 PRIVATE
    polygon
)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(lab4_tests
    tests/test_triangle.cpp
    tests/test_square.cpp
    tests/test_pentagon.cpp
    tests/test_geometry.cpp
    tests/test_polymorphism.cpp
    tests/test_collection.cpp
)

target_link_libraries(lab4_tests PRIVATE
    polygon
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(lab4_tests)

foreach(target polygon lab4 lab4_tests)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE
            -Wall -Wextra -Wpedantic
        )
    endif()
endforeach()