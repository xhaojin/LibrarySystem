#include <memory>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "Book.h"
#include "User.h"

class Library
{
private:
    std::unordered_map<int,std::shared_ptr<Book>> books; //图书馆的书籍集合，使用unordered_map以便快速查找

    std::unordered_map<int,std::shared_ptr<User>> users; //图书馆的用户集合，使用unordered_map以便快速查找

public:
    bool addBook(std::shared_ptr<Book> book); //添加书籍

	bool addUser(std::shared_ptr<User> user); //添加用户

	void removeBook(int bookId); //删除书籍

	void removeUser(int userId); //删除用户

	std::shared_ptr<Book> findBook(int bookId) const; //查找书籍

	std::vector<std::shared_ptr<Book>> findBooksByTitle(const std::string& keyword) const; //根据关键词模糊查找书籍

	std::shared_ptr<User> findUser(int userId) const; //查找用户

	std::vector<std::shared_ptr<User>> findUsersByName(const std::string& keyword) const; //根据关键词模糊查找用户

	bool borrowBook(int userId, int bookId); //借书

	bool returnBook(int userId, int bookId);  //还书

	void showAllBooks() const;  //显示所有书籍

	void showAllUsers() const;  //显示所有用户

	bool saveBooksToFile(const std::string& filename) const; //将书籍信息保存到文件

	bool loadBooksFromFile(const std::string& filename); //从文件加载书籍信息

	bool saveUsersToFile(const std::string& filename) const; //将用户信息保存到文件

	bool loadUsersFromFile(const std::string& filename); //从文件加载用户信息

	void restoreBorrowStatus(); //根据用户的借阅记录恢复书籍的借阅状态

	std::vector<std::shared_ptr<Book>> getBooksSortedByPrice() const; //根据价格排序书籍

	std::vector<std::shared_ptr<Book>> getBooksSortedByTitle() const; //根据标题排序书籍

	int getTotalBooks() const; //获取图书馆总书籍数量
	int getBorrowedBooksCount() const; //获取已借出的书籍数量
	int getAvailableBooksCount() const; //获取可借阅的书籍数量
	int getUserCount() const; //获取图书馆总用户数量
	double getBorrowRate() const; //获取图书馆的借阅率
};