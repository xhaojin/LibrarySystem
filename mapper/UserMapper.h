#pragma once

#include <memory>

#include "model/User.h"

#include <mysql/jdbc.h>

// SQLite版本（已弃用）
// #include <QSqlQuery>

class UserMapper
{
public:
    //==========================
    // MySQL
    //==========================

    static std::shared_ptr<User> fromResultSet(sql::ResultSet& rs);

    //==========================
    // SQLite（保留接口，已弃用）
    //==========================

    //static std::shared_ptr<User> fromQuery(const QSqlQuery& query);

    //static void bindToQuery(QSqlQuery& query, const User& user);
};