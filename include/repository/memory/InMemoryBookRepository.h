#include "../interfaces/IBookRepository.h"
#include <unordered_map>

class InMemoryBookRepository: public IBookRepository
{
private:
    std::unordered_map<int,std::shared_ptr<Book>> books;
public:
	~InMemoryBookRepository(){}

	bool add(std::shared_ptr<Book> book);

	void remove(int bookId);

	std::shared_ptr<Book> findById(int bookId);

	std::vector<std::shared_ptr<Book>> findByTitle(const std::string& titleKeyWord) const;

	std::vector<std::shared_ptr<Book>> findAll() const;
};