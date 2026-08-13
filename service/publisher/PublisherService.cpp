#include "PublisherService.h"

PublisherService::PublisherService(IPublisherRepository& publisherRepo): publisherRepo(publisherRepo)
{
}

bool PublisherService::add(const Publisher& publisher)
{
    // 名称不能为空
    if (publisher.getName().empty())
    {
        return false;
    }

    // 检查名称是否已经存在
    auto existing = publisherRepo.findByName(publisher.getName());

    if (existing)
    {
        return false;
    }

    return publisherRepo.add(publisher);
}

bool PublisherService::update(const Publisher& publisher)
{
    if (publisher.getId() <= 0)
    {
        return false;
    }

    if (publisher.getName().empty())
    {
        return false;
    }

    // 检查名称是否已经被其他出版社使用
    auto existing = publisherRepo.findByName(publisher.getName());

    if (existing && existing->getId() != publisher.getId())
    {
        return false;
    }

    return publisherRepo.update(publisher);
}

bool PublisherService::remove(long long publisherId)
{
    if (publisherId <= 0)
    {
        return false;
    }

    // 出版社不存在
    auto publisher = publisherRepo.findById(publisherId);

    if (!publisher)
    {
        return false;
    }

    // 已经被图书引用
    if (publisherRepo.isReferencedByBooks(publisherId))
    {
        return false;
    }

    return publisherRepo.remove(publisherId);
}

std::shared_ptr<Publisher> PublisherService::findById(long long publisherId) const
{
    if (publisherId <= 0)
    {
        return nullptr;
    }

    return publisherRepo.findById(publisherId);
}

std::shared_ptr<Publisher> PublisherService::findByName(const std::string& name) const
{
    if (name.empty())
    {
        return nullptr;
    }

    return publisherRepo.findByName(name);
}

std::vector<std::shared_ptr<Publisher>> PublisherService::search(const std::string& keyword) const
{
    if (keyword.empty())
    {
        return publisherRepo.findAll();
    }

    return publisherRepo.findByNameLike(keyword);
}

std::vector<std::shared_ptr<Publisher>> PublisherService::findAll() const
{
    return publisherRepo.findAll();
}