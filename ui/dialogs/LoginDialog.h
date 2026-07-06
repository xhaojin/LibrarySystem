#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <app/SessionManager.h>
#include "controller/auth/AuthController.h"

class LoginDialog : public QDialog
{
	Q_OBJECT

public:
	explicit LoginDialog(AuthController& authController, QWidget* parent = nullptr);

private slots:
	void onLoginClicked();

private:
	AuthController& authController;
	QLineEdit* usernameEdit;
	QLineEdit* passwordEdit;

	QPushButton* loginButton;
};