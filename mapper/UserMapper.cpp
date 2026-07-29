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

//std::shared_ptr<User> UserMapper::fromQuery(const QSqlQuery& query)
//{
//	return std::make_shared<User>(query.value("id").toInt(),
//
//		query.value("name").toString().toStdString(),
//
//		query.value("gender").toString().toStdString() == "Male" ? Gender::Male : Gender::Female,
//
//		query.value("age").toInt(),
//
//		query.value("phone").toString().toStdString(),
//
//		query.value("username").toString().toStdString(),
//
//		query.value("password").toString().toStdString(),
//
//		query.value("role").toString().toStdString() == "User" ? Role::User : Role::Admin
//	);
//}

//void UserMapper::bindToQuery(QSqlQuery& query, const User& user)
//{
//	query.bindValue(":id", user.getId());
//
//	query.bindValue(":name", QString::fromStdString(user.getName()));
//
//	query.bindValue(":gender", user.getGender() == Gender::Male ? "Male" : "Female");
//
//	query.bindValue(":age", user.getAge());
//
//	query.bindValue(":phone", QString::fromStdString(user.getPhone()));
//
//	query.bindValue(":username", QString::fromStdString(user.getUsername()));
//
//	query.bindValue(":password", QString::fromStdString(user.getPassword()));
//
//	query.bindValue(":role", user.getRole() == Role::Admin ? "Admin" : "User");
//}