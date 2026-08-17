#pragma once

#include "repository/interfaces/ICategoryRepository.h"
#include "database/mysql/MySQLDatabase.h"

class MySQLCategoryRepository : public ICategoryRepository
{
public:
    explicit MySQLCategoryRepository(MySQLDatabase& database);

    bool add(const Category& category) override;

    bool remove(long long categoryId) override;

    bool update(const Category& category) override;

    std::shared_ptr<Category> findById(long long categoryId) const override;

    std::vector<std::shared_ptr<Category>> findByName(const std::string& keyword) const override;

    std::vector<std::shared_ptr<Category>> findAll() const override;

private:
    MySQLDatabase& m_database;
};