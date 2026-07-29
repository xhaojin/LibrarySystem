#pragma once

enum class LoginStatus
{
    Success,          // 登录成功
    UserNotFound,     // 用户不存在
    WrongPassword,    // 密码错误
    Disabled,         // 用户被禁用
    DatabaseError     // 数据库异常
};