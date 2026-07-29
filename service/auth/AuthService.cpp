#include "AuthService.h"

#include "mapper/UserDTOMapper.h"

AuthService::AuthService(IUserRepository& userRepo) : userRepo(userRepo)
{
}

LoginResult AuthService::login(const std::string& username,const std::string& password)
{
    try
    {
        auto user = userRepo.findByUsername(username);

        // 用户不存在
        if (!user)
        {
            Logger::log("登录失败：用户不存在 -> " + username);

            return
            {
                LoginStatus::UserNotFound,
                std::nullopt
            };
        }

        // 用户禁用
        if (!user->isEnabled())
        {
            Logger::log("登录失败：用户已禁用 -> " + username);

            return
            {
                LoginStatus::Disabled,
                std::nullopt
            };
        }

        // 密码错误
        if (user->getPassword() != password)
        {
            Logger::log("登录失败：密码错误 -> " + username);

            return
            {
                LoginStatus::WrongPassword,
                std::nullopt
            };
        }

        // 更新登录信息（如果已经实现）
        // userRepo.updateLoginInfo(user->getId(), "127.0.0.1");

        Logger::log("登录成功：" + username);

        return
        {
            LoginStatus::Success,
            UserDTOMapper::toDTO(*user)
        };
    }
    catch (const std::exception& e)
    {
        Logger::log(std::string("System Error: ")+ e.what());

        return
        {
            LoginStatus::DatabaseError,
            std::nullopt
        };
    }
}