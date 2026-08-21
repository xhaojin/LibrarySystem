#include "BorrowPage.h"

#include <QMessageBox>
#include <QListWidgetItem>
#include <QTableWidgetItem>
#include <QAbstractItemView>

#include <exception>


BorrowPage::BorrowPage(ApplicationContext& context, QWidget* parent) : BasePage(parent), m_context(context)
{
	setupUI();
	setConnections();

	refresh();
}


// =========================================================
// UI
// =========================================================

void BorrowPage::setupUI()
{
	auto* mainLayout = new QVBoxLayout(this);

	// =====================================================
	// 上半部分：借书 + 还书
	// =====================================================

	auto* operationLayout = new QHBoxLayout();

	// =====================================================
	// 借书
	// =====================================================

	auto* borrowGroup = new QGroupBox("借书", this);

	auto* borrowLayout = new QVBoxLayout(borrowGroup);

	// -------------------------
	// 用户搜索
	// -------------------------

	borrowLayout->addWidget(new QLabel("用户：", this));

	auto* userSearchLayout = new QHBoxLayout();

	m_userSearchEdit = new QLineEdit(this);

	m_userSearchEdit->setPlaceholderText("输入用户姓名");

	m_userSearchButton = new QPushButton("搜索", this);

	userSearchLayout->addWidget(m_userSearchEdit);

	userSearchLayout->addWidget(m_userSearchButton);

	borrowLayout->addLayout(userSearchLayout);

	m_userSearchList = new QListWidget(this);

	m_userSearchList->setMaximumHeight(100);

	borrowLayout->addWidget(m_userSearchList);

	m_selectedUserLabel = new QLabel("未选择用户", this);

	borrowLayout->addWidget(m_selectedUserLabel);

	// -------------------------
	// 图书搜索
	// -------------------------

	borrowLayout->addWidget(new QLabel("图书：", this));

	auto* bookSearchLayout = new QHBoxLayout();

	m_bookSearchEdit = new QLineEdit(this);

	m_bookSearchEdit->setPlaceholderText("输入书名");

	m_bookSearchButton = new QPushButton("搜索", this);

	bookSearchLayout->addWidget(m_bookSearchEdit);

	bookSearchLayout->addWidget(m_bookSearchButton);

	borrowLayout->addLayout(bookSearchLayout);

	m_bookSearchList = new QListWidget(this);

	m_bookSearchList->setMaximumHeight(100);

	borrowLayout->addWidget(m_bookSearchList);

	m_selectedBookLabel = new QLabel("未选择图书", this);

	borrowLayout->addWidget(m_selectedBookLabel);

	// -------------------------
	// 应还日期
	// -------------------------

	auto* dueDateLayout = new QHBoxLayout();

	dueDateLayout->addWidget(new QLabel("应还日期：", this));

	m_dueDateEdit = new QDateEdit(this);

	m_dueDateEdit->setCalendarPopup(true);

	m_dueDateEdit->setDate(QDate::currentDate().addMonths(1));

	dueDateLayout->addWidget(m_dueDateEdit);

	borrowLayout->addLayout(dueDateLayout);

	// -------------------------
	// 备注
	// -------------------------

	m_borrowRemarkEdit = new QLineEdit(this);

	m_borrowRemarkEdit->setPlaceholderText("备注（可选）");

	borrowLayout->addWidget(m_borrowRemarkEdit);

	// -------------------------
	// 借书按钮
	// -------------------------

	m_borrowButton = new QPushButton("确认借书", this);

	borrowLayout->addWidget(m_borrowButton);

	operationLayout->addWidget(borrowGroup, 1);

	// =====================================================
	// 还书
	// =====================================================

	auto* returnGroup = new QGroupBox("还书", this);

	auto* returnLayout = new QVBoxLayout(returnGroup);

	// -------------------------
	// 用户搜索
	// -------------------------

	returnLayout->addWidget(new QLabel("用户：", this));

	auto* returnUserSearchLayout = new QHBoxLayout();

	m_returnUserSearchEdit = new QLineEdit(this);

	m_returnUserSearchEdit->setPlaceholderText("输入用户姓名");

	m_returnUserSearchButton = new QPushButton("搜索", this);

	returnUserSearchLayout->addWidget(m_returnUserSearchEdit);

	returnUserSearchLayout->addWidget(m_returnUserSearchButton);

	returnLayout->addLayout(returnUserSearchLayout);

	m_returnUserSearchList = new QListWidget(this);

	m_returnUserSearchList->setMaximumHeight(100);

	returnLayout->addWidget(m_returnUserSearchList);

	m_selectedReturnUserLabel = new QLabel("未选择用户", this);

	returnLayout->addWidget(m_selectedReturnUserLabel);

	// -------------------------
	// 当前借阅
	// -------------------------

	returnLayout->addWidget(new QLabel("当前借阅：", this));

	m_currentBorrowTable = new QTableWidget(this);

	m_currentBorrowTable->setColumnCount(4);

	m_currentBorrowTable->setHorizontalHeaderLabels({ "图书","副本","应还日期","操作" });

	m_currentBorrowTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	m_currentBorrowTable->setSelectionBehavior(QAbstractItemView::SelectRows);

	m_currentBorrowTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

	m_currentBorrowTable->setAlternatingRowColors(true);

	returnLayout->addWidget(m_currentBorrowTable, 1);

	operationLayout->addWidget(returnGroup, 1);

	mainLayout->addLayout(operationLayout, 2);

	// =====================================================
	// 借阅记录
	// =====================================================

	auto* recordGroup = new QGroupBox("借阅记录", this);

	auto* recordLayout = new QVBoxLayout(recordGroup);

	// -------------------------
	// 查询栏
	// -------------------------

	auto* recordSearchLayout = new QHBoxLayout();

	m_recordSearchEdit = new QLineEdit(this);

	m_recordSearchEdit->setPlaceholderText("搜索用户 / 图书 / 副本");

	m_statusComboBox = new QComboBox(this);

	m_statusComboBox->addItem("全部", -1);

	m_statusComboBox->addItem("借阅中", 0);

	m_statusComboBox->addItem("已归还", 1);

	m_statusComboBox->addItem("逾期", 2);

	m_recordSearchButton = new QPushButton("查询", this);

	m_refreshButton = new QPushButton("刷新", this);

	recordSearchLayout->addWidget(m_recordSearchEdit, 1);

	recordSearchLayout->addWidget(m_statusComboBox);

	recordSearchLayout->addWidget(m_recordSearchButton);

	recordSearchLayout->addWidget(m_refreshButton);

	recordLayout->addLayout(recordSearchLayout);

	// -------------------------
	// 借阅记录表
	// -------------------------

	m_recordTable = new QTableWidget(this);

	m_recordTable->setColumnCount(7);

	m_recordTable->setHorizontalHeaderLabels({ "用户","图书","副本","借阅时间","应还时间","归还时间","状态" });

	m_recordTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	m_recordTable->setSelectionBehavior(QAbstractItemView::SelectRows);

	m_recordTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

	m_recordTable->setAlternatingRowColors(true);

	recordLayout->addWidget(m_recordTable);

	mainLayout->addWidget(recordGroup, 3);
}


