#pragma once

#include <cstdint>
#include <string>

struct BookCopyDTO
{
    std::int64_t id;

    std::int64_t bookId;

    std::string inventoryNo;

    std::string location;

    int status;
};