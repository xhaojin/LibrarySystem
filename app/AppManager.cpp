#include "app/AppManager.h"
#include "ui/dialogs/LoginDialog.h"
#include "database/mysql/MySQLDatabase.h"

AppManager::AppManager() {
}

int AppManager::run(int argc, char* argv[]) {
	QApplication app(argc, argv);

	DBConfig config;

	config.host = "127.0.0.1";
	config.port = 3306;
	config.database = "library";
	config.username = "root";
	config.password = "1234";

	MySQLDatabase db(config);

	if (db.connect())
	{
		std::cout << "连接成功！" << std::endl;
	}
	else
	{
		std::cout << "连接失败！" << std::endl;
	}

	//context = std::make_unique<ApplicationContext>();

	//if (!context->initialize())
	//	return -1;

	//if (!showLoginDialog())
	//	return 0;

	//createMainWindow();

	//mainWindow->show();

	return app.exec();
}

void AppManager::createMainWindow() {
	mainWindow = std::make_unique<MainWindow>(*context);
}
bool AppManager::showLoginDialog() {
	//AuthService authService(context->userRepository());

	//AuthController authController(authService);

	//LoginDialog loginDialog(authController);

	//if (loginDialog.exec() != QDialog::Accepted)
	//{
	//	return false;
	//}

	//context->sessionManager().login(*loginDialog.authenticatedUser());
	return true;
}