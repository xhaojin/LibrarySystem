#include "BookEditDialog.h"

BookEditDialog::BookEditDialog(QWidget* parent) {
	setupUI();

	// =========================
	// 信号槽
	// =========================

	connect(okButton, &QPushButton::clicked, this, &QDialog::accept);

	connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

	connect(isbnEdit, &QLineEdit::textChanged, this, &BookEditDialog::updateOkButtonState);

	connect(titleEdit, &QLineEdit::textChanged, this, &BookEditDialog::updateOkButtonState);

	connect(authorEdit, &QLineEdit::textChanged, this, &BookEditDialog::updateOkButtonState);

	// 设置初始状态
	updateOkButtonState();
}

void BookEditDialog::setupUI() {
	auto* mainLayout = new QVBoxLayout(this);

	auto* formLayout = new QFormLayout();

	// =========================
	// ISBN
	// =========================

	isbnEdit = new QLineEdit(this);
	isbnEdit->setPlaceholderText("请输入 ISBN");

	formLayout->addRow("ISBN：", isbnEdit);

	// =========================
	// 书名
	// =========================

	titleEdit = new QLineEdit(this);
	titleEdit->setPlaceholderText("请输入书名");

	formLayout->addRow("书名：", titleEdit);

	// =========================
	// 作者
	// =========================

	authorEdit = new QLineEdit(this);
	authorEdit->setPlaceholderText("请输入作者");

	formLayout->addRow("作者：", authorEdit);

	// =========================
	// 出版社 ID
	// =========================

	publisherIdSpinBox = new QSpinBox(this);

	publisherIdSpinBox->setRange(0, 999999999);
	publisherIdSpinBox->setSpecialValueText("未选择");

	formLayout->addRow("出版社 ID：", publisherIdSpinBox);

	// =========================
	// 分类 ID
	// =========================

	categoryIdSpinBox = new QSpinBox(this);

	categoryIdSpinBox->setRange(0, 999999999);
	categoryIdSpinBox->setSpecialValueText("未选择");

	formLayout->addRow("分类 ID：", categoryIdSpinBox);

	// =========================
	// 出版年份
	// =========================

	publishYearSpinBox = new QSpinBox(this);

	publishYearSpinBox->setRange(0, 2100);
	publishYearSpinBox->setSpecialValueText("未填写");

	formLayout->addRow("出版年份：", publishYearSpinBox);

	// =========================
	// 价格
	// =========================

	priceSpinBox = new QDoubleSpinBox(this);

	priceSpinBox->setRange(0.0, 99999999.99);
	priceSpinBox->setDecimals(2);
	priceSpinBox->setSingleStep(1.0);
	priceSpinBox->setSuffix(" 元");

	formLayout->addRow("价格：", priceSpinBox);

	// =========================
	// 封面 URL
	// =========================

	coverUrlEdit = new QLineEdit(this);
	coverUrlEdit->setPlaceholderText("请输入封面 URL（可选）");

	formLayout->addRow("封面：", coverUrlEdit);

	// =========================
	// 描述
	// =========================

	descriptionEdit = new QTextEdit(this);
	descriptionEdit->setPlaceholderText("请输入图书描述（可选）");
	descriptionEdit->setMaximumHeight(100);

	formLayout->addRow("描述：", descriptionEdit);

	// =========================
	// 状态
	// =========================

	statusComboBox = new QComboBox(this);

	statusComboBox->addItem("正常", 0);
	statusComboBox->addItem("下架", 1);
	statusComboBox->addItem("禁用", 2);

	formLayout->addRow("状态：", statusComboBox);

	mainLayout->addLayout(formLayout);

	// =========================
	// 按钮
	// =========================

	auto* buttonLayout = new QHBoxLayout();

	okButton = new QPushButton("确定", this);
	cancelButton = new QPushButton("取消", this);

	buttonLayout->addStretch();
	buttonLayout->addWidget(okButton);
	buttonLayout->addWidget(cancelButton);

	mainLayout->addLayout(buttonLayout);
}

void BookEditDialog::setBook(const BookDTO& book) {
	isbnEdit->setText(QString::fromStdString(book.isbn));

	titleEdit->setText(QString::fromStdString(book.title));

	authorEdit->setText(QString::fromStdString(book.author));

	publisherIdSpinBox->setValue(static_cast<int>(book.publisherId));

	categoryIdSpinBox->setValue(static_cast<int>(book.categoryId));

	publishYearSpinBox->setValue(book.publishYear);

	priceSpinBox->setValue(book.price);

	//coverUrlEdit->setText(QString::fromStdString(book.coverUrl));

	//descriptionEdit->setPlainText(QString::fromStdString(book.description));

	int status = statusComboBox->findText(QString::fromStdString(book.status));

	if (status >= 0)
	{
		statusComboBox->setCurrentIndex(status);
	}
}

BookDTO BookEditDialog::getBook() const {
	BookDTO book{};

	book.isbn = isbnEdit->text().trimmed().toStdString();

	book.title = titleEdit->text().trimmed().toStdString();

	book.author = authorEdit->text().trimmed().toStdString();

	book.publisherId = publisherIdSpinBox->value();

	book.categoryId = categoryIdSpinBox->value();

	book.publishYear = publishYearSpinBox->value();

	book.price = priceSpinBox->value();

	//book.coverUrl = coverUrlEdit->text().trimmed().toStdString();

	//book.description = descriptionEdit->toPlainText().trimmed().toStdString();

	book.status = statusComboBox->currentText().toStdString();

	return book;
}

void BookEditDialog::updateOkButtonState()
{
	const bool valid =
		!isbnEdit->text().trimmed().isEmpty() &&
		!titleEdit->text().trimmed().isEmpty() &&
		!authorEdit->text().trimmed().isEmpty();

	okButton->setEnabled(valid);
}