#pragma once

#include <cstdint>
#include <string>

struct BorrowRecordViewDTO
{
    std::int64_t id = 0;

    std::string username;

    std::string bookTitle;

    std::string inventoryNo;

    std::string borrowTime;

    std::string dueTime;

    std::string returnTime;

    int status = 0;
};