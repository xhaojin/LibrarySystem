#include "BookPage.h"

BookPage::BookPage(ApplicationContext& context, QWidget* parent) :m_context(context), BasePage(parent)
{
	setupUI();
	setConnections();
	refresh();
}

void BookPage::setupUI() {
	auto* bookLayout = new QVBoxLayout(this);

	bookLayout->addWidget(new QLabel("图书管理"));

	// 工具栏
	auto* toolbar = new QHBoxLayout();

	if (m_context.sessionManager().isAdmin()) {
		addBookButton = new QPushButton("添加图书");
		toolbar->addWidget(addBookButton);
		removeBookButton = new QPushButton("删除图书");
		toolbar->addWidget(removeBookButton);
		updateBookButton = new QPushButton("更新图书");
		toolbar->addWidget(updateBookButton);
		toolbar->addSpacing(20);
	}

	if (m_context.sessionManager().isUser()) {
		borrowButton = new QPushButton("借阅书籍");
		returnButton = new QPushButton("归还书籍");
		toolbar->addWidget(borrowButton);
		toolbar->addWidget(returnButton);
	}

	toolbar->addStretch();
	refreshBookButton = new QPushButton("刷新");
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
	bookTable->setColumnCount(11);
	bookTable->setHorizontalHeaderLabels(
		{ "Book ID","Isbn","Title","Author","Publisher","Category","PublishYear","Price","Cover URL","Description","Status" });
	bookLayout->addWidget(bookTable);
}

void BookPage::setConnections() {
	// 连接按钮点击事件到槽函数
	connect(refreshBookButton, &QPushButton::clicked, this, [this]() {refreshBooksTable(m_context.bookController().getAllBooks());});
	if (m_context.sessionManager().isAdmin()) {
		connect(addBookButton, &QPushButton::clicked, this, &BookPage::addBook);
		connect(updateBookButton, &QPushButton::clicked, this, &BookPage::updateBook);
		connect(removeBookButton, &QPushButton::clicked, this, &BookPage::removeBook);
	}
	connect(sortPriceButton, &QPushButton::clicked, this, &BookPage::onSortPriceClicked);
	connect(sortTitleButton, &QPushButton::clicked, this, &BookPage::onSortTitleClicked);
	connect(searchButton, &QPushButton::clicked, this, &BookPage::onFindByTitleClicked);
	if (m_context.sessionManager().isUser()) {
		connect(borrowButton, &QPushButton::clicked, this, &BookPage::onBorrowBookClicked);
		connect(returnButton, &QPushButton::clicked, this, &BookPage::onReturnBookClicked);
	}
}

void BookPage::addBook() {
	BookEditDialog bookEditDialog(m_context, this); //图书编辑对话框
	bookEditDialog.setWindowTitle("添加图书");
	if (bookEditDialog.exec() != QDialog::Accepted)
		return;
	try
	{
		if (m_context.bookController().addBook(bookEditDialog.getBook()))
		{
			showInfo("添加成功");
			refresh();
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
	auto items = bookTable->selectedItems();
	if (items.isEmpty())
	{
		showWarning("请先选择一本图书");
		return;
	}
	int row = bookTable->currentRow();
	int bookId = bookTable->item(row, 0)->text().toInt();
	auto book = m_context.bookController().findBookById(bookId);

	BookEditDialog bookEditDialog(m_context, this);
	bookEditDialog.setWindowTitle("修改图书");
	bookEditDialog.setBook(book);

	if (bookEditDialog.exec() != QDialog::Accepted)
		return;

	BookDTO dto = bookEditDialog.getBook();
	dto.id = bookId;

	try
	{
		if (m_context.bookController().updateBook(dto))
		{
			showInfo("修改成功");
			refresh();
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
	auto book = m_context.bookController().findBookById(bookId);

	if (!confirmDelete(book.title.c_str())) {
		return;
	}

	try
	{
		if (m_context.bookController().removeBook(bookId))
		{
			showInfo("删除成功");
			refresh();
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

void BookPage::refresh() {
	refreshBooksTable(m_context.bookController().getAllBooks());
}

void BookPage::refreshBooksTable(const std::vector<BookDTO>& books)
{
	bookTable->clearContents();

	bookTable->setRowCount(static_cast<int>(books.size()));

	for (int row = 0; row < books.size(); ++row)
	{
		const auto& book = books[row];

		bookTable->setItem(row, 0, new QTableWidgetItem(QString::number(book.id)));

		bookTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(book.isbn)));

		bookTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(book.title)));

		bookTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(book.author)));

		bookTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(book.publisher)));

		bookTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(book.category)));

		bookTable->setItem(row, 6, new QTableWidgetItem(QString::number(book.publishYear)));

		bookTable->setItem(row, 7, new QTableWidgetItem(QString::number(book.price)));

		bookTable->setItem(row, 8, new QTableWidgetItem(QString::fromStdString(book.coverUrl)));

		bookTable->setItem(row, 9, new QTableWidgetItem(QString::fromStdString(book.description)));

		bookTable->setItem(row, 10, new QTableWidgetItem(QString::fromStdString(book.status)));
	}
}

void BookPage::onSortPriceClicked() {
	try
	{
		auto books = m_context.bookController().getBooksSortedByPrice();
		refreshBooksTable(books);
	}
	catch (const std::exception& e)
	{
		showWarning(e.what());
	}
}

void BookPage::onSortTitleClicked() {
	auto books = m_context.bookController().getBooksSortedByTitle();
	refreshBooksTable(books);
}

void BookPage::onFindByTitleClicked() {
	QString keyword = searchEdit->text();
	searchEdit->clear();
	auto books = m_context.bookController().findBooksByTitle(keyword.toStdString());
	refreshBooksTable(books);
}

void BookPage::onBorrowBookClicked()
{
	int userId = m_context.sessionManager().currentUser().id;
	auto items = bookTable->selectedItems();
	if (items.isEmpty()) {
		showWarning("请先选择一本图书");
		return;
	}
	auto row = bookTable->currentRow();
	int bookId = bookTable->item(row, 0)->text().toInt();

	try
	{
		m_context.borrowController().borrowBook(userId, bookId);

		refresh();

		showInfo("借书成功");
	}
	catch (const std::exception& e)
	{
		showError(e.what());
	}
}

void BookPage::onReturnBookClicked()
{
	int userId = m_context.sessionManager().currentUser().id;
	auto items = bookTable->selectedItems();
	if (items.isEmpty()) {
		showWarning("请先选择一本图书");
		return;
	}
	auto row = bookTable->currentRow();
	int bookId = bookTable->item(row, 0)->text().toInt();

	try
	{
		m_context.borrowController().returnBook(userId, bookId);

		refresh();

		showInfo("还书成功");
	}
	catch (const std::exception& e)
	{
		showError(e.what());
	}
}