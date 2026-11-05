cmake_minimum_required(VERSION 3.24)
project(search_tree)

set(CMAKE_CXX_STANDARD 20)
include(FetchContent)
set(BOOST_INCLUDE_LIBRARIES program_options)
set(BOOST_ENABLE_CMAKE ON)
FetchContent_Declare(Boost
        URL https://github.com/boostorg/boost/releases/download/boost-1.86.0/boost-1.86.0-cmake.tar.xz
        DOWNLOAD_EXTRACT_TIMESTAMP ON)
FetchContent_MakeAvailable(Boost)

add_library(tree SHARED src/tree.cpp)
target_include_directories(tree PUBLIC include)

add_library(html SHARED src/html.cpp)
target_include_directories(html PUBLIC include)

add_executable(search_tree main.cpp)
target_link_libraries(search_tree PRIVATE tree html Boost::program_options)

if(EXISTS ${CMAKE_SOURCE_DIR}/tests/doctest.h)
    add_executable(tree_tests tests/test_tree.cpp)
    target_include_directories(tree_tests PRIVATE tests)
    target_link_libraries(tree_tests PRIVATE tree)
else()
    message(STATUS "tests/doctest.h not found, tests are not built")
endif()