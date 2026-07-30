#include "BookDTOMapper.h"

BookDTO BookDTOMapper::toDTO(const Book& book)
{
    BookDTO dto;

    dto.id = book.getId();

    dto.isbn = book.getISBN();

    dto.title = book.getTitle();

    dto.author = book.getAuthor();

    // 后续由 PublisherService 查询名称
    dto.publisher = "";

    // 后续由 CategoryService 查询名称
    dto.category = "";

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