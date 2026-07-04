#include "DialogUtil.h"

#include <QMessageBox>

void DialogUtil::info(QWidget* parent, const QString& text)
{
	QMessageBox::information(parent, "提示", text);
}

void DialogUtil::warning(QWidget* parent, const QString& text)
{
	QMessageBox::warning(parent, "警告", text);
}

void DialogUtil::error(QWidget* parent, const QString& text)
{
	QMessageBox::critical(parent, "错误", text);
}

bool DialogUtil::confirmDelete(QWidget* parent, const QString& objectName)
{
	return QMessageBox::question(parent, "确认删除", QString("确定删除【%1】吗？\n\n此操作不可恢复。").arg(objectName),
		QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes;
}