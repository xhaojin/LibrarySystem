add_library(controller STATIC)

target_sources(controller PRIVATE
    auth/AuthController.cpp
    book/BookController.h 
    book/BookController.cpp 
    borrow/BorrowController.cpp 
    borrow/BorrowController.h 
    user/UserController.cpp 
    user/UserController.h
)

target_include_directories(controller PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(controller PUBLIC Qt6::Widgets Qt6::Core Qt6::Sql)