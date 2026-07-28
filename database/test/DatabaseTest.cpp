#include "DatabaseTest.h"

#include <mysql/jdbc.h>

#include <iostream>
#include <memory>

void DatabaseTest::testMySQLConnection()
{
    try
    {
        // 获取 Driver
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();

        // 建立连接
        std::unique_ptr<sql::Connection> conn(
            driver->connect("tcp://127.0.0.1:3306","root","1234")
        );

        // 选择数据库
        conn->setSchema("library");

        std::cout << "==================================" << std::endl;
        std::cout << "MySQL Connect Success!" << std::endl;

        // 创建 Statement
        std::unique_ptr<sql::Statement> stmt(conn->createStatement());

        // 执行 SQL
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT VERSION()"));

        if (res->next())
        {
            std::cout << "MySQL Version: "<< res->getString(1)<< std::endl;
        }

        std::cout << "==================================" << std::endl;
    }
    catch (const sql::SQLException& e)
    {
        std::cout << "==================================" << std::endl;
        std::cout << "MySQL Connect Failed!" << std::endl;
        std::cout << "Error : " << e.what() << std::endl;
        std::cout << "ErrorCode : " << e.getErrorCode() << std::endl;
        std::cout << "SQLState : " << e.getSQLState() << std::endl;
        std::cout << "==================================" << std::endl;
    }
}