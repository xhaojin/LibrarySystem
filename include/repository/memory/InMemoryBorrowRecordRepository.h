#include "../interfaces/IBorrowRecordRepository.h"

class InMemoryBorrowRecordRepository : public IBorrowRecordRepository
{
private:
    std::unordered_map<int, std::shared_ptr<BorrowRecord>> borrowRecords;
public:
    ~InMemoryBorrowRecordRepository();

    void add(std::shared_ptr<BorrowRecord> record);

    std::shared_ptr<BorrowRecord>findById(int recordId) const;

    std::vector<std::shared_ptr<BorrowRecord>>findAll() const;
};