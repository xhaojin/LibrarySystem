#pragma once

#include "dto/BookDTO.h"
#include "model/Book.h"

//Model(Book) → DTO(BookDTO)

class BookDTOMapper
{
public:
    static BookDTO toDTO(const Book& book,std::string publisher,std::string category);
};