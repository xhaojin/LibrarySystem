#include "UserDTOMapper.h"

UserDTO UserDTOMapper::toDTO(const User& user)
{
    UserDTO dto;

    dto.id = user.getId();
    dto.username = user.getUsername();
    dto.name = user.getName();

    switch (user.getGender())
    {
    case Gender::Male:
        dto.gender = "男";
        break;

    case Gender::Female:
        dto.gender = "女";
        break;

    default:
        dto.gender = "未知";
        break;
    }

    dto.age = user.getAge();
    dto.phone = user.getPhone();
    dto.enabled = user.isEnabled();

    return dto;
}

User UserDTOMapper::toModel(const UserDTO& dto)
{
    Gender gender;

    if (dto.gender == "Male")
    {
        gender = Gender::Male;
    }
    else if (dto.gender == "Female")
    {
        gender = Gender::Female;
    }
    else
    {
        gender = Gender::Unknown;
    }

    return User(
        dto.id,
        dto.username,
        "",
        dto.name,
        gender,
        dto.age,
        dto.phone,
        dto.enabled
    );
}