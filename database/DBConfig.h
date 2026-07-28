#pragma once

#include <string>

struct DBConfig
{
    std::string host = "127.0.0.1";

    int port = 3306;

    std::string database = "library";

    std::string username = "root";

    std::string password = "1234";

    std::string getUrl() const
    {
        return "tcp://" + host + ":" + std::to_string(port);
    }
};