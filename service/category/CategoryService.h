#pragma once

#include <memory>
#include <vector>
#include <string>

#include "model/Category.h"
#include "repository/interfaces/ICategoryRepository.h"

class CategoryService
{
public:
    explicit CategoryService(ICategoryRepository& categoryRepository);

    // 新增分类
    bool add(const Category& category);

    // 删除分类
    bool remove(long long categoryId);

    // 修改分类
    bool update(const Category& category);

    // 根据 ID 查询
    std::shared_ptr<Category> findById(long long categoryId) const;

    // 根据名称查询
    std::vector<std::shared_ptr<Category>> findByName(const std::string& keyword) const;

    // 查询全部
    std::vector<std::shared_ptr<Category>> findAll() const;

private:
    ICategoryRepository& m_categoryRepository;
};