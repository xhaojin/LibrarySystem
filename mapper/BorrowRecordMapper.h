#pragma once

#include <memory>

#include "model/BorrowRecord.h"

#include <QSqlQuery>

class BorrowRecordMapper
{
public:

    static std::shared_ptr<BorrowRecord> fromQuery(const QSqlQuery& query);

    static void bindToQuery(QSqlQuery& query, const BorrowRecord& borrowRecord);
};