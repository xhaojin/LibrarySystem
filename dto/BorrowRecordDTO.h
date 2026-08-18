#pragma once

#include <cstdint>
#include <string>

struct BorrowRecordDTO
{
    std::int64_t id;

    std::int64_t userId;

    std::int64_t copyId;

    std::int64_t operatorId;

    std::string borrowTime;

    std::string dueTime;

    std::string returnTime;

    int status;

    std::string remark;
};