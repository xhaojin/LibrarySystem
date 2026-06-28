#pragma once

#include <QMainWindow>
#include <qheaderview.h>
#include <qmessagebox.h>
#include <QStackedWidget>

#include "../../include/ui/pages/BookPage.h"

#include "UIController.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    UIController& controller;

    BookPage* bookpage;

    QLineEdit* userIdEdit;
    QLineEdit* bookIdEdit;
    QLineEdit* searchEdit;

    QPushButton* borrowButton;
    QPushButton* returnButton;
    QPushButton* refreshBookButton;
    QPushButton* refreshUserButton;
    QPushButton* refreshBorrowRecordButton;
    QPushButton* searchButton;
    QPushButton* sortPriceButton;
    QPushButton* sortTitleButton;
    QPushButton* addBookButton;
    QPushButton* removeBookButton;
    QPushButton* updateBookButton;
    QPushButton* addUserButton;
    QPushButton* removeUserButton;
    QPushButton* updateUserButton;

    QPushButton* bookBtn;
    QPushButton* userBtn;
    QPushButton* borrowBtn;

    QTableWidget* bookTable;
    QTableWidget* userTable;
    QTableWidget* borrowRecordTable;

    QStackedWidget* stackedWidget;

private:
    void setupUI();
    void applyRolePermission();
    void refreshBooksTable();
    void refreshUsersTable();
    void refreshBorrowRecordTable();

private slots:
    void onBorrowClicked();
    void onReturnClicked();
    void onFindByTitleClicked();
    void onTableCellClicked(int row, int column);
    void onSortPriceClicked();
    void onSortTitleClicked();

public:
    explicit MainWindow(UIController& controller,QWidget* parent = nullptr);
    //void showBooks(const std::vector<BookDTO>&);
    void showUsers(const std::vector<UserDTO>&);
    void showBorrowRecords(const std::vector<BorrowRecordDTO>&);
};