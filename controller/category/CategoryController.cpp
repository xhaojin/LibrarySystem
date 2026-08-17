#include "CategoryController.h"

CategoryController::CategoryController(CategoryService& categoryService) :categoryService(categoryService)
{
}

bool CategoryController::addCategory(const CategoryDTO& dto) {
	return categoryService.add(CategoryDTOMapper::toModel(dto));
}
bool CategoryController::removeCategory(int categoryId) {
	return categoryService.remove(categoryId);
}
bool CategoryController::updateCategory(const CategoryDTO& dto) {
	return categoryService.update(CategoryDTOMapper::toModel(dto));
}

CategoryDTO CategoryController::findCategoryById(int categoryId) const {
	CategoryDTO dto;
	return CategoryDTOMapper::toDTO(*categoryService.findById(categoryId));
}

std::vector<CategoryDTO> CategoryController::findCategories(const std::string& keyword) const {
	std::vector<CategoryDTO> dto;
	for (const auto& category : categoryService.findByName(keyword)) {
		dto.push_back(CategoryDTOMapper::toDTO(*category));
	}
	return dto;
}

std::vector<CategoryDTO> CategoryController::getAllCategories() const
{
	std::vector<CategoryDTO> dto;
	for (const auto& category : categoryService.findAll()) {
		dto.push_back(CategoryDTOMapper::toDTO(*category));
	}
	return dto;
}