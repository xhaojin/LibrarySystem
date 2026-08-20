#include "MySQLBookCopyRepository.h"

#include <mysql/jdbc.h>

#include <stdexcept>
#include <string>

namespace
{
    BookCopyDTO mapToDTO(sql::ResultSet* result)
    {
        BookCopyDTO copy;

        copy.id = result->getInt64("id");
        copy.bookId = result->getInt64("book_id");
        copy.inventoryNo = result->getString("inventory_no");

        if (result->isNull("location"))
        {
            copy.location.clear();
        }
        else
        {
            copy.location = result->getString("location");
        }

        copy.status = result->getInt("status");

        return copy;
    }
}

MySQLBookCopyRepository::MySQLBookCopyRepository(MySQLDatabase& database): m_database(database)
{
}

std::optional<BookCopyDTO> MySQLBookCopyRepository::findById(std::int64_t id) const
{
    const std::string sql = R"(
        SELECT
            id,
            book_id,
            inventory_no,
            location,
            status
        FROM book_copies
        WHERE id = ?
    )";

    try
    {
        sql::Connection* connection = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement(sql));

        statement->setInt64(1, id);

        std::unique_ptr<sql::ResultSet> result(statement->executeQuery());

        if (!result->next())
        {
            return std::nullopt;
        }

        return mapToDTO(result.get());
    }
    catch (const sql::SQLException& e)
    {
        throw std::runtime_error("MySQLBookCopyRepository::findById failed: "+ std::string(e.what()));
    }
}

std::vector<BookCopyDTO> MySQLBookCopyRepository::findAll() const
{
    std::vector<BookCopyDTO> copies;

    const std::string sql = R"(
        SELECT
            id,
            book_id,
            inventory_no,
            location,
            status
        FROM book_copies
        ORDER BY id DESC
    )";

    try
    {
        sql::Connection* connection = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement(sql));

        std::unique_ptr<sql::ResultSet> result(statement->executeQuery());

        while (result->next())
        {
            copies.push_back(mapToDTO(result.get()));
        }

        return copies;
    }
    catch (const sql::SQLException& e)
    {
        throw std::runtime_error("MySQLBookCopyRepository::findAll failed: "+ std::string(e.what()));
    }
}

std::vector<BookCopyDTO> MySQLBookCopyRepository::findByBookId(std::int64_t bookId) const
{
    std::vector<BookCopyDTO> copies;

    const std::string sql = R"(
        SELECT
            id,
            book_id,
            inventory_no,
            location,
            status
        FROM book_copies
        WHERE book_id = ?
        ORDER BY id ASC
    )";

    try
    {
        sql::Connection* connection = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement(sql));

        statement->setInt64(1, bookId);

        std::unique_ptr<sql::ResultSet> result(statement->executeQuery());

        while (result->next())
        {
            copies.push_back(mapToDTO(result.get()));
        }

        return copies;
    }
    catch (const sql::SQLException& e)
    {
        throw std::runtime_error("MySQLBookCopyRepository::findByBookId failed: "+ std::string(e.what()));
    }
}

std::optional<BookCopyDTO> MySQLBookCopyRepository::findByInventoryNo(const std::string& inventoryNo) const
{
    const std::string sql = R"(
        SELECT
            id,
            book_id,
            inventory_no,
            location,
            status
        FROM book_copies
        WHERE inventory_no = ?
    )";

    try
    {
        sql::Connection* connection = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement(sql));

        statement->setString(1, inventoryNo);

        std::unique_ptr<sql::ResultSet> result(statement->executeQuery());

        if (!result->next())
        {
            return std::nullopt;
        }

        return mapToDTO(result.get());
    }
    catch (const sql::SQLException& e)
    {
        throw std::runtime_error("MySQLBookCopyRepository::findByInventoryNo failed: "+ std::string(e.what()));
    }
}

