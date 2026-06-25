#pragma once

#include <string>

struct BorrowRecordDTO
{
    int id;

    int userId;

    int bookId;

    std::string borrowTime;

    std::string returnTime;

    bool returned;
};