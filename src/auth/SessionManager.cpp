#include "auth/SessionManager.h"

bool SessionManager::isLoggedIn() const
{
	return currentSession.has_value();
}

bool SessionManager::isAdmin() const
{
	return currentSession.has_value() && currentSession->role == Role::Admin;
}

void SessionManager::login(int userId, const std::string& username, Role role)
{
	Session session;

	session.userId = userId;

	session.username = username;

	session.role = role;

	session.loginTime = std::chrono::system_clock::now();

	currentSession = session;
}

void SessionManager::logout()
{
	currentSession.reset();
}

const Session* SessionManager::getSession() const
{
	if (!currentSession)
	{
		return nullptr;
	}

	return &(*currentSession);
}