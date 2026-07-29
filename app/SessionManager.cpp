#include "SessionManager.h"

#include <stdexcept>

void SessionManager::login(const UserDTO& user)
{
	m_currentUser = user;
}

void SessionManager::logout()
{
	m_currentUser.reset();
}

bool SessionManager::isLoggedIn() const
{
	return m_currentUser.has_value();
}

const UserDTO& SessionManager::currentUser() const
{
	if (!m_currentUser.has_value())
	{
		throw std::logic_error("No active session.");
	}

	return *m_currentUser;
}

bool SessionManager::isAdmin() const
{
	//return isLoggedIn() && m_currentUser.value().role == Role::Admin;
	return true;
}

bool SessionManager::isUser() const
{
	//return isLoggedIn() && m_currentUser.value().role == Role::User;
	return true;
}