std::optional<BookCopyDTO> MySQLBookCopyRepository::findAvailableByBookId(std::int64_t bookId) const
{
    const std::string sql = R"(
        SELECT
            id,
            book_id,
            inventory_no,
            location,
            status
        FROM book_copies
        WHERE book_id = ?
          AND status = 0
        ORDER BY id ASC
        LIMIT 1
    )";

    try
    {
        sql::Connection* connection =m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement(sql));

        statement->setInt64(1, bookId);

        std::unique_ptr<sql::ResultSet> result(statement->executeQuery());

        if (!result->next())
        {
            return std::nullopt;
        }

        return mapToDTO(result.get());
    }
    catch (const sql::SQLException& e)
    {
        throw std::runtime_error("MySQLBookCopyRepository::findAvailableByBookId failed: "+ std::string(e.what()));
    }
}

std::int64_t MySQLBookCopyRepository::insert(const BookCopyDTO& copy)
{
    const std::string sql = R"(
        INSERT INTO book_copies
        (
            book_id,
            inventory_no,
            location,
            status
        )
        VALUES (?, ?, ?, ?)
    )";

    try
    {
        sql::Connection* connection =m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement(sql));

        statement->setInt64(1, copy.bookId);
        statement->setString(2, copy.inventoryNo);

        if (copy.location.empty())
        {
            statement->setNull(3, 0);
        }
        else
        {
            statement->setString(3, copy.location);
        }

        statement->setInt(4, copy.status);

        statement->executeUpdate();

        std::unique_ptr<sql::Statement> idStatement(connection->createStatement());

        std::unique_ptr<sql::ResultSet> result(idStatement->executeQuery("SELECT LAST_INSERT_ID()"));

        if (!result->next())
        {
            throw std::runtime_error("Failed to get generated book copy id.");
        }

        return result->getInt64(1);
    }
    catch (const sql::SQLException& e)
    {
        throw std::runtime_error("MySQLBookCopyRepository::insert failed: "+ std::string(e.what()));
    }
}

bool MySQLBookCopyRepository::update(const BookCopyDTO& copy)
{
    const std::string sql = R"(
        UPDATE book_copies
        SET
            book_id = ?,
            inventory_no = ?,
            location = ?,
            status = ?
        WHERE id = ?
    )";

    try
    {
        sql::Connection* connection = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement(sql));

        statement->setInt64(1, copy.bookId);
        statement->setString(2, copy.inventoryNo);

        if (copy.location.empty())
        {
            statement->setNull(3, 0);
        }
        else
        {
            statement->setString(3, copy.location);
        }

        statement->setInt(4, copy.status);
        statement->setInt64(5, copy.id);

        return statement->executeUpdate() > 0;
    }
    catch (const sql::SQLException& e)
    {
        throw std::runtime_error("MySQLBookCopyRepository::update failed: "+ std::string(e.what()));
    }
}

bool MySQLBookCopyRepository::remove(std::int64_t id)
{
    const std::string sql = R"(DELETE FROM book_copies WHERE id = ?)";

    try
    {
        sql::Connection* connection = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement(sql));

        statement->setInt64(1, id);

        return statement->executeUpdate() > 0;
    }
    catch (const sql::SQLException& e)
    {
        throw std::runtime_error("MySQLBookCopyRepository::remove failed: "+ std::string(e.what()));
    }
}

std::optional<BookCopyDTO> MySQLBookCopyRepository::findAvailableByBookIdForUpdate(std::int64_t bookId) const
{
    const std::string sql = R"(
        SELECT
            id,
            book_id,
            inventory_no,
            location,
            status
        FROM book_copies
        WHERE book_id = ?
          AND status = 0
        ORDER BY id ASC
        LIMIT 1
        FOR UPDATE
    )";

    try
    {
        sql::Connection* connection = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement(sql));

        statement->setInt64(1, bookId);

        std::unique_ptr<sql::ResultSet> result(statement->executeQuery());

        if (!result->next())
        {
            return std::nullopt;
        }

        return mapToDTO(result.get());
    }
    catch (const sql::SQLException& e)
    {
        throw std::runtime_error("MySQLBookCopyRepository::""findAvailableByBookIdForUpdate failed: "+ std::string(e.what()));
    }
}