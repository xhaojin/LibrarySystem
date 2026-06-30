#pragma once

#include "model/User.h"

class IUserRepository
{
public:
    virtual ~IUserRepository() = default;

    virtual bool add(std::shared_ptr<User> user) = 0;

    virtual bool remove(int userId) = 0;

    virtual bool update(const User& user) = 0;

    virtual std::shared_ptr<User> findById(int userId) const = 0;

    virtual std::shared_ptr<User> findByUsername(const std::string& username) const = 0;

    virtual std::vector<std::shared_ptr<User>> findAll() const = 0;
};