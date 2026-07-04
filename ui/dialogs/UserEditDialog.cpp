#include "UserEditDialog.h"

UserEditDialog::UserEditDialog(QWidget* parent) {
	setupUI();

	connect(nameEdit, &QLineEdit::textChanged, this, &UserEditDialog::updateOkButtonState);
	connect(genderBox, &QComboBox::currentTextChanged, this, &UserEditDialog::updateOkButtonState);
	connect(ageBox, &QSpinBox::textChanged, this, &UserEditDialog::updateOkButtonState);
	connect(phoneEdit, &QLineEdit::textChanged, this, &UserEditDialog::updateOkButtonState);
	connect(usernameEdit, &QLineEdit::textChanged, this, &UserEditDialog::updateOkButtonState);
	connect(roleBox, &QComboBox::currentTextChanged, this, &UserEditDialog::updateOkButtonState);

	connect(okButton, &QPushButton::clicked, this, [this]() {accept();});

	connect(cancelButton, &QPushButton::clicked, this, [this]() {reject();});

	// 设置初始状态
	updateOkButtonState();
}

void UserEditDialog::setupUI() {
	// 1. 使用 QFormLayout 让表单整齐对齐
	QFormLayout* layout = new QFormLayout(this);

	// 2. 姓名输入框
	nameEdit = new QLineEdit(this);
	layout->addRow(tr("Name:"), nameEdit);

	// 3. 性别下拉框（仅 Male / Female）
	genderBox = new QComboBox(this);
	genderBox->addItems({ "Male", "Female" }); // 直接添加所有选项
	layout->addRow(tr("Gender:"), genderBox);

	// 4. 年龄输入框 ( QIntValidator 限制输入数字)
	ageBox = new QSpinBox(this);
	ageBox->setRange(0, 150);// 将验证器绑定到 ageEdit 上
	layout->addRow(tr("Age:"), ageBox);

	// 5. 电话输入框 (正则约束：目前限制为常见的国内11位手机号)
	phoneEdit = new QLineEdit(this);
	QRegularExpression phoneRegex("^1[3-9]\\d{9}$"); // 正则表达式：以1开头，第二位3-9，后面9位数字
	QRegularExpressionValidator* phoneValidator = new QRegularExpressionValidator(phoneRegex, this);
	phoneEdit->setValidator(phoneValidator);
	layout->addRow(tr("Phone:"), phoneEdit);

	// 6. 用户名输入框
	usernameEdit = new QLineEdit(this);
	layout->addRow(tr("Username:"), usernameEdit);

	// 7. 角色下拉框（仅 Admin / User）
	roleBox = new QComboBox(this);
	roleBox->addItems({ "Admin", "User" });
	layout->addRow(tr("Role:"), roleBox);

	// 8. 底部确认和取消按钮
	QHBoxLayout* btnLayout = new QHBoxLayout();
	btnLayout->addStretch(); // 弹簧，将按钮挤到右侧

	okButton = new QPushButton(tr("OK"), this);
	cancelButton = new QPushButton(tr("Cancel"), this);

	btnLayout->addWidget(okButton);
	btnLayout->addWidget(cancelButton);
	layout->addRow(btnLayout);
}

void UserEditDialog::setUser(const UserDTO& user)
{
	nameEdit->setText(QString::fromStdString(user.name));
	genderBox->setCurrentText(QString::fromStdString(user.gender)); // 设置下拉框选中的文本
	ageBox->setValue(user.age);
	phoneEdit->setText(QString::fromStdString(user.phone));
	usernameEdit->setText(QString::fromStdString(user.username));
	roleBox->setCurrentText(QString::fromStdString(user.role == Role::Admin ? "Admin" : "User"));
}

UserDTO UserEditDialog::getUser() const
{
	UserDTO user;
	user.name = nameEdit->text().trimmed().toStdString();
	user.gender = genderBox->currentText().toStdString();
	user.age = ageBox->value();
	user.phone = phoneEdit->text().trimmed().toStdString();
	user.username = usernameEdit->text().trimmed().toStdString();
	user.role = roleBox->currentText() == "Admin" ? Role::Admin : Role::User;
	return user;
}

void UserEditDialog::updateOkButtonState()
{
	// 定义几个判断条件
	bool nameIsValid = !nameEdit->text().trimmed().isEmpty();
	bool ageIsValid = !ageBox->text().trimmed().isEmpty();
	bool phoneIsValid = phoneEdit->hasAcceptableInput(); // 利用正则验证器自带的方法
	bool usernameIsValid = !usernameEdit->text().trimmed().isEmpty();

	// 只有当所有必填项非空，且电话符合正则时，OK按钮才启用
	okButton->setEnabled(nameIsValid && ageIsValid && phoneIsValid && usernameIsValid);
}