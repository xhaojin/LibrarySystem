#pragma once

#include "dto/UserDTO.h"
#include "model/User.h"

//Model(User) → DTO(UserDTO)

class UserDTOMapper
{
public:
    static UserDTO toDTO(const User& user);
};