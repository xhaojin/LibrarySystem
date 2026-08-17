#pragma once

#include <memory>
#include <vector>
#include <string>

#include "model/Category.h"

class ICategoryRepository
{
public:
    virtual ~ICategoryRepository() = default;

    virtual bool add(const Category& category) = 0;

    virtual bool remove(long long categoryId) = 0;

    virtual bool update(const Category& category) = 0;

    virtual std::shared_ptr<Category> findById(long long categoryId) const = 0;

    virtual std::vector<std::shared_ptr<Category>> findByName(const std::string& keyword) const = 0;

    virtual std::vector<std::shared_ptr<Category>> findAll() const = 0;

    virtual bool isReferencedByBooks(long long publisherId) const = 0;
};