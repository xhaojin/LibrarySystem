cmake_minimum_required(VERSION 3.20)

project(LibrarySystem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON) # Enable automatic MOC for Qt

include_directories(include)

file(GLOB_RECURSE SOURCES
    src/*.cpp
)

file(GLOB_RECURSE HEADERS
    include/*.h
)

add_executable(
    LibrarySystem
    ${SOURCES}
    ${HEADERS}
)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql) # Find the Qt6 Widgets module
set_target_properties(LibrarySystem PROPERTIES WIN32_EXECUTABLE TRUE) # Set the executable property for Windows (optional, but can help with certain configurations)
target_link_libraries(LibrarySystem Qt6::Widgets Qt6::Sql) # Link the Qt6 Widgets library to your executable