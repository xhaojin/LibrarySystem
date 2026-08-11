#pragma once

#include "repository/interfaces/IBookRepository.h"

#include "database/mysql/MySQLDatabase.h"

#include <memory>

class MySQLBookRepository : public IBookRepository
{
public:
    explicit MySQLBookRepository(MySQLDatabase& database);

    bool add(std::shared_ptr<Book> book) override;

    bool remove(long long bookId) override;

    bool update(const Book& book) override;

    bool updateStatus(long long bookId,BookStatus status) override;

    std::shared_ptr<Book> findById(long long bookId) const override;

    std::shared_ptr<Book> findByISBN(const std::string& isbn) const override;

    std::vector<std::shared_ptr<Book>> findByTitle(const std::string& keyword) const override;

    int getTotalBooks() const override;

    std::vector<BookDTO> findAllWithDetail() const override;

    std::vector<BookDTO> findByTitleWithDetail(const std::string& keyword) const override;

    std::vector<BookDTO> sortByTitleWithDetail() const override;

    std::vector<BookDTO> sortByPriceWithDetail() const override;

private:
    MySQLDatabase& m_database;
};