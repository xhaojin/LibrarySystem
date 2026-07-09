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
}

void LoginDialog::onLoginClicked()
{
	try
	{
		auto user = authController.login(usernameEdit->text().toStdString(), passwordEdit->text().toStdString());
		if (user.has_value())
		{
			m_authenticatedUser = *user;

			accept();
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