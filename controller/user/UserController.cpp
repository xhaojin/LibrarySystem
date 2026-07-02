#include "UserController.h"

UserController::UserController(UserService& userService):userService(userService) {

}

std::vector<UserDTO> UserController::getAllUsers() const
{
	return userService.getAllUsersDTO();
}