#pragma once
#include <QApplication>
#include "ui/MainWindow.h"
#include "ui/LoginWindow.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include "../include/repository/SQLite/SQLiteDatabase.h"
#include "../include/repository/SQLite/SQLiteBookRepository.h"
#include "../include/repository/SQLite/SQLiteBorrowRecordRepository.h"
#include "../include/repository/SQLite/SQLiteUserRepository.h"

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