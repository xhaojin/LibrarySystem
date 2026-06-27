#include "app/AppManager.h"

AppManager::AppManager() {
}

int AppManager::run(int argc, char* argv[]) {
	QApplication app(argc, argv);

	// 初始化数据库
	database = std::make_unique<SQLiteDatabase>();
	if (!database->open("library.db") && !database->initialize())
	{
		return -1;
	}

	bookRepo = std::make_unique<SQLiteBookRepository>(*database);
	userRepo = std::make_unique<SQLiteUserRepository>(*database);
	borrowRepo = std::make_unique<SQLiteBorrowRecordRepository>(*database);
	service = std::make_unique<LibraryService>(*bookRepo, *userRepo, *borrowRepo);
	controller = std::make_unique<UIController>(*service);
	loginWindow = std::make_unique<LoginWindow>(*controller);

	loginWindow->show();

	connect(loginWindow.get(), &LoginWindow::loginSuccess, this, &AppManager::onLoginSuccess);

	return app.exec();
}

void AppManager::onLoginSuccess() {
	loginWindow->close();
	mainWindow = std::make_unique<MainWindow>(*controller);
	mainWindow->show();
}