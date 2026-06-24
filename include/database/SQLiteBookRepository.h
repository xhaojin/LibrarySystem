#pragma once

#include "../repository/interfaces/IBookRepository.h"
#include "SQLiteDatabase.h"

class SQLiteBookRepository: public IBookRepository
{
public:

    explicit SQLiteBookRepository(SQLiteDatabase& database);

    bool add(std::shared_ptr<Book> book) override;

    std::shared_ptr<Book> findById(int bookId) const override;

    std::vector<std::shared_ptr<Book>> findAll() const override;

private:

    SQLiteDatabase& db;
};