#pragma once

#include "dto/BookCopyDTO.h"

#include <cstdint>
#include <optional>
#include <vector>

class IBookCopyRepository
{
public:
    virtual ~IBookCopyRepository() = default;

    virtual std::optional<BookCopyDTO> findById(std::int64_t id) const = 0;

    virtual std::vector<BookCopyDTO> findAll() const = 0;

    virtual std::vector<BookCopyDTO> findByBookId(std::int64_t bookId) const = 0;

    virtual std::optional<BookCopyDTO> findByInventoryNo(const std::string& inventoryNo) const = 0;

    virtual std::optional<BookCopyDTO> findAvailableByBookId(std::int64_t bookId) const = 0;

    virtual std::int64_t insert(const BookCopyDTO& copy) = 0;

    virtual bool update(const BookCopyDTO& copy) = 0;

    virtual bool remove(std::int64_t id) = 0;
};