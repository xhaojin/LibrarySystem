#pragma once

#include <memory>
#include <vector>
#include <string>

#include "repository/interfaces/IPublisherRepository.h"
#include "database/mysql/MySQLDatabase.h"

class MySQLPublisherRepository : public IPublisherRepository
{
private:
    MySQLDatabase& m_database;

public:
    explicit MySQLPublisherRepository(MySQLDatabase& database);

    // =========================
    // 增删改
    // =========================

    bool add(const Publisher& publisher) override;

    bool update(const Publisher& publisher) override;

    bool remove(long long publisherId) override;

    // =========================
    // 查询
    // =========================

    std::shared_ptr<Publisher> findById(long long publisherId) const override;

    std::shared_ptr<Publisher> findByName(const std::string& name) const override;

    std::vector<std::shared_ptr<Publisher>> findByNameLike(const std::string& keyword) const override;

    std::vector<std::shared_ptr<Publisher>> findAll() const override;

    bool isReferencedByBooks(long long publisherId) const override;
};