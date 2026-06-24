#pragma once

#include <memory>

#include "../domain/Book.h"

#include <QSqlQuery>

class BookMapper
{
public:

    static std::shared_ptr<Book> fromQuery(const QSqlQuery& query);

    static void bindToQuery(QSqlQuery& query,const Book& book);
};