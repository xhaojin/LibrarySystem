#pragma once

#include "repository/interfaces/IBookRepository.h"
#include "dto/BookDTO.h"

class BookService {
private:
	IBookRepository& bookRepo;

public:
	explicit BookService(IBookRepository& bookRepo);

	// 图书管理
	bool addBook(const Book& book);
	bool removeBook(int bookId);
	bool updateBook(const BookDTO& dto);

	// 查询
	std::vector<BookDTO> findBooksByTitle(const std::string& keyword);
	BookDTO findBookById(int bookId) const;
	std::vector<BookDTO> getAllBooksDTO() const;

	// 排序
	std::vector<BookDTO> getBooksSortedByPrice() const;
	std::vector<BookDTO> getBooksSortedByTitle() const;
};