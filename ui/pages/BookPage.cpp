#include "BookPage.h"

BookPage::BookPage(BookController& bookController, QWidget* parent) :bookController(bookController), BasePage(parent)
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
	TableUtil::init(bookTable);
	bookTable->setColumnCount(6);
	bookTable->setHorizontalHeaderLabels({ "Book ID","Title","Author","Publisher","Price","Status" });
	bookLayout->addWidget(bookTable);
}

void BookPage::setConnections() {
	// 连接按钮点击事件到槽函数
	connect(refreshBookButton, &QPushButton::clicked, this, [this]() {refreshBooksTable(bookController.getAllBooks());});
	connect(addBookButton, &QPushButton::clicked, this, &BookPage::addBook);
	connect(updateBookButton, &QPushButton::clicked, this, &BookPage::updateBook);
	connect(removeBookButton, &QPushButton::clicked, this, &BookPage::removeBook);
	connect(sortPriceButton, &QPushButton::clicked, this, &BookPage::onSortPriceClicked);
	connect(sortTitleButton, &QPushButton::clicked, this, &BookPage::onSortTitleClicked);
	connect(searchButton, &QPushButton::clicked, this, &BookPage::onFindByTitleClicked);
}

void BookPage::addBook() {
	BookEditDialog bookEditDialog(this); //图书编辑对话框
	bookEditDialog.setWindowTitle("添加图书");
	if (bookEditDialog.exec() != QDialog::Accepted)
		return;
	try
	{
		if (bookController.addBook(bookEditDialog.getBook()))
		{
			showInfo("添加成功");
			refreshBooksTable(bookController.getAllBooks());
		}
		else
		{
			showWarning("添加失败");
		}
	}
	catch (const std::exception& e)
	{
		showError(e.what());
	}
}

void BookPage::updateBook() {
	//从UI界面获取到当前点击选中的要修改的图书的ID，然后通过BookController获取到该图书的详细信息，最后将其传递给BookEditDialog进行修改。
	auto items = bookTable->selectedItems();
	if (items.isEmpty())
	{
		showWarning("请先选择一本图书");
		return;
	}
	int row = bookTable->currentRow();
	int bookId = bookTable->item(row, 0)->text().toInt();
	auto book = bookController.findBookById(bookId);

	BookEditDialog bookEditDialog(this);
	bookEditDialog.setWindowTitle("修改图书");
	bookEditDialog.setBook(book);

	if (bookEditDialog.exec() != QDialog::Accepted)
		return;

	BookDTO dto = bookEditDialog.getBook();
	dto.id = bookId;

	try
	{
		if (bookController.updateBook(dto))
		{
			showInfo("修改成功");
			refreshBooksTable(bookController.getAllBooks());
		}
		else
		{
			showWarning("修改失败");
		}
	}
	catch (const std::exception& e)
	{
		showError(e.what());
	}
}

void BookPage::removeBook() {
	auto items = bookTable->selectedItems();
	if (items.isEmpty())
	{
		showWarning("请先选择一本图书");
		return;
	}
	int row = bookTable->currentRow();
	int bookId = bookTable->item(row, 0)->text().toInt();
	auto book = bookController.findBookById(bookId);

	if (!confirmDelete(book.title.c_str())) {
		return;
	}

	try
	{
		if (bookController.removeBook(bookId))
		{
			showInfo("删除成功");
			refreshBooksTable(bookController.getAllBooks());
		}
		else
		{
			showWarning("删除失败");
		}
	}
	catch (const std::exception& e)
	{
		showError(e.what());
	}
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
		showWarning(e.what());
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