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

bool BookService::updateBook(const Book& book) {
	// =========================
	// 1. 基础校验
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
	// 2. 检查 ISBN 是否被其他图书使用
	// =========================

	auto existingBook = bookRepo.findByISBN(book.getISBN());

	if (existingBook != nullptr && existingBook->getId() != book.getId())
	{
		return false;
	}

	// =========================
	// 3. 更新
	// =========================

	return bookRepo.update(book);
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
	return BookDTOMapper::toDTO(*book, "", "");
}

std::vector<BookDTO> BookService::getBooksSortedByPrice() const {
	return bookRepo.sortByPriceWithDetail();
}

std::vector<BookDTO> BookService::getBooksSortedByTitle() const {
	return bookRepo.sortByTitleWithDetail();
}

std::vector<BookDTO> BookService::getAllBooksDTO() const {
	return bookRepo.findAllWithDetail();
}