#include "UIController.h"
#include "common/utils/Logger.h"
#include <stdexcept>

UIController::UIController(BookService& bookService, UserService& userService, BorrowService& borrowService)
	: bookService(bookService), userService(userService), borrowService(borrowService)
{
}

void UIController::borrowBook(int userId, int bookId)
{
	try
	{
		borrowService.borrowBook(userId, bookId);
	}
	catch (const std::exception& e)
	{
		Logger::log(std::string("[UI_ERROR] ") + e.what());
		throw; // 继续抛给UI（Qt可显示弹窗）
	}
}

void UIController::returnBook(int userId, int bookId)
{
	try
	{
		borrowService.returnBook(userId, bookId);
	}
	catch (const std::exception& e)
	{
		Logger::log(std::string("[UI_ERROR] ") + e.what());
		throw;
	}
}

std::vector<BookDTO> UIController::getAllBooks() const
{
	return bookService.getAllBooksDTO();
}

std::vector<UserDTO> UIController::getAllUsers() const
{
	return userService.getAllUsersDTO();
}

std::vector<BorrowRecordDTO> UIController::getAllBorrowRecords() const {
	return borrowService.getAllBorrowRecords();
}

std::vector<BookDTO> UIController::findBooksByTitle(const std::string& keyword)
{
	try
	{
		return bookService.findBooksByTitle(keyword);
	}
	catch (const std::exception& e)
	{
		Logger::log(std::string("[UI_ERROR] ") + e.what());
		throw;
	}
}

std::vector<BookDTO> UIController::getBooksSortedByPrice() const {
	try
	{
		return bookService.getBooksSortedByPrice();
	}
	catch (const std::exception& e)
	{
		Logger::log(std::string("[UI_ERROR] ") + e.what());
		throw;
	}
}

std::vector<BookDTO> UIController::getBooksSortedByTitle() const {
	try
	{
		return bookService.getBooksSortedByTitle();
	}
	catch (const std::exception& e)
	{
		Logger::log(std::string("[UI_ERROR] ") + e.what());
		throw;
	}
}