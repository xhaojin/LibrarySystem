#pragma once
#include <QApplication>
#include "ui/mainWindow/MainWindow.h"

/*
* AppManager 负责应用生命周期。
* ApplicationContext 负责依赖生命周期。
*/

class AppManager : public QObject
{
    Q_OBJECT

public:
    AppManager();

    int run(int argc, char* argv[]);

private:
    void createMainWindow(); // 创建主窗口
    bool showLoginDialog(); // 显示登录对话框

private:
    std::unique_ptr<ApplicationContext> context;

    std::unique_ptr<MainWindow> mainWindow;
};