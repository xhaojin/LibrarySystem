#pragma once

#include <memory>

namespace sql
{
    class Connection;
}

class IDatabase
{
public:
    virtual ~IDatabase() = default;

    virtual bool connect() = 0;

    virtual void disconnect() = 0;

    virtual bool isConnected() const = 0;

    virtual sql::Connection* getConnection() const = 0;

    virtual void beginTransaction() = 0;

    virtual void commit() = 0;

    virtual void rollback() = 0;
};