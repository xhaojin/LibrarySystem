#pragma once

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QHeaderView>

#include "ui/pages/base/BasePage.h"
#include "common/utils/TableUtil.h"
#include "core/ApplicationContext.h"

class BorrowRecordPage : public BasePage
{
	Q_OBJECT

public:
	explicit BorrowRecordPage(ApplicationContext& context, QWidget* parent = nullptr);
	void refresh() override; //刷新表格

private:
	void setupUI();
	void setConnections();
	void refreshBorrowRecordsTable(const std::vector<BorrowRecordDTO>& books); //刷新借阅记录表格
	void onSearchClicked(); //按用户名查找

private:
	ApplicationContext& m_context;

	QPushButton* refreshBorrowRecordButton; //刷新

	QPushButton* searchButton; //搜索按钮

	QLineEdit* searchByUsernameEdit; //搜索框1

	QLineEdit* searchByBookTitleEdit; //搜索框2

	QTableWidget* borrowRecordTable; //借阅记录表格
};