#pragma once

#include <optional>

#include "dto/UserDTO.h"
#include "LoginStatus.h"

struct LoginResult
{
    LoginStatus status;
    std::optional<UserDTO> user;
};