#include <QApplication>

#include "MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // 数据层
    Library library;

    library.loadBooksFromFile("books.csv");
    library.loadUsersFromFile("users.csv");

    // 业务层
    LibraryService service(library);

    // 控制层
    UIController controller(service);

    // UI层
    MainWindow window(controller);
    window.show();

    return app.exec();
}