// =========================================================
// Connections
// =========================================================

void BorrowPage::setConnections()
{
	// 借书 - 用户搜索
	connect(m_userSearchButton, &QPushButton::clicked, this, &BorrowPage::onUserSearch);

	connect(m_userSearchEdit, &QLineEdit::returnPressed, this, &BorrowPage::onUserSearch);

	connect(m_userSearchList, &QListWidget::itemClicked, this, &BorrowPage::onUserSelected);

	// 借书 - 图书搜索
	connect(m_bookSearchButton, &QPushButton::clicked, this, &BorrowPage::onBookSearch);

	connect(m_bookSearchEdit, &QLineEdit::returnPressed, this, &BorrowPage::onBookSearch);

	connect(m_bookSearchList, &QListWidget::itemClicked, this, &BorrowPage::onBookSelected);

	// 借书
	connect(m_borrowButton, &QPushButton::clicked, this, &BorrowPage::onBorrowClicked);

	// 还书 - 用户搜索
	connect(m_returnUserSearchButton, &QPushButton::clicked, this, &BorrowPage::onReturnUserSearch);

	connect(m_returnUserSearchEdit, &QLineEdit::returnPressed, this, &BorrowPage::onReturnUserSearch);

	connect(m_returnUserSearchList, &QListWidget::itemClicked, this, &BorrowPage::onReturnUserSelected);

	// 借阅记录
	connect(m_recordSearchButton, &QPushButton::clicked, this, &BorrowPage::onRecordSearch);

	connect(m_recordSearchEdit, &QLineEdit::returnPressed, this, &BorrowPage::onRecordSearch);

	// 刷新
	connect(m_refreshButton, &QPushButton::clicked, this, &BorrowPage::onRefreshClicked);
}

