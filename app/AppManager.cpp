#include "app/AppManager.h"

AppManager::AppManager() {
}

int AppManager::run(int argc, char* argv[]) {
	QApplication app(argc, argv);

	// 初始化数据库
	database = std::make_unique<SQLiteDatabase>();
	if (!database->open("library.db"))
	{
		return -1;
	}

	if (!database->initialize())
	{
		return -1;
	}

	bookRepo = std::make_unique<SQLiteBookRepository>(*database);
	userRepo = std::make_unique<SQLiteUserRepository>(*database);
	borrowRepo = std::make_unique<SQLiteBorrowRecordRepository>(*database);

	bookService = std::make_unique<BookService>(*bookRepo);
	userService = std::make_unique<UserService>(*userRepo);
	borrowService = std::make_unique<BorrowService>(*bookRepo, *userRepo, *borrowRepo);
	controller = std::make_unique<UIController>(*bookService,*userService,*borrowService);

	mainWindow = std::make_unique<MainWindow>(*controller);

	mainWindow->show();

	return app.exec();
}

void AppManager::onLoginSuccess() {

}