#include "Book.h"

Book::Book(
	int id,
	const std::string& title,
	const std::string& author,
	const std::string& publisher,
	double price)
	: id(id),
	title(title),
	author(author),
	publisher(publisher),
	price(price),
	BorrowedStatus(false)
{
}

int Book::getId() const {
	return this->id;
}

const std::string& Book::getTitle() const {
	return this->title;
}

const std::string& Book::getAuthor() const {
	return this->author;
}

const std::string& Book::getPublisher() const {
	return this->publisher;
}

double Book::getPrice() const {
	return this->price;
}

bool Book::isBorrowed() const {
	return this->BorrowedStatus;
}

void Book::setPrice(double price) {
	if (price >= 0) {
		this->price = price;
	}
}