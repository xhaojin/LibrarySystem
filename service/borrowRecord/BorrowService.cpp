#include "BorrowService.h"

BorrowService::BorrowService(IBookRepository& bookRepo, IUserRepository& userRepo, IBorrowRecordRepository& borrowRepo)
	:bookRepo(bookRepo),userRepo(userRepo),borrowRepo(borrowRepo) {

}

void BorrowService::borrowBook(int userId, int bookId) {
	auto user = userRepo.findById(userId);
	if (!user) {
		std::string msg = "[USER_ERROR] User not found: " + std::to_string(userId);
		Logger::log(msg);
		throw std::runtime_error(msg);
	}
	auto book = bookRepo.findById(bookId);
	if (!book) {
		std::string msg = "[BOOK_ERROR] Book not found: " + std::to_string(bookId);
		Logger::log(msg);
		throw std::runtime_error(msg);
	}
	if (book->isBorrowed()) {
		std::string msg = "[STATE_ERROR] Book already borrowed: " + std::to_string(bookId);
		Logger::log(msg);
		throw std::runtime_error(msg);
	}
	// 修改图书状态
	book->setBorrowedStatus(true);

	if (!bookRepo.update(*book))
	{
		throw std::runtime_error("Failed to update book status");
	}

	// 创建借阅记录
	auto record = std::make_shared<BorrowRecord>(0, userId, bookId, QDateTime::currentDateTime(), std::nullopt);

	if (!borrowRepo.add(record))
	{
		throw std::runtime_error("Failed to create borrow record");
	}

	Logger::log("[BORROW_SUCCESS] User " + std::to_string(userId) + " borrowed book " + std::to_string(bookId));
}

void BorrowService::returnBook(int userId, int bookId) {
	auto user = userRepo.findById(userId);
	if (!user) {
		std::string msg = "[USER_ERROR] User not found: " + std::to_string(userId);
		Logger::log(msg);
		throw std::runtime_error(msg);
	}
	auto book = bookRepo.findById(bookId);
	if (!book) {
		std::string msg = "[BOOK_ERROR] Book not found: " + std::to_string(bookId);
		Logger::log(msg);
		throw std::runtime_error(msg);
	}
	if (!book->isBorrowed()) {
		std::string msg = "[STATE_ERROR] Book already borrowed: " + std::to_string(bookId);
		Logger::log(msg);
		throw std::runtime_error(msg);
	}
	auto record = borrowRepo.findActiveRecord(userId, bookId);

	if (!record)
	{
		std::string msg = "[RECORD_ERROR] Active borrow record not found";

		Logger::log(msg);

		throw std::runtime_error(msg);
	}

	// 更新借阅记录
	record->setReturnTime(QDateTime::currentDateTime());

	if (!borrowRepo.update(*record))
	{
		throw std::runtime_error("Failed to update borrow record");
	}

	// 更新图书状态
	book->setBorrowedStatus(false);

	if (!bookRepo.update(*book))
	{
		throw std::runtime_error("Failed to update book status");
	}

	Logger::log("[RETURN_SUCCESS] User " + std::to_string(userId) + " returned book " + std::to_string(bookId));
}

std::vector<BorrowRecordDTO> BorrowService::getAllBorrowRecords() const {
	std::vector<BorrowRecordDTO> recordDTOs;
	for (const auto& record : borrowRepo.findAll()) {
		recordDTOs.push_back(BorrowRecordDTO{
			record->getId(),
			record->getUserId(),
			record->getBookId(),
			record->getBorrowTime().toString().toStdString(),
			record->getReturnTime().value().toString().toStdString(),
			record->getReturnTime().has_value()
			});
	}
	return recordDTOs;
}