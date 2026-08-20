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
	// 左侧导航栏（菜单）
	// =========================
	auto* navLeftLayout = new QVBoxLayout();

	rootLayout->addLayout(navLeftLayout, 1);

	// =========================
	// stackedWidget
	// =========================
	stackedWidget = new QStackedWidget(centralWidget);

	// =========================
	// 控制页面导航切换
	// =========================
	int pageId = 0;

	// =========================
	// Book Page
	// =========================
	bookMenuBtn = new QPushButton("图书管理");
	navLeftLayout->addWidget(bookMenuBtn);
	bookpage = new BookPage(m_context);
	stackedWidget->addWidget(bookpage);
	connect(bookMenuBtn, &QPushButton::clicked, this, [=] {stackedWidget->setCurrentIndex(pageId); bookpage->refresh();});
	pageId++;

	// =========================
	// User Page
	// =========================
	if (m_context.sessionManager().isAdmin()) {
		userMenuBtn = new QPushButton("用户管理");
		navLeftLayout->addWidget(userMenuBtn);
	//	userpage = new UserPage(m_context.userController());
	//	stackedWidget->addWidget(userpage);
	//	connect(userMenuBtn, &QPushButton::clicked, this, [=] {stackedWidget->setCurrentIndex(pageId); userpage->refresh();});
	//	pageId++;
	}

	// =========================
	// Borrow Page
	// =========================
	borrowMenuBtn = new QPushButton("借阅记录管理");
	navLeftLayout->addWidget(borrowMenuBtn);
	borrowpage = new BorrowPage(m_context);
	stackedWidget->addWidget(borrowpage);
	connect(borrowMenuBtn, &QPushButton::clicked, this, [=] {stackedWidget->setCurrentIndex(pageId); borrowpage->refresh();});
	pageId++;

	// =========================
	// Publisher Page
	// =========================
	publisherMenuBtn = new QPushButton("出版社管理");
	navLeftLayout->addWidget(publisherMenuBtn);
	publisherpage = new PublisherPage(m_context);
	stackedWidget->addWidget(publisherpage);
	connect(publisherMenuBtn, &QPushButton::clicked, this, [=] {stackedWidget->setCurrentIndex(pageId); publisherpage->refresh();});
	pageId++;

	// =========================
	// Category Page
	// =========================
	categoryMenuBtn = new QPushButton("分类管理");
	navLeftLayout->addWidget(categoryMenuBtn);
	categorypage = new CategoryPage(m_context);
	stackedWidget->addWidget(categorypage);
	connect(categoryMenuBtn, &QPushButton::clicked, this, [=] {stackedWidget->setCurrentIndex(pageId); categorypage->refresh();});
	pageId++;

	// =========================
	// 默认页面
	// =========================
	stackedWidget->setCurrentIndex(0);
	navLeftLayout->addStretch(); // ⭐关键：把按钮顶上去
	rootLayout->addWidget(stackedWidget, 4);

	// =========================
	// 窗口属性（最后统一设置）
	// =========================
	setWindowTitle(QString("欢迎您：%1！").arg(QString::fromStdString(m_context.sessionManager().currentUser().username)));
	resize(1200, 700);
}