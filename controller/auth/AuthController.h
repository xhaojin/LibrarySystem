#pragma once

#include "service/auth/AuthService.h"

class AuthController {
public:
	explicit AuthController(AuthService& authService);

	LoginResult login(const std::string& username, const std::string& password);

private:
	AuthService& authService;
};