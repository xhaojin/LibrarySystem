#pragma once

#include "IDatabase.h"
#include "DBConfig.h"

#include <memory>
#include <string>

namespace sql
{
    class Connection;
}

class MySQLDatabase : public IDatabase
{
public:
    explicit MySQLDatabase(const DBConfig& config);

    ~MySQLDatabase() override;

    // 禁止拷贝
    MySQLDatabase(const MySQLDatabase&) = delete;
    MySQLDatabase& operator=(const MySQLDatabase&) = delete;

    // 允许移动
    MySQLDatabase(MySQLDatabase&&) noexcept = default;
    MySQLDatabase& operator=(MySQLDatabase&&) noexcept = default;

public:
    bool connect() override;

    void disconnect() override;

    bool isConnected() const override;

    std::string serverVersion() const;

    sql::Connection* getConnection() const;

private:
    DBConfig config_;

    std::unique_ptr<sql::Connection> connection_;
};