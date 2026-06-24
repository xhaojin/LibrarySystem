#include "../../include/utils/Time.h"

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