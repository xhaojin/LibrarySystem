#pragma once

#include <QWidget>

class BasePage : public QWidget
{
    Q_OBJECT

public:

    explicit BasePage(QWidget* parent = nullptr);

protected:

    void showInfo(const QString& text);

    void showWarning(const QString& text);

    void showError(const QString& text);

    bool confirmDelete(const QString& objectName);

    virtual void refresh() = 0; //刷新表格
};