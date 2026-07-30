#include "Book.h"

Book::Book(
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
    bool deleted)
    : id(id),
    isbn(isbn),
    title(title),
    author(author),
    publisherId(publisherId),
    categoryId(categoryId),
    publishYear(publishYear),
    price(price),
    coverUrl(coverUrl),
    description(description),
    status(status),
    deleted(deleted)
{
}

long long Book::getId() const
{
    return id;
}

const std::string& Book::getISBN() const
{
    return isbn;
}

const std::string& Book::getTitle() const
{
    return title;
}

const std::string& Book::getAuthor() const
{
    return author;
}

long long Book::getPublisherId() const
{
    return publisherId;
}

long long Book::getCategoryId() const
{
    return categoryId;
}

int Book::getPublishYear() const
{
    return publishYear;
}

double Book::getPrice() const
{
    return price;
}

const std::string& Book::getCoverUrl() const
{
    return coverUrl;
}

const std::string& Book::getDescription() const
{
    return description;
}

BookStatus Book::getStatus() const
{
    return status;
}

bool Book::isDeleted() const
{
    return deleted;
}

bool Book::isAvailable() const
{
    return status == BookStatus::Normal && !deleted;
}

bool Book::isOffShelf() const
{
    return status == BookStatus::OffShelf;
}