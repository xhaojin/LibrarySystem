#pragma once

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QFormLayout>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QRegularExpressionValidator>
#include "dto/UserDTO.h"

class UserEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserEditDialog(QWidget* parent = nullptr);

    void setUser(const UserDTO& book);

    UserDTO getUser() const;

private:
    void setupUI();
    void updateOkButtonState();

private:
    QLineEdit* nameEdit;
    QComboBox* genderBox;
    QSpinBox* ageBox;
    QLineEdit* phoneEdit;
    QLineEdit* usernameEdit;
    QComboBox* roleBox;

    QPushButton* okButton;
    QPushButton* cancelButton;
};