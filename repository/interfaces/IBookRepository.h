#pragma once

#include <memory>
#include <vector>

#include "model/Book.h"

#include "dto/BookDTO.h"

class IBookRepository
{
public:
    virtual ~IBookRepository() = default;

    // 新增图书信息
    virtual bool add(std::shared_ptr<Book> book) = 0;

    // 逻辑删除
    virtual bool remove(long long bookId) = 0;

    // 修改图书信息
    virtual bool update(const Book& book) = 0;

    // 修改图书状态（正常/下架/停用）
    virtual bool updateStatus(long long bookId, BookStatus status) = 0;

    // 根据ID查询
    virtual std::shared_ptr<Book> findById(long long bookId) const = 0;

    // 根据ISBN查询（以后扫码枪会用到）
    virtual std::shared_ptr<Book> findByISBN(const std::string& isbn) const = 0;

    // 按标题模糊查询
    virtual std::vector<std::shared_ptr<Book>> findByTitle(const std::string& keyword) const = 0;

    // 查询全部
    virtual std::vector<std::shared_ptr<Book>> findAll() const = 0;

    // 排序
    virtual std::vector<std::shared_ptr<Book>> sortByTitle() const = 0;

    virtual std::vector<std::shared_ptr<Book>> sortByPrice() const = 0;

    // 图书信息数量
    virtual int getTotalBooks() const = 0;
    
    //新增或修改图书时，需要检查 ISBN 是否已存在，避免违反数据库唯一约束，并能给出更友好的提示。
    //virtual bool existsISBN(const std::string& isbn) const = 0;

    //以后如果实现分类管理，在删除分类前，需要判断该分类下是否还有图书。
    //virtual int countByCategory(long long categoryId) const = 0;

    //用于列表展示
    virtual std::vector<BookDTO> findAllWithDetail() const = 0;
};