#pragma once

#include "model/Category.h"
#include "dto/CategoryDTO.h"

class CategoryDTOMapper
{
public:

    // Model -> DTO
    static CategoryDTO toDTO(const Category& category);

    // DTO -> Model
    static Category toModel(const CategoryDTO& dto);
};