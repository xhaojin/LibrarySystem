add_library(service STATIC)

target_sources(service PRIVATE
    auth/AuthService.cpp
    book/BookService.cpp
    user/UserService.cpp
    borrow/BorrowService.cpp
    statistics/StatisticsService.cpp
    "auth/LoginStatus.h"
    "auth/LoginResult.h"
    "publisher/PublisherService.h"
    "publisher/PublisherService.cpp"
)

target_include_directories(service PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(service PRIVATE
    repository
    model
    dto
)

target_link_libraries(service PRIVATE Qt6::Widgets Qt6::Sql)