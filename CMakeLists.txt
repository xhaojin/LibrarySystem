cmake_minimum_required(VERSION 3.20)

project(LibrarySystem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON) # Enable automatic MOC for Qt

include_directories(include)

add_executable(
    LibrarySystem
    src/main.cpp
 "include/Book.h" "src/Book.cpp" "include/User.h" "src/User.cpp" "src/Library.cpp" "include/Logger.h" "src/Logger.cpp" "include/LibraryService.h" "src/LibraryService.cpp" "include/BookDTO.h" "include/UserDTO.h" "src/UIController.cpp" "include/MainWindow.h" "src/MainWindow.cpp")

find_package(Qt6 REQUIRED COMPONENTS Widgets) # Find the Qt6 Widgets module
set_target_properties(LibrarySystem PROPERTIES WIN32_EXECUTABLE TRUE) # Set the executable property for Windows (optional, but can help with certain configurations)
target_link_libraries(LibrarySystem Qt6::Widgets) # Link the Qt6 Widgets library to your executable