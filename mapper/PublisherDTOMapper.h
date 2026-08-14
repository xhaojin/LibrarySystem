#pragma once

#include <memory>

#include "model/Publisher.h"
#include "dto/PublisherDTO.h"

class PublisherDTOMapper
{
public:

    // Publisher → PublisherDTO
    static PublisherDTO toDTO(const Publisher& publisher);

    // PublisherDTO → Publisher
    static Publisher toModel(const PublisherDTO& dto);
};