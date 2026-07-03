#include "BookController.h"

BookController::BookController(BookService& bookService):bookService(bookService) {

}

bool BookController::addBook(const BookDTO& dto) {
	try
	{
		return bookService.addBook(dto);
	}
	catch (const std::exception& e)
	{
		Logger::log(std::string("[UI_ERROR] ") + e.what());
		throw;
	}
}
bool BookController::updateBook(const BookDTO& dto) {
	try
	{
		return bookService.updateBook(dto);
	}
	catch (const std::exception& e)
	{
		Logger::log(std::string("[UI_ERROR] ") + e.what());
		throw;
	}
}
bool BookController::removeBook(int bookId) {
	try
	{
		return bookService.removeBook(bookId);
	}
	catch (const std::exception& e)
	{
		Logger::log(std::string("[UI_ERROR] ") + e.what());
		throw;
	}
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

BookDTO BookController::findBookById(int bookId) const {
	try
	{
		return bookService.findBookById(bookId);
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