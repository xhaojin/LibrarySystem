#pragma once

#include <memory>
#include <vector>
#include <string>

#include "model/Publisher.h"

class IPublisherRepository
{
public:
    virtual ~IPublisherRepository() = default;

    // 新增
    virtual bool add(const Publisher& publisher) = 0;

    // 修改
    virtual bool update(const Publisher& publisher) = 0;

    // 删除
    virtual bool remove(long long publisherId) = 0;

    // 根据 ID 查询
    virtual std::shared_ptr<Publisher> findById(long long publisherId) const = 0;

    // 根据名称查询
    virtual std::shared_ptr<Publisher> findByName(const std::string& name) const = 0;

    // 模糊搜索
    virtual std::vector<std::shared_ptr<Publisher>> findByNameLike(const std::string& keyword) const = 0;

    // 查询全部
    virtual std::vector<std::shared_ptr<Publisher>> findAll() const = 0;
};