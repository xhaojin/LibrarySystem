#include "BookService.h"

BookService::BookService(IBookRepository& bookRepo) :bookRepo(bookRepo) {

}

bool BookService::addBook(const BookDTO& dto) {
	std::shared_ptr<Book> book;
	book = std::make_shared<Book>(dto.id, dto.title, dto.author, dto.publisher, dto.price, dto.isBorrowed);
	return bookRepo.add(book);
}
bool BookService::removeBook(int bookId) {
	return bookRepo.remove(bookId);
}
bool BookService::updateBook(const BookDTO& dto) {
	return bookRepo.update(Book(dto.id, dto.title, dto.author, dto.publisher, dto.price, dto.isBorrowed));
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

BookDTO BookService::findBookById(int bookId) const {
	auto book = bookRepo.findById(bookId);
	return BookDTO{
		book->getId(),
		book->getTitle(),
		book->getAuthor(),
		book->getPublisher(),
		book->getPrice(),
		book->isBorrowed()
	};
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