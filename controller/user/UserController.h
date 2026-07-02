#pragma once

#include "service/user/UserService.h"

class UserController
{
private:
	UserService& userService;

public:
	explicit UserController(UserService& userService);

	std::vector<UserDTO> getAllUsers() const;
};