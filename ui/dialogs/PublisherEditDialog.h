#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QLabel>

#include "dto/PublisherDTO.h"

class PublisherEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PublisherEditDialog(QWidget* parent = nullptr);

    // 编辑模式
    void setPublisher(const PublisherDTO& publisher);

    // 获取用户填写的数据
    PublisherDTO getPublisher() const;

private slots:
    void updateOkButtonState();

private:
    void setupUI();

private:
    // =========================
    // 基本信息
    // =========================

    QLineEdit* nameEdit;
    QLineEdit* contactEdit;
    QLineEdit* websiteEdit;

    // =========================
    // 按钮
    // =========================

    QPushButton* okButton;
    QPushButton* cancelButton;
};