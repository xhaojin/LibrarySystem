#include "ui/mainWindow/MainWindow.h"

MainWindow::MainWindow(ApplicationContext& context, QWidget* parent) : m_context(context), QMainWindow(parent)
{
	setupUI();
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
	bookpage = new BookPage(m_context.bookController(), m_context.borrowController());

	// =========================
	// User Page
	// =========================
	userpage = new UserPage(m_context.userController());

	// =========================
	// Borrow Page
	// =========================
	borrowpage = new BorrowRecordPage(m_context.borrowController());

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
	connect(bookMenuBtn, &QPushButton::clicked, this, [=] {stackedWidget->setCurrentIndex(0); bookpage->refresh();});

	connect(userMenuBtn, &QPushButton::clicked, this, [=] {stackedWidget->setCurrentIndex(1); userpage->refresh();});

	connect(borrowMenuBtn, &QPushButton::clicked, this, [=] {stackedWidget->setCurrentIndex(2); borrowpage->refresh();});

	// =========================
	// 窗口属性（最后统一设置）
	// =========================
	setWindowTitle("Library System");
	resize(900, 600);
}