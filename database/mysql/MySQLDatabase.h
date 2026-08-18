#pragma once

#include "../IDatabase.h"
#include "../DBConfig.h"

#include <memory>

#include <mysql/jdbc.h>

class MySQLDatabase : public IDatabase
{
public:

    explicit MySQLDatabase(const DBConfig& config);

    ~MySQLDatabase() override;

    bool connect() override;

    void disconnect() override;

    bool isConnected() const override;

    sql::Connection* getConnection() const override;

    void beginTransaction();

    void commit();

    void rollback();

private:

    DBConfig m_config;

    sql::mysql::MySQL_Driver* m_driver;

    std::unique_ptr<sql::Connection> m_connection;
};