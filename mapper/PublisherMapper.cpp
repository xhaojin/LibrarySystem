#include "PublisherMapper.h"

#include <mysql/jdbc.h>

std::shared_ptr<Publisher> PublisherMapper::fromResultSet(sql::ResultSet& rs)
{
    const long long id = rs.getInt64("id");

    const std::string name = rs.getString("name");

    const std::string contact = rs.getString("contact");

    const std::string website = rs.getString("website");

    return std::make_shared<Publisher>(
        id,
        name,
        contact,
        website
    );
}