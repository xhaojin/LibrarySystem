#include "Library.h"

using namespace std;

int main()
{
    cout << "===== Library System Test =====" << endl;


    // 创建图书馆
    Library library;
    
    library.loadBooksFromFile("books.csv"); // 从文件加载书籍信息
    library.loadUsersFromFile("users.csv"); // 从文件加载用户信息
    library.restoreBorrowStatus(); // 恢复书籍的借阅状态

    cout << "\nBooks in library:" << endl;
    library.showAllBooks();

    cout << "\nUsers in library:" << endl;
    library.showAllUsers();

    // ======================
    // 测试文件保存
    // ======================

    cout << "\nSaving data..." << endl;

    if (library.saveUsersToFile("users.csv")) {
        cout<<"Users saved successfully." << endl;
    }

    if (library.saveBooksToFile("books.csv")) {
        cout << "Books saved successfully." << endl;
    }


    cout << "Finish!" << endl;


    return 0;
}