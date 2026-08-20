#pragma once

#include "repository/interfaces/IBookCopyRepository.h"
#include "database/mysql/MySQLDatabase.h"

#include <cstdint>
#include <memory>

class MySQLBookCopyRepository : public IBookCopyRepository
{
public:
    explicit MySQLBookCopyRepository(MySQLDatabase& database);

    std::optional<BookCopyDTO> findById(std::int64_t id) const override;

    std::vector<BookCopyDTO> findAll() const override;

    std::vector<BookCopyDTO> findByBookId(std::int64_t bookId) const override;

    std::optional<BookCopyDTO> findByInventoryNo(const std::string& inventoryNo) const override;

    std::optional<BookCopyDTO> findAvailableByBookId(std::int64_t bookId) const override;

    std::int64_t insert(const BookCopyDTO& copy) override;

    bool update(const BookCopyDTO& copy) override;

    bool remove(std::int64_t id) override;

    std::optional<BookCopyDTO> findAvailableByBookIdForUpdate(std::int64_t bookId) const override;

private:
    MySQLDatabase& m_database;
};