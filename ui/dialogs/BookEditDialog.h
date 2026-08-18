#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "dto/BookDTO.h"

#include "core/ApplicationContext.h"

class BookEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BookEditDialog(ApplicationContext& context, QWidget* parent = nullptr);

    // 编辑模式
    void setBook(const BookDTO& book);

    // 获取用户填写的数据
    BookDTO getBook() const;

private slots:
    void updateOkButtonState();

private:
    void setupUI();
    void loadPublishers();
    void loadCategories();

private:
    // =========================
    // 基本信息
    // =========================

    QLineEdit* isbnEdit;
    QLineEdit* titleEdit;
    QLineEdit* authorEdit;

    // =========================
    // 关联信息
    // =========================

    QComboBox* publisherComboBox;
    QComboBox* categoryComboBox;

    // =========================
    // 图书信息
    // =========================

    QSpinBox* publishYearSpinBox;
    QDoubleSpinBox* priceSpinBox;

    QLineEdit* coverUrlEdit;
    QTextEdit* descriptionEdit;

    // =========================
    // 状态
    // =========================

    QComboBox* statusComboBox;

    // =========================
    // 按钮
    // =========================

    QPushButton* okButton;
    QPushButton* cancelButton;

	ApplicationContext& m_context;
};