#include "../../../include/repository/SQLite/SQLiteDatabase.h"

SQLiteDatabase::SQLiteDatabase()
{
}

SQLiteDatabase::~SQLiteDatabase()
{
	close();
}

bool SQLiteDatabase::open(const QString& dbPath)
{
    db = QSqlDatabase::addDatabase("QSQLITE", "LibraryConnection");

    db.setDatabaseName(dbPath);

    return db.open();
}

void SQLiteDatabase::close()
{
    if (db.isOpen())
    {
        db.close();
    }
}

bool SQLiteDatabase::initialize()
{
    QSqlQuery query(db);

    bool success = true;

    success &= query.exec(
        "CREATE TABLE IF NOT EXISTS books ("
        "id INTEGER PRIMARY KEY,"
        "title TEXT NOT NULL,"
        "author TEXT,"
        "publisher TEXT,"
        "price REAL,"
        "borrowed INTEGER"
        ");");

    success &= query.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY,"
        "name TEXT NOT NULL,"
        "gender TEXT,"
        "age INTEGER,"
        "phone TEXT,"
        "username TEXT UNIQUE,"
        "password TEXT,"
        "role TEXT"
        ");");

    success &= query.exec(
        "CREATE TABLE IF NOT EXISTS borrow_records ("
        "id INTEGER PRIMARY KEY,"
        "user_id INTEGER,"
        "book_id INTEGER,"
        "borrow_time TEXT,"
        "return_time TEXT,"
        "FOREIGN KEY(user_id) REFERENCES users(id),"
        "FOREIGN KEY(book_id) REFERENCES books(id)"
        ");");

    return success;
}

QSqlDatabase& SQLiteDatabase::database()
{
    return db;
}