cmake_minimum_required(VERSION 3.30)
project(my_algorithm)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(my_optional src/main.cpp)
