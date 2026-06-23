#include "service/LibraryService.h"

LibraryService::LibraryService(IBookRepository& bookRepo,IUserRepository& userRepo,IBorrowRecordRepository& borrowRepo)
	: bookRepo(bookRepo),userRepo(userRepo),borrowRepo(borrowRepo) {
}

UserDTO LibraryService::login(const std::string& username, const std::string& password) {
	auto user = userRepo.findByUsername(username);
	if (!user) {
		std::string msg = "[LOGIN_ERROR] User not found: " + username;
		Logger::log(msg);
		throw std::runtime_error(msg);
	}
	if (user->getPassword() != password) {
		std::string msg = "[LOGIN_ERROR] Invalid password for user: " + username;
		Logger::log(msg);
		throw std::runtime_error(msg);
	}
	UserDTO userDTO;
	userDTO.id = user->getId();
	userDTO.name = user->getName();
	userDTO.username = user->getUsername();
	userDTO.role = user->getRole();
	userDTO.gender = (user->getGender() == Gender::Male ? "男" : "女");
	userDTO.age = user->getAge();
	userDTO.phone = user->getPhone();
	userDTO.borrowedCount = (int)user->getBorrowedBookIds().size();
	Logger::log("[LOGIN_SUCCESS] Username: " + username);
	return userDTO;
}


void LibraryService::borrowBook(int userId, int bookId) {
	auto user = userRepo.findById(userId);
	if (!user) {
		std::string msg = "[USER_ERROR] User not found: " + std::to_string(userId);
		Logger::log(msg);
		throw std::runtime_error(msg);
	}
	auto book = bookRepo.findById(bookId);
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

	//auto record = std::make_shared<BorrowRecord>(library.getNextBorrowRecordId(), userId, bookId, QDateTime::currentDateTime());
	//library.getBorrowRecords().borrowRecords.emplace(record->getId(), record);

	book->setBorrowedStatus(true);
	user->addBorrowedBook(bookId);
	Logger::log("User " + std::to_string(userId) + " borrowed book " + std::to_string(bookId)); // Log the borrowing action
}

void LibraryService::returnBook(int userId, int bookId) {
	auto user = userRepo.findById(userId);
	if (!user) {
		std::string msg = "[USER_ERROR] User not found: " + std::to_string(userId);
		Logger::log(msg);
		throw std::runtime_error(msg);
	}
	auto book = bookRepo.findById(bookId);
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
	//for (auto& pair : library.getBorrowRecords())
	//{
	//	auto record = pair.second;

	//	if (record->getUserId() == userId && record->getBookId() == bookId && !record->isReturned())
	//	{
	//		record->returnBook();

	//		break;
	//	}
	//}
	if (user->getBorrowedBookIds().find(bookId) != user->getBorrowedBookIds().end()) {
		book->setBorrowedStatus(false);
		user->removeBorrowedBook(bookId);
		Logger::log("User " + std::to_string(userId) + " returned book " + std::to_string(bookId)); // Log the returning action
	}
}

std::vector<BookDTO> LibraryService::findBooksByTitle(const std::string& keyword) {
	std::vector<BookDTO> bookDTOs;
	auto books = bookRepo.findByTitle(keyword);
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
	for (const auto& book : bookRepo.findAll()) {
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
	for (const auto& book : bookRepo.findAll()) {
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
	return bookRepo.findAll().size();
}
int LibraryService::getBorrowedBooksCount() const {
	int count = 0;
	for (const auto& book : bookRepo.findAll()) {
		if (book->isBorrowed()) {
			count++;
		}
	}
	return count;
}
int LibraryService::getAvailableBooksCount() const {
	int count = 0;
	for (const auto& book : bookRepo.findAll()) {
		if (!book->isBorrowed()) {
			count++;
		}
	}
	return count;
}
int LibraryService::getUserCount() const {
	return userRepo.findAll().size();
}
double LibraryService::getBorrowRate() const {
	return getTotalBooks() == 0 ? 0.0 : static_cast<double>(getBorrowedBooksCount()) / getTotalBooks();
}

std::vector<BookDTO> LibraryService::getAllBooksDTO() const {
	std::vector<BookDTO> bookDTOs;
	for (const auto& book : bookRepo.findAll()) {
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

std::vector<UserDTO> LibraryService::getAllUsersDTO() const {
	std::vector<UserDTO> userDTOs;
	for (const auto& user : userRepo.findAll()) {
		userDTOs.push_back(UserDTO{
			user->getId(),
			user->getName(),
			user->getUsername(),
			user->getRole(),
			(user->getGender() == Gender::Male ? "男" : "女"),
			user->getAge(),
			user->getPhone(),
			(int)user->getBorrowedBookIds().size()
			});
	}
	return userDTOs;
}