#include "domain/BorrowRecord.h"

BorrowRecord::BorrowRecord(int id, int userId, int bookId, QDateTime borrowTime) :id(id), userId(userId), bookId(bookId), borrowTime(borrowTime)
{
}

BorrowRecord::BorrowRecord(int id, int userId, int bookId, QDateTime borrowTime, std::optional<QDateTime> returnTime)
	:id(id), userId(userId), bookId(bookId), borrowTime(borrowTime),returnTime(returnTime)
{}


int BorrowRecord::getId() const {
	return  this->id;
}

int BorrowRecord::getUserId() const {
	return this->userId;
}

int BorrowRecord::getBookId() const {
	return this->bookId;
}

QDateTime BorrowRecord::getBorrowTime() const {
	return this->borrowTime;
}

const std::optional<QDateTime>& BorrowRecord::getReturnTime() const {
	return this->returnTime;
}

void BorrowRecord::setReturnTime(const QDateTime& returnTime) {
	this->returnTime = returnTime;
}

void BorrowRecord::returnBook()
{
	returnTime = QDateTime::currentDateTimeUtc();
}

bool BorrowRecord::isReturned() const
{
	return returnTime.has_value();
}