#include <QApplication>

#include "ui/MainWindow.h"
#include "ui/LoginWindow.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include "../include/repository/SQLite/SQLiteDatabase.h"
#include "../include/repository/SQLite/SQLiteBookRepository.h"
#include "../include/repository/SQLite/SQLiteBorrowRecordRepository.h"
#include "../include/repository/SQLite/SQLiteUserRepository.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	// 数据层
	SQLiteDatabase database;
	if (!database.open("library.db"))
	{
		qDebug() << "open failed";
		return -1;
	}

	if (!database.initialize())
	{
		qDebug() << "init failed";
		return -1;
	}
	SQLiteBookRepository bookRepo(database);
	SQLiteUserRepository userRepo(database);
	SQLiteBorrowRecordRepository borrowRepo(database);

	// 业务层
	LibraryService service(bookRepo, userRepo, borrowRepo);

	// 控制层
	UIController controller(service);

	// UI层
	LoginWindow loginwindow(controller);
	loginwindow.show();	

	return app.exec();
}