#include "UserPage.h"

UserPage::UserPage(UserController& userController, QWidget* parent) : userController(userController), QWidget(parent)
{
	setupUI();
	setConnections();
	refreshUsersTable(userController.getAllUsers());
}

void UserPage::setupUI() {
	auto* userLayout = new QVBoxLayout(this);

	userLayout->addWidget(new QLabel("用户管理"));

	// 工具栏
	auto* toolbar = new QHBoxLayout();

	addUserButton = new QPushButton("添加用户");
	removeUserButton = new QPushButton("删除用户");
	updateUserButton = new QPushButton("更新用户");
	refreshUserButton = new QPushButton("刷新");

	toolbar->addWidget(addUserButton);
	toolbar->addWidget(removeUserButton);
	toolbar->addWidget(updateUserButton);
	toolbar->addStretch();
	toolbar->addWidget(refreshUserButton);
	userLayout->addLayout(toolbar);

	//搜索排序栏
	auto* searchbar = new QHBoxLayout();
	searchbar->addWidget(new QLabel("用户名："));
	searchEdit = new QLineEdit();
	searchEdit->setPlaceholderText("请输入用户名");
	searchButton = new QPushButton("搜索");
	searchbar->addWidget(searchEdit);
	searchbar->addWidget(searchButton);
	userLayout->addLayout(searchbar);

	userTable = new QTableWidget(this);
	userTable->setColumnCount(8);
	userTable->setHorizontalHeaderLabels({ "User ID","name","gender","age","phone","username","role","borrowedCount" });
	userTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	userLayout->addWidget(userTable);
}

void UserPage::setConnections() {
	connect(refreshUserButton, &QPushButton::clicked, this, [this]() {
		auto users = userController.getAllUsers();
		refreshUsersTable(users);
		});
}

void UserPage::refreshUsersTable(const std::vector<UserDTO>& users)
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