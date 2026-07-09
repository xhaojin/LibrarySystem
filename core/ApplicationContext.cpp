#include "ApplicationContext.h"

ApplicationContext::ApplicationContext()
{
}

bool ApplicationContext::initialize()
{
	if (!initializeDatabase())
		return false;

	createRepositories();

	createServices();

	createControllers();

	createSession();

	return true;
}

bool ApplicationContext::initializeDatabase() {
	database_ = std::make_unique<SQLiteDatabase>();

	if (!database_->open("library.db"))
		return false;

	if (!database_->initialize())
		return false;

	return true;
}

void ApplicationContext::createRepositories() {
	bookRepo_ = std::make_unique<SQLiteBookRepository>(*database_);

	userRepo_ = std::make_unique<SQLiteUserRepository>(*database_);

	borrowRepo_ = std::make_unique<SQLiteBorrowRecordRepository>(*database_);
}

void ApplicationContext::createServices() {
	userService_ = std::make_unique<UserService>(*userRepo_);

	bookService_ = std::make_unique<BookService>(*bookRepo_);

	borrowService_ = std::make_unique<BorrowService>(*bookRepo_, *userRepo_, *borrowRepo_);
}

void ApplicationContext::createControllers() {
	userController_ = std::make_unique<UserController>(*userService_);

	bookController_ = std::make_unique<BookController>(*bookService_);

	borrowController_ = std::make_unique<BorrowController>(*borrowService_);
}

void ApplicationContext::createSession() {
	sessionManager_ = std::make_unique<SessionManager>();
}

BookController& ApplicationContext::bookController()
{
	return *bookController_;
}

UserController& ApplicationContext::userController()
{
	return *userController_;
}

BorrowController& ApplicationContext::borrowController()
{
	return *borrowController_;
}

SQLiteUserRepository& ApplicationContext::userRepository() {
	return *userRepo_;
}

SessionManager& ApplicationContext::sessionManager() {
	return *sessionManager_;
}