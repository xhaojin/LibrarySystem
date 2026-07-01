#include "BorrowRecordPage.h"

BorrowRecordPage::BorrowRecordPage(QWidget* parent): QWidget(parent)
{
	setupUI();
}

void BorrowRecordPage::setupUI() {
	auto* borrowLayout = new QVBoxLayout(this);

	borrowLayout->addWidget(new QLabel("借阅记录管理"));

	// 工具栏
	auto* toolbar = new QHBoxLayout();

	toolbar->addWidget(new QLabel("用户名："));
	searchEdit = new QLineEdit();
	searchEdit->setPlaceholderText("请输入用户名");
	searchButton = new QPushButton("搜索");
	refreshBorrowRecordButton = new QPushButton("刷新");

	toolbar->addWidget(searchEdit);
	toolbar->addWidget(searchButton);
	toolbar->addStretch();
	toolbar->addWidget(refreshBorrowRecordButton);
	borrowLayout->addLayout(toolbar);

	borrowRecordTable = new QTableWidget(this);
	borrowRecordTable->setColumnCount(5);
	borrowRecordTable->setHorizontalHeaderLabels({ "BorrowRecord ID","user_id","book_id","borrow_time","return_time" });
	borrowRecordTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	borrowLayout->addWidget(borrowRecordTable);
}

void BorrowRecordPage::refreshBorrowRecords(const std::vector<BorrowRecordDTO>& records)
{
	borrowRecordTable->clearContents();

	borrowRecordTable->setRowCount(static_cast<int>(records.size()));

	for (int row = 0; row < records.size(); ++row)
	{
		const auto& re = records[row];

		borrowRecordTable->setItem(row, 0, new QTableWidgetItem(QString::number(re.id)));

		borrowRecordTable->setItem(row, 1, new QTableWidgetItem(QString::number(re.userId)));

		borrowRecordTable->setItem(row, 2, new QTableWidgetItem(QString::number(re.bookId)));

		borrowRecordTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(re.borrowTime)));

		borrowRecordTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(re.returnTime)));
	}
}