#include "repository/interfaces/IBookRepository.h"
#include "repository/interfaces/IUserRepository.h"
#include "repository/interfaces/IBorrowRecordRepository.h"
#include "dto/BookDTO.h"
#include "dto/UserDTO.h"
#include "dto/BorrowRecordDTO.h"
#include "utils/logger.h"
#include <QSqlQuery>

class LibraryService
{
private:

    IBookRepository& bookRepo;
    IUserRepository& userRepo;
    IBorrowRecordRepository& borrowRepo;

public:

    LibraryService(IBookRepository& bookRepo,IUserRepository& userRepo,IBorrowRecordRepository& borrowRepo);

    UserDTO login(const std::string& username,const std::string& password);

    // 借阅业务
    void borrowBook(int userId, int bookId);
    void returnBook(int userId, int bookId);

    // 图书管理
    void addBook(const BookDTO& dto);
    void removeBook(int bookId);
    void updateBook(const BookDTO& dto);

    // 用户管理
    void addUser(const UserDTO& dto);
    void removeUser(int userId);
    void updateUser(const UserDTO& dto);

    // 查询
    std::vector<BookDTO> findBooksByTitle(const std::string& keyword);

    std::vector<BookDTO> getAllBooksDTO() const;

    std::vector<UserDTO> getAllUsersDTO() const;

    std::vector<BorrowRecordDTO> getAllBorrowRecords() const;

    // 排序
    std::vector<BookDTO> getBooksSortedByPrice() const;

    std::vector<BookDTO> getBooksSortedByTitle() const;

    // 统计
    int getTotalBooks() const;
    int getBorrowedBooksCount() const;
    int getAvailableBooksCount() const;
    int getUserCount() const;
    double getBorrowRate() const;
};