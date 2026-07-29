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