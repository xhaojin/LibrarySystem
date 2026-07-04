#include "UserPage.h"

UserPage::UserPage(UserController& userController, QWidget* parent) : userController(userController), BasePage(parent)
{
	setupUI();
	setConnections();
	refresh();
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
	TableUtil::init(userTable);
	userTable->setColumnCount(8);
	userTable->setHorizontalHeaderLabels({ "User ID","name","gender","age","phone","username","role","borrowedCount" });
	userLayout->addWidget(userTable);
}

void UserPage::setConnections() {
	connect(refreshUserButton, &QPushButton::clicked, this, [this]() {refresh();});
	connect(addUserButton, &QPushButton::clicked, this, &UserPage::addUser);
	connect(updateUserButton, &QPushButton::clicked, this, &UserPage::updateUser);
	connect(removeUserButton, &QPushButton::clicked, this, &UserPage::removeUser);
	connect(searchButton, &QPushButton::clicked, this, &UserPage::onFindByNameClicked);
}

void UserPage::addUser() {
	UserEditDialog userEditDialog(this); //用户编辑对话框
	userEditDialog.setWindowTitle("添加用户");
	if (userEditDialog.exec() != QDialog::Accepted)
		return;
	try
	{
		if (userController.addUser(userEditDialog.getUser()))
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
void UserPage::updateUser() {
	auto items = userTable->selectedItems();
	if (items.isEmpty())
	{
		showWarning("请先选择一名用户");
		return;
	}
	int row = userTable->currentRow();
	int userId = userTable->item(row, 0)->text().toInt();
	auto user = userController.findUserById(userId);

	UserEditDialog userEditDialog(this);
	userEditDialog.setWindowTitle("修改用户");
	userEditDialog.setUser(user);

	if (userEditDialog.exec() != QDialog::Accepted)
		return;

	UserDTO dto = userEditDialog.getUser();
	dto.id = userId;

	try
	{
		if (userController.updateUser(dto))
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
void UserPage::removeUser() {
	auto items = userTable->selectedItems();
	if (items.isEmpty())
	{
		showWarning("请先选择一名用户");
		return;
	}
	int row = userTable->currentRow();
	int userId = userTable->item(row, 0)->text().toInt();
	auto user = userController.findUserById(userId);

	if (!confirmDelete(user.name.c_str())) {
		return;
	}

	try
	{
		if (userController.removeUser(userId))
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
void UserPage::onFindByNameClicked() {
	QString keyword = searchEdit->text();
	searchEdit->clear();
	auto users = userController.findUsersByName(keyword.toStdString());
	refreshUsersTable(users);
}

void UserPage::refresh()
{
	refreshUsersTable(userController.getAllUsers());
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