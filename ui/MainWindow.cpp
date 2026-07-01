#include "ui/MainWindow.h"

MainWindow::MainWindow(UIController& controller, QWidget* parent) : QMainWindow(parent), controller(controller)
{
	setupUI();

	//applyRolePermission();

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

	bookMenuBtn = new QPushButton("图书管理");
	userMenuBtn = new QPushButton("用户管理");
	borrowMenuBtn = new QPushButton("借阅记录管理");

	navLeftLayout->addWidget(bookMenuBtn);
	navLeftLayout->addWidget(userMenuBtn);
	navLeftLayout->addWidget(borrowMenuBtn);
	navLeftLayout->addStretch(); // ⭐关键：把按钮顶上去

	rootLayout->addLayout(navLeftLayout, 1);

	// =========================
	// 2. stackedWidget
	// =========================
	stackedWidget = new QStackedWidget(centralWidget);

	// =========================
	// Book Page
	// =========================
	bookpage = new BookPage();

	// =========================
	// User Page
	// =========================
	userpage = new UserPage();

	// =========================
	// Borrow Page
	// =========================
	borrowpage = new BorrowRecordPage();

	// =========================
	// 加入 stackedWidget
	// =========================
	stackedWidget->addWidget(bookpage);
	stackedWidget->addWidget(userpage);
	stackedWidget->addWidget(borrowpage);

	rootLayout->addWidget(stackedWidget, 4);

	// =========================
	// 默认页面
	// =========================
	stackedWidget->setCurrentIndex(0);

	// =========================
	// 信号槽（导航切换）
	// =========================
	connect(bookMenuBtn, &QPushButton::clicked, this, [=] {stackedWidget->setCurrentIndex(0);});

	connect(userMenuBtn, &QPushButton::clicked, this, [=] {stackedWidget->setCurrentIndex(1);});

	connect(borrowMenuBtn, &QPushButton::clicked, this, [=] {stackedWidget->setCurrentIndex(2);});

	connect(bookpage, &BookPage::refreshRequested, this, &MainWindow::refreshBooksTable);

	connect(userpage, &UserPage::refreshRequested, this, &MainWindow::refreshUsersTable);

	connect(borrowpage, &BorrowRecordPage::refreshRequested, this, &MainWindow::refreshBorrowRecordTable);

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
	userpage->refreshUsers(controller.getAllUsers());
}
void MainWindow::refreshBorrowRecordTable() {
	borrowpage->refreshBorrowRecords(controller.getAllBorrowRecords());
	//showBorrowRecords(controller.getAllBorrowRecords());
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
	//QString keyword = searchEdit->text();
	//searchEdit->clear();
	//auto books = controller.findBooksByTitle(keyword.toStdString());
	////showBooks(books);
}

void MainWindow::onTableCellClicked(int row, int column) {
	//if (column == 0) // Book ID列
	//{
	//	auto* item = bookTable->item(row, 0);
	//	if (item)
	//	{
	//		int bookId = item->text().toInt();
	//		bookIdEdit->setText(QString::number(bookId));
	//	}
	//}
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