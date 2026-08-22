#include "BookMapper.h"

std::shared_ptr<Book> BookMapper::fromResultSet(sql::ResultSet& rs)
{
    return std::make_shared<Book>(
        rs.getInt64("id"),
        rs.getString("isbn"),
        rs.getString("title"),
        rs.getString("author"),

        rs.isNull("publisher_id") ? 0 : rs.getInt64("publisher_id"),
        rs.isNull("category_id") ? 0 : rs.getInt64("category_id"),

        rs.isNull("publish_year") ? 0 : rs.getInt("publish_year"),

        rs.isNull("price") ? 0.0 : rs.getDouble("price"),

        rs.isNull("cover_url") ? "" : rs.getString("cover_url"),

        rs.isNull("description") ? "" : rs.getString("description"),

        static_cast<BookStatus>(rs.getInt("status")),

        rs.getBoolean("deleted")
    );
}