#pragma once

#include <QSqlDatabase>

class IDatabase
{
public:
    virtual ~IDatabase() = default;

    virtual bool connect() = 0;

    virtual void disconnect() = 0;

    virtual bool isConnected() const = 0;

    virtual QSqlDatabase database() const = 0;
};