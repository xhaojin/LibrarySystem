#include "BorrowController.h"

BorrowController::BorrowController(BorrowService& borrowService) : borrowService(borrowService) {
}

void BorrowController::borrowBook(int userId, int bookId)
{
	try
	{
		borrowService.borrowBook(userId, bookId);
	}
	catch (const std::exception& e)
	{
		Logger::log(std::string("[UI_ERROR] ") + e.what());
		throw; // 继续抛给UI（Qt可显示弹窗）
	}
}

void BorrowController::returnBook(int userId, int bookId)
{
	try
	{
		borrowService.returnBook(userId, bookId);
	}
	catch (const std::exception& e)
	{
		Logger::log(std::string("[UI_ERROR] ") + e.what());
		throw;
	}
}

std::vector<BorrowRecordDTO> BorrowController::getAllBorrowRecords() const {
	return borrowService.getAllBorrowRecords();
}