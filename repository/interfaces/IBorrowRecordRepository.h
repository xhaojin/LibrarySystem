#pragma once

#include "dto/BorrowRecordDTO.h"

#include <optional>
#include <vector>

class IBorrowRecordRepository
{
public:

    virtual ~IBorrowRecordRepository() = default;

    virtual std::optional<BorrowRecordDTO> findById(std::int64_t id) const = 0;

    virtual std::vector<BorrowRecordDTO> findAll() const = 0;

    virtual std::vector<BorrowRecordDTO> findByUserId(std::int64_t userId) const = 0;

    virtual std::vector<BorrowRecordDTO> findByCopyId(std::int64_t copyId) const = 0;

    virtual std::int64_t insert(const BorrowRecordDTO& record) = 0;

    virtual bool update(const BorrowRecordDTO& record) = 0;

    virtual bool remove(std::int64_t id) = 0;
};