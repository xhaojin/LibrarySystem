#pragma once

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QHeaderView>

#include "dto/BookDTO.h"

class BookPage : public QWidget
{
    Q_OBJECT

public:
    explicit BookPage(QWidget* parent = nullptr);

    void refreshBooks(const std::vector<BookDTO>& books);

signals:
    void borrowBookRequested(int userId, int bookId);
    void returnBookRequested(int userId, int bookId);

    void addBookRequested();
    void removeBookRequested();
    void updateBookRequested();

    void refreshRequested();

    void searchRequested(const QString& keyword);

    void sortByTitleRequested();
    void sortByPriceRequested();

private:
    void setupUI();

private:
    QPushButton* borrowButton; //借阅书籍按钮
    QPushButton* returnButton; //归还书籍按钮

    QPushButton* refreshBookButton; //刷新

    QPushButton* searchButton; //搜索按钮

    QLineEdit* searchEdit; //搜索框

    QPushButton* sortPriceButton; //按价格排序
    QPushButton* sortTitleButton; //按标题排序

    QPushButton* addBookButton; //添加书籍
    QPushButton* removeBookButton; //删除书籍
    QPushButton* updateBookButton; //更新书籍

    QTableWidget* bookTable; //图书表格
};