#include "utils/Logger.h"
#include <fstream>
#include <ctime>

static std::string getCurrentTime()
{
    time_t now = time(nullptr);
    tm* ltm = localtime(&now);

    char buffer[64];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);

    return std::string(buffer);
}

void Logger::log(const std::string& message)
{
    std::ofstream file("log.txt", std::ios::app);
    if (!file) return;

    file << "[" << getCurrentTime() << "] " << message << "\n";
}