#include "UserMapper.h"

std::shared_ptr<User> UserMapper::fromQuery(const QSqlQuery& query)
{
	return std::make_shared<User>(query.value("id").toInt(),

		query.value("name").toString().toStdString(),

		query.value("gender").toString().toStdString() == "Male" ? Gender::Male : Gender::Female,

		query.value("age").toInt(),

		query.value("phone").toString().toStdString(),

		query.value("username").toString().toStdString(),

		query.value("password").toString().toStdString(),

		query.value("role").toString().toStdString() == "User" ? Role::User : Role::Admin
	);
}

void UserMapper::bindToQuery(QSqlQuery& query, const User& user)
{
	query.bindValue(":id", user.getId());

	query.bindValue(":name", QString::fromStdString(user.getName()));

	query.bindValue(":gender", user.getGender() == Gender::Male ? "Male" : "Female");

	query.bindValue(":age", user.getAge());

	query.bindValue(":phone", QString::fromStdString(user.getPhone()));

	query.bindValue(":username", QString::fromStdString(user.getUsername()));

	query.bindValue(":password", QString::fromStdString(user.getPassword()));

	query.bindValue(":role", user.getRole() == Role::Admin ? "Admin" : "User");
}