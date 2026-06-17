#include <iostream>
#include <Library.h>

int main()
{
	Library library;
	Book book1(1, "The Great Gatsby", "F. Scott Fitzgerald", "Scribner", 10.99);
	Book book2(2, "To Kill a Mockingbird", "Harper Lee", "J.B. Lippincott & Co.", 7.99);
	library.addBook(std::make_shared<Book>(book1));
	library.addBook(std::make_shared<Book>(book2));
	User user1(1, "John Doe", Gender::Male, 30, "123-456-7890");
	User user2(2, "Jane Smith", Gender::Female, 25, "098-765-4321");
	library.addUser(std::make_shared<User>(user1));
	library.addUser(std::make_shared<User>(user2));
	library.showAllBooks();
	library.showAllUsers();
	if(library.borrowBook(1, 1)) { // John Doe borrows "The Great Gatsby"
		std::cout << "Book borrowed successfully!" << std::endl;
	} else {
		std::cout << "Failed to borrow book." << std::endl;
	}
	if (library.borrowBook(2, 1)) { // Jane Smith borrows "The Great Gatsby"
		std::cout << "Book borrowed successfully!" << std::endl;
	}
	else {
		std::cout << "Failed to borrow book." << std::endl;
	}
	if (library.returnBook(1, 1)) { // John Doe returns "The Great Gatsby"
		std::cout << "Book returned successfully!" << std::endl;
	} else {
		std::cout << "Failed to return book." << std::endl;
	}
	if (library.borrowBook(2, 1)) { // Jane Smith borrows "The Great Gatsby"
		std::cout << "Book borrowed successfully!" << std::endl;
	}
	else {
		std::cout << "Failed to borrow book." << std::endl;
	}
    return 0;
}