#include "MySQLCategoryRepository.h"

#include "mapper/CategoryMapper.h"

#include <mysql/jdbc.h>

MySQLCategoryRepository::MySQLCategoryRepository(MySQLDatabase& database): m_database(database)
{
}

bool MySQLCategoryRepository::add(const Category& category)
{
    try
    {
        auto* conn = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> stmt(
            conn->prepareStatement(
                R"(
                    INSERT INTO categories
                    (name, sort_order, description)
                    VALUES (?, ?, ?)
                )"
            )
        );

        stmt->setString(1,category.getName());

        stmt->setInt(2,category.getSortOrder());

        stmt->setString(3,category.getDescription());

        return stmt->executeUpdate() > 0;
    }
    catch (...)
    {
        return false;
    }
}

bool MySQLCategoryRepository::remove(long long categoryId)
{
    try
    {
        auto* conn = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> stmt(
            conn->prepareStatement(
                "DELETE FROM categories WHERE id = ?"
            )
        );

        stmt->setInt64(1,categoryId);

        return stmt->executeUpdate() > 0;
    }
    catch (...)
    {
        return false;
    }
}

bool MySQLCategoryRepository::update(const Category& category)
{
    try
    {
        auto* conn = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> stmt(
            conn->prepareStatement(
                R"(
                    UPDATE categories
                    SET name = ?,
                        sort_order = ?,
                        description = ?
                    WHERE id = ?
                )"
            )
        );

        stmt->setString(1,category.getName());

        stmt->setInt(2,category.getSortOrder());

        stmt->setString(3,category.getDescription());

        stmt->setInt64(4,category.getId());

        return stmt->executeUpdate() > 0;
    }
    catch (...)
    {
        return false;
    }
}

std::shared_ptr<Category> MySQLCategoryRepository::findById(long long categoryId) const
{
    try
    {
        auto* conn = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> stmt(
            conn->prepareStatement(
                R"(
                    SELECT id,
                           name,
                           sort_order,
                           description
                    FROM categories
                    WHERE id = ?
                )"
            )
        );

        stmt->setInt64(1,categoryId);

        std::unique_ptr<sql::ResultSet> rs(stmt->executeQuery());

        if (!rs->next())
        {
            return nullptr;
        }

        return CategoryMapper::fromResultSet(*rs);
    }
    catch (...)
    {
        return nullptr;
    }
}

std::vector<std::shared_ptr<Category>> MySQLCategoryRepository::findByName(const std::string& keyword) const
{
    std::vector<std::shared_ptr<Category>> categories;

    try
    {
        auto* conn = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> stmt(
            conn->prepareStatement(
                R"(
                    SELECT id,
                           name,
                           sort_order,
                           description
                    FROM categories
                    WHERE name LIKE ?
                    ORDER BY sort_order ASC, id ASC
                )"
            )
        );

        stmt->setString(1,"%" + keyword + "%");

        std::unique_ptr<sql::ResultSet> rs(stmt->executeQuery());

        while (rs->next())
        {
            categories.push_back(CategoryMapper::fromResultSet(*rs));
        }
    }
    catch (...)
    {
        return {};
    }

    return categories;
}

std::vector<std::shared_ptr<Category>> MySQLCategoryRepository::findAll() const
{
    std::vector<std::shared_ptr<Category>> categories;

    try
    {
        auto* conn = m_database.getConnection();

        std::unique_ptr<sql::Statement> stmt(conn->createStatement());

        std::unique_ptr<sql::ResultSet> rs(
            stmt->executeQuery(
                R"(
                    SELECT id,
                           name,
                           sort_order,
                           description
                    FROM categories
                    ORDER BY sort_order ASC, id ASC
                )"
            )
        );

        while (rs->next())
        {
            categories.push_back(CategoryMapper::fromResultSet(*rs));
        }
    }
    catch (...)
    {
        return {};
    }

    return categories;
}