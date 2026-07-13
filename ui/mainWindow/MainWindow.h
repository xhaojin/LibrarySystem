#pragma once

#include <QMainWindow>
#include <qheaderview.h>
#include <qmessagebox.h>
#include <QStackedWidget>

#include "ui/pages/BookPage.h"
#include "ui/pages/UserPage.h"
#include "ui/pages/BorrowRecordPage.h"
#include "core/ApplicationContext.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	ApplicationContext& m_context; //应用程序上下文

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
	explicit MainWindow(ApplicationContext& context, QWidget* parent = nullptr);

};