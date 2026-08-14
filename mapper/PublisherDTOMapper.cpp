#include "PublisherDTOMapper.h"

PublisherDTO PublisherDTOMapper::toDTO(const Publisher& publisher)
{
    PublisherDTO dto;

    dto.id = publisher.getId();
    dto.name = publisher.getName();
    dto.contact = publisher.getContact();
    dto.website = publisher.getWebsite();

    return dto;
}

Publisher PublisherDTOMapper::toModel(const PublisherDTO& dto)
{
    return Publisher(
        dto.id,
        dto.name,
        dto.contact,
        dto.website
    );
}