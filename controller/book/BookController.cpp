#include "BookController.h"

BookController::BookController(BookService& bookService):bookService(bookService) {

}

std::vector<BookDTO> BookController::findBooksByTitle(const std::string& keyword)
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

std::vector<BookDTO> BookController::getBooksSortedByPrice() const {
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

std::vector<BookDTO> BookController::getBooksSortedByTitle() const {
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

std::vector<BookDTO> BookController::getAllBooks() const
{
	return bookService.getAllBooksDTO();
}