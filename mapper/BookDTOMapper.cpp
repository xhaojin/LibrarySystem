#include "BookDTOMapper.h"

BookDTO BookDTOMapper::toDTO(const Book& book, std::string publisher, std::string category)
{
    BookDTO dto;

    dto.id = book.getId();

    dto.isbn = book.getISBN();

    dto.title = book.getTitle();

    dto.author = book.getAuthor();

    dto.publisherId = book.getPublisherId();

    dto.categoryId = book.getCategoryId();

    dto.publisher = publisher;

    dto.category = category;

    dto.publishYear = book.getPublishYear();

    dto.price = book.getPrice();

    switch (book.getStatus())
    {
    case BookStatus::Normal:
        dto.status = "正常";
        break;

    case BookStatus::OffShelf:
        dto.status = "下架";
        break;

    case BookStatus::Disabled:
        dto.status = "停用";
        break;

    default:
        dto.status = "未知";
        break;
    }

    return dto;
}