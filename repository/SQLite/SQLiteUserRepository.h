#pragma once

#include "../interfaces/IUserRepository.h"
#include "database/sqlite/SQLiteDatabase.h"

class SQLiteUserRepository :public IUserRepository {
public:
    explicit SQLiteUserRepository(SQLiteDatabase& database);

    bool add(const User& user) override;

    bool remove(int bookId) override;

    bool update(const User& user) override;

    std::shared_ptr<User> findById(int userId) const override;

    std::vector<std::shared_ptr<User>> findByName(const std::string& name) const override;

    std::shared_ptr<User> findByUserName(const std::string& username) const override;

    std::vector<std::shared_ptr<User>> findAll() const override;
private:

    SQLiteDatabase& db;
};