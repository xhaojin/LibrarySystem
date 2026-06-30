#pragma once

#include <memory>

#include "model/User.h"

#include <QSqlQuery>

class UserMapper
{
public:

    static std::shared_ptr<User> fromQuery(const QSqlQuery& query);

    static void bindToQuery(QSqlQuery& query, const User& user);
};