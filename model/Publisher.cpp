#include "Publisher.h"

Publisher::Publisher(
    long long id,
    const std::string& name,
    const std::string& contact,
    const std::string& website)
    : id(id),
    name(name),
    contact(contact),
    website(website)
{
}

long long Publisher::getId() const
{
    return id;
}

const std::string& Publisher::getName() const
{
    return name;
}

const std::string& Publisher::getContact() const
{
    return contact;
}

const std::string& Publisher::getWebsite() const
{
    return website;
}