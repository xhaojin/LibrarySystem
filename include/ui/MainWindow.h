#pragma once

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <qheaderview.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <qmessagebox.h>

#include "UIController.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    UIController& controller;

    QLineEdit* userIdEdit;
    QLineEdit* bookIdEdit;
    QLineEdit* searchEdit;

    QPushButton* borrowButton;
    QPushButton* returnButton;
    QPushButton* refreshButton;
    QPushButton* searchButton;
    QPushButton* sortPriceButton;
    QPushButton* sortTitleButton;

    QTableWidget* bookTable;

private:
    void setupUI();
    void refreshBooksTable();

private slots:
    void onBorrowClicked();
    void onReturnClicked();
    void onSearchClicked();
    void onTableCellClicked(int row, int column);
    void onSortPriceClicked();
    void onSortTitleClicked();

public:
    explicit MainWindow(UIController& controller,QWidget* parent = nullptr);
    void showBooks(const std::vector<BookDTO>&);
};