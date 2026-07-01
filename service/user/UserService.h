#include "repository/interfaces/IUserRepository.h"
#include "dto/UserDTO.h"


class UserService {
private:
	IUserRepository& userRepo;

public:
	explicit UserService(IUserRepository& userRepo);

	//TODO 用户管理
	void addUser(const UserDTO& dto);
	void removeUser(int userId);
	void updateUser(const UserDTO& dto);

	//查询
	std::vector<UserDTO> getAllUsersDTO() const;
};