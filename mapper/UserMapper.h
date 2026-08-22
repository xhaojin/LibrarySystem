#pragma once

#include <memory>

#include "model/User.h"

#include <mysql/jdbc.h>

//数据库(ResultSet) ↔ Model(User)

class UserMapper
{
public:
    static std::shared_ptr<User> fromResultSet(sql::ResultSet& rs);
};