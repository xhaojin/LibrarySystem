#pragma once

#include "service/auth/AuthService.h"

class AuthController {
public:
	explicit AuthController(AuthService& authService);

	//登录类
	UserDTO login(const std::string& username, const std::string& password);

private:
	AuthService& authService;
};