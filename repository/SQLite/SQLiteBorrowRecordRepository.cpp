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

std::vector<BorrowRecordDTO> SQLiteBorrowRecordRepository::findRecordsByCondition(const std::string& username, const std::string& bookTitle) const
{
	std::vector<BorrowRecordDTO> records;
	QString sql = R"(SELECT br.id,u.name,b.title,br.borrow_time,br.return_time FROM borrow_records br 
	JOIN users u ON br.user_id = u.id 
	JOIN books b ON br.book_id = b.id 
	WHERE 1=1
	)";

	if (!username.empty())
	{
		sql += " AND u.name LIKE :userName";
	}

	if (!bookTitle.empty())
	{
		sql += " AND b.title LIKE :bookTitle";
	}

	QSqlQuery query(db.database());
	query.prepare(sql);

	if (!username.empty())
	{
		query.bindValue(":userName","%" + QString::fromStdString(username) + "%");
	}

	if (!bookTitle.empty())
	{
		query.bindValue(":bookTitle","%" + QString::fromStdString(bookTitle) + "%");
	}

	query.exec();
	while (query.next())
	{
		BorrowRecordDTO dto;
		dto.id = query.value(0).toInt();
		dto.username = query.value(1).toString().toStdString();
		dto.bookTitle = query.value(2).toString().toStdString();
		dto.borrowTime = query.value(3).toString().toStdString();
		dto.returnTime = query.value(4).toString().toStdString();
		dto.returned = !query.value(4).toString().isEmpty();
		records.push_back(dto);
	}
	return records;
}

std::vector<BorrowRecordDTO> SQLiteBorrowRecordRepository::findAllDTO() const
{
	std::vector<BorrowRecordDTO> records;

	QSqlQuery query(db.database());

	query.prepare(R"(SELECT br.id,br.user_id,u.name,br.book_id,b.title,br.borrow_time,br.return_time FROM borrow_records br
        INNER JOIN users u ON br.user_id = u.id
        INNER JOIN books b ON br.book_id = b.id ORDER BY br.borrow_time DESC
    )");

	query.exec();

	while (query.next())
	{
		BorrowRecordDTO dto;

		dto.id = query.value(0).toInt();

		dto.userId = query.value(1).toInt();

		dto.username = query.value(2).toString().toStdString();

		dto.bookId = query.value(3).toInt();

		dto.bookTitle = query.value(4).toString().toStdString();

		dto.borrowTime = query.value(5).toString().toStdString();

		dto.returnTime = query.value(6).toString().toStdString();

		dto.returned = !query.value(6).toString().isEmpty();

		records.push_back(dto);
	}

	return records;
}