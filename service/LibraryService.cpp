#include "LibraryService.h"

LibraryService::LibraryService(IBookRepository& bookRepo, IUserRepository& userRepo, IBorrowRecordRepository& borrowRepo)
	: bookRepo(bookRepo), userRepo(userRepo), borrowRepo(borrowRepo) {
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
	// 修改图书状态
	book->setBorrowedStatus(true);

	if (!bookRepo.update(*book))
	{
		throw std::runtime_error("Failed to update book status");
	}

	// 创建借阅记录
	auto record = std::make_shared<BorrowRecord>(0, userId, bookId, QDateTime::currentDateTime(), std::nullopt);

	if (!borrowRepo.add(record))
	{
		throw std::runtime_error("Failed to create borrow record");
	}

	Logger::log("[BORROW_SUCCESS] User " + std::to_string(userId) + " borrowed book " + std::to_string(bookId));
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
	auto record = borrowRepo.findActiveRecord(userId, bookId);

	if (!record)
	{
		std::string msg = "[RECORD_ERROR] Active borrow record not found";

		Logger::log(msg);

		throw std::runtime_error(msg);
	}

	// 更新借阅记录
	record->setReturnTime(QDateTime::currentDateTime());

	if (!borrowRepo.update(*record))
	{
		throw std::runtime_error("Failed to update borrow record");
	}

	// 更新图书状态
	book->setBorrowedStatus(false);

	if (!bookRepo.update(*book))
	{
		throw std::runtime_error("Failed to update book status");
	}

	Logger::log("[RETURN_SUCCESS] User " + std::to_string(userId) + " returned book " + std::to_string(bookId));
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
	for (const auto& book : bookRepo.sortByPrice()) {
		sortedBooks.push_back(BookDTO{
			book->getId(),
			book->getTitle(),
			book->getAuthor(),
			book->getPublisher(),
			book->getPrice(),
			book->isBorrowed()
			});
	}
	return sortedBooks;
}

std::vector<BookDTO> LibraryService::getBooksSortedByTitle() const {
	std::vector<BookDTO> sortedBooks;
	for (const auto& book : bookRepo.sortByTitle()) {
		sortedBooks.push_back(BookDTO{
			book->getId(),
			book->getTitle(),
			book->getAuthor(),
			book->getPublisher(),
			book->getPrice(),
			book->isBorrowed()
			});
	}
	return sortedBooks;
}

int LibraryService::getTotalBooks() const {
	return bookRepo.getTotalBooks();
}
int LibraryService::getBorrowedBooksCount() const {
	return bookRepo.getBorrowedBooksCount();
}
int LibraryService::getAvailableBooksCount() const {
	return bookRepo.getAvailableBooksCount();
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
			user->getPhone()
			});
	}
	return userDTOs;
}

std::vector<BorrowRecordDTO> LibraryService::getAllBorrowRecords() const {
	std::vector<BorrowRecordDTO> recordDTOs;
	for (const auto& record : borrowRepo.findAll()) {
		recordDTOs.push_back(BorrowRecordDTO{
			record->getId(),
			record->getUserId(),
			record->getBookId(),
			record->getBorrowTime().toString().toStdString(),
			record->getReturnTime().value().toString().toStdString(),
			record->getReturnTime().has_value()
			});
	}
	return recordDTOs;
}