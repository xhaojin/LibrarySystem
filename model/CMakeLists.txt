add_library(model STATIC)

target_sources(model PRIVATE
    Book.cpp
    User.cpp
    BorrowRecord.cpp
    "Publisher.h"
    "Publisher.cpp"
    "Category.h"
    "Category.cpp"
)

target_include_directories(model PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(model PRIVATE Qt6::Widgets Qt6::Sql)