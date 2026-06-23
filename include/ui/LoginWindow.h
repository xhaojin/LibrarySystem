#pragma once

#include <QWidget>

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessagebox>

#include "UIController.h"

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
};