#include "User.h"

User::User(int id, const std::string& name, Gender gender, int age, const std::string& phone)
    : id(id), name(name), gender(gender), age(age), phone(phone) {
}

int User::getId() const {
    return this->id;
}
const std::string& User::getName() const {
    return this->name;
}
const Gender& User::getGender() const {
    return this->gender;
}
int User::getAge() const {
    return this->age;
}
const std::string& User::getPhone() const {
    return this->phone;
}

bool User::addBorrowedBook(int bookId) {
    if(std::find(this->borrowedBookIds.begin(),this->borrowedBookIds.end(),bookId) == this->borrowedBookIds.end()) {
        this->borrowedBookIds.insert(bookId);
		return true; // Successfully added
    }
    return false;
}

bool User::removeBorrowedBook(int bookId) {
    if (std::find(this->borrowedBookIds.begin(), this->borrowedBookIds.end(), bookId) != this->borrowedBookIds.end()) {
        this->borrowedBookIds.erase(bookId);
        return true; // Successfully added
    }
    return false;
}

const std::unordered_set<int>& User::getBorrowedBookIds() const {
    return this->borrowedBookIds;
}

void User::showUserInfo() {
    std::cout << "User ID: " << this->id << std::endl;
    std::cout << "Name: " << this->name << std::endl;
    std::cout << "Gender: " << (this->gender == Gender::Male ? "Male" : "Female") << std::endl;
    std::cout << "Age: " << this->age << std::endl;
    std::cout << "Phone: " << this->phone << std::endl;
}