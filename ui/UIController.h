#pragma once

#include "service/book/BookService.h"
#include "service/user/UserService.h"
#include "service/borrowRecord/BorrowService.h"

#include "app/SessionManager.h"

class UIController
{
private:
	BookService& bookService;
	UserService& userService;
	BorrowService& borrowService;

public:
	UIController(BookService& bookService, UserService& userService, BorrowService& borrowService);

	// 操作类
	void borrowBook(int userId, int bookId);
	void returnBook(int userId, int bookId);
	std::vector<BookDTO> findBooksByTitle(const std::string& keyword);
	std::vector<BookDTO> getBooksSortedByPrice() const;
	std::vector<BookDTO> getBooksSortedByTitle() const;

	// UI数据类
	std::vector<BookDTO> getAllBooks() const;
	std::vector<UserDTO> getAllUsers() const;
	std::vector<BorrowRecordDTO> getAllBorrowRecords() const;
};