#include "AuthController.h"

AuthController::AuthController(AuthService& authService):authService(authService) {

}

LoginResult AuthController::login(const std::string& username, const std::string& password)
{
	try
	{
		auto result = authService.login(username, password);
		return result;
	}
	catch (const std::exception& e)
	{
		Logger::log(std::string("[UI_ERROR] ") + e.what());
		throw;
	}
}