#include "../../include/mapper/BorrowRecordMapper.h"
#include "../../include/utils/Time.h"

std::shared_ptr<BorrowRecord> BorrowRecordMapper::fromQuery(const QSqlQuery& query)
{
	return std::make_shared<BorrowRecord>(query.value("id").toInt(),

		query.value("user_id").toInt(),

		query.value("book_id").toInt(),

		Time::stringToDateTime(query.value("borrow_time").toString()),

		Time::stringToOptionalDateTime(query.value("return_time").toString())
	);
}

void BorrowRecordMapper::bindToQuery(QSqlQuery& query, const BorrowRecord& borrowRecord)
{
	query.bindValue(":id", borrowRecord.getId());

	query.bindValue(":user_id", borrowRecord.getUserId());

	query.bindValue(":book_id", borrowRecord.getBookId());

	query.bindValue(":borrow_time", borrowRecord.getBorrowTime().toString(Qt::ISODate));

	query.bindValue(":return_time", borrowRecord.isReturned() ? QVariant(borrowRecord.getReturnTime()->toString(Qt::ISODate)) : QVariant());
}