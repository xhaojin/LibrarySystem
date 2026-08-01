#include "MySQLBookRepository.h"

#include "../../mapper/BookMapper.h"
#include "../../mapper/BookDTOMapper.h"

#include <mysql/jdbc.h>

MySQLBookRepository::MySQLBookRepository(MySQLDatabase& database) : m_database(database)
{
}

bool MySQLBookRepository::add(std::shared_ptr<Book> book)
{
	try
	{
		auto* conn = m_database.getConnection();

		std::unique_ptr<sql::PreparedStatement> stmt(
			conn->prepareStatement(
				R"(INSERT INTO books(
                    isbn,
                    title,
                    author,
                    publisher_id,
                    category_id,
                    publish_year,
                    price,
                    cover_url,
                    description,
                    status
                )
                VALUES(?,?,?,?,?,?,?,?,?,?))"));

		stmt->setString(1, book->getISBN());
		stmt->setString(2, book->getTitle());
		stmt->setString(3, book->getAuthor());

		if (book->getPublisherId() == 0)
			stmt->setNull(4, sql::DataType::BIGINT);
		else
			stmt->setInt64(4, book->getPublisherId());

		if (book->getCategoryId() == 0)
			stmt->setNull(5, sql::DataType::BIGINT);
		else
			stmt->setInt64(5, book->getCategoryId());

		if (book->getPublishYear() == 0)
			stmt->setNull(6, sql::DataType::INTEGER);
		else
			stmt->setInt(6, book->getPublishYear());

		stmt->setDouble(7, book->getPrice());

		stmt->setString(8, book->getCoverUrl());

		stmt->setString(9, book->getDescription());

		stmt->setInt(10, static_cast<int>(book->getStatus()));

		return stmt->executeUpdate() > 0;
	}
	catch (...)
	{
		return false;
	}
}

bool MySQLBookRepository::remove(long long bookId)
{
	try
	{
		auto* conn = m_database.getConnection();

		std::unique_ptr<sql::PreparedStatement> stmt(
			conn->prepareStatement(
				"UPDATE books SET deleted = TRUE WHERE id = ?"));

		stmt->setInt64(1, bookId);

		return stmt->executeUpdate() > 0;
	}
	catch (...)
	{
		return false;
	}
}

