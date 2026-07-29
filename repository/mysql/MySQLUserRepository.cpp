#include "MySQLUserRepository.h"
#include "../../mapper/UserMapper.h"
#include <mysql/jdbc.h>

MySQLUserRepository::MySQLUserRepository(MySQLDatabase& database) : m_database(database)
{
}

bool MySQLUserRepository::add(const User& user)
{
    try
    {
        auto* conn = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> stmt(
            conn->prepareStatement
            (R"(INSERT INTO users(username,password,name,gender,age,phone,enabled)VALUES(?,?,?,?,?,?,?))")
        );

        stmt->setString(1, user.getUsername());
        stmt->setString(2, user.getPassword());
        stmt->setString(3, user.getName());
        stmt->setInt(4, static_cast<int>(user.getGender()));
        stmt->setInt(5, user.getAge());
        stmt->setString(6, user.getPhone());
        stmt->setBoolean(7, user.isEnabled());

        return stmt->executeUpdate() > 0;
    }
    catch (...)
    {
        return false;
    }
}

bool MySQLUserRepository::remove(int userId)
{
    try
    {
        auto* conn = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> stmt(
            conn->prepareStatement(
                "UPDATE users SET deleted = TRUE WHERE id = ? "));

        stmt->setInt(1, userId);

        return stmt->executeUpdate() > 0;
    }
    catch (...)
    {
        return false;
    }
}

bool MySQLUserRepository::update(const User& user)
{
    try
    {
        auto* conn = m_database.getConnection();

        std::unique_ptr<sql::PreparedStatement> stmt(
            conn->prepareStatement
            (R"(UPDATE users SET username = ?,password = ?,name = ?,gender = ?,age = ?,phone = ?,enabled = ? WHERE id = ?)"));

        stmt->setString(1, user.getUsername());
        stmt->setString(2, user.getPassword());
        stmt->setString(3, user.getName());
        stmt->setInt(4, static_cast<int>(user.getGender()));
        stmt->setInt(5, user.getAge());
        stmt->setString(6, user.getPhone());
        stmt->setBoolean(7, user.isEnabled());
        stmt->setInt64(8, user.getId());

        return stmt->executeUpdate() > 0;
    }
    catch (...)
    {
        return false;
    }
}

std::shared_ptr<User> MySQLUserRepository::findById(int userId) const
{
    auto* conn = m_database.getConnection();

    std::unique_ptr<sql::PreparedStatement> stmt(
        conn->prepareStatement(
            "SELECT * FROM users WHERE id = ? AND deleted = FALSE"));

    stmt->setInt(1, userId);

    std::unique_ptr<sql::ResultSet> rs(stmt->executeQuery());

    if (!rs->next()) return nullptr;

    return UserMapper::fromResultSet(*rs);
}

std::shared_ptr<User> MySQLUserRepository::findByUsername(const std::string& username) const
{
    auto* conn = m_database.getConnection();

    std::unique_ptr<sql::PreparedStatement> stmt(
        conn->prepareStatement("SELECT * FROM users WHERE username = ? AND deleted = FALSE"));

    stmt->setString(1, username);

    std::unique_ptr<sql::ResultSet> rs(stmt->executeQuery());

    if (!rs->next()) return nullptr;

    return UserMapper::fromResultSet(*rs);
}

std::vector<std::shared_ptr<User>> MySQLUserRepository::findByName(const std::string& name) const
{
    std::vector<std::shared_ptr<User>> users;

    auto* conn = m_database.getConnection();

    std::unique_ptr<sql::PreparedStatement> stmt(
        conn->prepareStatement("SELECT * FROM users WHERE name LIKE ? AND deleted = FALSE"));

    stmt->setString(1, "%" + name + "%");

    std::unique_ptr<sql::ResultSet> rs(stmt->executeQuery());

    while (rs->next())
    {
        users.push_back(UserMapper::fromResultSet(*rs));
    }

    return users;
}

std::vector<std::shared_ptr<User>> MySQLUserRepository::findAll() const
{
    std::vector<std::shared_ptr<User>> users;

    auto* conn = m_database.getConnection();

    std::unique_ptr<sql::Statement> stmt(conn->createStatement());

    std::unique_ptr<sql::ResultSet> rs(
        stmt->executeQuery("SELECT * FROM users WHERE deleted = FALSE ORDER BY id"));

    while (rs->next())
    {
        users.push_back(UserMapper::fromResultSet(*rs));
    }

    return users;
}