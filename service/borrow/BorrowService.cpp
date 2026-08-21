#include "BorrowService.h"

#include "common/utils/Time.h"

BorrowService::BorrowService(MySQLDatabase& database,MySQLUserRepository& userRepository,
    MySQLBookCopyRepository& bookCopyRepository,
    MySQLBorrowRecordRepository& borrowRecordRepository)
    : m_database(database),m_userRepository(userRepository),
    m_bookCopyRepository(bookCopyRepository),m_borrowRecordRepository(borrowRecordRepository)
{
}

bool BorrowService::borrowBook(std::int64_t userId,std::int64_t bookId,std::int64_t operatorId,const std::string& dueTime,const std::string& remark)
{
    try
    {
        // =========================
        // 1. 检查用户
        // =========================

        auto user = m_userRepository.findById(userId);

        if (!user)
        {
            return false;
        }

        // =========================
        // 2. 开启事务
        // =========================

        m_database.beginTransaction();

        // =========================
        // 3. 查询并锁定可借副本
        // =========================

        auto copy = m_bookCopyRepository.findAvailableByBookIdForUpdate(bookId);

        if (!copy)
        {
            m_database.rollback();

            return false;
        }

        // =========================
        // 4. 创建借阅记录
        // =========================

        BorrowRecordDTO record{};

        record.id = 0;

        record.userId = userId;

        record.copyId = copy->id;

        record.operatorId = operatorId;

        record.borrowTime = Time::getCurrentDateTime();

        record.dueTime = dueTime;

        record.returnTime = "";

        record.status = 0;

        record.remark = remark;

        m_borrowRecordRepository.insert(record);

        // =========================
        // 5. 修改副本状态
        // =========================

        copy->status = 1;

        if (!m_bookCopyRepository.update(*copy))
        {
            m_database.rollback();

            return false;
        }

        // =========================
        // 6. 提交事务
        // =========================

        m_database.commit();

        return true;
    }
    catch (...)
    {
        try
        {
            m_database.rollback();
        }
        catch (...)
        {
        }

        throw;
    }
}

bool BorrowService::returnBook(std::int64_t borrowRecordId,std::int64_t operatorId,const std::string& remark)
{
    try
    {
        // =========================
        // 1. 查询借阅记录
        // =========================

        auto record = m_borrowRecordRepository.findById(borrowRecordId);

        if (!record)
        {
            return false;
        }

        // 已经归还
        if (record->status == 1)
        {
            return false;
        }

        // =========================
        // 2. 查询副本
        // =========================

        auto copy = m_bookCopyRepository.findById(record->copyId);

        if (!copy)
        {
            return false;
        }

        // =========================
        // 3. 开启事务
        // =========================

        m_database.beginTransaction();

        // =========================
        // 4. 更新借阅记录
        // =========================

        record->returnTime = Time::getCurrentDateTime();

        record->operatorId = operatorId;

        record->remark = remark;

        record->status = 1;

        if (!m_borrowRecordRepository.update(*record))
        {
            m_database.rollback();

            return false;
        }

        // =========================
        // 5. 更新副本状态
        // =========================

        copy->status = 0;

        if (!m_bookCopyRepository.update(*copy))
        {
            m_database.rollback();

            return false;
        }

        // =========================
        // 6. 提交
        // =========================

        m_database.commit();

        return true;
    }
    catch (...)
    {
        try
        {
            m_database.rollback();
        }
        catch (...)
        {
        }

        throw;
    }
}

std::vector<BorrowRecordDTO> BorrowService::getAllBorrowRecords() const
{
    return m_borrowRecordRepository.findAll();
}

std::vector<BorrowRecordViewDTO> BorrowService::findCurrentBorrowRecords(std::int64_t userId) const
{
    if (userId <= 0)
    {
        throw std::invalid_argument("Invalid userId.");
    }

    return m_borrowRecordRepository.findCurrentViewByUserId(userId);
}