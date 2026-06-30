#pragma once

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QHeaderView>

#include "dto/BorrowRecordDTO.h"

class BorrowRecordPage : public QWidget
{
    Q_OBJECT

public:
    explicit BorrowRecordPage(QWidget* parent = nullptr);

    void refreshBorrowRecords(const std::vector<BorrowRecordDTO>& books);

signals:
    void addBorrowRecordRequested();
    void removeBorrowRecordRequested();
    void updateBorrowRecordRequested();

    void refreshRequested();

    void searchRequested(const QString& keyword);

private:
    void setupUI();

private:
    QPushButton* refreshBorrowRecordButton; //刷新

    QPushButton* searchButton; //搜索按钮

    QLineEdit* searchEdit; //搜索框

    QTableWidget* borrowRecordTable; //借阅记录表格
};