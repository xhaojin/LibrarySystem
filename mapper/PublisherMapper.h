#pragma once

#include <memory>

#include "model/Publisher.h"

namespace sql
{
    class ResultSet;
}

class PublisherMapper
{
public:
    static std::shared_ptr<Publisher> fromResultSet(sql::ResultSet& rs);
};