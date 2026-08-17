#pragma once

#include <string>

class Category
{
private:
    long long id;
    std::string name;
    int sortOrder;
    std::string description;

public:
    Category(
        long long id,
        const std::string& name,
        int sortOrder,
        const std::string& description
    );

    long long getId() const;

    const std::string& getName() const;

    int getSortOrder() const;

    const std::string& getDescription() const;
};