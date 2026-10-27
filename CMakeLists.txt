cmake_minimum_required(VERSION 3.10)
project(search_tree)

set(CMAKE_CXX_STANDARD 20)

add_library(tree SHARED src/tree.cpp)
target_include_directories(tree PUBLIC include)

add_library(html SHARED src/html.cpp)
target_include_directories(html PUBLIC include)

add_executable(search_tree main.cpp)
target_link_libraries(search_tree PRIVATE tree html)
