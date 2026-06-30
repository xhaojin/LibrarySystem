#pragma once

#include <QMainWindow>
#include <qheaderview.h>
#include <qmessagebox.h>
#include <QStackedWidget>

#include "pages/BookPage.h"
#include "pages/UserPage.h"
#include "pages/BorrowRecordPage.h"

#include "UIController.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    UIController& controller;

    BookPage* bookpage;
    UserPage* userpage;
    BorrowRecordPage* borrowpage;

    QLineEdit* userIdEdit;
    QLineEdit* bookIdEdit;
    QLineEdit* searchEdit;

    QPushButton* bookMenuBtn;
    QPushButton* userMenuBtn;
    QPushButton* borrowMenuBtn;

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