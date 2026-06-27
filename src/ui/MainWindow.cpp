#include "ui/MainWindow.h"

MainWindow::MainWindow(UIController& controller, QWidget* parent) : QMainWindow(parent), controller(controller)
{
	setupUI();

	setupPermissions();

	refreshBooksTable();
	refreshBorrowRecordTable();
	refreshUsersTable();
}

void MainWindow::setupUI()
{
	auto* centralWidget = new QWidget(this);

	setCentralWidget(centralWidget);

	auto* mainLayout = new QVBoxLayout(centralWidget);

	//------------------------
	// 用户ID
	//------------------------

	auto* userLayout = new QHBoxLayout();

	userLayout->addWidget(new QLabel("User ID:"));

	userIdEdit = new QLineEdit();

	userLayout->addWidget(userIdEdit);

	mainLayout->addLayout(userLayout);

	//------------------------
	// 图书ID
	//------------------------

	auto* bookLayout = new QHBoxLayout();

	bookLayout->addWidget(new QLabel("Book ID:"));

	bookIdEdit = new QLineEdit();

	bookLayout->addWidget(bookIdEdit);

	mainLayout->addLayout(bookLayout);

	//------------------------
	// 按钮(借书，还书，刷新，排序)
	//------------------------

	auto* buttonLayout1 = new QHBoxLayout();

	borrowButton = new QPushButton("Borrow");

	returnButton = new QPushButton("Return");

	refreshBookButton = new QPushButton("RefreshBook");

	refreshUserButton = new QPushButton("RefreshUser");

	refreshBorrowRecordButton = new QPushButton("RefreshBorrowRecord");

	sortPriceButton = new QPushButton("Sort by Price");

	sortTitleButton = new QPushButton("Sort by Title");

	buttonLayout1->addWidget(borrowButton);
	buttonLayout1->addWidget(returnButton);
	buttonLayout1->addWidget(refreshBookButton);
	buttonLayout1->addWidget(refreshUserButton);
	buttonLayout1->addWidget(refreshBorrowRecordButton);
	buttonLayout1->addWidget(sortPriceButton);
	buttonLayout1->addWidget(sortTitleButton);

	mainLayout->addLayout(buttonLayout1);

	//------------------------
	// 搜索
	//------------------------

	auto* searchLayout = new QHBoxLayout();

	searchLayout->addWidget(new QLabel("SearchByTitle:"));

	searchEdit = new QLineEdit();

	searchButton = new QPushButton("Search");

	searchLayout->addWidget(searchEdit);
	searchLayout->addWidget(searchButton);

	mainLayout->addLayout(searchLayout);

	//------------------------
	// 按钮(添加书，删除书，修改书)
	//------------------------

	auto* buttonLayout2 = new QHBoxLayout();

	addBookButton = new QPushButton("AddBook");

	removeBookButton = new QPushButton("RemoveBook");

	updateBookButton = new QPushButton("UpdateBook");

	buttonLayout2->addWidget(addBookButton);
	buttonLayout2->addWidget(removeBookButton);
	buttonLayout2->addWidget(updateBookButton);

	mainLayout->addLayout(buttonLayout2);

	//------------------------
	// 按钮(添加用户，删除用户，修改用户)
	//------------------------

	auto* buttonLayout3 = new QHBoxLayout();

	addUserButton = new QPushButton("AddUser");

	removeUserButton = new QPushButton("RemoveUser");

	updateUserButton = new QPushButton("UpdateUser");

	buttonLayout3->addWidget(addUserButton);
	buttonLayout3->addWidget(removeUserButton);
	buttonLayout3->addWidget(updateUserButton);

	mainLayout->addLayout(buttonLayout3);

	//------------------------
	// 图书表格
	//------------------------

	bookTable = new QTableWidget();

	mainLayout->addWidget(bookTable);

	setWindowTitle("Library System");

	resize(900, 600);

	bookTable->setColumnCount(6);

	bookTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 设置列宽自适应

	bookTable->setHorizontalHeaderLabels({ "Book ID","Title","Author","Publisher","Price","Status" });

	//------------------------
	// 用户表格
	//------------------------

	userTable = new QTableWidget();

	mainLayout->addWidget(userTable);

	userTable->setColumnCount(8);

	userTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 设置列宽自适应

	userTable->setHorizontalHeaderLabels({ "User ID","name","gender","age","phone","username","role","borrowedCount"});

	//------------------------
	// 借阅记录表格
	//------------------------

	borrowRecordTable = new QTableWidget();

	mainLayout->addWidget(borrowRecordTable);

	borrowRecordTable->setColumnCount(5);

	borrowRecordTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 设置列宽自适应

	borrowRecordTable->setHorizontalHeaderLabels({ "BorrowRecord ID","user_id","book_id","borrow_time","return_time" });

	// 连接信号和槽

	connect(borrowButton, &QPushButton::clicked, this, &MainWindow::onBorrowClicked);

	connect(returnButton, &QPushButton::clicked, this, &MainWindow::onReturnClicked);

	connect(refreshBookButton, &QPushButton::clicked, this, &MainWindow::refreshBooksTable);

	connect(refreshUserButton, &QPushButton::clicked, this, &MainWindow::refreshUsersTable);

	connect(refreshBorrowRecordButton, &QPushButton::clicked, this, &MainWindow::refreshBorrowRecordTable);

	connect(searchButton, &QPushButton::clicked, this, &MainWindow::onFindByTitleClicked);

	connect(bookTable, &QTableWidget::cellClicked, this, &MainWindow::onTableCellClicked);

	connect(sortPriceButton, &QPushButton::clicked, this, &MainWindow::onSortPriceClicked);

	connect(sortTitleButton, &QPushButton::clicked, this, &MainWindow::onSortTitleClicked);

}

