#pragma once

#include <string>

class Publisher
{
private:
    long long id;
    std::string name;
    std::string contact;
    std::string website;

public:
    Publisher(
        long long id,
        const std::string& name,
        const std::string& contact,
        const std::string& website
    );

    long long getId() const;

    const std::string& getName() const;

    const std::string& getContact() const;

    const std::string& getWebsite() const;
};