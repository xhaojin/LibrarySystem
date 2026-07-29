#include "app/AppManager.h"
#include "ui/dialogs/LoginDialog.h"

AppManager::AppManager() {
}

int AppManager::run(int argc, char* argv[]) {
	QApplication app(argc, argv);

	context = std::make_unique<ApplicationContext>();

	if (!context->initialize())
		return -1;

	if (!showLoginDialog())
		return 0;

	createMainWindow();

	mainWindow->show();

	return app.exec();
}

void AppManager::createMainWindow() {
	mainWindow = std::make_unique<MainWindow>(*context);
}
bool AppManager::showLoginDialog() {
	AuthService authService(context->userRepository());

	AuthController authController(authService);

	LoginDialog loginDialog(authController);

	if (loginDialog.exec() != QDialog::Accepted)
	{
		return false;
	}

	context->sessionManager().login(*loginDialog.authenticatedUser());
	return true;
}