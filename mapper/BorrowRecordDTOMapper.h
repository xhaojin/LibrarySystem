#pragma once

#include <memory>

#include "dto/BorrowRecordDTO.h"

namespace sql
{
    class ResultSet;
}

class BorrowRecordDTOMapper
{
public:
    static BorrowRecordDTO toDTO(sql::ResultSet& rs);
};