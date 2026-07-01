#include "StatisticsService.h"

StatisticsService::StatisticsService(IBookRepository& bookRepo, IUserRepository& userRepo):bookRepo(bookRepo),userRepo(userRepo) {

}

int StatisticsService::getTotalBooks() const {
	return bookRepo.getTotalBooks();
}
int StatisticsService::getBorrowedBooksCount() const {
	return bookRepo.getBorrowedBooksCount();
}
int StatisticsService::getAvailableBooksCount() const {
	return bookRepo.getAvailableBooksCount();
}
int StatisticsService::getUserCount() const {
	return userRepo.findAll().size();
}
double StatisticsService::getBorrowRate() const {
	return getTotalBooks() == 0 ? 0.0 : static_cast<double>(getBorrowedBooksCount()) / getTotalBooks();
}