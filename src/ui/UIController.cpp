#include "ui/UIController.h"
#include "utils/Logger.h"
#include <stdexcept>

UIController::UIController(LibraryService& s)
	: service(s)
{
}

void UIController::borrowBook(int userId, int bookId)
{
	try
	{
		service.borrowBook(userId, bookId);
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
		service.returnBook(userId, bookId);
	}
	catch (const std::exception& e)
	{
		Logger::log(std::string("[UI_ERROR] ") + e.what());
		throw;
	}
}

std::vector<BookDTO> UIController::getAllBooks() const
{
	return service.getAllBooksDTO();
}

std::vector<UserDTO> UIController::getAllUsers() const
{
	return service.getAllUsersDTO();
}

std::vector<BookDTO> UIController::searchBooksByTitle(const std::string& keyword)
{
	try
	{
		return service.findBooksByTitle(keyword);
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
		return service.getBooksSortedByPrice();
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
		return service.getBooksSortedByTitle();
	}
	catch (const std::exception& e)
	{
		Logger::log(std::string("[UI_ERROR] ") + e.what());
		throw;
	}
}

UserDTO UIController::login(const std::string& username, const std::string& password)
{
	try
	{
		auto user = service.login(username, password);
		return user;
	}
	catch (const std::exception& e)
	{
		Logger::log(std::string("[UI_ERROR] ") + e.what());
		throw;
	}
}