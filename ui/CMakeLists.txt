add_library(ui STATIC)

target_sources(ui PRIVATE
    MainWindow.cpp
    LoginWindow.cpp
    UIController.cpp
    pages/BookPage.cpp
    pages/UserPage.cpp
    pages/BorrowRecordPage.cpp
)

target_include_directories(ui PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(ui PRIVATE
    Qt6::Widgets
    Qt6::Sql
)