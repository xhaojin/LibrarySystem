#pragma once

#include "service/category/CategoryService.h"

#include "dto/CategoryDTO.h"

#include "mapper/CategoryDTOMapper.h"

class CategoryController
{
private:
	CategoryService& categoryService;

public:
	explicit CategoryController(CategoryService& categoryService);

	bool addCategory(const CategoryDTO& dto);
	bool removeCategory(int categoryId);
	bool updateCategory(const CategoryDTO& dto);
	CategoryDTO findCategoryById(int categoryId) const;
	std::vector<CategoryDTO> findCategories(const std::string& keyword) const;
	std::vector<CategoryDTO> getAllCategories() const;
};