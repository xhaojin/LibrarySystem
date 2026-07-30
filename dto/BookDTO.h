#pragma once

#include <string>

struct BookDTO
{
    long long id;

    std::string isbn;

    std::string title;

    std::string author;

    std::string publisher;

    std::string category;

    int publishYear;

    double price;

    std::string status;
};