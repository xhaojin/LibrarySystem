#include "BookService.h"

#include "mapper/BookDTOMapper.h"

BookService::BookService(IBookRepository& bookRepo) :bookRepo(bookRepo) {

}

bool BookService::addBook(const Book& book) {
    // =========================
    // 1. 基础参数校验
    // =========================

    if (book.getISBN().empty())
    {
        return false;
    }

    if (book.getTitle().empty())
    {
        return false;
    }

    if (book.getAuthor().empty())
    {
        return false;
    }

    // =========================
    // 2. ISBN 唯一性检查
    // =========================

    if (bookRepo.findByISBN(book.getISBN()) != nullptr)
    {
        return false;
    }

    // =========================
    // 3. 新增
    // =========================

    auto bookPtr = std::make_shared<Book>(book);

    return bookRepo.add(bookPtr);
}
bool BookService::removeBook(int bookId) {
	return bookRepo.remove(bookId);
}
bool BookService::updateBook(const BookDTO& dto) {
	//return bookRepo.update(Book(dto.id, dto.title, dto.author, dto.publisher, dto.price, dto.isBorrowed));
	return true;
}

std::vector<BookDTO> BookService::findBooksByTitle(const std::string& keyword) {
	std::vector<BookDTO> bookDTOs;
	auto books = bookRepo.findByTitle(keyword);
	for (const auto& book : books) {
		//bookDTOs.push_back();
	}
	return bookDTOs;
}

BookDTO BookService::findBookById(int bookId) const {
	auto book = bookRepo.findById(bookId);
	return BookDTO{};
}

std::vector<BookDTO> BookService::getBooksSortedByPrice() const {
	std::vector<BookDTO> sortedBooks;
	for (const auto& book : bookRepo.sortByPrice()) {
		//sortedBooks.push_back();
	}
	return sortedBooks;
}

std::vector<BookDTO> BookService::getBooksSortedByTitle() const {
	std::vector<BookDTO> sortedBooks;
	for (const auto& book : bookRepo.sortByTitle()) {
		//sortedBooks.push_back();
	}
	return sortedBooks;
}

std::vector<BookDTO> BookService::getAllBooksDTO() const {
	return bookRepo.findAllWithDetail();
}