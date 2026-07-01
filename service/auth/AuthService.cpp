#include "AuthService.h"

AuthService::AuthService(IUserRepository& userRepo):userRepo(userRepo) {

}

UserDTO AuthService::login(const std::string& username, const std::string& password) {
	auto user = userRepo.findByUsername(username);
	if (!user) {
		std::string msg = "[LOGIN_ERROR] User not found: " + username;
		Logger::log(msg);
		throw std::runtime_error(msg);
	}
	if (user->getPassword() != password) {
		std::string msg = "[LOGIN_ERROR] Invalid password for user: " + username;
		Logger::log(msg);
		throw std::runtime_error(msg);
	}
	UserDTO userDTO;
	userDTO.id = user->getId();
	userDTO.name = user->getName();
	userDTO.username = user->getUsername();
	userDTO.role = user->getRole();
	userDTO.gender = (user->getGender() == Gender::Male ? "男" : "女");
	userDTO.age = user->getAge();
	userDTO.phone = user->getPhone();
	Logger::log("[LOGIN_SUCCESS] Username: " + username);
	return userDTO;
}