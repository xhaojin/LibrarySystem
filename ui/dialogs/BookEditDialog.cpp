#include "BookEditDialog.h"

BookEditDialog::BookEditDialog(ApplicationContext& context, QWidget* parent) : m_context(context) {
	setupUI();

	loadPublishers();
	loadCategories();

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
	// 出版社
	// =========================

	publisherComboBox = new QComboBox(this);

	publisherComboBox->addItem("未选择",QVariant::fromValue<qlonglong>(0));

	formLayout->addRow("出版社：",publisherComboBox);

	// =========================
	// 分类
	// =========================

	categoryComboBox = new QComboBox(this);

	categoryComboBox->addItem("未选择",QVariant::fromValue<qlonglong>(0));

	formLayout->addRow("分类：",categoryComboBox);

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

	int publisherIndex = publisherComboBox->findData(QVariant::fromValue<qlonglong>(book.publisherId));

	if (publisherIndex >= 0)
	{
		publisherComboBox->setCurrentIndex(publisherIndex);
	}
	else
	{
		publisherComboBox->setCurrentIndex(0);
	}

	int categoryIndex = categoryComboBox->findData(QVariant::fromValue<qlonglong>(book.categoryId));

	if (categoryIndex >= 0)
	{
		categoryComboBox->setCurrentIndex(categoryIndex);
	}
	else
	{
		categoryComboBox->setCurrentIndex(0);
	}

	publishYearSpinBox->setValue(book.publishYear);

	priceSpinBox->setValue(book.price);

	coverUrlEdit->setText(QString::fromStdString(book.coverUrl));

	descriptionEdit->setPlainText(QString::fromStdString(book.description));

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

	book.publisherId = publisherComboBox->currentData().toLongLong();

	book.categoryId = categoryComboBox->currentData().toLongLong();

	book.publishYear = publishYearSpinBox->value();

	book.price = priceSpinBox->value();

	book.coverUrl = coverUrlEdit->text().trimmed().toStdString();

	book.description = descriptionEdit->toPlainText().trimmed().toStdString();

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

void BookEditDialog::loadPublishers()
{
	publisherComboBox->clear();

	publisherComboBox->addItem("未选择",QVariant::fromValue<qlonglong>(0));

	auto publishers = m_context.publisherController().getAllPublishers();

	for (const auto& publisher : publishers)
	{
		publisherComboBox->addItem(QString::fromStdString(publisher.name),
			QVariant::fromValue<qlonglong>(publisher.id));
	}
}

void BookEditDialog::loadCategories()
{
	categoryComboBox->clear();

	categoryComboBox->addItem("未选择",QVariant::fromValue<qlonglong>(0));

	auto categories = m_context.categoryController().getAllCategories();

	for (const auto& category : categories)
	{
		categoryComboBox->addItem(QString::fromStdString(category.name),
			QVariant::fromValue<qlonglong>(category.id));
	}
}