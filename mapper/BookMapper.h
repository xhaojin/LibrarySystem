#pragma once

#include <memory>

#include "model/Book.h"

#include <mysql/jdbc.h>

// SQLite版本（已弃用）
// #include <QSqlQuery>

class BookMapper
{
public:
    //==========================
    // MySQL
    //==========================
    
    static std::shared_ptr<Book> fromResultSet(sql::ResultSet& rs);

    //==========================
    // SQLite（保留接口，已弃用）
    //==========================

    //static std::shared_ptr<Book> fromQuery(const QSqlQuery& query);

    //static void bindToQuery(QSqlQuery& query,const Book& book);
};