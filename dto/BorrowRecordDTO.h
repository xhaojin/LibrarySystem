#pragma once

#include <string>

struct BorrowRecordDTO
{
    int id;

    int userId;

    int bookId;

    std::string username;

    std::string bookTitle;

    std::string borrowTime;

    std::string returnTime;

    bool returned;
};