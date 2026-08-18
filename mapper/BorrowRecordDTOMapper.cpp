#include "BorrowRecordDTOMapper.h"

#include <mysql/jdbc.h>

BorrowRecordDTO BorrowRecordDTOMapper::toDTO(sql::ResultSet& rs)
{
    BorrowRecordDTO record;

    record.id = rs.getInt64("id");
    record.userId = rs.getInt64("user_id");
    record.copyId = rs.getInt64("copy_id");

    record.operatorId = rs.isNull("operator_id")? 0: rs.getInt64("operator_id");

    record.borrowTime = rs.getString("borrow_time");
    record.dueTime = rs.getString("due_time");

    record.returnTime = rs.isNull("return_time")? "": rs.getString("return_time");

    record.status = rs.getInt("status");

    record.remark = rs.isNull("remark")? "": rs.getString("remark");

    return record;
}