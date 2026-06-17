#include <string>
#include <iostream>

class Book {
private:
    int id; //图书的编号
    std::string title; //图书的标题
    std::string author; //图书的作者
    std::string publisher; //图书的出版社
    double price; //图书的价格
    bool BorrowedStatus; //图书的借阅状态
public:
    //构造函数
    Book(int id,const std::string& title,const std::string& author,const std::string& publisher,double price);

    int getId() const;
    const std::string& getTitle() const;
    const std::string& getAuthor() const;
    const std::string& getPublisher() const;
    double getPrice() const;
    bool isBorrowed() const;

    void setPrice(double price);

    bool borrow();

    bool returnBook();

    void showBookInfo();
};