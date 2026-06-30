add_library(repository STATIC)

target_sources(repository PRIVATE
    SQLite/SQLiteBookRepository.cpp
    SQLite/SQLiteUserRepository.cpp
    SQLite/SQLiteBorrowRecordRepository.cpp
)

target_include_directories(repository PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(repository PRIVATE
    database
    model
)

target_link_libraries(repository PRIVATE Qt6::Widgets Qt6::Sql)