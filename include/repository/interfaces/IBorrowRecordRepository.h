#pragma once

#include "domain/BorrowRecord.h"

class IBorrowRecordRepository
{
public:
    virtual ~IBorrowRecordRepository() = default;

    virtual void add(std::shared_ptr<BorrowRecord> record) = 0;

    virtual std::shared_ptr<BorrowRecord>findById(int recordId) const = 0;

    virtual std::vector<std::shared_ptr<BorrowRecord>>findAll() const = 0;
};