#include "LoginWindow.h"

LoginWindow::LoginWindow(AuthController& authController, QWidget* parent)
	: QWidget(parent), authController(authController)
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

	connect(loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
}

void LoginWindow::onLoginClicked()
{
	try
	{
		auto user = authController.login(usernameEdit->text().toStdString(), passwordEdit->text().toStdString());
		SessionManager::login(user);
		//QMessageBox::information(this, "Success", QString::fromStdString(user.name));
		emit loginSuccess();
	}
	catch (const std::exception& e)
	{
		QMessageBox::warning(this, "Error", e.what());
	}
}