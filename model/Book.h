#pragma once

#include <string>

enum class BookStatus
{
    Normal = 0, //正常
    OffShelf = 1, //下架
    Disabled = 2 //禁用
};

class Book
{
private:
    long long id;

    std::string isbn;
    std::string title;
    std::string author;

    long long publisherId;
    long long categoryId;

    int publishYear;

    double price;

    std::string coverUrl;

    std::string description;

    BookStatus status;

    bool deleted;

public:

    Book(
        long long id,
        const std::string& isbn,
        const std::string& title,
        const std::string& author,
        long long publisherId,
        long long categoryId,
        int publishYear,
        double price,
        const std::string& coverUrl,
        const std::string& description,
        BookStatus status,
        bool deleted
    );

    long long getId() const;

    const std::string& getISBN() const;

    const std::string& getTitle() const;

    const std::string& getAuthor() const;

    long long getPublisherId() const;

    long long getCategoryId() const;

    int getPublishYear() const;

    double getPrice() const;

    const std::string& getCoverUrl() const;

    const std::string& getDescription() const;

    BookStatus getStatus() const;

    bool isDeleted() const;

    bool isAvailable() const;

    bool isOffShelf() const;
};