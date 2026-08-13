#pragma once

#include <memory>
#include <vector>
#include <string>
#include <optional>

#include "model/Publisher.h"
#include "repository/interfaces/IPublisherRepository.h"

class PublisherService
{
private:
    IPublisherRepository& publisherRepo;

public:
    explicit PublisherService(IPublisherRepository& publisherRepo);

    // =========================
    // 增删改
    // =========================

    bool add(const Publisher& publisher);

    bool update(const Publisher& publisher);

    bool remove(long long publisherId);

    // =========================
    // 查询
    // =========================

    std::shared_ptr<Publisher> findById(long long publisherId) const;

    std::shared_ptr<Publisher> findByName(const std::string& name) const;

    std::vector<std::shared_ptr<Publisher>> search(const std::string& keyword) const;

    std::vector<std::shared_ptr<Publisher>> findAll() const;
};