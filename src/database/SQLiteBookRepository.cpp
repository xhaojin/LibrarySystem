#include "../../include/database/SQLiteBookRepository.h"
#include "../../include/mapper/BookMapper.h"

SQLiteBookRepository::SQLiteBookRepository(SQLiteDatabase& database) :db(database)
{
}

bool SQLiteBookRepository::add(std::shared_ptr<Book> book)
{
    QSqlQuery query(db.database());

    query.prepare(
        "INSERT INTO books "
        "(id,title,author,publisher,"
        "price,borrowed)"
        "VALUES "
        "(:id,:title,:author,"
        ":publisher,:price,"
        ":borrowed)");

    BookMapper::bindToQuery(query, *book);

    return query.exec();
}

std::shared_ptr<Book> SQLiteBookRepository::findById(int bookId) const
{
    QSqlQuery query(db.database());

    query.prepare(
        "SELECT * FROM books "
        "WHERE id=:id");

    query.bindValue(":id",bookId);

    if (!query.exec())
    {
        return nullptr;
    }

    if (!query.next())
    {
        return nullptr;
    }

    return BookMapper::fromQuery(query);
}

std::vector<std::shared_ptr<Book>> SQLiteBookRepository::findAll() const
{
    std::vector<std::shared_ptr<Book>> books;

    QSqlQuery query(db.database());

    query.exec("SELECT * FROM books");

    while (query.next())
    {
        books.push_back(BookMapper::fromQuery(query));
    }

    return books;
}