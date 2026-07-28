add_library(database STATIC)

# ==============================
# Source Files
# ==============================
target_sources(database PRIVATE
    "sqlite/SQLiteDatabase.cpp"
    "sqlite/SQLiteDatabase.h"

    "mysql/MySQLDatabase.cpp"
    "mysql/MySQLDatabase.h"

    "test/DatabaseTest.cpp"
    "test/DatabaseTest.h"

    DBConfig.h
    IDatabase.h
)

# ==============================
# Include Directories
# ==============================
target_include_directories(database
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}

PRIVATE
    ${MYSQL_CONNECTOR_ROOT}/include
)

# ==============================
# Libraries
# ==============================
target_link_libraries(database
PRIVATE
    Qt6::Widgets
    Qt6::Sql
    "${MYSQL_CONNECTOR_ROOT}/lib64/vs14/mysqlcppconn.lib"
)