add_library(database STATIC)

target_sources(database PRIVATE
    SQLiteDatabase.cpp
    SQLiteDatabase.h
)

target_include_directories(database PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(database PRIVATE Qt6::Widgets Qt6::Sql)