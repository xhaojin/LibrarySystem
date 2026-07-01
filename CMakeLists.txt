cmake_minimum_required(VERSION 3.20)

project(LibrarySystem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt 自动处理
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

# ===== 子模块 =====
add_subdirectory(app)
add_subdirectory(ui)
add_subdirectory(controller)
add_subdirectory(service)
add_subdirectory(repository)
add_subdirectory(database)
add_subdirectory(model)
add_subdirectory(mapper)
add_subdirectory(dto)
add_subdirectory(common)

# ===== main =====
add_executable(LibrarySystem WIN32 main.cpp)

# 链接所有模块
target_link_libraries(LibrarySystem
    app
    ui
    controller
    service
    repository
    database
    model
    mapper
    dto
    common
    Qt6::Widgets
    Qt6::Sql
)