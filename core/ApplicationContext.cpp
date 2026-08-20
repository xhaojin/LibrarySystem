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
	DBConfig config;

	config.host = "127.0.0.1";
	config.port = 3306;
	config.database = "library";
	config.username = "root";
	config.password = "1234";

	database_ = std::make_unique<MySQLDatabase>(config);

	return database_->connect();
}

void ApplicationContext::createRepositories() {
	bookRepo_ = std::make_unique<MySQLBookRepository>(*database_);

	userRepo_ = std::make_unique<MySQLUserRepository>(*database_);

	bookCopyRepo_ = std::make_unique<MySQLBookCopyRepository>(*database_);

	borrowRecordRepo_ = std::make_unique<MySQLBorrowRecordRepository>(*database_);

	publisherRepo_ = std::make_unique<MySQLPublisherRepository>(*database_);

	categoryRepo_ = std::make_unique<MySQLCategoryRepository>(*database_);
}

void ApplicationContext::createServices() {
	userService_ = std::make_unique<UserService>(*userRepo_);

	bookService_ = std::make_unique<BookService>(*bookRepo_);

	borrowService_ = std::make_unique<BorrowService>(*database_, *userRepo_, *bookCopyRepo_, *borrowRecordRepo_);

	publisherService_ = std::make_unique<PublisherService>(*publisherRepo_);

	categoryService_ = std::make_unique<CategoryService>(*categoryRepo_);
}

void ApplicationContext::createControllers() {
	userController_ = std::make_unique<UserController>(*userService_);

	bookController_ = std::make_unique<BookController>(*bookService_);

	borrowController_ = std::make_unique<BorrowController>(*borrowService_);

	publisherController_ = std::make_unique<PublisherController>(*publisherService_);

	categoryController_ = std::make_unique<CategoryController>(*categoryService_);
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

PublisherController& ApplicationContext::publisherController()
{
	return *publisherController_;
}

CategoryController& ApplicationContext::categoryController()
{
	return *categoryController_;
}

//SQLiteUserRepository& ApplicationContext::userRepository() {
//	return *userRepo_;
//}

MySQLUserRepository& ApplicationContext::userRepository()
{
	return *userRepo_;
}

SessionManager& ApplicationContext::sessionManager() {
	return *sessionManager_;
}