#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>

#include <QLabel>

#include "dto/CategoryDTO.h"

class CategoryEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CategoryEditDialog(QWidget* parent = nullptr);

    // 编辑模式
    void setCategory(const CategoryDTO& category);

    // 获取用户填写的数据
    CategoryDTO getCategory() const;

private slots:
    void updateOkButtonState();

private:
    void setupUI();

private:
    // =========================
    // 基本信息
    // =========================

    QLineEdit* nameEdit;
    QSpinBox* sortOrderSpinBox;
    QTextEdit* descriptionEdit;

    // =========================
    // 按钮
    // =========================

    QPushButton* okButton;
    QPushButton* cancelButton;
};