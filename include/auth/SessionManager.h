#pragma once

#include <optional>

#include "Session.h"

class SessionManager
{
public:

	bool isLoggedIn() const; // 判断是否有用户登录

	bool isAdmin() const; // 判断当前登录用户是否是管理员

	void login(int userId, const std::string& username, Role role); // 登录

	void logout(); // 登出

	const Session* getSession() const; // 获取当前会话信息，返回nullptr表示没有用户登录

private:

	std::optional<Session> currentSession;
};