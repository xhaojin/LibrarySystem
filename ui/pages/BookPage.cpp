#include "BookPage.h"

BookPage::BookPage(BookController& bookController, QWidget* parent) :bookController(bookController), QWidget(parent)
{
	setupUI();
	setConnections();
	refreshBooksTable(bookController.getAllBooks());
}

void BookPage::setupUI() {
	auto* bookLayout = new QVBoxLayout(this);

	bookLayout->addWidget(new QLabel("图书管理"));

	// 工具栏
	auto* toolbar = new QHBoxLayout();

	addBookButton = new QPushButton("添加图书");
	bookEditDialog = new BookEditDialog(this);
	removeBookButton = new QPushButton("删除图书");
	updateBookButton = new QPushButton("更新图书");
	borrowButton = new QPushButton("借阅书籍");
	returnButton = new QPushButton("归还书籍");
	refreshBookButton = new QPushButton("刷新");

	toolbar->addWidget(addBookButton);
	toolbar->addWidget(removeBookButton);
	toolbar->addWidget(updateBookButton);
	toolbar->addSpacing(20);
	toolbar->addWidget(borrowButton);
	toolbar->addWidget(returnButton);
	toolbar->addStretch();
	toolbar->addWidget(refreshBookButton);

	bookLayout->addLayout(toolbar);

	//搜索排序栏
	auto* searchbar = new QHBoxLayout();
	searchbar->addWidget(new QLabel("图书名称："));
	searchEdit = new QLineEdit();
	searchEdit->setPlaceholderText("请输入书名");
	searchButton = new QPushButton("搜索");
	sortTitleButton = new QPushButton("标题排序");
	sortPriceButton = new QPushButton("价格排序");
	searchbar->addWidget(searchEdit);
	searchbar->addWidget(searchButton);
	searchbar->addStretch();
	searchbar->addWidget(sortTitleButton);
	searchbar->addWidget(sortPriceButton);
	bookLayout->addLayout(searchbar);

	//表格
	bookTable = new QTableWidget(this);
	bookTable->setColumnCount(6);
	bookTable->setHorizontalHeaderLabels({ "Book ID","Title","Author","Publisher","Price","Status" });
	bookTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	bookLayout->addWidget(bookTable);
}

void BookPage::setConnections() {
	// 连接按钮点击事件到槽函数
	connect(refreshBookButton, &QPushButton::clicked, this, [this]() {refreshBooksTable(bookController.getAllBooks());});
	connect(sortPriceButton, &QPushButton::clicked, this, &BookPage::onSortPriceClicked);
	connect(sortTitleButton, &QPushButton::clicked, this, &BookPage::onSortTitleClicked);
	connect(searchButton, &QPushButton::clicked, this, &BookPage::onFindByTitleClicked);
}

void BookPage::refreshBooksTable(const std::vector<BookDTO>& books)
{
	bookTable->clearContents();

	bookTable->setRowCount(static_cast<int>(books.size()));

	for (int row = 0; row < books.size(); ++row)
	{
		const auto& book = books[row];

		bookTable->setItem(row, 0, new QTableWidgetItem(QString::number(book.id)));

		bookTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(book.title)));

		bookTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(book.author)));

		bookTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(book.publisher)));

		bookTable->setItem(row, 4, new QTableWidgetItem(QString::number(book.price)));

		bookTable->setItem(row, 5, new QTableWidgetItem(book.isBorrowed ? "已借出" : "可借阅"));
	}
}

void BookPage::onSortPriceClicked() {
	try
	{
		auto books = bookController.getBooksSortedByPrice();
		refreshBooksTable(books);
	}
	catch (const std::exception& e)
	{
		QMessageBox::warning(this, "", e.what());
	}
}

void BookPage::onSortTitleClicked() {
	auto books = bookController.getBooksSortedByTitle();
	refreshBooksTable(books);
}

void BookPage::onFindByTitleClicked() {
	QString keyword = searchEdit->text();
	searchEdit->clear();
	auto books = bookController.findBooksByTitle(keyword.toStdString());
	refreshBooksTable(books);
}

//void BookPage::onBorrowClicked()
//{
//	int userId = userIdEdit->text().toInt();
//
//	int bookId = bookIdEdit->text().toInt();
//
//	try
//	{
//		controller.borrowBook(userId, bookId);
//
//		refreshBooksTable();
//
//		QMessageBox::information(this, "成功", "借书成功");
//
//		userIdEdit->clear();
//		bookIdEdit->clear();
//	}
//	catch (const std::exception& e)
//	{
//		QMessageBox::warning(this, "借书失败", e.what());
//	}
//}
//
//void BookPage::onReturnClicked()
//{
//	int userId = userIdEdit->text().toInt();
//
//	int bookId = bookIdEdit->text().toInt();
//
//	try
//	{
//		controller.returnBook(userId, bookId);
//
//		refreshBooksTable();
//
//		QMessageBox::information(this, "成功", "还书成功");
//
//		userIdEdit->clear();
//		bookIdEdit->clear();
//	}
//	catch (const std::exception& e)
//	{
//		QMessageBox::warning(this, "还书失败", e.what());
//	}
//}