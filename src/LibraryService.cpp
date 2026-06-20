#include "LibraryService.h"

LibraryService::LibraryService(Library& library) : library(library) {
}

void LibraryService::borrowBook(int userId, int bookId) {
	auto user = library.findUser(userId);
	if (!user) {
		std::string msg = "[USER_ERROR] User not found: " + std::to_string(userId);
		Logger::log(msg);
		throw std::runtime_error(msg);
	}
	auto book = library.findBook(bookId);
	if (!book) {
		std::string msg = "[BOOK_ERROR] Book not found: " + std::to_string(bookId);
		Logger::log(msg);
		throw std::runtime_error(msg);
	}
	if (book->isBorrowed()) {
		std::string msg = "[STATE_ERROR] Book already borrowed: " + std::to_string(bookId);
		Logger::log(msg);
		throw std::runtime_error(msg);
	}
	book->setBorrowedStatus(true);
	user->addBorrowedBook(bookId);
	Logger::log("User " + std::to_string(userId) + " borrowed book " + std::to_string(bookId)); // Log the borrowing action
}

void LibraryService::returnBook(int userId, int bookId) {
	auto user = library.findUser(userId);
	if (!user) {
		std::string msg = "[USER_ERROR] User not found: " + std::to_string(userId);
		Logger::log(msg);
		throw std::runtime_error(msg);
	}
	auto book = library.findBook(bookId);
	if (!book) {
		std::string msg = "[BOOK_ERROR] Book not found: " + std::to_string(bookId);
		Logger::log(msg);
		throw std::runtime_error(msg);
	}
	if (!book->isBorrowed()) {
		std::string msg = "[STATE_ERROR] Book already borrowed: " + std::to_string(bookId);
		Logger::log(msg);
		throw std::runtime_error(msg);
	}
	if (user->getBorrowedBookIds().find(bookId) != user->getBorrowedBookIds().end()) {
		book->setBorrowedStatus(false);
		user->removeBorrowedBook(bookId);
		Logger::log("User " + std::to_string(userId) + " returned book " + std::to_string(bookId)); // Log the returning action
	}
}

std::vector<BookDTO> LibraryService::findBooksByTitle(const std::string& keyword) {
	std::vector<BookDTO> bookDTOs;
	auto books = library.findBooksByTitle(keyword);
	for (const auto& book : books) {
		bookDTOs.push_back(BookDTO{
			book->getId(),
			book->getTitle(),
			book->getAuthor(),
			book->getPublisher(),
			book->getPrice(),
			book->isBorrowed()
		});
	}
	return bookDTOs;
}


std::vector<BookDTO> LibraryService::getBooksSortedByPrice() const {
	std::vector<BookDTO> sortedBooks;
	for (const auto& pair : library.getBooks()) {
		const auto& book = pair.second;
		sortedBooks.push_back(BookDTO{
			book->getId(),
			book->getTitle(),
			book->getAuthor(),
			book->getPublisher(),
			book->getPrice(),
			book->isBorrowed()
		});
	}
	std::sort(sortedBooks.begin(), sortedBooks.end(), [](const BookDTO& a, const BookDTO& b) {
		return a.price < b.price;
		});
	return sortedBooks;
}

std::vector<BookDTO> LibraryService::getBooksSortedByTitle() const {
	std::vector<BookDTO> sortedBooks;
	for (const auto& pair : library.getBooks()) {
		const auto& book = pair.second;
		sortedBooks.push_back(BookDTO{
			book->getId(),
			book->getTitle(),
			book->getAuthor(),
			book->getPublisher(),
			book->getPrice(),
			book->isBorrowed()
			});
	}
	std::sort(sortedBooks.begin(), sortedBooks.end(), [](const BookDTO& a, const BookDTO& b) {
		return a.title < b.title;
		});
	return sortedBooks;
}

int LibraryService::getTotalBooks() const {
	return library.getBooks().size();
}
int LibraryService::getBorrowedBooksCount() const {
	int count = 0;
	for (const auto& pair : library.getBooks()) {
		if (pair.second->isBorrowed()) {
			count++;
		}
	}
	return count;
}
int LibraryService::getAvailableBooksCount() const {
	int count = 0;
	for (const auto& pair : library.getBooks()) {
		if (!pair.second->isBorrowed()) {
			count++;
		}
	}
	return count;
}
int LibraryService::getUserCount() const {
	return library.getUsers().size();
}
double LibraryService::getBorrowRate() const {
	return getTotalBooks() == 0 ? 0.0 : static_cast<double>(getBorrowedBooksCount()) / getTotalBooks();
}

std::vector<BookDTO> LibraryService::getAllBooksDTO() const {
	std::vector<BookDTO> bookDTOs;
	for (const auto& pair: library.getBooks()) {
		bookDTOs.push_back(BookDTO{
			pair.second->getId(),
			pair.second->getTitle(),
			pair.second->getAuthor(),
			pair.second->getPublisher(),
			pair.second->getPrice(),
			pair.second->isBorrowed()
		});
	}
	return bookDTOs;
}

std::vector<UserDTO> LibraryService::getAllUsersDTO() const {
	std::vector<UserDTO> userDTOs;
	for (const auto& pair: library.getUsers()) {
		userDTOs.push_back(UserDTO{
			pair.second->getId(),
			pair.second->getName(),
			(pair.second->getGender() == Gender::Male ? "男" : "女"),
			pair.second->getAge(),
			pair.second->getPhone(),
			(int)pair.second->getBorrowedBookIds().size()
		});
	}
	return userDTOs;
}