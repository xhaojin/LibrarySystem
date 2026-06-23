#pragma once

#include <string>
#include <chrono>
#include "domain/Role.h"

class Session
{
public:

    int userId;

    std::string username;

    Role role;

    std::chrono::system_clock::time_point loginTime;
};