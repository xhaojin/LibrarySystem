add_library(mapper STATIC)

target_sources(mapper PRIVATE
    BookMapper.cpp
    UserMapper.cpp
    BorrowRecordMapper.cpp
 "UserDTOMapper.h" "UserDTOMapper.cpp")

target_include_directories(mapper PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}
    ${MYSQL_CONNECTOR_ROOT}/include
)

target_link_libraries(mapper PRIVATE Qt6::Sql)