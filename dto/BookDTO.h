#pragma once

#include <string>
//DTO：专门给UI用的数据结构，包含了UI需要展示的字段，方便UI层使用
struct BookDTO
{
    int id = 0;
    std::string title;
    std::string author;
    std::string publisher;
    double price = 0.0;
    bool isBorrowed = false;
};