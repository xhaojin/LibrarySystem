#include "CategoryEditDialog.h"

CategoryEditDialog::CategoryEditDialog(QWidget* parent)
    : QDialog(parent),
    nameEdit(nullptr),
    sortOrderSpinBox(nullptr),
    descriptionEdit(nullptr),
    okButton(nullptr),
    cancelButton(nullptr)
{
    setupUI();
    updateOkButtonState();
}

void CategoryEditDialog::setupUI()
{
    setMinimumWidth(400);

    // =========================
    // 输入框
    // =========================

    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("请输入分类名称");

    sortOrderSpinBox = new QSpinBox(this);
    sortOrderSpinBox->setRange(0, 9999);
    sortOrderSpinBox->setValue(0);

    descriptionEdit = new QTextEdit(this);
    descriptionEdit->setPlaceholderText("请输入分类描述");

    // =========================
    // 表单布局
    // =========================

    auto* formLayout = new QFormLayout;

    formLayout->addRow("分类名称：", nameEdit);

    formLayout->addRow("排序序号：", sortOrderSpinBox);

    formLayout->addRow("分类描述：", descriptionEdit);

    // =========================
    // 按钮
    // =========================

    okButton = new QPushButton("确定", this);
    cancelButton = new QPushButton("取消", this);

    okButton->setDefault(true);

    auto* buttonLayout = new QHBoxLayout;

    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    // =========================
    // 主布局
    // =========================

    auto* mainLayout = new QVBoxLayout(this);

    mainLayout->addLayout(formLayout);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    // =========================
    // 信号
    // =========================

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);

    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    connect(nameEdit, &QLineEdit::textChanged, this, &CategoryEditDialog::updateOkButtonState);
}

void CategoryEditDialog::updateOkButtonState()
{
    const bool valid = !nameEdit->text().trimmed().isEmpty();

    okButton->setEnabled(valid);
}

void CategoryEditDialog::setCategory(const CategoryDTO& category)
{
    nameEdit->setText(QString::fromStdString(category.name));

    sortOrderSpinBox->setValue(category.sortOrder);

    descriptionEdit->setText(QString::fromStdString(category.description));

    updateOkButtonState();
}

CategoryDTO CategoryEditDialog::getCategory() const
{
    CategoryDTO category;

    category.name = nameEdit->text().trimmed().toStdString();

    category.sortOrder = sortOrderSpinBox->value();

    category.description = descriptionEdit->toPlainText().trimmed().toStdString();

    return category;
}