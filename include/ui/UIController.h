#pragma once

#include "service/LibraryService.h"

#include "auth/SessionManager.h"

class UIController
{
private:
    LibraryService& service;
    SessionManager sessionManager;

public:
    UIController(LibraryService& s);

    // 操作类
    void borrowBook(int userId, int bookId);
    void returnBook(int userId, int bookId);
    std::vector<BookDTO> searchBooksByTitle(const std::string& keyword);
    std::vector<BookDTO> getBooksSortedByPrice() const;
    std::vector<BookDTO> getBooksSortedByTitle() const;

    //登录类
    UserDTO login(const std::string& username,const std::string& password);
    bool isLoggedIn() const;
    bool isAdmin() const;
    void logout();
    const Session* getSession() const;

    // UI数据类
    std::vector<BookDTO> getAllBooks() const;
    std::vector<UserDTO> getAllUsers() const;
};