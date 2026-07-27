#include "MySQLDatabase.h"

#include <mysql/jdbc.h>

#include <iostream>

MySQLDatabase::MySQLDatabase(const DBConfig& config): config_(config)
{
}

MySQLDatabase::~MySQLDatabase()
{
	disconnect();
}

bool MySQLDatabase::connect()
{
	try
	{
		sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();

		std::string url = "tcp://" + config_.host + ":" + std::to_string(config_.port);

		connection_.reset(driver->connect("tcp://127.0.0.1:3306","root","1234"));

		connection_->setSchema(config_.database);

		return true;
	}
	catch (const sql::SQLException& e)
	{
		std::cerr<< "MySQL connect failed: "<< e.what()<< std::endl;

		connection_.reset();

		return false;
	}
}

void MySQLDatabase::disconnect()
{
	if (connection_)
	{
		connection_->close();
		connection_.reset();
	}
}

bool MySQLDatabase::isConnected() const
{
	return connection_ != nullptr && !connection_->isClosed();
}

std::string MySQLDatabase::serverVersion() const
{
	if (!connection_)return {};

	return connection_->getMetaData()->getDatabaseProductVersion();
}

sql::Connection* MySQLDatabase::getConnection() const
{
	return connection_.get();
}