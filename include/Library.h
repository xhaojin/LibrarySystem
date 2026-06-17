#include <memory>
#include <unordered_map>
#include "Book.h"
#include "User.h"

class Library
{
private:
    std::unordered_map<int,std::shared_ptr<Book>> books;

    std::unordered_map<int,std::shared_ptr<User>> users;

public:
    bool addBook(std::shared_ptr<Book> book);

    bool addUser(std::shared_ptr<User> user);

    void removeBook(int bookId);

    void removeUser(int userId);

    std::shared_ptr<Book> findBook(int bookId) const;

    std::shared_ptr<User> findUser(int userId) const;

    bool borrowBook(int userId,int bookId);

    bool returnBook(int userId,int bookId);

    void showAllBooks() const;

    void showAllUsers() const;
};