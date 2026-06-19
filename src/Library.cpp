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

bool Library::saveBooksToFile(const std::string& filename) const {
	std::ofstream outFile(filename);
	if (!outFile) {
		return false; // Failed to open file
	}
	outFile << "bookId" << "," << "title" << "," << "author" << "," << "publisher" << "," 
		<< "price" << "," << "borrowedStatus" << "\n"; // Write header line
	for (const auto& pair : books) {
		const auto& book = pair.second;
		outFile << book->getId() << ","
			<< book->getTitle() << ","
			<< book->getAuthor() << ","
			<< book->getPublisher() << ","
			<< book->getPrice() << ","
			<< (book->isBorrowed() ? "true" : "false") << "\n";
	}
	outFile.close();
	return true;
}

bool Library::loadBooksFromFile(const std::string& filename) {
	std::ifstream inFile(filename);
	if (!inFile) {
		return false; // Failed to open file
	}
	std::string line;
	std::getline(inFile, line); // Skip header line
	while (std::getline(inFile,line)) {
		std::stringstream ss(line);
		std::string token;
		std::getline(ss, token, ',');
		int bookId = std::stoi(token);
		std::getline(ss, token, ',');
		std::string title = token;
		std::getline(ss, token, ',');
		std::string author = token;
		std::getline(ss, token, ',');
		std::string publisher = token;
		std::getline(ss, token, ',');
		double price = std::stod(token);
		books.insert({ bookId, std::make_shared<Book>(bookId, title, author, publisher, price) });
	}
	return true;
}

bool Library::saveUsersToFile(const std::string& filename) const {
	std::ofstream outFile(filename);
	if (!outFile) {
		return false;
	}
	outFile << "userId" << "," << "name" << "," << "gender" << "," << "age" << "," 
		<< "phone" << "," << "borrowedBookIds" << "\n"; // Write header line
	for (const auto& pair: users) {
		const auto& user = pair.second;
		outFile << user->getId() << ","
			<< user->getName() << ","
			<< ((user->getGender() == Gender::Male) ? "Male" : "Female") << ","
			<< user->getAge() << ','
			<< user->getPhone() << ',';
		for (int bookId: user->getBorrowedBookIds()) {
			outFile << bookId << "|";
		}
		outFile << "\n";
	}
	outFile.close();
	return true;
}

bool Library::loadUsersFromFile(const std::string& filename) {
	std::ifstream inFile(filename);
	if (!inFile) {
		return false;
	}
	std::string line;
	std::getline(inFile, line); // Skip header line
	while (std::getline(inFile, line)) {
		std::stringstream ss(line);
		std::string token;
		std::getline(ss, token, ',');
		int userId = std::stoi(token);
		std::getline(ss, token, ',');
		std::string name = token;
		std::getline(ss, token, ',');
		Gender gender = (token == "Male") ? Gender::Male : Gender::Female;
		std::getline(ss, token, ',');
		int age = std::stoi(token);
		std::getline(ss, token, ',');
		std::string phone = token;
		auto user = std::make_shared<User>(userId, name, gender, age, phone);
		std::getline(ss, token);
		if (!token.empty()) {
			std::stringstream borrowedBooksStream(token);
			std::string borrowedBooksStr;
			while (std::getline(borrowedBooksStream, borrowedBooksStr, '|')) {
				int borrowedBookId = std::stoi(borrowedBooksStr);
				user->addBorrowedBook(borrowedBookId);
			}
		}
		users.emplace(userId, user);
	}
	inFile.close();
	return true;
}

void Library::restoreBorrowStatus() {
	for (const auto& pair : users) {
		const auto& user = pair.second;
		for (int bookId : user->getBorrowedBookIds()) {
			auto book = findBook(bookId);
			if (book) {
				book->borrow();
			}
		}
	}
}

std::vector<std::shared_ptr<Book>> Library::findBooksByTitle(const std::string& keyword) const {
	std::vector<std::shared_ptr<Book>> result;
	for (const auto& pair : books) {
		if (pair.second->getTitle().find(keyword) != std::string::npos) {
			result.push_back(pair.second);
		}
	}
	return result;
}


std::vector<std::shared_ptr<User>> Library::findUsersByName(const std::string& keyword) const {
	std::vector<std::shared_ptr<User>> result;
	for (const auto& pair : users) {
		if (pair.second->getName().find(keyword) != std::string::npos) {
			result.push_back(pair.second);
		}
	}
	return result;
}
