#pragma once

#include "IDatabase.h"
#include "DBConfig.h"

#include <QSqlDatabase>

class MySQLDatabase : public IDatabase
{
public:
    explicit MySQLDatabase(const DBConfig& config);
    ~MySQLDatabase() override;

    bool connect() override;
    void disconnect() override;
    bool isConnected() const override;

    QSqlDatabase database() const override;

private:
    DBConfig config_;
    QSqlDatabase db_;
};