// =========================================================
// Refresh
// =========================================================

void BorrowPage::refresh()
{
	loadBorrowRecords();

	m_currentBorrowTable->clearContents();
	m_currentBorrowTable->setRowCount(0);

	clearUserSelection();
	clearBookSelection();
	clearReturnUserSelection();
}

// =========================================================
// User Search
// =========================================================

void BorrowPage::onUserSearch()
{
	const QString keyword = m_userSearchEdit->text().trimmed();

	m_userSearchList->clear();

	if (keyword.isEmpty())
	{
		return;
	}

	try
	{
		auto users = m_context.userRepository().findByName(keyword.toStdString());

		for (const auto& user : users)
		{
			if (!user)continue;

			QString text = QString::fromStdString(user->getName());

			auto* item = new QListWidgetItem(text);

			item->setData(Qt::UserRole, static_cast<qlonglong>(user->getId()));

			m_userSearchList->addItem(item);
		}

		if (m_userSearchList->count() == 0)
		{
			m_userSearchList->addItem("没有找到匹配的用户");
		}
	}
	catch (const std::exception& e)
	{
		showError("搜索失败");
	}
}


// =========================================================
// User Selected
// =========================================================

void BorrowPage::onUserSelected(QListWidgetItem* item)
{
	if (!item)return;

	bool ok = false;

	const qlonglong id = item->data(Qt::UserRole).toLongLong(&ok);

	if (!ok || id <= 0)return;

	m_selectedUserId = static_cast<std::int64_t>(id);

	m_selectedUserLabel->setText("已选择用户：" + item->text());

	m_userSearchList->clear();
}


// =========================================================
// Book Search
// =========================================================

void BorrowPage::onBookSearch()
{
	const QString keyword = m_bookSearchEdit->text().trimmed();

	m_bookSearchList->clear();

	if (keyword.isEmpty())
	{
		return;
	}

	try
	{
		auto books = m_context.bookController().findBooksByTitle(keyword.toStdString());

		for (const auto& book : books)
		{

			QString text = QString::fromStdString(book.title);

			auto* item = new QListWidgetItem(text);

			item->setData(Qt::UserRole, static_cast<qlonglong>(book.id));

			m_bookSearchList->addItem(item);
		}

		if (m_bookSearchList->count() == 0)
		{
			m_bookSearchList->addItem("没有找到匹配的图书");
		}
	}
	catch (const std::exception& e)
	{
		showError("搜索失败");
	}
}


// =========================================================
// Book Selected
// =========================================================

void BorrowPage::onBookSelected(QListWidgetItem* item)
{
	if (!item)return;

	bool ok = false;

	const qlonglong id = item->data(Qt::UserRole).toLongLong(&ok);

	if (!ok || id <= 0)return;

	m_selectedBookId = static_cast<std::int64_t>(id);

	m_selectedBookLabel->setText("已选择图书：" + item->text());

	m_bookSearchList->clear();
}


