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
#include "controller/user/UserController.h"

class UserPage : public QWidget
{
    Q_OBJECT

public:
    explicit UserPage(UserController& userController,QWidget* parent = nullptr);

private:
    void setupUI();
    void setConnections();
    void refreshUsersTable(const std::vector<UserDTO>& books); //刷新用户表格

private:
    UserController& userController; //用户控制器

    QPushButton* refreshUserButton; //刷新

    QPushButton* searchButton; //搜索按钮

    QLineEdit* searchEdit; //搜索框

    QPushButton* addUserButton; //添加用户
    QPushButton* removeUserButton; //删除用户
    QPushButton* updateUserButton; //更新用户

    QTableWidget* userTable; //用户表格
};