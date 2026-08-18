#pragma once

#include <string>

struct BookDTO
{
    long long id;

    std::string isbn;

    std::string title;

    std::string author;

    long long publisherId;
    std::string publisher;

    long long categoryId;
    std::string category;

    int publishYear;

    double price;

    std::string coverUrl;

    std::string description;

    std::string status;
};