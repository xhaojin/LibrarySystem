#include "SQLiteBookRepository.h"
#include "mapper/BookMapper.h"

SQLiteBookRepository::SQLiteBookRepository(SQLiteDatabase& database) :db(database)
{
}

bool SQLiteBookRepository::add(std::shared_ptr<Book> book)
{
	QSqlQuery query(db.database());

	query.prepare(
		"INSERT INTO books "
		"(id,title,author,publisher,"
		"price,borrowed)"
		"VALUES "
		"(:id,:title,:author,"
		":publisher,:price,"
		":borrowed)");

	BookMapper::bindToQuery(query, *book);

	return query.exec();
}

bool SQLiteBookRepository::remove(int bookId) {
	QSqlQuery query(db.database());

	query.prepare("DELETE FROM books WHERE id=:id");

	query.bindValue(":id", bookId);

	return query.exec();
}

bool SQLiteBookRepository::update(const Book& book) {

	QSqlQuery query(db.database());

	query.prepare("UPDATE books SET title = :title, author = :author, "
		"publisher = :publisher, price = :price, borrowed = :borrowed "
		"WHERE id = :id");

	BookMapper::bindToQuery(query, book);

	return query.exec();
}

std::shared_ptr<Book> SQLiteBookRepository::findById(int bookId) const
{
	QSqlQuery query(db.database());

	query.prepare("SELECT * FROM books WHERE id=:id");

	query.bindValue(":id", bookId);

	if (!query.exec())
	{
		return nullptr;
	}

	if (!query.next())
	{
		return nullptr;
	}

	return BookMapper::fromQuery(query);
}

std::vector<std::shared_ptr<Book>> SQLiteBookRepository::findByTitle(const std::string& titleKeyWord) const {
	std::vector<std::shared_ptr<Book>> books;

	QSqlQuery query(db.database());

	query.prepare("SELECT * FROM books WHERE title LIKE :keyword");

	query.bindValue(":keyword", "%" + QString::fromStdString(titleKeyWord) + "%");

	if (query.exec()) {
		while (query.next())
		{
			books.push_back(BookMapper::fromQuery(query));
		}
	}

	return books;
}

std::vector<std::shared_ptr<Book>> SQLiteBookRepository::findAll() const
{
	std::vector<std::shared_ptr<Book>> books;

	QSqlQuery query(db.database());

	query.exec("SELECT * FROM books");

	while (query.next())
	{
		books.push_back(BookMapper::fromQuery(query));
	}

	return books;
}

std::vector<std::shared_ptr<Book>> SQLiteBookRepository::sortByTitle() const {
	std::vector<std::shared_ptr<Book>> books;

	QSqlQuery query(db.database());

	query.exec("SELECT * FROM books ORDER BY title ASC");

	while (query.next())
	{
		books.push_back(BookMapper::fromQuery(query));
	}

	return books;
}
std::vector<std::shared_ptr<Book>> SQLiteBookRepository::sortByPrice() const {
	std::vector<std::shared_ptr<Book>> books;

	QSqlQuery query(db.database());

	query.exec("SELECT * FROM books ORDER BY price ASC");

	while (query.next())
	{
		books.push_back(BookMapper::fromQuery(query));
	}

	return books;
}

int SQLiteBookRepository::getTotalBooks() const {
	QSqlQuery query(db.database());

	if (!query.exec("SELECT COUNT(*) FROM books")) {
		return -1;
	}

	if (query.next()) {
		return query.value(0).toInt();
	}

	return 0;
}

int SQLiteBookRepository::getBorrowedBooksCount() const {
	QSqlQuery query(db.database());

	if (!query.exec("SELECT COUNT(*) FROM books WHERE borrowed = 1")) {
		return -1;
	}

	if (query.next()) {
		return query.value(0).toInt();
	}

	return 0;
}

int	SQLiteBookRepository::getAvailableBooksCount() const {
	QSqlQuery query(db.database());

	if (!query.exec("SELECT COUNT(*) FROM books WHERE borrowed = 0")) {
		return -1;
	}

	if (query.next()) {
		return query.value(0).toInt();
	}

	return 0;
}