bool MySQLBookRepository::update(const Book& book)
{
	try
	{
		auto* conn = m_database.getConnection();

		std::unique_ptr<sql::PreparedStatement> stmt(
			conn->prepareStatement(
				R"(UPDATE books
                SET
                    isbn=?,
                    title=?,
                    author=?,
                    publisher_id=?,
                    category_id=?,
                    publish_year=?,
                    price=?,
                    cover_url=?,
                    description=?,
                    status=?
                WHERE id=?)"));

		stmt->setString(1, book.getISBN());
		stmt->setString(2, book.getTitle());
		stmt->setString(3, book.getAuthor());

		if (book.getPublisherId() == 0)
			stmt->setNull(4, sql::DataType::BIGINT);
		else
			stmt->setInt64(4, book.getPublisherId());

		if (book.getCategoryId() == 0)
			stmt->setNull(5, sql::DataType::BIGINT);
		else
			stmt->setInt64(5, book.getCategoryId());

		if (book.getPublishYear() == 0)
			stmt->setNull(6, sql::DataType::INTEGER);
		else
			stmt->setInt(6, book.getPublishYear());

		stmt->setDouble(7, book.getPrice());

		stmt->setString(8, book.getCoverUrl());

		stmt->setString(9, book.getDescription());

		stmt->setInt(10, static_cast<int>(book.getStatus()));

		stmt->setInt64(11, book.getId());

		return stmt->executeUpdate() > 0;
	}
	catch (...)
	{
		return false;
	}
}

bool MySQLBookRepository::updateStatus(long long bookId, BookStatus status)
{
	try
	{
		auto* conn = m_database.getConnection();

		std::unique_ptr<sql::PreparedStatement> stmt(
			conn->prepareStatement(
				"UPDATE books SET status=? WHERE id=?"));

		stmt->setInt(1, static_cast<int>(status));
		stmt->setInt64(2, bookId);

		return stmt->executeUpdate() > 0;
	}
	catch (...)
	{
		return false;
	}
}

std::shared_ptr<Book> MySQLBookRepository::findById(long long bookId) const
{
	auto* conn = m_database.getConnection();

	std::unique_ptr<sql::PreparedStatement> stmt(
		conn->prepareStatement(
			"SELECT * FROM books WHERE id = ? AND deleted = FALSE"));

	stmt->setInt64(1, bookId);

	std::unique_ptr<sql::ResultSet> rs(stmt->executeQuery());

	if (!rs->next())
		return nullptr;

	return BookMapper::fromResultSet(*rs);
}

std::shared_ptr<Book> MySQLBookRepository::findByISBN(const std::string& isbn) const
{
	auto* conn = m_database.getConnection();

	std::unique_ptr<sql::PreparedStatement> stmt(
		conn->prepareStatement(
			"SELECT * FROM books WHERE isbn = ? AND deleted = FALSE"));

	stmt->setString(1, isbn);

	std::unique_ptr<sql::ResultSet> rs(stmt->executeQuery());

	if (!rs->next())
		return nullptr;

	return BookMapper::fromResultSet(*rs);
}

std::vector<std::shared_ptr<Book>> MySQLBookRepository::findByTitle(const std::string& keyword) const
{
	std::vector<std::shared_ptr<Book>> books;

	auto* conn = m_database.getConnection();

	std::unique_ptr<sql::PreparedStatement> stmt(
		conn->prepareStatement(
			"SELECT * FROM books "
			"WHERE title LIKE ? "
			"AND deleted = FALSE "
			"ORDER BY title"));

	stmt->setString(1, "%" + keyword + "%");

	std::unique_ptr<sql::ResultSet> rs(stmt->executeQuery());

	while (rs->next())
	{
		books.push_back(BookMapper::fromResultSet(*rs));
	}

	return books;
}

std::vector<std::shared_ptr<Book>> MySQLBookRepository::findAll() const
{
	std::vector<std::shared_ptr<Book>> books;

	auto* conn = m_database.getConnection();

	std::unique_ptr<sql::Statement> stmt(conn->createStatement());

	std::unique_ptr<sql::ResultSet> rs(
		stmt->executeQuery(
			"SELECT * FROM books "
			"WHERE deleted = FALSE "
			"ORDER BY id"));

	while (rs->next())
	{
		books.push_back(BookMapper::fromResultSet(*rs));
	}

	return books;
}

std::vector<std::shared_ptr<Book>> MySQLBookRepository::sortByTitle() const
{
	std::vector<std::shared_ptr<Book>> books;

	auto* conn = m_database.getConnection();

	std::unique_ptr<sql::Statement> stmt(conn->createStatement());

	std::unique_ptr<sql::ResultSet> rs(
		stmt->executeQuery(
			"SELECT * FROM books "
			"WHERE deleted = FALSE "
			"ORDER BY title ASC"));

	while (rs->next())
	{
		books.push_back(BookMapper::fromResultSet(*rs));
	}

	return books;
}

std::vector<std::shared_ptr<Book>> MySQLBookRepository::sortByPrice() const
{
	std::vector<std::shared_ptr<Book>> books;

	auto* conn = m_database.getConnection();

	std::unique_ptr<sql::Statement> stmt(conn->createStatement());

	std::unique_ptr<sql::ResultSet> rs(
		stmt->executeQuery(
			"SELECT * FROM books "
			"WHERE deleted = FALSE "
			"ORDER BY price ASC"));

	while (rs->next())
	{
		books.push_back(BookMapper::fromResultSet(*rs));
	}

	return books;
}

int MySQLBookRepository::getTotalBooks() const
{
	auto* conn = m_database.getConnection();

	std::unique_ptr<sql::Statement> stmt(conn->createStatement());

	std::unique_ptr<sql::ResultSet> rs(
		stmt->executeQuery(
			"SELECT COUNT(*) AS total "
			"FROM books "
			"WHERE deleted = FALSE"));

	if (rs->next())
	{
		return rs->getInt("total");
	}

	return 0;
}

std::vector<BookDTO> MySQLBookRepository::findAllWithDetail() const
{
	std::vector<BookDTO> books;

	try
	{
		auto* conn = m_database.getConnection();

		std::unique_ptr<sql::Statement> stmt(conn->createStatement());

		std::unique_ptr<sql::ResultSet> rs(
			stmt->executeQuery(
				R"(SELECT b.id,b.isbn,b.title,b.author,p.id AS publisher_id,p.name AS publisher_name,c.id AS category_id,
            c.name AS category_name,
            b.publish_year,b.price,b.cover_url, b.description,b.deleted,
            b.status FROM books b
			LEFT JOIN publishers p ON b.publisher_id=p.id
			LEFT JOIN categories c ON b.category_id=c.id
			WHERE b.deleted=FALSE
			ORDER BY b.id)"));

		while (rs->next())
		{
			auto book = BookMapper::fromResultSet(*rs);
			std::string publisher = rs->isNull("publisher_name") ? "" : rs->getString("publisher_name");
			std::string category = rs->isNull("category_name") ? "" : rs->getString("category_name");
			books.emplace_back(BookDTOMapper::toDTO(*book, publisher, category));
		}
	}
	catch (const sql::SQLException& e)
	{
		std::cerr << "SQL error: " << e.what() << std::endl;
	}

	return books;
}