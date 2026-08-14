cmake_minimum_required(VERSION 3.20)

project(LibrarySystem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 针对 MSVC 编译器启用 C++ 异常处理
if(MSVC)
    add_compile_options(/EHsc)
endif()

# Qt 自动处理
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(MYSQL_CONNECTOR_ROOT
    ${CMAKE_SOURCE_DIR}/thirdparty/mysql-connector-c++-8.0.33-winx64
)

add_library(MySQLConnector SHARED IMPORTED)

set_target_properties(MySQLConnector PROPERTIES
    IMPORTED_IMPLIB
        "${MYSQL_CONNECTOR_ROOT}/lib64/vs14/mysqlcppconn.lib"

    IMPORTED_LOCATION
        "${MYSQL_CONNECTOR_ROOT}/lib64/mysqlcppconn-9-vs14.dll"

    INTERFACE_INCLUDE_DIRECTORIES
        "${MYSQL_CONNECTOR_ROOT}/include"
)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

# ===== 子模块 =====
add_subdirectory(app)
add_subdirectory(core)
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
add_executable(LibrarySystem main.cpp "dto/PublisherDTO.h")

target_include_directories(LibrarySystem
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}
)

# 链接所有模块
target_link_libraries(LibrarySystem
    app
    core
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