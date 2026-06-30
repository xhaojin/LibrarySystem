#pragma once
#include "model/Book.h"
#include <vector>

class IBookRepository
{
public:
	virtual ~IBookRepository() = default;

	virtual bool add(std::shared_ptr<Book> book) = 0;

	virtual bool remove(int bookId) = 0;

	virtual bool update(const Book& book) = 0;

	virtual std::shared_ptr<Book> findById(int bookId) const = 0;

	virtual std::vector<std::shared_ptr<Book>> findByTitle(const std::string& titleKeyWord) const = 0;

	virtual std::vector<std::shared_ptr<Book>> findAll() const = 0;

	virtual std::vector<std::shared_ptr<Book>> sortByTitle() const = 0;

	virtual std::vector<std::shared_ptr<Book>> sortByPrice() const = 0;

	virtual int getTotalBooks() const = 0;

	virtual int getBorrowedBooksCount() const = 0;

	virtual int	getAvailableBooksCount() const = 0;
};