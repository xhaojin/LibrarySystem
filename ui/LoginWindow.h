#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

#include "UIController.h"
#include "MainWindow.h"

class LoginWindow : public QWidget
{
	Q_OBJECT

public:
	explicit LoginWindow(UIController& controller, QWidget* parent = nullptr);

signals:
	void loginSuccess();

private slots:
	void onLoginClicked();

private:
	UIController& controller;
	QLineEdit* usernameEdit;
	QLineEdit* passwordEdit;

	QPushButton* loginButton;
};