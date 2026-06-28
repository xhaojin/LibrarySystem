#include "ui/MainWindow.h"

MainWindow::MainWindow(UIController& controller, QWidget* parent) : QMainWindow(parent), controller(controller)
{
	setupUI();

	applyRolePermission();

	refreshBooksTable();
	refreshBorrowRecordTable();
	refreshUsersTable();
}

void MainWindow::setupUI()
{
	auto* centralWidget = new QWidget(this);
	setCentralWidget(centralWidget);

	auto* rootLayout = new QHBoxLayout(centralWidget);

	// =========================
	// 1. 左侧导航栏（菜单）
	// =========================
	auto* navLeftLayout = new QVBoxLayout();

	bookBtn = new QPushButton("图书管理");
	userBtn = new QPushButton("用户管理");
	borrowBtn = new QPushButton("借阅记录管理");

	navLeftLayout->addWidget(bookBtn);
	navLeftLayout->addWidget(userBtn);
	navLeftLayout->addWidget(borrowBtn);
	navLeftLayout->addStretch(); // ⭐关键：把按钮顶上去

	rootLayout->addLayout(navLeftLayout,1);

	// =========================
	// 2. stackedWidget
	// =========================
	stackedWidget = new QStackedWidget(centralWidget);

	// =========================
	// Book Page
	// =========================
	bookpage = new BookPage(stackedWidget);
	//auto* bookLayout = new QVBoxLayout(bookPage);

	//bookLayout->addWidget(new QLabel("图书管理"));

	//// 工具栏
	//auto* toolbar = new QHBoxLayout();

	//addBookButton = new QPushButton("添加图书");
	//removeBookButton = new QPushButton("删除图书");
	//updateBookButton = new QPushButton("更新图书");
	//borrowButton = new QPushButton("借阅书籍");
	//returnButton = new QPushButton("归还书籍");
	//refreshBookButton = new QPushButton("刷新");

	//toolbar->addWidget(addBookButton);
	//toolbar->addWidget(removeBookButton);
	//toolbar->addWidget(updateBookButton);
	//toolbar->addSpacing(20);
	//toolbar->addWidget(borrowButton);
	//toolbar->addWidget(returnButton);
	//toolbar->addStretch();
	//toolbar->addWidget(refreshBookButton);

	//bookLayout->addLayout(toolbar);

	////搜索排序栏
	//auto* searchbar = new QHBoxLayout();
	//searchbar->addWidget(new QLabel("图书名称："));
	//searchEdit = new QLineEdit();
	//searchEdit->setPlaceholderText("请输入书名");
	//searchButton = new QPushButton("搜索");
	//sortTitleButton = new QPushButton("标题排序");
	//sortPriceButton = new QPushButton("价格排序");
	//searchbar->addWidget(searchEdit);
	//searchbar->addWidget(searchButton);
	//searchbar->addStretch();
	//searchbar->addWidget(sortTitleButton);
	//searchbar->addWidget(sortPriceButton);
	//bookLayout->addLayout(searchbar);

	////表格
	//bookTable = new QTableWidget(bookPage);
	//bookTable->setColumnCount(6);
	//bookTable->setHorizontalHeaderLabels({"Book ID","Title","Author","Publisher","Price","Status"});
	//bookTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//bookLayout->addWidget(bookTable);

	// =========================
	// User Page
	// =========================
	QWidget* userPage = new QWidget(stackedWidget);
	auto* userLayout = new QVBoxLayout(userPage);

	userTable = new QTableWidget(userPage);
	userLayout->addWidget(userTable);

	userTable->setColumnCount(8);
	userTable->setHorizontalHeaderLabels({"User ID","name","gender","age","phone","username","role","borrowedCount"});
	userTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	// =========================
	// Borrow Page
	// =========================
	QWidget* borrowPage = new QWidget(stackedWidget);
	auto* borrowLayout = new QVBoxLayout(borrowPage);

	borrowRecordTable = new QTableWidget(borrowPage);
	borrowLayout->addWidget(borrowRecordTable);

	borrowRecordTable->setColumnCount(5);
	borrowRecordTable->setHorizontalHeaderLabels({"BorrowRecord ID","user_id","book_id","borrow_time","return_time"});
	borrowRecordTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	// =========================
	// 加入 stackedWidget
	// =========================
	stackedWidget->addWidget(bookpage);
	stackedWidget->addWidget(userPage);
	stackedWidget->addWidget(borrowPage);

	rootLayout->addWidget(stackedWidget,4);

	// =========================
	// 默认页面
	// =========================
	stackedWidget->setCurrentIndex(0);

	// =========================
	// 信号槽（导航切换）
	// =========================
	connect(bookBtn, &QPushButton::clicked, this, [=] {stackedWidget->setCurrentIndex(0);});

	connect(userBtn, &QPushButton::clicked, this, [=] {stackedWidget->setCurrentIndex(1);});

	connect(borrowBtn, &QPushButton::clicked, this, [=] {stackedWidget->setCurrentIndex(2);});

	connect(bookpage, &BookPage::refreshRequested, this, &MainWindow::refreshBooksTable);

	// =========================
	// 窗口属性（最后统一设置）
	// =========================
	setWindowTitle("Library System");
	resize(900, 600);
}

void MainWindow::applyRolePermission() {
	auto role = SessionManager::currentUser().role;
	bool isAdmin = SessionManager::isAdmin();
	//addBookButton->setVisible(isAdmin);
	//removeBookButton->setVisible(isAdmin);
	//updateBookButton->setVisible(isAdmin);
	//addUserButton->setVisible(isAdmin);
	//removeUserButton->setVisible(isAdmin);
	//updateUserButton->setVisible(isAdmin);
}

void MainWindow::refreshBooksTable() {
	bookpage->refreshBooks(controller.getAllBooks());
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
	//showBooks(books);
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

//void MainWindow::showBooks(const std::vector<BookDTO>& books)
//{
	//bookTable->clearContents();

	//bookTable->setRowCount(static_cast<int>(books.size()));

	//for (int row = 0; row < books.size(); ++row)
	//{
	//	const auto& book = books[row];

	//	bookTable->setItem(row, 0, new QTableWidgetItem(QString::number(book.id)));

	//	bookTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(book.title)));

	//	bookTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(book.author)));

	//	bookTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(book.publisher)));

	//	bookTable->setItem(row, 4, new QTableWidgetItem(QString::number(book.price)));

	//	bookTable->setItem(row, 5, new QTableWidgetItem(book.isBorrowed ? "已借出" : "可借阅"));
	//}
//}

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
		//showBooks(books);
	}
	catch (const std::exception& e)
	{
		QMessageBox::warning(this, "", e.what());
	}
}

void MainWindow::onSortTitleClicked() {
	auto books = controller.getBooksSortedByTitle();
	//showBooks(books);
}