#pragma once

#include "service/borrow/BorrowService.h"

class BorrowController
{
private:
	BorrowService& borrowService;

public:
	explicit BorrowController(BorrowService& borrowService);

	void borrowBook(int userId, int bookId);
	void returnBook(int userId, int bookId);
	std::vector<BorrowRecordDTO> getAllBorrowRecords() const;
};