#include "PublisherController.h"

PublisherController::PublisherController(PublisherService& publisherService) :publisherService(publisherService)
{
}

bool PublisherController::addPublisher(const PublisherDTO& dto) {
	return publisherService.add(PublisherDTOMapper::toModel(dto));
}
bool PublisherController::removePublisher(int publisherId) {
	return publisherService.remove(publisherId);
}
bool PublisherController::updatePublisher(const PublisherDTO& dto) {
	return publisherService.update(PublisherDTOMapper::toModel(dto));
}

PublisherDTO PublisherController::findPublisherById(int publisherId) const {
	PublisherDTO dto;
	return PublisherDTOMapper::toDTO(*publisherService.findById(publisherId));
}

std::vector<PublisherDTO> PublisherController::findPublishers(const std::string& keyword) const {
	std::vector<PublisherDTO> dto;
	for (const auto& publisher : publisherService.search(keyword)) {
		dto.push_back(PublisherDTOMapper::toDTO(*publisher));
	}
	return dto;
}

std::vector<PublisherDTO> PublisherController::getAllPublishers() const
{
	std::vector<PublisherDTO> dto;
	for (const auto& publisher : publisherService.findAll()) {
		dto.push_back(PublisherDTOMapper::toDTO(*publisher));
	}
	return dto;
}