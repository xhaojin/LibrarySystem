#pragma once

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QHeaderView>

#include "dto/BorrowRecordDTO.h"
#include "controller/borrow/BorrowController.h"

class BorrowRecordPage : public QWidget
{
	Q_OBJECT

public:
	explicit BorrowRecordPage(BorrowController& borrowController, QWidget* parent = nullptr);

private:
	void setupUI();
	void setConnections();
	void refreshBorrowRecordsTable(const std::vector<BorrowRecordDTO>& books); //刷新借阅记录表格

private:
	BorrowController& borrowController; //借阅记录服务

	QPushButton* refreshBorrowRecordButton; //刷新

	QPushButton* searchButton; //搜索按钮

	QLineEdit* searchEdit; //搜索框

	QTableWidget* borrowRecordTable; //借阅记录表格
};