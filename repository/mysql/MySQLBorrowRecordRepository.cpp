#include "MySQLBorrowRecordRepository.h"

#include <mysql/jdbc.h>

#include <mapper/BorrowRecordDTOMapper.h>

#include <stdexcept>
#include <string>

MySQLBorrowRecordRepository::MySQLBorrowRecordRepository(MySQLDatabase& database): m_database(database)
{
}

std::optional<BorrowRecordDTO> MySQLBorrowRecordRepository::findById(std::int64_t id) const
{
    const std::string sql = R"(
        SELECT
            id,
            user_id,
            copy_id,
            operator_id,
            borrow_time,
            due_time,
            return_time,
            status,
            remark
        FROM borrow_records
        WHERE id = ?
    )";

    try
    {
        sql::Connection* connection = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement(sql));

        statement->setInt64(1, id);

        std::unique_ptr<sql::ResultSet> result(statement->executeQuery());

        if (!result->next()) return std::nullopt;

        return BorrowRecordDTOMapper::toDTO(*result);
    }
    catch (const sql::SQLException& e)
    {
        throw std::runtime_error("MySQLBorrowRecordRepository::findById failed: "+ std::string(e.what()));
    }
}

std::vector<BorrowRecordDTO> MySQLBorrowRecordRepository::findAll() const
{
    std::vector<BorrowRecordDTO> records;

    const std::string sql = R"(
        SELECT
            id,
            user_id,
            copy_id,
            operator_id,
            borrow_time,
            due_time,
            return_time,
            status,
            remark
        FROM borrow_records
        ORDER BY id DESC
    )";

    try
    {
        sql::Connection* connection = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement(sql));

        std::unique_ptr<sql::ResultSet> result(statement->executeQuery());

        while (result->next())
        {
            records.push_back(BorrowRecordDTOMapper::toDTO(*result));
        }

        return records;
    }
    catch (const sql::SQLException& e)
    {
        throw std::runtime_error("MySQLBorrowRecordRepository::findAll failed: "+ std::string(e.what()));
    }
}

std::vector<BorrowRecordDTO> MySQLBorrowRecordRepository::findByUserId(std::int64_t userId) const
{
    std::vector<BorrowRecordDTO> records;

    const std::string sql = R"(
        SELECT
            id,
            user_id,
            copy_id,
            operator_id,
            borrow_time,
            due_time,
            return_time,
            status,
            remark
        FROM borrow_records
        WHERE user_id = ?
        ORDER BY id DESC
    )";

    try
    {
        sql::Connection* connection = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement(sql));

        statement->setInt64(1, userId);

        std::unique_ptr<sql::ResultSet> result(statement->executeQuery());

        while (result->next())
        {
            records.push_back(BorrowRecordDTOMapper::toDTO(*result));
        }

        return records;
    }
    catch (const sql::SQLException& e)
    {
        throw std::runtime_error("MySQLBorrowRecordRepository::findByUserId failed: "+ std::string(e.what()));
    }
}

std::vector<BorrowRecordDTO> MySQLBorrowRecordRepository::findByCopyId(std::int64_t copyId) const
{
    std::vector<BorrowRecordDTO> records;

    const std::string sql = R"(
        SELECT
            id,
            user_id,
            copy_id,
            operator_id,
            borrow_time,
            due_time,
            return_time,
            status,
            remark
        FROM borrow_records
        WHERE copy_id = ?
        ORDER BY id DESC
    )";

    try
    {
        sql::Connection* connection = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement(sql));

        statement->setInt64(1, copyId);

        std::unique_ptr<sql::ResultSet> result(statement->executeQuery());

        while (result->next())
        {
            records.push_back(BorrowRecordDTOMapper::toDTO(*result));
        }

        return records;
    }
    catch (const sql::SQLException& e)
    {
        throw std::runtime_error("MySQLBorrowRecordRepository::findByCopyId failed: "+ std::string(e.what()));
    }
}

std::int64_t MySQLBorrowRecordRepository::insert(const BorrowRecordDTO& record)
{
    const std::string sql = R"(
        INSERT INTO borrow_records
        (
            user_id,
            copy_id,
            operator_id,
            borrow_time,
            due_time,
            return_time,
            status,
            remark
        )
        VALUES (?, ?, ?, ?, ?, ?, ?, ?)
    )";

    try
    {
        sql::Connection* connection = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement(sql));

        statement->setInt64(1, record.userId);
        statement->setInt64(2, record.copyId);

        if (record.operatorId == 0)
            statement->setNull(3, sql::DataType::BIGINT);
        else
            statement->setInt64(3, record.operatorId);

        statement->setString(4, record.borrowTime);
        statement->setString(5, record.dueTime);

        if (record.returnTime.empty())
            statement->setNull(6, 0);
        else
            statement->setString(6, record.returnTime);

        statement->setInt(7, record.status);
        statement->setString(8, record.remark);

        statement->executeUpdate();

        // 获取 MySQL AUTO_INCREMENT 生成的 ID
        std::unique_ptr<sql::Statement> idStatement(connection->createStatement());

        std::unique_ptr<sql::ResultSet> result(idStatement->executeQuery("SELECT LAST_INSERT_ID()"));

        if (!result->next())
        {
            throw std::runtime_error("Failed to get generated borrow record id.");
        }

        return result->getInt64(1);
    }
    catch (const sql::SQLException& e)
    {
        throw std::runtime_error("MySQLBorrowRecordRepository::insert failed: "+ std::string(e.what()));
    }
}

bool MySQLBorrowRecordRepository::update(const BorrowRecordDTO& record)
{
    const std::string sql = R"(
        UPDATE borrow_records
        SET
            user_id = ?,
            copy_id = ?,
            operator_id = ?,
            borrow_time = ?,
            due_time = ?,
            return_time = ?,
            status = ?,
            remark = ?
        WHERE id = ?
    )";

    try
    {
        sql::Connection* connection = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement(sql));

        statement->setInt64(1, record.userId);
        statement->setInt64(2, record.copyId);

        if (record.operatorId == 0)
            statement->setNull(3, sql::DataType::BIGINT);
        else
            statement->setInt64(3, record.operatorId);

        statement->setString(4, record.borrowTime);
        statement->setString(5, record.dueTime);

        if (record.returnTime.empty())
            statement->setNull(6, 0);
        else
            statement->setString(6, record.returnTime);

        statement->setInt(7, record.status);
        statement->setString(8, record.remark);
        statement->setInt64(9, record.id);

        return statement->executeUpdate() > 0;
    }
    catch (const sql::SQLException& e)
    {
        throw std::runtime_error("MySQLBorrowRecordRepository::update failed: "+ std::string(e.what()));
    }
}

bool MySQLBorrowRecordRepository::remove(std::int64_t id)
{
    const std::string sql = R"(DELETE FROM borrow_records WHERE id = ?)";

    try
    {
        sql::Connection* connection = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement(sql));

        statement->setInt64(1, id);

        return statement->executeUpdate() > 0;
    }
    catch (const sql::SQLException& e)
    {
        throw std::runtime_error("MySQLBorrowRecordRepository::remove failed: "+ std::string(e.what()));
    }
}