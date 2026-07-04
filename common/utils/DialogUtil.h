#pragma once

#include <QWidget>
#include <QString>

class DialogUtil
{
public:

    static void info(QWidget* parent,const QString& text);

    static void warning(QWidget* parent,const QString& text);

    static void error(QWidget* parent,const QString& text);

    static bool confirmDelete(QWidget* parent,const QString& objectName);
};