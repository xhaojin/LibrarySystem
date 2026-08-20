#pragma once

#include <memory>

#include "database/mysql/MySQLDatabase.h"
#include "repository/mysql/MySQLUserRepository.h"
#include "repository/mysql/MySQLBookRepository.h"
#include "repository/mysql/MySQLBookCopyRepository.h"
#include "repository/mysql/MySQLBorrowRecordRepository.h"
#include "repository/mysql/MySQLPublisherRepository.h"
#include "repository/mysql/MySQLCategoryRepository.h"

#include "controller/book/BookController.h"
#include "controller/user/UserController.h"
#include "controller/borrow/BorrowController.h"
#include "controller/publisher/PublisherController.h"
#include "controller/category/CategoryController.h"

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
	PublisherController& publisherController();
    CategoryController& categoryController();
    //SQLiteUserRepository& userRepository();
    MySQLUserRepository& userRepository();
    SessionManager& sessionManager();

private:

    std::unique_ptr<MySQLDatabase> database_;
    std::unique_ptr<MySQLBookRepository> bookRepo_;
    std::unique_ptr<MySQLUserRepository> userRepo_;
    std::unique_ptr<MySQLBookCopyRepository> bookCopyRepo_;
    std::unique_ptr<MySQLBorrowRecordRepository> borrowRecordRepo_;
    std::unique_ptr<MySQLPublisherRepository> publisherRepo_;
    std::unique_ptr<MySQLCategoryRepository> categoryRepo_;

    std::unique_ptr<BookService> bookService_;
    std::unique_ptr<UserService> userService_;
    std::unique_ptr<BorrowService> borrowService_;
	std::unique_ptr<PublisherService> publisherService_;
    std::unique_ptr<CategoryService> categoryService_;

    std::unique_ptr<BookController> bookController_;
    std::unique_ptr<UserController> userController_;
    std::unique_ptr<BorrowController> borrowController_;
    std::unique_ptr<PublisherController> publisherController_;
    std::unique_ptr<CategoryController> categoryController_;

    std::unique_ptr<SessionManager> sessionManager_;
};