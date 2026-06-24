#include <QApplication>

#include "ui/MainWindow.h"
#include "ui/LoginWindow.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	// 数据层

	// 业务层


	// 控制层
	//UIController controller(service);

	// UI层
	//LoginWindow loginwindow(controller);
	//loginwindow.show();

	//test
	//SQLiteDatabase db;

	//if (!db.open("library.db"))
	//{
	//	qDebug() << "open failed";
	//	return -1;
	//}

	//if (!db.initialize())
	//{
	//	qDebug() << "init failed";
	//	return -1;
	//}

	//qDebug() << "database ready";

	return app.exec();
}