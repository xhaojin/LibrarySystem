#pragma once

#include <memory>

#include "model/Category.h"

#include <mysql/jdbc.h>

class CategoryMapper
{
public:
    // MySQL ResultSet -> Category
    static std::shared_ptr<Category> fromResultSet(sql::ResultSet& rs);
};