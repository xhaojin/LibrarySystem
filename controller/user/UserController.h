#pragma once

#include "service/user/UserService.h"

class UserController
{
private:
	UserService& userService;

public:
	explicit UserController(UserService& userService);

	bool addUser(const UserDTO& dto);
	bool removeUser(int userId);
	bool updateUser(const UserDTO& dto);
	UserDTO findUserById(int userId) const;
	std::vector<UserDTO> findUsersByName(const std::string& username) const;
	std::vector<UserDTO> getAllUsers() const;
};