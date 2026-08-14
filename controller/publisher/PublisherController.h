#pragma once

#include "service/publisher/PublisherService.h"

#include "dto/PublisherDTO.h"

#include "mapper/PublisherDTOMapper.h"

class PublisherController
{
private:
	PublisherService& publisherService;

public:
	explicit PublisherController(PublisherService& publisherService);

	bool addPublisher(const PublisherDTO& dto);
	bool removePublisher(int publisherId);
	bool updatePublisher(const PublisherDTO& dto);
	PublisherDTO findPublisherById(int publisherId) const;
	std::vector<PublisherDTO> findPublishers(const std::string& keyword) const;
	std::vector<PublisherDTO> getAllPublishers() const;
};