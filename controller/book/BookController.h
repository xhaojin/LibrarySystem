#pragma once

#include "service/book/BookService.h"
#include "common/utils/Logger.h"

class BookController
{
private:
	BookService& bookService;

public:
	explicit BookController(BookService& bookService);

	std::vector<BookDTO> findBooksByTitle(const std::string& keyword);
	std::vector<BookDTO> getBooksSortedByPrice() const;
	std::vector<BookDTO> getBooksSortedByTitle() const;
	std::vector<BookDTO> getAllBooks() const;
};