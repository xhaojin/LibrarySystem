#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_set>

enum class Gender
{
    Male,
    Female
};

class User
{
private:
    int id;
    std::string name;
    Gender gender;
    int age;
    std::string phone;

    std::unordered_set<int> borrowedBookIds;
public:
    User(int id, const std::string& name, Gender gender, int age, const std::string& phone);

    int getId() const;
    const std::string& getName() const;
    const Gender& getGender() const;
    int getAge() const;
    const std::string& getPhone() const;

    bool addBorrowedBook(int bookId); //借书

    bool removeBorrowedBook(int bookId); //还书

    const std::unordered_set<int>& getBorrowedBookIds() const; //查询用户的借阅记录

    void showUserInfo();

};