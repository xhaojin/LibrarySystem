#pragma once

#include "repository/mysql/MySQLUserRepository.h"
#include "repository/mysql/MySQLBookCopyRepository.h"
#include "repository/mysql/MySQLBorrowRecordRepository.h"
#include "database/mysql/MySQLDatabase.h"

#include <cstdint>
#include <memory>

class BorrowService
{
public:
    BorrowService(
        MySQLDatabase& database,
        MySQLUserRepository& userRepository,
        MySQLBookCopyRepository& bookCopyRepository,
        MySQLBorrowRecordRepository& borrowRecordRepository);

    bool borrowBook(std::int64_t userId,std::int64_t bookId,std::int64_t operatorId,const std::string& dueTime,const std::string& remark = "");

    bool returnBook(std::int64_t borrowRecordId,std::int64_t operatorId,const std::string& remark = "");

    std::vector<BorrowRecordDTO> getAllBorrowRecords() const;

    std::vector<BorrowRecordViewDTO> findCurrentBorrowRecords(std::int64_t userId) const;

private:
    MySQLDatabase& m_database;

    MySQLUserRepository& m_userRepository;

    MySQLBookCopyRepository& m_bookCopyRepository;

    MySQLBorrowRecordRepository& m_borrowRecordRepository;
};