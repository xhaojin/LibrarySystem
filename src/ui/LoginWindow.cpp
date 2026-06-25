#include "ui/LoginWindow.h"

LoginWindow::LoginWindow(UIController& controller, QWidget* parent)
	: QWidget(parent), controller(controller)
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
		auto user = controller.login(usernameEdit->text().toStdString(), passwordEdit->text().toStdString());
		SessionManager::login(user);
		QMessageBox::information(this, "Success", QString::fromStdString(user.name));
		mainWindow = std::make_unique<MainWindow>(controller);
		mainWindow->show();
		this->close();
	}
	catch (const std::exception& e)
	{
		QMessageBox::warning(this, "Error", e.what());
	}
}