#pragma once

#include <string>

struct CategoryDTO
{
    long long id;

    std::string name;

    int sortOrder;

    std::string description;
};