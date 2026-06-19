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

    int getId() const; //查询图书的编号
    const std::string& getTitle() const; //查询图书的标题
    const std::string& getAuthor() const; //查询图书的作者
    const std::string& getPublisher() const; //查询图书的出版社
    double getPrice() const; //查询图书的价格
    bool isBorrowed() const; //查询图书的借阅状态

    void setPrice(double price); //设置图书价格

    void setBorrowedStatus(bool status); //设置图书的借阅状态S

    void showBookInfo();
};