#include "Time.h"

std::optional<QDateTime> Time::stringToOptionalDateTime(const QString& str) {
    // 1. 处理空字符串或 "(NULL)" 等数据库特殊情况
    if (str.isEmpty() || str.trimmed().isEmpty()) {
        return std::nullopt;
    }

    // 2. 尝试转换（这里按你存库时的 ISO 格式解析）
    QDateTime dt = QDateTime::fromString(str, Qt::ISODate);

    // 3. 最终判断
    if (dt.isValid()) {
        return dt;
    }
    else {
        return std::nullopt;  // 转换失败，返回空
    }
}

QDateTime Time::stringToDateTime(const QString& str) {
    // 1. 处理空字符串或 "(NULL)" 等数据库特殊情况
    if (str.isEmpty() || str.trimmed().isEmpty()) {
        return QDateTime();
    }

    // 2. 尝试转换（这里按你存库时的 ISO 格式解析）
    QDateTime dt = QDateTime::fromString(str, Qt::ISODate);

    // 3. 最终判断
    if (dt.isValid()) {
        return dt;
    }
    else {
        return QDateTime();  // 转换失败，返回空
    }
}

std::string Time::getCurrentDateTime()
{
    auto now = std::chrono::system_clock::now();

    std::time_t time = std::chrono::system_clock::to_time_t(now);

    std::tm localTime{};

    #ifdef _WIN32
        localtime_s(&localTime, &time);
    #else
        localtime_r(&time, &localTime);
    #endif

    std::ostringstream oss;

    oss << std::put_time(&localTime,"%Y-%m-%d %H:%M:%S");

    return oss.str();
}