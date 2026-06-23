#include "../interfaces/IUserRepository.h"
#include <unordered_map>

class InMemoryUserRepository : public IUserRepository
{
private:
    std::unordered_map<int, std::shared_ptr<User>> users;
public:
    ~InMemoryUserRepository(){}

    bool add(std::shared_ptr<User> user);

    std::shared_ptr<User> findById(int userId);

    std::shared_ptr<User> findByUsername(const std::string& username);

    std::vector<std::shared_ptr<User>> findAll();
};