#include "../../../include/repository/SQLite/SQLiteUserRepository.h"
#include "../../../include/mapper/UserMapper.h"

SQLiteUserRepository::SQLiteUserRepository(SQLiteDatabase& database) : db(database) {}

bool SQLiteUserRepository::add(std::shared_ptr<User> user) {
	QSqlQuery query(db.database());

	query.prepare(
		"INSERT INTO users "
		"(id,name,gender,age,phone,username,password,role)"
		"VALUES "
		"(:id,:name,:gender,:age,:phone,:username,:password,:role)");

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
		"age = :age, phone = :phone, username = :username, password = :password, role = :role "
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

std::shared_ptr<User> SQLiteUserRepository::findByUsername(const std::string& username) const {
	std::shared_ptr<User> user;

	QSqlQuery query(db.database());

	query.prepare("SELECT * FROM users WHERE title LIKE :keyword");

	query.bindValue(":keyword", QString::fromStdString(username));

	while (query.next())
	{
		return UserMapper::fromQuery(query);
	}

	return user;
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