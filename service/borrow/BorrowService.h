#include "repository/interfaces/IBookRepository.h"
#include "repository/interfaces/IUserRepository.h"
#include "repository/interfaces/IBorrowRecordRepository.h"
#include "dto/BorrowRecordDTO.h"
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

	std::vector<BorrowRecordDTO> getAllBorrowRecords() const;
};