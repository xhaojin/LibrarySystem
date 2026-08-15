#include "PublisherEditDialog.h"

PublisherEditDialog::PublisherEditDialog(QWidget* parent)
    : QDialog(parent),
    nameEdit(nullptr),
    contactEdit(nullptr),
    websiteEdit(nullptr),
    okButton(nullptr),
    cancelButton(nullptr)
{
    setupUI();
    updateOkButtonState();
}

void PublisherEditDialog::setupUI()
{
    setMinimumWidth(400);

    // =========================
    // 输入框
    // =========================

    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("请输入出版社名称");

    contactEdit = new QLineEdit(this);
    contactEdit->setPlaceholderText("请输入联系方式");

    websiteEdit = new QLineEdit(this);
    websiteEdit->setPlaceholderText("请输入出版社官网");

    // =========================
    // 表单布局
    // =========================

    auto* formLayout = new QFormLayout;

    formLayout->addRow("出版社名称：",nameEdit);

    formLayout->addRow("联系方式：",contactEdit);

    formLayout->addRow("官网：",websiteEdit);

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

    connect(okButton,&QPushButton::clicked,this,&QDialog::accept);

    connect(cancelButton,&QPushButton::clicked,this,&QDialog::reject);

    connect(nameEdit,&QLineEdit::textChanged,this,&PublisherEditDialog::updateOkButtonState);
}

void PublisherEditDialog::updateOkButtonState()
{
    const bool valid = !nameEdit->text().trimmed().isEmpty();

    okButton->setEnabled(valid);
}

void PublisherEditDialog::setPublisher(const PublisherDTO& publisher)
{
    nameEdit->setText(QString::fromStdString(publisher.name));

    contactEdit->setText(QString::fromStdString(publisher.contact));

    websiteEdit->setText(QString::fromStdString(publisher.website));

    updateOkButtonState();
}

PublisherDTO PublisherEditDialog::getPublisher() const
{
    PublisherDTO publisher;

    publisher.name = nameEdit->text().trimmed().toStdString();

    publisher.contact = contactEdit->text().trimmed().toStdString();

    publisher.website = websiteEdit->text().trimmed().toStdString();

    return publisher;
}