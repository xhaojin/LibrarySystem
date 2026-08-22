#pragma once

#include <memory>

#include "model/Book.h"

#include <mysql/jdbc.h>

//数据库(ResultSet) ↔ Model(Book)

class BookMapper
{
public:
    static std::shared_ptr<Book> fromResultSet(sql::ResultSet& rs);
};