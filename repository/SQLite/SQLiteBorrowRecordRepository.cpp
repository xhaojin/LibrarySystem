#include "SQLiteBorrowRecordRepository.h"
#include "mapper/BorrowRecordMapper.h"

SQLiteBorrowRecordRepository::SQLiteBorrowRecordRepository(SQLiteDatabase& database) :db(database)
{
}

bool SQLiteBorrowRecordRepository::add(std::shared_ptr<BorrowRecord> record)
{
	QSqlQuery query(db.database());

	query.prepare(
		"INSERT INTO borrow_records "
		"(user_id,book_id,borrow_time,return_time)"
		"VALUES "
		"(:user_id,:book_id,:borrow_time,:return_time)");

	BorrowRecordMapper::bindToQuery(query, *record);

	return query.exec();
}

bool SQLiteBorrowRecordRepository::update(const BorrowRecord& record)
{
	QSqlQuery query(db.database());

	query.prepare(
		"UPDATE borrow_records "
		"SET "
		"user_id=:user_id,"
		"book_id=:book_id,"
		"borrow_time=:borrow_time,"
		"return_time=:return_time "
		"WHERE id=:id");

	BorrowRecordMapper::bindToQuery(query, record);

	return query.exec();
}

std::shared_ptr<BorrowRecord> SQLiteBorrowRecordRepository::findById(int recordId) const
{
	QSqlQuery query(db.database());

	query.prepare("SELECT * FROM borrow_records WHERE id=:id");

	query.bindValue(":id", recordId);

	if (!query.exec())
		return nullptr;

	if (!query.next())
		return nullptr;

	return BorrowRecordMapper::fromQuery(query);
}

std::vector<std::shared_ptr<BorrowRecord>> SQLiteBorrowRecordRepository::findAll() const
{
	std::vector<std::shared_ptr<BorrowRecord>>records;

	QSqlQuery query(db.database());

	query.exec("SELECT * FROM borrow_records");

	while (query.next())
	{
		records.push_back(BorrowRecordMapper::fromQuery(query));
	}

	return records;
}

std::vector<std::shared_ptr<BorrowRecord>> SQLiteBorrowRecordRepository::findByUserId(int userId) const
{
	std::vector<std::shared_ptr<BorrowRecord>>records;

	QSqlQuery query(db.database());

	query.prepare("SELECT * FROM borrow_records WHERE user_id=:user_id");

	query.bindValue(":user_id", userId);

	query.exec();

	while (query.next())
	{
		records.push_back(BorrowRecordMapper::fromQuery(query));
	}

	return records;
}

std::vector<std::shared_ptr<BorrowRecord>> SQLiteBorrowRecordRepository::findByBookId(int bookId) const
{
	std::vector<std::shared_ptr<BorrowRecord>> records;

	QSqlQuery query(db.database());

	query.prepare("SELECT * FROM borrow_records WHERE book_id=:book_id");

	query.bindValue(":book_id", bookId);

	query.exec();

	while (query.next())
	{
		records.push_back(BorrowRecordMapper::fromQuery(query));
	}

	return records;
}

std::shared_ptr<BorrowRecord> SQLiteBorrowRecordRepository::findActiveRecord(int userId, int bookId) const
{
	QSqlQuery query(db.database());

	query.prepare(
		"SELECT * "
		"FROM borrow_records "
		"WHERE user_id=:user_id "
		"AND book_id=:book_id "
		"AND return_time IS NULL "
		"LIMIT 1");

	query.bindValue(":user_id", userId);

	query.bindValue(":book_id", bookId);

	if (!query.exec())
		return nullptr;

	if (!query.next())
		return nullptr;

	return BorrowRecordMapper::fromQuery(query);
}

std::vector<std::shared_ptr<BorrowRecord>> SQLiteBorrowRecordRepository::findActiveRecords() const
{
	std::vector<std::shared_ptr<BorrowRecord>>
		records;

	QSqlQuery query(db.database());

	query.exec("SELECT * FROM borrow_records WHERE return_time IS NULL");

	while (query.next())
	{
		records.push_back(BorrowRecordMapper::fromQuery(query));
	}

	return records;
}