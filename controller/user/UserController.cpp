#include "UserController.h"

UserController::UserController(UserService& userService):userService(userService) {

}

bool UserController::addUser(const UserDTO& dto) {
	return userService.addUser(dto);
}
bool UserController::removeUser(int userId) {
	return userService.removeUser(userId);
}
bool UserController::updateUser(const UserDTO& dto) {
	return userService.updateUser(dto);
}

UserDTO UserController::findUserById(int userId) const {
	return userService.findUserById(userId);
}

std::vector<UserDTO> UserController::findUsersByName(const std::string& username) const {
	return userService.findUsersByName(username);
}

std::vector<UserDTO> UserController::getAllUsers() const
{
	return userService.getAllUsersDTO();
}