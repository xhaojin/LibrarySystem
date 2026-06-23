#include "domain/User.h"

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

bool User::addBorrowedBook(int bookId) {
	if (std::find(this->borrowedBookIds.begin(), this->borrowedBookIds.end(), bookId) == this->borrowedBookIds.end()) {
		this->borrowedBookIds.insert(bookId);
		return true; // Successfully added
	}
	return false;
}

bool User::removeBorrowedBook(int bookId) {
	if (std::find(this->borrowedBookIds.begin(), this->borrowedBookIds.end(), bookId) != this->borrowedBookIds.end()) {
		this->borrowedBookIds.erase(bookId);
		return true; // Successfully added
	}
	return false;
}

const std::unordered_set<int>& User::getBorrowedBookIds() const {
	return this->borrowedBookIds;
}