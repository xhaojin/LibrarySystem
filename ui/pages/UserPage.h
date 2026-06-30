#pragma once

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QHeaderView>

#include "dto/UserDTO.h"

class UserPage : public QWidget
{
    Q_OBJECT

public:
    explicit UserPage(QWidget* parent = nullptr);

    void refreshUsers(const std::vector<UserDTO>& books);

signals:
    void addUserRequested();
    void removeUserRequested();
    void updateUserRequested();

    void refreshRequested();

    void searchRequested(const QString& keyword);

private:
    void setupUI();

private:
    QPushButton* refreshUserButton; //刷新

    QPushButton* searchButton; //搜索按钮

    QLineEdit* searchEdit; //搜索框

    QPushButton* addUserButton; //添加用户
    QPushButton* removeUserButton; //删除用户
    QPushButton* updateUserButton; //更新用户

    QTableWidget* userTable; //用户表格
};