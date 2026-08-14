add_library(mapper STATIC)

target_sources(mapper PRIVATE
    BookMapper.cpp
    UserMapper.cpp
    BorrowRecordMapper.cpp
    "UserDTOMapper.h"
    "UserDTOMapper.cpp"
    "BookDTOMapper.h"
    "BookDTOMapper.cpp"
    "PublisherMapper.h"
    "PublisherMapper.cpp"
 "PublisherDTOMapper.h" "PublisherDTOMapper.cpp")

target_include_directories(mapper PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(mapper PRIVATE Qt6::Sql MySQLConnector)