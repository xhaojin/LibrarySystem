#include "MySQLPublisherRepository.h"

#include "mapper/PublisherMapper.h"

#include <mysql/jdbc.h>

MySQLPublisherRepository::MySQLPublisherRepository(MySQLDatabase& database): m_database(database)
{
}

bool MySQLPublisherRepository::add(const Publisher& publisher)
{
    try
    {
        auto* conn = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> stmt(
            conn->prepareStatement(R"(
                INSERT INTO publishers
                (
                    name,
                    contact,
                    website
                )
                VALUES (?, ?, ?)
            )")
        );

        stmt->setString(1,publisher.getName());

        stmt->setString(2,publisher.getContact());

        stmt->setString(3,publisher.getWebsite());

        return stmt->executeUpdate() > 0;
    }
    catch (const sql::SQLException&)
    {
        return false;
    }
}

bool MySQLPublisherRepository::update(const Publisher& publisher)
{
    try
    {
        auto* conn = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> stmt(
            conn->prepareStatement(R"(
                UPDATE publishers
                SET
                    name = ?,
                    contact = ?,
                    website = ?
                WHERE id = ?
            )")
        );

        stmt->setString(1,publisher.getName());

        stmt->setString(2,publisher.getContact());

        stmt->setString(3,publisher.getWebsite());

        stmt->setInt64(4,publisher.getId());

        return stmt->executeUpdate() > 0;
    }
    catch (const sql::SQLException&)
    {
        return false;
    }
}

bool MySQLPublisherRepository::remove(long long publisherId)
{
    try
    {
        auto* conn = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> stmt(
            conn->prepareStatement(R"(
                DELETE FROM publishers
                WHERE id = ?
            )")
        );

        stmt->setInt64(1,publisherId);

        return stmt->executeUpdate() > 0;
    }
    catch (const sql::SQLException&)
    {
        return false;
    }
}

std::shared_ptr<Publisher> MySQLPublisherRepository::findById(long long publisherId) const
{
    try
    {
        auto* conn = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> stmt(
            conn->prepareStatement(R"(
                SELECT
                    id,
                    name,
                    contact,
                    website
                FROM publishers
                WHERE id = ?
            )")
        );

        stmt->setInt64(1,publisherId);

        std::unique_ptr<sql::ResultSet> rs(stmt->executeQuery());

        if (!rs->next())
        {
            return nullptr;
        }

        return PublisherMapper::fromResultSet(*rs);
    }
    catch (const sql::SQLException&)
    {
        return nullptr;
    }
}

std::shared_ptr<Publisher> MySQLPublisherRepository::findByName(const std::string& name) const
{
    try
    {
        auto* conn = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> stmt(
            conn->prepareStatement(R"(
                SELECT
                    id,
                    name,
                    contact,
                    website
                FROM publishers
                WHERE name = ?
            )")
        );

        stmt->setString(1,name);

        std::unique_ptr<sql::ResultSet> rs(stmt->executeQuery());

        if (!rs->next())
        {
            return nullptr;
        }

        return PublisherMapper::fromResultSet(*rs);
    }
    catch (const sql::SQLException&)
    {
        return nullptr;
    }
}

std::vector<std::shared_ptr<Publisher>> MySQLPublisherRepository::findByNameLike(const std::string& keyword) const
{
    std::vector<std::shared_ptr<Publisher>> publishers;

    try
    {
        auto* conn = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> stmt(
            conn->prepareStatement(R"(
                SELECT
                    id,
                    name,
                    contact,
                    website
                FROM publishers
                WHERE name LIKE ?
                ORDER BY name ASC
            )")
        );

        stmt->setString(1,"%" + keyword + "%");

        std::unique_ptr<sql::ResultSet> rs(stmt->executeQuery());

        while (rs->next())
        {
            publishers.push_back(PublisherMapper::fromResultSet(*rs));
        }
    }
    catch (const sql::SQLException&)
    {
        // 保持返回空 vector
    }

    return publishers;
}

std::vector<std::shared_ptr<Publisher>> MySQLPublisherRepository::findAll() const
{
    std::vector<std::shared_ptr<Publisher>> publishers;

    try
    {
        auto* conn = m_database.getConnection();

        std::unique_ptr<sql::Statement> stmt(conn->createStatement());

        std::unique_ptr<sql::ResultSet> rs(
            stmt->executeQuery(R"(
                SELECT
                    id,
                    name,
                    contact,
                    website
                FROM publishers
                ORDER BY id
            )")
        );

        while (rs->next())
        {
            publishers.push_back(PublisherMapper::fromResultSet(*rs));
        }
    }
    catch (const sql::SQLException&)
    {
        // 保持返回空 vector
    }

    return publishers;
}