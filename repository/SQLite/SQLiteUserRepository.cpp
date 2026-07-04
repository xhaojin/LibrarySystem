#include "SQLiteUserRepository.h"
#include "mapper/UserMapper.h"

SQLiteUserRepository::SQLiteUserRepository(SQLiteDatabase& database) : db(database) {}

bool SQLiteUserRepository::add(std::shared_ptr<User> user) {
	QSqlQuery query(db.database());

	query.prepare(
		"INSERT INTO users "
		"(name,gender,age,phone,username,role) "
		"VALUES "
		"(:name,:gender,:age,:phone,:username,:role)");

	UserMapper::bindToQuery(query, *user);

	return query.exec();
}

bool SQLiteUserRepository::remove(int userId) {
	QSqlQuery query(db.database());

	query.prepare("DELETE FROM users WHERE id=:id");

	query.bindValue(":id", userId);

	return query.exec();
}

bool SQLiteUserRepository::update(const User& user) {

	QSqlQuery query(db.database());

	query.prepare("UPDATE users SET name = :name, gender = :gender, "
		"age = :age, phone = :phone, username = :username, role = :role "
		"WHERE id = :id");

	UserMapper::bindToQuery(query, user);

	return query.exec();
}

std::shared_ptr<User> SQLiteUserRepository::findById(int userId) const {
	QSqlQuery query(db.database());

	query.prepare("SELECT * FROM users WHERE id=:id");

	query.bindValue(":id", userId);

	if (!query.exec())
	{
		return nullptr;
	}

	if (!query.next())
	{
		return nullptr;
	}

	return UserMapper::fromQuery(query);
}

std::vector<std::shared_ptr<User>> SQLiteUserRepository::findByUsername(const std::string& username) const {
	std::vector<std::shared_ptr<User>> users;

	QSqlQuery query(db.database());

	query.prepare("SELECT * FROM users WHERE username LIKE :username");

	query.bindValue(":username", "%" + QString::fromStdString(username) + "%");

	query.exec();

	while (query.next())
	{
		users.push_back(UserMapper::fromQuery(query));
	}

	return users;
}

std::vector<std::shared_ptr<User>> SQLiteUserRepository::findAll() const {
	std::vector<std::shared_ptr<User>> users;

	QSqlQuery query(db.database());

	query.exec("SELECT * FROM users");

	while (query.next())
	{
		users.push_back(UserMapper::fromQuery(query));
	}

	return users;
}