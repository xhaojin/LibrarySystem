#pragma once

#include "repository/interfaces/IBookRepository.h"
#include "repository/interfaces/IUserRepository.h"

class StatisticsService {
private:
    IBookRepository& bookRepo;
    IUserRepository& userRepo;

public:
    explicit StatisticsService(IBookRepository& bookRepo, IUserRepository& userRepo);

    // 统计
    int getTotalBooks() const;
    int getBorrowedBooksCount() const;
    int getAvailableBooksCount() const;
    int getUserCount() const;
    double getBorrowRate() const;
};