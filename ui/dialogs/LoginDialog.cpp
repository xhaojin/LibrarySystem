#include "LoginDialog.h"

LoginDialog::LoginDialog(AuthController& authController, QWidget* parent)
	: QDialog(parent), authController(authController)
{
	setWindowTitle("Library Login");
	resize(300, 200);

	auto* layout = new QVBoxLayout(this);

	layout->addWidget(new QLabel("Username"));

	usernameEdit = new QLineEdit;
	layout->addWidget(usernameEdit);

	layout->addWidget(new QLabel("Password"));

	passwordEdit = new QLineEdit;
	passwordEdit->setEchoMode(QLineEdit::Password);

	layout->addWidget(passwordEdit);

	loginButton = new QPushButton("Login");

	layout->addWidget(loginButton);

	connect(loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);

	//测试阶段打开
	usernameEdit->setText("admin");
	passwordEdit->setText("admin123");
}

void LoginDialog::onLoginClicked()
{
	try
	{
		auto result = authController.login(usernameEdit->text().toStdString(), passwordEdit->text().toStdString());

		switch (result.status)
		{
		case LoginStatus::Success:
			if (result.user.has_value()) m_authenticatedUser = *result.user;
			accept();
			break;

		case LoginStatus::UserNotFound:
			QMessageBox::warning(this, "登录失败", "用户名不存在");
			break;

		case LoginStatus::WrongPassword:
			QMessageBox::warning(this, "登录失败", "密码错误");
			break;

		case LoginStatus::Disabled:
			QMessageBox::warning(this, "登录失败", "账号已被禁用");
			break;

		case LoginStatus::DatabaseError:
			QMessageBox::critical(this, "登录失败", "数据库连接异常");
			break;
		}
	}
	catch (const std::exception& e)
	{
		QMessageBox::warning(this, "Error", e.what());
	}
}

const std::optional<UserDTO>& LoginDialog::authenticatedUser() const {
	return m_authenticatedUser;
}