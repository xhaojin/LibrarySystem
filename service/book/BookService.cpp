#include "BookService.h"

BookService::BookService(IBookRepository& bookRepo) :bookRepo(bookRepo) {

}

std::vector<BookDTO> BookService::findBooksByTitle(const std::string& keyword) {
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


std::vector<BookDTO> BookService::getBooksSortedByPrice() const {
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

std::vector<BookDTO> BookService::getBooksSortedByTitle() const {
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

std::vector<BookDTO> BookService::getAllBooksDTO() const {
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