#pragma once

#include <string>

struct DBConfig
{
    std::string host = "127.0.0.1";

    uint16_t port = 3306;

    std::string database = "library";
    
    std::string username = "root";

    std::string password = "1234";
};