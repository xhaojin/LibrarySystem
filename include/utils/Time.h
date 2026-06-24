#pragma once
#include <string>
#include <optional>
#include <QDateTime>

class Time {
public:
    static std::optional<QDateTime> stringToOptionalDateTime(const QString& str);
    static QDateTime stringToDateTime(const QString& str);
};