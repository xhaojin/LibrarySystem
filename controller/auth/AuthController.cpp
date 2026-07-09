#include "AuthController.h"

AuthController::AuthController(AuthService& authService):authService(authService) {

}

std::optional<UserDTO> AuthController::login(const std::string& username, const std::string& password)
{
	try
	{
		auto user = authService.login(username, password);
		return user;
	}
	catch (const std::exception& e)
	{
		Logger::log(std::string("[UI_ERROR] ") + e.what());
		throw;
	}
}