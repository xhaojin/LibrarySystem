#include "User.h"

User::User(
    int id,
    std::string username,
    std::string password,
    std::string name,
    Gender gender,
    int age,
    std::string phone,
    bool enabled,
    bool deleted)
    : m_id(id),
    m_username(std::move(username)),
    m_password(std::move(password)),
    m_name(std::move(name)),
    m_gender(gender),
    m_age(age),
    m_phone(std::move(phone)),
    m_enabled(enabled),
    m_deleted(deleted)
{
}

//================ Getter =================

int User::getId() const
{
    return m_id;
}

const std::string& User::getUsername() const
{
    return m_username;
}

const std::string& User::getPassword() const
{
    return m_password;
}

const std::string& User::getName() const
{
    return m_name;
}

Gender User::getGender() const
{
    return m_gender;
}

int User::getAge() const
{
    return m_age;
}

const std::string& User::getPhone() const
{
    return m_phone;
}

bool User::isEnabled() const
{
    return m_enabled;
}

bool User::isDeleted() const
{
    return m_deleted;
}

const std::string& User::getLastLoginIp() const
{
    return m_lastLoginIp;
}

const std::optional<std::string>& User::getLastLoginTime() const
{
    return m_lastLoginTime;
}

//================ Setter =================

void User::setUsername(const std::string& username)
{
    m_username = username;
}

void User::setPassword(const std::string& password)
{
    m_password = password;
}

void User::setName(const std::string& name)
{
    m_name = name;
}

void User::setGender(Gender gender)
{
    m_gender = gender;
}

void User::setAge(int age)
{
    m_age = age;
}

void User::setPhone(const std::string& phone)
{
    m_phone = phone;
}

void User::setEnabled(bool enabled)
{
    m_enabled = enabled;
}

void User::setDeleted(bool deleted)
{
    m_deleted = deleted;
}

void User::setLastLoginIp(const std::string& ip)
{
    m_lastLoginIp = ip;
}

void User::setLastLoginTime(const std::optional<std::string>& time)
{
    m_lastLoginTime = time;
}