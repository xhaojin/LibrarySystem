#pragma once

#include "service/borrow/BorrowService.h"

class BorrowController
{
private:
	BorrowService& borrowService;

public:
	explicit BorrowController(BorrowService& borrowService);

	bool borrowBook(std::int64_t userId, std::int64_t bookId, std::int64_t operatorId, const std::string& dueTime, const std::string& remark = "");

	bool returnBook(std::int64_t borrowRecordId, std::int64_t operatorId, const std::string& remark = "");

	std::vector<BorrowRecordDTO> getAllBorrowRecords() const;
};