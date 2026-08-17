#include "CategoryService.h"

CategoryService::CategoryService(ICategoryRepository& categoryRepository): m_categoryRepository(categoryRepository)
{
}

bool CategoryService::add(const Category& category)
{
    if (category.getName().empty())
    {
        return false;
    }

    if (category.getSortOrder() < 0)
    {
        return false;
    }

    return m_categoryRepository.add(category);
}

bool CategoryService::remove(long long categoryId)
{
    if (categoryId <= 0)
    {
        return false;
    }

    // 类别不存在
    auto category = m_categoryRepository.findById(categoryId);

    if (!category)
    {
        return false;
    }

    // 已经被图书引用
    if (m_categoryRepository.isReferencedByBooks(categoryId))
    {
        return false;
    }

    return m_categoryRepository.remove(categoryId);
}

bool CategoryService::update(const Category& category)
{
    if (category.getId() <= 0)
    {
        return false;
    }

    if (category.getName().empty())
    {
        return false;
    }

    if (category.getSortOrder() < 0)
    {
        return false;
    }

    return m_categoryRepository.update(category);
}

std::shared_ptr<Category> CategoryService::findById(long long categoryId) const
{
    if (categoryId <= 0)
    {
        return nullptr;
    }

    return m_categoryRepository.findById(categoryId);
}

std::vector<std::shared_ptr<Category>> CategoryService::findByName(const std::string& keyword) const
{
    if (keyword.empty())
    {
        return m_categoryRepository.findAll();
    }

    return m_categoryRepository.findByName(keyword);
}

std::vector<std::shared_ptr<Category>> CategoryService::findAll() const
{
    return m_categoryRepository.findAll();
}