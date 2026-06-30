#pragma once
#include <QApplication>
#include "ui/MainWindow.h"
#include "ui/LoginWindow.h"
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

private slots:
    void onLoginSuccess();

private:
    std::unique_ptr<SQLiteDatabase> database;

    std::unique_ptr<IBookRepository> bookRepo;

    std::unique_ptr<IUserRepository> userRepo;

    std::unique_ptr<IBorrowRecordRepository> borrowRepo;

    std::unique_ptr<LibraryService> service;

    std::unique_ptr<UIController> controller;

    std::unique_ptr<LoginWindow> loginWindow;

    std::unique_ptr<MainWindow> mainWindow;
};