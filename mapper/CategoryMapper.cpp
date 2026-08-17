#include "CategoryMapper.h"

std::shared_ptr<Category> CategoryMapper::fromResultSet(sql::ResultSet& rs)
{
    return std::make_shared<Category>(
        rs.getInt64("id"),
        rs.getString("name"),
        rs.getInt("sort_order"),
        rs.getString("description")
    );
}