#include "UserService.h"

UserService::UserService(IUserRepository& userRepo) :userRepo(userRepo) {

}

std::vector<UserDTO> UserService::getAllUsersDTO() const {
	std::vector<UserDTO> userDTOs;
	for (const auto& user : userRepo.findAll()) {
		userDTOs.push_back(UserDTO{
			user->getId(),
			user->getName(),
			user->getUsername(),
			user->getRole(),
			(user->getGender() == Gender::Male ? "男" : "女"),
			user->getAge(),
			user->getPhone()
			});
	}
	return userDTOs;
}