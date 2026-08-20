#pragma once

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QHeaderView>
#include <QComboBox>
#include <QDate>
#include <QFormLayout>
#include <QGroupBox>

#include "ui/pages/base/BasePage.h"
#include "common/utils/TableUtil.h"
#include "core/ApplicationContext.h"

class BorrowPage : public BasePage
{
	Q_OBJECT

public:
	explicit BorrowPage(ApplicationContext& context, QWidget* parent = nullptr);
	void refresh() override; //刷新表格

private:
	void setupUI();
	void setConnections();
	void refreshBorrowRecordsTable(const std::vector<BorrowRecordDTO>& books); //刷新借阅记录表格
	void loadUsers();
	void loadBooks();
	void loadBorrowRecords();

private slots:
	void onBorrowClicked();
	void onReturnClicked();

private:
	ApplicationContext& m_context;

    // =========================
    // 借书
    // =========================

    QComboBox* m_userComboBox;
    QComboBox* m_bookComboBox;
    QComboBox* m_borrowOperatorComboBox;

    QDateEdit* m_dueDateEdit;

    QLineEdit* m_borrowRemarkEdit;

    QPushButton* m_borrowButton;

    // =========================
    // 还书
    // =========================

    QComboBox* m_borrowRecordComboBox;
    QComboBox* m_returnOperatorComboBox;

    QLineEdit* m_returnRemarkEdit;

    QPushButton* m_returnButton;

    // =========================
    // 借阅记录
    // =========================

    QTableWidget* m_recordTable;

    QPushButton* m_refreshButton;
};