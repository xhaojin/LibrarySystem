#include "BorrowRecordPage.h"

BorrowRecordPage::BorrowRecordPage(ApplicationContext& context, QWidget* parent) :m_context(context), BasePage(parent)
{
	setupUI();
	setConnections();
	refresh();
}

void BorrowRecordPage::setupUI() {
	auto* borrowLayout = new QVBoxLayout(this);

	borrowLayout->addWidget(new QLabel("借阅记录管理"));

	// 工具栏
	auto* toolbar = new QHBoxLayout();

	if (m_context.sessionManager().isAdmin()) {
		toolbar->addWidget(new QLabel("用户名："));
		searchByUsernameEdit = new QLineEdit();
		searchByUsernameEdit->setPlaceholderText("请输入用户名");
		toolbar->addWidget(searchByUsernameEdit);
	}

	toolbar->addWidget(new QLabel("图书名："));
	searchByBookTitleEdit = new QLineEdit();
	searchByBookTitleEdit->setPlaceholderText("请输入图书名");

	searchButton = new QPushButton("搜索");
	refreshBorrowRecordButton = new QPushButton("刷新");

	toolbar->addWidget(searchByBookTitleEdit);
	toolbar->addWidget(searchButton);
	toolbar->addStretch();
	toolbar->addWidget(refreshBorrowRecordButton);
	borrowLayout->addLayout(toolbar);

	borrowRecordTable = new QTableWidget(this);
	TableUtil::init(borrowRecordTable);
	borrowRecordTable->setColumnCount(5);
	borrowRecordTable->setHorizontalHeaderLabels({ "BorrowRecord ID","name","bookTitle","borrow_time","return_time" });
	borrowLayout->addWidget(borrowRecordTable);
}

void BorrowRecordPage::setConnections()
{
	connect(refreshBorrowRecordButton, &QPushButton::clicked, this, [this]() {refresh();});
	connect(searchButton, &QPushButton::clicked, this, [this]() {onSearchClicked();});
}

void BorrowRecordPage::refresh()
{
	if (m_context.sessionManager().isAdmin()) {
		refreshBorrowRecordsTable(m_context.borrowController().getAllBorrowRecords());
	}
	else {
		refreshBorrowRecordsTable(m_context.borrowController().findBorrowRecordByNameAndBookTitle(m_context.sessionManager().currentUser().name,""));
	}
}

void BorrowRecordPage::refreshBorrowRecordsTable(const std::vector<BorrowRecordDTO>& records)
{
	borrowRecordTable->clearContents();

	borrowRecordTable->setRowCount(static_cast<int>(records.size()));

	for (int row = 0; row < records.size(); ++row)
	{
		const auto& re = records[row];

		borrowRecordTable->setItem(row, 0, new QTableWidgetItem(QString::number(re.id)));

		borrowRecordTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(re.username)));

		borrowRecordTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(re.bookTitle)));

		borrowRecordTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(re.borrowTime)));

		borrowRecordTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(re.returnTime)));
	}
}

void BorrowRecordPage::onSearchClicked() {
	std::string name;
	if (m_context.sessionManager().isAdmin()) {
		name = searchByUsernameEdit->text().toStdString();
		searchByUsernameEdit->clear();
	}
	else {
		name = m_context.sessionManager().currentUser().name;
	}
	QString bookTitle = searchByBookTitleEdit->text();
	searchByBookTitleEdit->clear();
	auto records = m_context.borrowController().findBorrowRecordByNameAndBookTitle(name, bookTitle.toStdString());
	refreshBorrowRecordsTable(records);
}