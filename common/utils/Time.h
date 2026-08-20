#pragma once
#include <string>
#include <optional>
#include <QDateTime>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>

class Time {
public:

    static std::optional<QDateTime> stringToOptionalDateTime(const QString& str);

    static QDateTime stringToDateTime(const QString& str);

    static std::string getCurrentDateTime();
};