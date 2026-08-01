#pragma once

//#include "database/sqlite/SQLiteDatabase.h"
//#include "repository/SQLite/SQLiteBookRepository.h"
//#include "repository/SQLite/SQLiteBorrowRecordRepository.h"
//#include "repository/SQLite/SQLiteUserRepository.h"
#include <memory>
#include "database/mysql/MySQLDatabase.h"
#include "repository/mysql/MySQLUserRepository.h"
#include "repository/mysql/MySQLBookRepository.h"
#include "controller/book/BookController.h"
#include "controller/user/UserController.h"
#include "controller/borrow/BorrowController.h"
#include "app/SessionManager.h"

class ApplicationContext
{
public:
    ApplicationContext();

    bool initialize();
    bool initializeDatabase();
    void createRepositories();
    void createServices();
    void createControllers();
    void createSession();

    BookController& bookController();
    UserController& userController();
    BorrowController& borrowController();
    //SQLiteUserRepository& userRepository();
    MySQLUserRepository& userRepository();
    SessionManager& sessionManager();

private:

    std::unique_ptr<MySQLDatabase> database_;
    std::unique_ptr<MySQLBookRepository> bookRepo_;
    std::unique_ptr<MySQLUserRepository> userRepo_;
    //std::unique_ptr<SQLiteBorrowRecordRepository> borrowRepo_;

    std::unique_ptr<BookService> bookService_;
    std::unique_ptr<UserService> userService_;
    std::unique_ptr<BorrowService> borrowService_;

    std::unique_ptr<BookController> bookController_;
    std::unique_ptr<UserController> userController_;
    std::unique_ptr<BorrowController> borrowController_;

    std::unique_ptr<SessionManager> sessionManager_;
};