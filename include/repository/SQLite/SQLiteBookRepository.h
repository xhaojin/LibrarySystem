#pragma once

#include "../interfaces/IBookRepository.h"
#include "SQLiteDatabase.h"

class SQLiteBookRepository: public IBookRepository
{
public:

    explicit SQLiteBookRepository(SQLiteDatabase& database);

    bool add(std::shared_ptr<Book> book) override;

    bool remove(int bookId) override;

    bool update(const Book& book) override;

    std::shared_ptr<Book> findById(int bookId) const override;

    std::vector<std::shared_ptr<Book>> findByTitle(const std::string& titleKeyWord) const override;

    std::vector<std::shared_ptr<Book>> findAll() const override;

    std::vector<std::shared_ptr<Book>> sortByTitle() const override;

    std::vector<std::shared_ptr<Book>> sortByPrice() const override;

    int getTotalBooks() const override;

    int getBorrowedBooksCount() const override;

    int	getAvailableBooksCount() const override;

private:

    SQLiteDatabase& db;
};