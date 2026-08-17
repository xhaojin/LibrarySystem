#include "CategoryDTOMapper.h"

CategoryDTO CategoryDTOMapper::toDTO(const Category& category)
{
    CategoryDTO dto;

    dto.id = category.getId();

    dto.name = category.getName();

    dto.sortOrder = category.getSortOrder();

    dto.description = category.getDescription();

    return dto;
}

Category CategoryDTOMapper::toModel(const CategoryDTO& dto)
{
    return Category(
        dto.id,
        dto.name,
        dto.sortOrder,
        dto.description
    );
}