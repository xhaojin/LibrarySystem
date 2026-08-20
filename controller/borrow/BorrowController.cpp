#include "BorrowController.h"

BorrowController::BorrowController(BorrowService& borrowService) : borrowService(borrowService) 
{
}

bool BorrowController::borrowBook(std::int64_t userId, std::int64_t bookId, std::int64_t operatorId, const std::string& dueTime, const std::string& remark)
{
    return borrowService.borrowBook(userId, bookId, operatorId, dueTime, remark);
}

bool BorrowController::returnBook(std::int64_t borrowRecordId, std::int64_t operatorId, const std::string& remark)
{
    return borrowService.returnBook(borrowRecordId, operatorId, remark);
}

std::vector<BorrowRecordDTO> BorrowController::getAllBorrowRecords() const
{
    return borrowService.getAllBorrowRecords();
}