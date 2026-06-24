#pragma once

#include "../interfaces/IUserRepository.h"
#include "SQLiteDatabase.h"

class SQLiteUserRepository :public IUserRepository {
public:
    explicit SQLiteUserRepository(SQLiteDatabase& database);

    bool add(std::shared_ptr<User> user) override;

    bool remove(int bookId) override;

    bool update(const User& user) override;

    std::shared_ptr<User> findById(int userId) const override;

    std::shared_ptr<User> findByUsername(const std::string& username) const override;

    std::vector<std::shared_ptr<User>> findAll() const override;
private:

    SQLiteDatabase& db;
};