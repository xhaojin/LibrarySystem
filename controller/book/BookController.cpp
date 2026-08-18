#include "BookController.h"

BookController::BookController(BookService& bookService) :bookService(bookService) {

}

bool BookController::addBook(const BookDTO& dto) {
	try
	{
		Book book
		(
			0, dto.isbn, dto.title, dto.author, dto.publisherId,
			dto.categoryId, dto.publishYear,dto.price, dto.coverUrl, dto.description,BookStatus::Normal, false
		);

		return bookService.addBook(book);
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
		BookStatus s = BookStatus::Normal;
		if (dto.status == "正常")
		{
			s = BookStatus::Normal;
		}
		else if (dto.status == "下架")
		{
			s = BookStatus::OffShelf;
		}
		else if (dto.status == "禁用")
		{
			s = BookStatus::Disabled;
		}
		Book book(
			dto.id, dto.isbn, dto.title, dto.author, dto.publisherId,dto.categoryId, dto.publishYear, dto.price, 
			dto.coverUrl, dto.description,s, false
		);
		return bookService.updateBook(book);
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