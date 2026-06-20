#include "Library.h"
#include "BookDTO.h"
#include "UserDTO.h"

class LibraryService
{
private:
	Library& library; //图书馆的实例，使用引用以便在类中访问图书馆的成员

public:

	LibraryService(Library& library); //构造函数，接受一个Library实例的引用

	void borrowBook(int userId, int bookId); //借书

	void returnBook(int userId, int bookId);  //还书

	std::vector<BookDTO> findBooksByTitle(const std::string& keyword); //根据关键词模糊查找书籍

	std::vector<BookDTO> getBooksSortedByPrice() const; //根据价格排序书籍

	std::vector<BookDTO> getBooksSortedByTitle() const; //根据标题排序书籍

	int getTotalBooks() const; //获取图书馆总书籍数量
	int getBorrowedBooksCount() const; //获取已借出的书籍数量
	int getAvailableBooksCount() const; //获取可借阅的书籍数量
	int getUserCount() const; //获取图书馆总用户数量
	double getBorrowRate() const; //获取图书馆的借阅率

	std::vector<BookDTO> getAllBooksDTO() const; //获取所有书籍的DTO列表
	std::vector<UserDTO> getAllUsersDTO() const; //获取所有用户的DTO列表
};