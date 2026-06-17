#include "Library.h"

bool Library::addBook(std::shared_ptr<Book> book) {
	if (books.find(book->getId()) != books.end()) {
		return false; // Book already exists
	}
	books[book->getId()] = book;
	return true;
}

bool Library::addUser(std::shared_ptr<User> user) {
	if (users.find(user->getId()) != users.end()) {
		return false; // User already exists
	}
	users[user->getId()] = user;
	return true;
}

void Library::removeBook(int bookId) {
	auto book = findBook(bookId); // Ensure the book exists before attempting to remove it
	if (book && !book->isBorrowed()) {
		books.erase(bookId);
	}
}

void Library::removeUser(int userId) {
	auto user = findUser(userId); // Ensure the user exists before attempting to remove it
	if (user && user->getBorrowedBookIds().empty()) {
		users.erase(userId);
	}
}

std::shared_ptr<Book> Library::findBook(int bookId) const {
	auto it = books.find(bookId);
	if (it != books.end()) {
		return it->second;
	}
	return nullptr;
}

std::shared_ptr<User> Library::findUser(int userId) const {
	auto it = users.find(userId);
	if (it != users.end()) {
		return it->second;
	}
	return nullptr;
}

bool Library::borrowBook(int userId, int bookId) {
	auto user = findUser(userId);
	auto book = findBook(bookId);
	if (!user || !book) {
		return false; // User or book not found
	}
	if (book->borrow()) {
		user->addBorrowedBook(bookId);
		return true;
	}
	return false;
}

bool Library::returnBook(int userId, int bookId) {
	auto user = findUser(userId);
	auto book = findBook(bookId);
	if (!user || !book) {
		return false; // User or book not found
	}
	if (user->getBorrowedBookIds().find(bookId) != user->getBorrowedBookIds().end() && book->returnBook()) {
		user->removeBorrowedBook(bookId);
		return true;
	}
	return false;
}

void Library::showAllBooks() const {
	for (const auto& pair : books) {
		pair.second->showBookInfo();
	}
}

void Library::showAllUsers() const {
	for (const auto& pair : users) {
		pair.second->showUserInfo();
	}
}