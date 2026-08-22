#include "UserMapper.h"

std::shared_ptr<User> UserMapper::fromResultSet(sql::ResultSet& rs)
{
    auto user = std::make_shared<User>();

    user->setId(rs.getInt("id"));

    user->setUsername(rs.getString("username"));

    user->setPassword(rs.getString("password"));

    user->setName(rs.getString("name"));

    user->setGender(static_cast<Gender>(rs.getInt("gender")));

    user->setAge(rs.getInt("age"));

    user->setPhone(rs.getString("phone"));

    user->setEnabled(rs.getBoolean("enabled"));

    user->setDeleted(rs.getBoolean("deleted"));

    // last_login_time 允许为空
    if (!rs.isNull("last_login_time"))
    {
        user->setLastLoginTime(rs.getString("last_login_time"));
    }

    // last_login_ip 允许为空
    if (!rs.isNull("last_login_ip"))
    {
        user->setLastLoginIp(rs.getString("last_login_ip"));
    }

    return user;
}