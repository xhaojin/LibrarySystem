add_library(mapper STATIC)

target_sources(mapper PRIVATE
    BookMapper.cpp
    UserMapper.cpp
    BorrowRecordMapper.cpp
)

target_include_directories(mapper PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(mapper PRIVATE Qt6::Sql)