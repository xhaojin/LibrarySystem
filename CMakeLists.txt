cmake_minimum_required(VERSION 3.20)

project(LibrarySystem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(
    LibrarySystem
    src/main.cpp
 "include/Book.h" "src/Book.cpp")