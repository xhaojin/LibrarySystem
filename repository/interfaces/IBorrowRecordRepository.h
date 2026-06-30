#pragma once

#include "model/BorrowRecord.h"

class IBorrowRecordRepository
{
public:

    virtual ~IBorrowRecordRepository() = default;

    virtual bool add(std::shared_ptr<BorrowRecord> record) = 0;

    virtual bool update(const BorrowRecord& record) = 0;

    virtual std::shared_ptr<BorrowRecord> findById(int recordId) const = 0;

    virtual std::vector<std::shared_ptr<BorrowRecord>> findAll() const = 0;

    virtual std::vector<std::shared_ptr<BorrowRecord>> findByUserId(int userId) const = 0;

    virtual std::vector<std::shared_ptr<BorrowRecord>> findByBookId(int bookId) const = 0;

    virtual std::shared_ptr<BorrowRecord> findActiveRecord(int userId,int bookId) const = 0;

    virtual std::vector<std::shared_ptr<BorrowRecord>> findActiveRecords() const = 0;
};