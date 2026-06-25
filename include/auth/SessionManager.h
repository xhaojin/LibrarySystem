#pragma once

#include <optional>

#include "../dto/UserDTO.h"

class SessionManager
{
public:

	static void login(const UserDTO& user);

	static void logout();

	static bool isLoggedIn();

	static const UserDTO& currentUser();

	static bool isAdmin();

private:

	static std::optional<UserDTO> currentUserInfo;
};