// =========================================================
// Borrow
// =========================================================

void BorrowPage::onBorrowClicked()
{
	if (m_selectedUserId <= 0)
	{
		showWarning("请先选择用户");

		return;
	}

	if (m_selectedBookId <= 0)
	{
		showWarning("请先选择图书");

		return;
	}

	const QString dueTime = m_dueDateEdit->date().toString("yyyy-MM-dd") + " 23:59:59";

	try
	{

		const std::int64_t operatorId = m_context.sessionManager().currentUser().id;

		const bool success = m_context.borrowController().borrowBook(
			m_selectedUserId,
			m_selectedBookId,
			operatorId,
			dueTime.toStdString(),
			m_borrowRemarkEdit->text().toStdString());

		if (!success)
		{
			showWarning("借书失败，请查询图书库存或用户状态");

			return;
		}

		showInfo("借书成功");

		clearUserSelection();
		clearBookSelection();

		m_borrowRemarkEdit->clear();

		loadBorrowRecords();
	}
	catch (const std::exception& e)
	{
		showError("借书异常");
	}
}


// =========================================================
// Return User Search
// =========================================================

void BorrowPage::onReturnUserSearch()
{
	const QString keyword = m_returnUserSearchEdit->text().trimmed();

	m_returnUserSearchList->clear();

	if (keyword.isEmpty())
	{
		return;
	}

	try
	{
		auto users = m_context.userRepository().findByName(keyword.toStdString());

		for (const auto& user : users)
		{
			if (!user)continue;

			QString text = QString::fromStdString(user->getName());

			auto* item = new QListWidgetItem(text);

			item->setData(Qt::UserRole, static_cast<qlonglong>(user->getId()));

			m_returnUserSearchList->addItem(item);
		}

		if (m_returnUserSearchList->count() == 0)
		{
			m_returnUserSearchList->addItem("没有找到匹配的用户");
		}
	}
	catch (const std::exception& e)
	{
		showError("搜索失败");
	}
}


// =========================================================
// Return User Selected
// =========================================================

void BorrowPage::onReturnUserSelected(QListWidgetItem* item)
{
	if (!item)return;

	bool ok = false;

	const qlonglong id = item->data(Qt::UserRole).toLongLong(&ok);

	if (!ok || id <= 0)return;

	m_selectedReturnUserId = static_cast<std::int64_t>(id);

	m_selectedReturnUserLabel->setText("已选择用户：" + item->text());

	m_returnUserSearchList->clear();

	loadCurrentBorrowRecords(m_selectedReturnUserId);
}


// =========================================================
// Load Current Borrow Records
// =========================================================

void BorrowPage::loadCurrentBorrowRecords(std::int64_t userId)
{
	m_currentBorrowTable->clearContents();
	m_currentBorrowTable->setRowCount(0);

	if (userId <= 0)return;

	try
	{
		auto records = m_context.borrowController().findCurrentBorrowRecords(userId);

		refreshCurrentBorrowTable(records);
	}
	catch (const std::exception& e)
	{
		showError("加载失败");
	}
}


// =========================================================
// Refresh Current Borrow Table
// =========================================================

