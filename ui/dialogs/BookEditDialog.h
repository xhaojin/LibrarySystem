#pragma once

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "dto/BookDTO.h"

class BookEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BookEditDialog(QWidget* parent = nullptr);

    void setBook(const BookDTO& book);

    BookDTO getBook() const;

private:
    void setupUI();
    void updateOkButtonState();

private:
    QLineEdit* titleEdit;
    QLineEdit* authorEdit;
    QLineEdit* publisherEdit;
    QDoubleSpinBox* priceSpinBox;

    QPushButton* okButton;
    QPushButton* cancelButton;
};