void MainWindow::setupPermissions() {
	auto role = SessionManager::currentUser().role;
	borrowButton->setVisible(true);
	returnButton->setVisible(true);
	refreshBookButton->setVisible(true);
	searchButton->setVisible(true);
	sortPriceButton->setVisible(true);
	sortTitleButton->setVisible(true);
}

void MainWindow::refreshBooksTable() {
	showBooks(controller.getAllBooks());
}

void MainWindow::refreshUsersTable() {
	showUsers(controller.getAllUsers());
}
void MainWindow::refreshBorrowRecordTable() {
	showBorrowRecords(controller.getAllBorrowRecords());
}

void MainWindow::onBorrowClicked()
{
	int userId = userIdEdit->text().toInt();

	int bookId = bookIdEdit->text().toInt();

	try
	{
		controller.borrowBook(userId, bookId);

		refreshBooksTable();

		QMessageBox::information(this, "成功", "借书成功");

		userIdEdit->clear();
		bookIdEdit->clear();
	}
	catch (const std::exception& e)
	{
		QMessageBox::warning(this, "借书失败", e.what());
	}
}

void MainWindow::onReturnClicked()
{
	int userId = userIdEdit->text().toInt();

	int bookId = bookIdEdit->text().toInt();

	try
	{
		controller.returnBook(userId, bookId);

		refreshBooksTable();

		QMessageBox::information(this, "成功", "还书成功");

		userIdEdit->clear();
		bookIdEdit->clear();
	}
	catch (const std::exception& e)
	{
		QMessageBox::warning(this, "还书失败", e.what());
	}
}

void MainWindow::onFindByTitleClicked() {
	QString keyword = searchEdit->text();
	searchEdit->clear();
	auto books = controller.findBooksByTitle(keyword.toStdString());
	showBooks(books);
}

void MainWindow::onTableCellClicked(int row, int column) {
	if (column == 0) // Book ID列
	{
		auto* item = bookTable->item(row, 0);
		if (item)
		{
			int bookId = item->text().toInt();
			bookIdEdit->setText(QString::number(bookId));
		}
	}
}

void MainWindow::showBooks(const std::vector<BookDTO>& books)
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

void MainWindow::showUsers(const std::vector<UserDTO>& users)
{
	userTable->clearContents();

	userTable->setRowCount(static_cast<int>(users.size()));

	for (int row = 0; row < users.size(); ++row)
	{
		const auto& user = users[row];

		userTable->setItem(row, 0, new QTableWidgetItem(QString::number(user.id)));

		userTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(user.name)));

		userTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(user.gender)));

		userTable->setItem(row, 3, new QTableWidgetItem(QString::number(user.age)));

		userTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(user.phone)));

		userTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(user.username)));

		userTable->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(user.role == Role::Admin ? "Admin" : "User")));

		userTable->setItem(row, 7, new QTableWidgetItem(QString::number(user.borrowedCount)));
	}
}

void MainWindow::showBorrowRecords(const std::vector<BorrowRecordDTO>& record)
{
	borrowRecordTable->clearContents();

	borrowRecordTable->setRowCount(static_cast<int>(record.size()));

	for (int row = 0; row < record.size(); ++row)
	{
		const auto& re = record[row];

		borrowRecordTable->setItem(row, 0, new QTableWidgetItem(QString::number(re.id)));

		borrowRecordTable->setItem(row, 1, new QTableWidgetItem(QString::number(re.userId)));

		borrowRecordTable->setItem(row, 2, new QTableWidgetItem(QString::number(re.bookId)));

		borrowRecordTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(re.borrowTime)));

		borrowRecordTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(re.returnTime)));
	}
}

void MainWindow::onSortPriceClicked() {
	try
	{
		auto books = controller.getBooksSortedByPrice();
		showBooks(books);
	}
	catch (const std::exception& e)
	{
		QMessageBox::warning(this, "", e.what());
	}
}

void MainWindow::onSortTitleClicked() {
	auto books = controller.getBooksSortedByTitle();
	showBooks(books);
}