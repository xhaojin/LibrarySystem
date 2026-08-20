#pragma once

#include "repository/interfaces/IBorrowRecordRepository.h"
#include "database/mysql/MySQLDatabase.h"

#include <memory>

class MySQLBorrowRecordRepository : public IBorrowRecordRepository
{
public:
    explicit MySQLBorrowRecordRepository(MySQLDatabase& database);

    std::optional<BorrowRecordDTO> findById(std::int64_t id) const override;

    std::vector<BorrowRecordDTO> findAll() const override;

    std::vector<BorrowRecordDTO> findByUserId(std::int64_t userId) const override;

    std::vector<BorrowRecordDTO> findByCopyId(std::int64_t copyId) const override;

    std::int64_t insert(const BorrowRecordDTO& record) override;

    bool update(const BorrowRecordDTO& record) override;

    bool remove(std::int64_t id) override;

private:
    MySQLDatabase& m_database;
};