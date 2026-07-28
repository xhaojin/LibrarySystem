//#include "MySQLDatabase.h"
//
//#include <QSqlError>
//#include <QDebug>
//
//MySQLDatabase::MySQLDatabase(const DBConfig& config): config_(config)
//{
//    db_ = QSqlDatabase::addDatabase("QMYSQL"); // 创建连接对象
//}
//
//MySQLDatabase::~MySQLDatabase()
//{
//    disconnect();
//}
//
//bool MySQLDatabase::connect()
//{
//    db_.setHostName(QString::fromStdString(config_.host));
//    db_.setPort(config_.port);
//    db_.setDatabaseName(QString::fromStdString(config_.database));
//    db_.setUserName(QString::fromStdString(config_.username));
//    db_.setPassword(QString::fromStdString(config_.password));
//
//    if (!db_.open())
//    {
//        qDebug() << db_.lastError().text();
//        return false;
//    }
//
//    return true;
//}
//
//void MySQLDatabase::disconnect()
//{
//    if (db_.isOpen())
//    {
//        db_.close();
//    }
//}
//
//bool MySQLDatabase::isConnected() const
//{
//    return db_.isOpen();
//}
//
//QSqlDatabase MySQLDatabase::database() const
//{
//    return db_;
//}