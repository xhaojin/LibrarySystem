#include "repository/interfaces/IBookRepository.h"
#include "repository/interfaces/IUserRepository.h"
#include "repository/interfaces/IBorrowRecordRepository.h"
#include "dto/BorrowRecordDTO.h"
#include "dto/UserDTO.h"
#include "common/utils/logger.h"

class BorrowService {
private:
	IBookRepository& bookRepo;
	IUserRepository& userRepo;
	IBorrowRecordRepository& borrowRepo;

public:
	explicit BorrowService(IBookRepository& bookRepo, IUserRepository& userRepo, IBorrowRecordRepository& borrowRepo);

	// 借阅业务
	void borrowBook(int userId, int bookId);
	void returnBook(int userId, int bookId);
	std::vector<BorrowRecordDTO> findRecordsByNameAndBookTitle(const std::string& name, const std::string& bookTitle) const;
	std::vector<BorrowRecordDTO> getAllBorrowRecords() const;
	std::vector<BorrowRecordDTO> getBorrowRecords(const UserDTO& currentUser) const;
};