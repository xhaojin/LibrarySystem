#pragma once

#include <QString>
#include <QSqlQuery>
#include <QSqlDatabase>

class SQLiteDatabase
{
public:

    SQLiteDatabase();

    ~SQLiteDatabase();

    bool open(const QString& dbPath);

    void close();

    bool initialize();

    QSqlDatabase& database();

private:

    QSqlDatabase db;
};