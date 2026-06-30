#include "model/User.h"

User::User(
	int id,
	const std::string& name,
	Gender gender,
	int age,
	const std::string& phone,
	const std::string& username,
	const std::string& password,
	Role role)
	: id(id), name(name), gender(gender), age(age), phone(phone), username(username), password(password), role(role) {
}

int User::getId() const {
	return this->id;
}
const std::string& User::getName() const {
	return this->name;
}
const Gender& User::getGender() const {
	return this->gender;
}
int User::getAge() const {
	return this->age;
}
const std::string& User::getPhone() const {
	return this->phone;
}
const std::string& User::getUsername() const {
	return this->username;
}

const std::string& User::getPassword() const {
	return this->password;
}

Role User::getRole() const {
	return this->role;
}

bool User::isAdmin() const {
	return this->role == Role::Admin;
}