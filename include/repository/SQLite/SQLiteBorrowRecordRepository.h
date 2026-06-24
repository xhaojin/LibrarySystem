#pragma once

#include "../interfaces/IBorrowRecordRepository.h"
#include "SQLiteDatabase.h"

class SQLiteBorrowRecordRepository : public IBorrowRecordRepository
{
public:

	explicit SQLiteBorrowRecordRepository(SQLiteDatabase& database);

	bool add(std::shared_ptr<BorrowRecord> record) override;

	bool update(const BorrowRecord& record) override;

	std::shared_ptr<BorrowRecord> findById(int recordId) const override;

	std::vector<std::shared_ptr<BorrowRecord>> findAll() const override;

	std::vector<std::shared_ptr<BorrowRecord>> findByUserId(int userId) const override;

	std::vector<std::shared_ptr<BorrowRecord>> findByBookId(int bookId) const override;

	std::shared_ptr<BorrowRecord> findActiveRecord(int userId, int bookId) const override;

	std::vector<std::shared_ptr<BorrowRecord>> findActiveRecords() const override;

private:

	SQLiteDatabase& db;
};