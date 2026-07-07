#pragma once

#include <memory>
#include "database/SQLiteDatabase.h"
#include "repository/SQLite/SQLiteBookRepository.h"
#include "repository/SQLite/SQLiteBorrowRecordRepository.h"
#include "repository/SQLite/SQLiteUserRepository.h"
#include "controller/book/BookController.h"
#include "controller/user/UserController.h"
#include "controller/borrow/BorrowController.h"
#include "controller/auth/AuthController.h"

class ApplicationContext
{
public:
    ApplicationContext();

    bool initialize();
    bool initializeDatabase();
    void createRepositories();
    void createServices();
    void createControllers();

    BookController& bookController();
    UserController& userController();
    BorrowController& borrowController();
    SQLiteUserRepository& userRepository();

private:

    std::unique_ptr<SQLiteDatabase> database_;

    std::unique_ptr<SQLiteBookRepository> bookRepo_;
    std::unique_ptr<SQLiteUserRepository> userRepo_;
    std::unique_ptr<SQLiteBorrowRecordRepository> borrowRepo_;

    std::unique_ptr<BookService> bookService_;
    std::unique_ptr<UserService> userService_;
    std::unique_ptr<BorrowService> borrowService_;

    std::unique_ptr<BookController> bookController_;
    std::unique_ptr<UserController> userController_;
    std::unique_ptr<BorrowController> borrowController_;
};