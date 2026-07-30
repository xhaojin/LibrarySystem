#include "BookMapper.h"

std::shared_ptr<Book> BookMapper::fromResultSet(sql::ResultSet& rs)
{
    return std::make_shared<Book>(
        rs.getInt64("id"),
        rs.getString("isbn"),
        rs.getString("title"),
        rs.getString("author"),

        rs.isNull("publisher_id") ? 0 : rs.getInt64("publisher_id"),
        rs.isNull("category_id") ? 0 : rs.getInt64("category_id"),

        rs.isNull("publish_year") ? 0 : rs.getInt("publish_year"),

        rs.isNull("price") ? 0.0 : rs.getDouble("price"),

        rs.isNull("cover_url") ? "" : rs.getString("cover_url"),

        rs.isNull("description") ? "" : rs.getString("description"),

        static_cast<BookStatus>(rs.getInt("status")),

        rs.getBoolean("deleted")
    );
}

//std::shared_ptr<Book> BookMapper::fromQuery(const QSqlQuery& query)
//{
//    return std::make_shared<Book>(query.value("id").toInt(),
//
//        query.value("title").toString().toStdString(),
//
//        query.value("author").toString().toStdString(),
//
//        query.value("publisher").toString().toStdString(),
//
//        query.value("price").toDouble(),
//
//        query.value("borrowed").toBool()
//    );
//}
//
//void BookMapper::bindToQuery(QSqlQuery& query,const Book& book)
//{
//    query.bindValue(":id",book.getId());
//
//    query.bindValue(":title",QString::fromStdString(book.getTitle()));
//
//    query.bindValue(":author", QString::fromStdString(book.getAuthor()));
//
//    query.bindValue(":publisher", QString::fromStdString(book.getPublisher()));
//
//    query.bindValue(":price", book.getPrice());
//
//    query.bindValue(":borrowed", book.isBorrowed());
//}