#pragma once

#include <memory>

#include "model/Book.h"

#include <QSqlQuery>

class BookMapper
{
public:
    //==========================
    // MySQL
    //==========================
    


    //==========================
    // SQLite（保留接口，已弃用）
    //==========================

    //static std::shared_ptr<Book> fromQuery(const QSqlQuery& query);

    //static void bindToQuery(QSqlQuery& query,const Book& book);
};