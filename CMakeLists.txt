cmake_minimum_required(VERSION 3.10)
project(oc26)

set(CMAKE_CXX_STANDARD 20)

add_library(counter SHARED src/counter.cpp)
target_include_directories(counter PUBLIC include)

add_library(matrix SHARED src/matrix.cpp)
target_include_directories(matrix PUBLIC include)

add_executable(oc26 main.cpp)
target_link_libraries(oc26 PRIVATE counter matrix)

