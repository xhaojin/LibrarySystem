#include "../../../include/ui/pages/BookPage.h"

BookPage::BookPage(QWidget* parent)
{
	setupUI();
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
	bookTable->setColumnCount(6);
	bookTable->setHorizontalHeaderLabels({ "Book ID","Title","Author","Publisher","Price","Status" });
	bookTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	bookLayout->addWidget(bookTable);
}

void BookPage::refreshBooks(const std::vector<BookDTO>& books)
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