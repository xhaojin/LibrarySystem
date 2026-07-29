#pragma once

#include <string>
#include <optional>

enum class Gender
{
    Unknown = 0,
    Male = 1,
    Female = 2
};

class User
{
public:
    User(
        int id,
        std::string username,
        std::string password,
        std::string name,
        Gender gender,
        int age,
        std::string phone,
        bool enabled = true,
        bool deleted = false);

    User() = default;

    // Getter
    int getId() const;

    const std::string& getUsername() const;

    const std::string& getPassword() const;

    const std::string& getName() const;

    Gender getGender() const;

    int getAge() const;

    const std::string& getPhone() const;

    bool isEnabled() const;

    bool isDeleted() const;

    const std::string& getLastLoginIp() const;

    const std::optional<std::string>& getLastLoginTime() const;

    // Setter
    void setId(int id);

    void setUsername(const std::string& username);

    void setPassword(const std::string& password);

    void setName(const std::string& name);

    void setGender(Gender gender);

    void setAge(int age);

    void setPhone(const std::string& phone);

    void setEnabled(bool enabled);

    void setDeleted(bool deleted);

    void setLastLoginIp(const std::string& ip);

    void setLastLoginTime(const std::optional<std::string>& time);

private:
    int m_id;

    std::string m_username;

    std::string m_password;

    std::string m_name;

    Gender m_gender;

    int m_age;

    std::string m_phone;

    bool m_enabled;

    bool m_deleted;

    std::string m_lastLoginIp;

    std::optional<std::string> m_lastLoginTime;
};