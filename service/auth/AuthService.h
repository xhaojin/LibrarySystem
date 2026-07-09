#pragma once

#include "dto/UserDTO.h"
#include "common/utils/logger.h"
#include <optional>
#include "repository/interfaces/IUserRepository.h"

class AuthService {
private:
	IUserRepository& userRepo;

public:
	explicit AuthService(IUserRepository& userRepo);
	std::optional<UserDTO> login(const std::string& username, const std::string& password); //登录方法
};