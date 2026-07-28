#include "MySQLDatabase.h"

#include <iostream>

MySQLDatabase::MySQLDatabase(const DBConfig& config) : m_config(config), m_driver(nullptr)
{
}

MySQLDatabase::~MySQLDatabase()
{
	disconnect();
}

bool MySQLDatabase::connect()
{
	if (isConnected())
		return true;

	try
	{
		m_driver = sql::mysql::get_mysql_driver_instance();

		m_connection.reset(m_driver->connect(m_config.getUrl(), m_config.username, m_config.password));

		m_connection->setSchema(m_config.database);

		std::cout << "[MySQL] Connect Success." << std::endl;

		return true;
	}
	catch (const sql::SQLException& e)
	{
		std::cout << "[MySQL] Connect Failed." << std::endl;
		std::cout << e.what() << std::endl;

		m_connection.reset();

		return false;
	}
}

void MySQLDatabase::disconnect()
{
	if (m_connection)
	{
		try
		{
			m_connection->close();
		}
		catch (...)
		{
		}

		m_connection.reset();
	}
}

bool MySQLDatabase::isConnected() const
{
	return m_connection != nullptr &&
		!m_connection->isClosed();
}

sql::Connection* MySQLDatabase::getConnection()
{
	return m_connection.get();
}

void MySQLDatabase::beginTransaction()
{
	m_connection->setAutoCommit(false);
}

void MySQLDatabase::commit()
{
	m_connection->commit();
	m_connection->setAutoCommit(true);
}

void MySQLDatabase::rollback()
{
	m_connection->rollback();
	m_connection->setAutoCommit(true);
}