#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "model/Role.h"

enum class Gender
{
	Male,
	Female
};

class User
{
private:
	int id;
	std::string name;
	Gender gender;
	int age;
	std::string phone;

	std::string username;
	std::string password;

	Role role;

public:
	User(int id, const std::string& name, Gender gender, int age, const std::string& phone, const std::string& username, const std::string& password, Role role);

	int getId() const;

	const std::string& getName() const;

	const Gender& getGender() const;

	int getAge() const;

	const std::string& getPhone() const;

	const std::string& getUsername() const;

	const std::string& getPassword() const;

	Role getRole() const;

	bool isAdmin() const;
};