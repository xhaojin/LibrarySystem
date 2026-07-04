#include "repository/interfaces/IUserRepository.h"
#include "dto/UserDTO.h"


class UserService {
private:
	IUserRepository& userRepo;

public:
	explicit UserService(IUserRepository& userRepo);

	bool addUser(const UserDTO& dto);
	bool removeUser(int userId);
	bool updateUser(const UserDTO& dto);
	UserDTO findUserById(int userId) const;
	std::vector<UserDTO> findUsersByName(const std::string& username) const;
	std::vector<UserDTO> getAllUsersDTO() const;
};