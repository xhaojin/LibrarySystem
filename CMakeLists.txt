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

# ==============================
# Third Party
# ==============================
set(MYSQL_CONNECTOR_ROOT
    ${CMAKE_SOURCE_DIR}/thirdparty/mysql-connector-c++-8.4.0-winx64
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
add_executable(LibrarySystem WIN32 main.cpp  "thirdparty/mysql-connector-c++-8.4.0-winx64/include/jdbc/mysql_connection.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/jdbc/mysql_driver.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/jdbc/mysql_error.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/jdbc/cppconn/build_config.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/jdbc/cppconn/callback.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/jdbc/cppconn/config.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/jdbc/cppconn/connection.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/jdbc/cppconn/datatype.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/jdbc/cppconn/driver.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/jdbc/cppconn/exception.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/jdbc/cppconn/metadata.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/jdbc/cppconn/parameter_metadata.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/jdbc/cppconn/prepared_statement.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/jdbc/cppconn/resultset.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/jdbc/cppconn/resultset_metadata.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/jdbc/cppconn/sqlstring.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/jdbc/cppconn/statement.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/jdbc/cppconn/variant.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/jdbc/cppconn/version_info.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/jdbc/cppconn/warning.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysql/jdbc.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/common.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/common_constants.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/version_info.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/xapi.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/xdevapi.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/common/api.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/common/error.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/common/op_if.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/common/settings.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/common/util.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/common/value.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/devapi/collations.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/devapi/collection_crud.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/devapi/common.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/devapi/crud.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/devapi/document.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/devapi/error.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/devapi/executable.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/devapi/mysql_charsets.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/devapi/mysql_collations.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/devapi/result.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/devapi/row.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/devapi/settings.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/devapi/table_crud.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/devapi/detail/crud.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/devapi/detail/error.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/devapi/detail/result.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/devapi/detail/row.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/devapi/detail/session.h" "thirdparty/mysql-connector-c++-8.4.0-winx64/include/mysqlx/devapi/detail/settings.h")

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