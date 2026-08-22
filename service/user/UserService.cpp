#include "UserService.h"
#include "mapper/UserDTOMapper.h"

UserService::UserService(IUserRepository& userRepo) :userRepo(userRepo) {

}

bool UserService::addUser(const UserDTO& dto) {
	return userRepo.add(UserDTOMapper::toModel(dto));
}
bool UserService::removeUser(int userId) {
	return userRepo.remove(userId);
}
bool UserService::updateUser(const UserDTO& dto) {
	return userRepo.update(UserDTOMapper::toModel(dto));
}

UserDTO UserService::findUserById(int userId) const {
	auto user = userRepo.findById(userId);
	return UserDTOMapper::toDTO(*user);
}

std::vector<UserDTO> UserService::findUsersByName(const std::string& name) const {
	std::vector<UserDTO> userDTOs;
	for (const auto& user : userRepo.findByName(name)) {
		userDTOs.push_back(UserDTOMapper::toDTO(*user));
	}
	return userDTOs;
}

std::vector<UserDTO> UserService::getAllUsersDTO() const {
	std::vector<UserDTO> userDTOs;
	for (const auto& user : userRepo.findAll()) {
		userDTOs.push_back(UserDTOMapper::toDTO(*user));
	}
	return userDTOs;
}