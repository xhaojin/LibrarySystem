#include "Category.h"

Category::Category(
    long long id,
    const std::string& name,
    int sortOrder,
    const std::string& description)
    : id(id),
    name(name),
    sortOrder(sortOrder),
    description(description)
{
}

long long Category::getId() const
{
    return id;
}

const std::string& Category::getName() const
{
    return name;
}

int Category::getSortOrder() const
{
    return sortOrder;
}

const std::string& Category::getDescription() const
{
    return description;
}