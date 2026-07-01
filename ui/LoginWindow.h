#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <app/SessionManager.h>
#include "controller/auth/AuthController.h"

class LoginWindow : public QWidget
{
	Q_OBJECT

public:
	explicit LoginWindow(AuthController& authController, QWidget* parent = nullptr);

signals:
	void loginSuccess();

private slots:
	void onLoginClicked();

private:
	AuthController& authController;
	QLineEdit* usernameEdit;
	QLineEdit* passwordEdit;

	QPushButton* loginButton;
};