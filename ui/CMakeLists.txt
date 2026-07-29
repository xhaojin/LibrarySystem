add_library(ui STATIC)

target_sources(ui PRIVATE
    MainWindow/MainWindow.cpp
    dialogs/LoginDialog.cpp
    pages/BookPage.cpp
    pages/UserPage.cpp
    pages/BorrowRecordPage.cpp
    dialogs/BookEditDialog.cpp
    pages/base/BasePage.cpp
    pages/base/BasePage.h
    dialogs/UserEditDialog.h
    dialogs/UserEditDialog.cpp
)

target_include_directories(ui PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${MYSQL_CONNECTOR_ROOT}/include
)

target_link_libraries(ui PRIVATE
    Qt6::Widgets
    Qt6::Sql
    MySQLConnector
)