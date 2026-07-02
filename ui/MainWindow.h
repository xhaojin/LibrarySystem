#pragma once

#include <QMainWindow>
#include <qheaderview.h>
#include <qmessagebox.h>
#include <QStackedWidget>

#include "pages/BookPage.h"
#include "pages/UserPage.h"
#include "pages/BorrowRecordPage.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	BookController& bookController; //图书控制器
	UserController& userController; //用户控制器
	BorrowController& borrowController; //借阅记录控制器

	BookPage* bookpage; //图书管理页面
	UserPage* userpage; //用户管理页面
	BorrowRecordPage* borrowpage; //借阅记录页面

	QPushButton* bookMenuBtn; //图书管理按钮
	QPushButton* userMenuBtn; //用户管理按钮
	QPushButton* borrowMenuBtn; //借阅记录管理按钮

	QStackedWidget* stackedWidget;  //堆叠窗口，用于切换不同的页面

private:
	void setupUI();

public:
	explicit MainWindow(BookController& bookController,
		UserController& userController,
		BorrowController& borrowController, QWidget* parent = nullptr);

};