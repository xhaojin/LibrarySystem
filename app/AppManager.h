#pragma once
#include <QApplication>
#include "ui/mainWindow/MainWindow.h"
#include <QDebug>
#include "database/SQLiteDatabase.h"
#include "repository/SQLite/SQLiteBookRepository.h"
#include "repository/SQLite/SQLiteBorrowRecordRepository.h"
#include "repository/SQLite/SQLiteUserRepository.h"

class AppManager : public QObject
{
    Q_OBJECT

public:
    AppManager();

    int run(int argc, char* argv[]);

private:
    bool initializeDatabase(); // 初始化数据库
    void createRepositories(); // 创建仓库
    void createServices(); // 创建服务
    void createControllers(); // 创建控制器
    void createMainWindow(); // 创建主窗口
    bool showLoginDialog(); // 显示登录对话框

private:
    std::unique_ptr<SQLiteDatabase> database;
    std::unique_ptr<IBookRepository> bookRepo;
    std::unique_ptr<IUserRepository> userRepo;
    std::unique_ptr<IBorrowRecordRepository> borrowRepo;

    std::unique_ptr<BookService> bookService;
    std::unique_ptr<UserService> userService;
    std::unique_ptr<BorrowService> borrowService;

    std::unique_ptr<BookController> bookController;
    std::unique_ptr<UserController> userController;
    std::unique_ptr<BorrowController> borrowController;

    std::unique_ptr<MainWindow> mainWindow;
};