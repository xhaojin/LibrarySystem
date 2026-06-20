#include <string>
//DTO：专门给UI用的数据结构，包含了UI需要展示的字段，方便UI层使用
struct UserDTO
{
    int id;
    std::string name;
    std::string gender;
    int age;
    std::string phone;
    int borrowedCount;
};