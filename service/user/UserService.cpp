#include "UserService.h"

UserService::UserService(IUserRepository& userRepo) :userRepo(userRepo) {

}

bool UserService::addUser(const UserDTO& dto) {
	std::shared_ptr<User> user;
	user = std::make_shared<User>(dto.id, dto.name, (dto.gender == "Male" ? Gender::Male : Gender::Female), dto.age, dto.phone, dto.username, "", dto.role);
	return userRepo.add(user);
}
bool UserService::removeUser(int userId) {
	return userRepo.remove(userId);
}
bool UserService::updateUser(const UserDTO& dto) {
	return userRepo.update(User(dto.id, dto.name, (dto.gender == "Male" ? Gender::Male : Gender::Female), dto.age, dto.phone, dto.username, "", dto.role));
}

UserDTO UserService::findUserById(int userId) const {
	auto user = userRepo.findById(userId);
	return UserDTO{
		user->getId(),
		user->getName(),
		user->getUsername(),
		user->getRole(),
		user->getGender() == Gender::Male ? "男" : "女",
		user->getAge(),
		user->getPhone()
	};
}

std::vector<UserDTO> UserService::findUsersByName(const std::string& name) const {
	std::vector<UserDTO> userDTOs;
	for (const auto& user : userRepo.findByName(name)) {
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