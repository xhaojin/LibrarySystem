#pragma once

#include "../interfaces/IUserRepository.h"
#include "database/mysql/MySQLDatabase.h"

class MySQLUserRepository : public IUserRepository
{
public:
    explicit MySQLUserRepository(MySQLDatabase& database);

    bool add(const User& user) override;

    bool remove(int userId) override;

    bool update(const User& user) override;

    std::shared_ptr<User> findById(int userId) const override;

    std::vector<std::shared_ptr<User>> findByName(const std::string& name) const override;

    std::shared_ptr<User> findByUsername(const std::string& username) const override;

    std::vector<std::shared_ptr<User>> findAll() const override;

private:
    MySQLDatabase& m_database;
};