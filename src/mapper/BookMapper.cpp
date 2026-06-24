#include "../../include/mapper/BookMapper.h"

std::shared_ptr<Book> BookMapper::fromQuery(const QSqlQuery& query)
{
    return std::make_shared<Book>(query.value("id").toInt(),

        query.value("title").toString().toStdString(),

        query.value("author").toString().toStdString(),

        query.value("publisher").toString().toStdString(),

        query.value("price").toDouble(),

        query.value("borrowed").toBool()
    );
}

void BookMapper::bindToQuery(QSqlQuery& query,const Book& book)
{
    query.bindValue(":id",book.getId());

    query.bindValue(":title",QString::fromStdString(book.getTitle()));

    query.bindValue(":author", QString::fromStdString(book.getAuthor()));

    query.bindValue(":publisher", QString::fromStdString(book.getPublisher()));

    query.bindValue(":price", book.getPrice());

    query.bindValue(":borrowed", book.isBorrowed());
}