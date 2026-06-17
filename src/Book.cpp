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

bool Book::borrow() {
	if (!this->BorrowedStatus) {
		this->BorrowedStatus = true;
		return true; // Successfully borrowed
	}
	return false; // Book is already borrowed
}

bool Book::returnBook() {
	if (this->BorrowedStatus) {
		this->BorrowedStatus = false;
		return true; // Successfully returned
	}
	return false; // Book was not borrowed
}

void Book::showBookInfo() {
	std::cout << "Book ID: " << this->id << std::endl;
	std::cout << "Title: " << this->title << std::endl;
	std::cout << "Author: " << this->author << std::endl;
	std::cout << "Publisher: " << this->publisher << std::endl;
	std::cout << "Price: $" << this->price << std::endl;
	std::cout << "Borrowed Status: " << (this->BorrowedStatus ? "Yes" : "No") << std::endl;
}