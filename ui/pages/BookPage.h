#pragma once

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QHeaderView>
#include <QMessageBox>

#include "dto/BookDTO.h"
#include "ui/dialogs/BookEditDialog.h"
#include "controller/book/BookController.h"

class BookPage : public QWidget
{
    Q_OBJECT

public:
    explicit BookPage(BookController& bookController,QWidget* parent = nullptr);

private:
    void setupUI();
    void setConnections();
    void refreshBooksTable(const std::vector<BookDTO>& books); //刷新图书表格
    void onFindByTitleClicked(); //按标题查找
    void onSortPriceClicked(); //按价格排序
    void onSortTitleClicked(); //按标题排序

private:
    BookController& bookController; //图书控制器

    QPushButton* borrowButton; //借阅书籍按钮
    QPushButton* returnButton; //归还书籍按钮

    QPushButton* refreshBookButton; //刷新

    QPushButton* searchButton; //按标题搜索按钮
    QLineEdit* searchEdit; //搜索框

    QPushButton* sortPriceButton; //按价格排序
    QPushButton* sortTitleButton; //按标题排序

    QPushButton* addBookButton; //添加书籍
    QPushButton* removeBookButton; //删除书籍
    QPushButton* updateBookButton; //更新书籍

    QTableWidget* bookTable; //图书表格
    BookEditDialog* bookEditDialog; //图书编辑对话框
};