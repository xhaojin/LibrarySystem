#pragma once

#include <QWidget>

#include <QLineEdit>
#include <QPushButton>
#pragma once

#include <QVBoxLayout>
#pragma once

#include <QLabel>
#include <QMessageBox>

#include "UIController.h"
#include "MainWindow.h"

class LoginWindow : public QWidget
{
	Q_OBJECT

public:
	explicit LoginWindow(UIController& controller, QWidget* parent = nullptr);

private slots:
	void onLoginClicked();

private:
	UIController& controller;
	QLineEdit* usernameEdit;
	QLineEdit* passwordEdit;

	QPushButton* loginButton;

	std::unique_ptr<MainWindow> mainWindow;
};