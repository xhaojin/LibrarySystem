#include "BasePage.h"

#include "common/utils/DialogUtil.h"

BasePage::BasePage(QWidget* parent)
    : QWidget(parent)
{
}

void BasePage::showInfo(const QString& text)
{
    DialogUtil::info(this, text);
}

void BasePage::showWarning(const QString& text)
{
    DialogUtil::warning(this, text);
}

void BasePage::showError(const QString& text)
{
    DialogUtil::error(this, text);
}

bool BasePage::confirmDelete(const QString& objectName)
{
    return DialogUtil::confirmDelete(this, objectName);
}