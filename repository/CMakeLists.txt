add_library(repository STATIC)

target_sources(repository PRIVATE
    "mysql/MySQLUserRepository.h"
    "mysql/MySQLUserRepository.cpp"
    "mysql/MySQLBookRepository.h"
    "mysql/MySQLBookRepository.cpp"
    "mysql/MySQLPublisherRepository.h"
    "mysql/MySQLPublisherRepository.cpp"
    "mysql/MySQLCategoryRepository.h"
    "mysql/MySQLCategoryRepository.cpp"
    "mysql/MySQLBorrowRecordRepository.h"
    "mysql/MySQLBorrowRecordRepository.cpp"
    "mysql/MySQLBookCopyRepository.h"
    "mysql/MySQLBookCopyRepository.cpp"
)

target_include_directories(repository PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(repository PRIVATE
    database
    model
)

target_link_libraries(repository PRIVATE Qt6::Widgets Qt6::Sql MySQLConnector)