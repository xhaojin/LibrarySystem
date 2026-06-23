#pragma once

#include <optional>
#include <string>
#include <QDateTime>

class BorrowRecord
{
private:

	int id;

	int userId;

	int bookId;

	QDateTime borrowTime;

	std::optional<QDateTime> returnTime;

public:

	BorrowRecord(int id, int userId, int bookId, QDateTime borrowTime);

	int getId() const;

	int getUserId() const;

	int getBookId() const;

	QDateTime getBorrowTime() const;

	const std::optional<QDateTime>& getReturnTime() const;

	bool isReturned() const;

	void returnBook();
};