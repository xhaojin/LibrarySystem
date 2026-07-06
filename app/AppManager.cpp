#include "app/AppManager.h"
#include "ui/dialogs/LoginDialog.h"

AppManager::AppManager() {
}

int AppManager::run(int argc, char* argv[]) {
	QApplication app(argc, argv);

	// 初始化数据库
	database = std::make_unique<SQLiteDatabase>();
	if (!database->open("library.db"))
		return -1;

	if (!database->initialize())
		return -1;

	userRepo = std::make_unique<SQLiteUserRepository>(*database);
	bookRepo = std::make_unique<SQLiteBookRepository>(*database);
	borrowRepo = std::make_unique<SQLiteBorrowRecordRepository>(*database);

	AuthService authService(*userRepo);

	AuthController authController(authService);

	LoginDialog loginDialog(authController);

	if (loginDialog.exec() != QDialog::Accepted)
		return 0;

	bookService = std::make_unique<BookService>(*bookRepo);
	userService = std::make_unique<UserService>(*userRepo);
	borrowService = std::make_unique<BorrowService>(*bookRepo, *userRepo, *borrowRepo);

	bookController = std::make_unique<BookController>(*bookService);
	userController = std::make_unique<UserController>(*userService);
	borrowController = std::make_unique<BorrowController>(*borrowService);

	mainWindow = std::make_unique<MainWindow>(*bookController, *userController, *borrowController);

	mainWindow->show();

	return app.exec();
}