void BorrowPage::refreshCurrentBorrowTable(const std::vector<BorrowRecordViewDTO>& records)
{
	m_currentBorrowTable->clearContents();

	m_currentBorrowTable->setRowCount(static_cast<int>(records.size()));

	for (int row = 0;row < static_cast<int>(records.size());++row)
	{
		const auto& record = records[row];

		// 图书
		m_currentBorrowTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(record.bookTitle)));

		// 副本编号
		m_currentBorrowTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(record.inventoryNo)));

		// 应还日期
		m_currentBorrowTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(record.dueTime)));

		// 还书按钮
		auto* returnButton =new QPushButton("还书",m_currentBorrowTable);

		returnButton->setProperty("borrowRecordId",QVariant::fromValue(static_cast<qlonglong>(record.id)));

		m_currentBorrowTable->setCellWidget(row,3,returnButton);

		connect(returnButton,&QPushButton::clicked,this,[this, returnButton]()
			{
				const qlonglong recordId =returnButton->property("borrowRecordId").toLongLong();

				if (recordId <= 0)
				{
					showWarning("无效的借阅记录id");

					return;
				}

				try
				{
					const std::int64_t operatorId = 1;

					m_context.borrowController().returnBook(static_cast<std::int64_t>(recordId),operatorId);

					showInfo("还书成功");

					// 刷新当前用户的借阅
					loadCurrentBorrowRecords(m_selectedReturnUserId);

					// 刷新下面的借阅记录
					loadBorrowRecords();
				}
				catch (const std::exception& e)
				{
					showError("还书失败");
				}
			});
	}
}


// =========================================================
// Borrow Records
// =========================================================

void BorrowPage::loadBorrowRecords()
{
	try
	{
		auto records = m_context.borrowRecordRepository().findAllView();

		refreshBorrowRecordsTable(records);
	}
	catch (const std::exception& e)
	{
		showError("加载借阅记录失败");
	}
}


// =========================================================
// Search Records
// =========================================================

void BorrowPage::onRecordSearch()
{
	const QString keyword = m_recordSearchEdit->text().trimmed();

	const int status = m_statusComboBox->currentData().toInt();

	try
	{
		auto records = m_context.borrowRecordRepository().findViewRecords(keyword.toStdString(), status);

		refreshBorrowRecordsTable(records);
	}
	catch (const std::exception& e)
	{
		showError("查询失败");
	}
}


// =========================================================
// Refresh Record Table
// =========================================================

void BorrowPage::refreshBorrowRecordsTable(const std::vector<BorrowRecordViewDTO>& records)
{
	m_recordTable->clearContents();

	m_recordTable->setRowCount(static_cast<int>(records.size()));

	for (int row = 0;row < static_cast<int>(records.size());++row)
	{
		const auto& record = records[row];

		m_recordTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(record.username)));

		m_recordTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(record.bookTitle)));

		m_recordTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(record.inventoryNo)));

		m_recordTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(record.borrowTime)));

		m_recordTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(record.dueTime)));

		m_recordTable->setItem(row, 5, new QTableWidgetItem(record.returnTime.empty() ? "-" : QString::fromStdString(record.returnTime)));

		QString statusText;

		switch (record.status)
		{
		case 0:
			statusText = "借阅中";
			break;

		case 1:
			statusText = "已归还";
			break;

		case 2:
			statusText = "逾期";
			break;

		default:
			statusText = "未知";
			break;
		}

		m_recordTable->setItem(row, 6, new QTableWidgetItem(statusText));
	}
}


// =========================================================
// Refresh Button
// =========================================================

void BorrowPage::onRefreshClicked()
{
	refresh();
}


// =========================================================
// Clear Selection
// =========================================================

void BorrowPage::clearUserSelection()
{
	m_selectedUserId = 0;

	m_selectedUserLabel->setText("未选择用户");

	m_userSearchEdit->clear();

	m_userSearchList->clear();
}


void BorrowPage::clearBookSelection()
{
	m_selectedBookId = 0;

	m_selectedBookLabel->setText("未选择图书");

	m_bookSearchEdit->clear();

	m_bookSearchList->clear();
}


void BorrowPage::clearReturnUserSelection()
{
	m_selectedReturnUserId = 0;

	m_selectedReturnUserLabel->setText("未选择用户");

	m_returnUserSearchEdit->clear();

	m_returnUserSearchList->clear();

	m_currentBorrowTable->clearContents();

	m_currentBorrowTable->setRowCount(0);
}