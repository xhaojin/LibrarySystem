#pragma once

#include "service/book/BookService.h"
#include "common/utils/Logger.h"

class BookController
{
private:
	BookService& bookService;

public:
	explicit BookController(BookService& bookService);

	bool addBook(const BookDTO& dto);
	bool updateBook(const BookDTO& dto);
	bool removeBook(int bookId);
	std::vector<BookDTO> findBooksByTitle(const std::string& keyword);
	BookDTO findBookById(int bookId) const;
	std::vector<BookDTO> getBooksSortedByPrice() const;
	std::vector<BookDTO> getBooksSortedByTitle() const;
	std::vector<BookDTO> getAllBooks() const;
};