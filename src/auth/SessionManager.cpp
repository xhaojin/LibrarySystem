#include "auth/SessionManager.h"
#include <iostream>

std::optional<UserDTO> SessionManager::currentUserInfo;

void SessionManager::login(const UserDTO& user)
{
    currentUserInfo = user;
}

void SessionManager::logout()
{
    currentUserInfo.reset();
}

bool SessionManager::isLoggedIn()
{
    return currentUserInfo.has_value();
}

const UserDTO& SessionManager::currentUser()
{
    if (!currentUserInfo)
    {
        throw std::runtime_error("No user logged in");
    }

    return *currentUserInfo;
}

bool SessionManager::isAdmin() {
    return currentUserInfo.has_value() && currentUserInfo->role == Role::Admin;
}