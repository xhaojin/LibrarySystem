#pragma once

#include <optional>

#include "dto/UserDTO.h"

/*
* 会话管理
*/

class SessionManager
{
public:

	void login(const UserDTO& user); //登录

	void logout(); //退出登录

	bool isLoggedIn() const; //是否已登录

	const UserDTO& currentUser() const; //当前登录用户

	bool isAdmin() const; //权限判断

	bool isUser() const; //权限判断

private:

	std::optional<UserDTO> m_currentUser;
};