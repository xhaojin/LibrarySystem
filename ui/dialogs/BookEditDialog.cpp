#include "BookEditDialog.h"

BookEditDialog::BookEditDialog(QWidget* parent) {
	setupUI();

	connect(titleEdit, &QLineEdit::textChanged, this, &BookEditDialog::updateOkButtonState);

	connect(authorEdit, &QLineEdit::textChanged, this, &BookEditDialog::updateOkButtonState);

	connect(publisherEdit, &QLineEdit::textChanged, this, &BookEditDialog::updateOkButtonState);

	connect(okButton, &QPushButton::clicked, this, [this]() {accept();});

	connect(cancelButton, &QPushButton::clicked, this, [this]() {reject();});
}

void BookEditDialog::setupUI() {
	auto* layout = new QVBoxLayout(this);
	layout->addWidget(new QLabel("编辑图书信息"));

	auto* formLayout = new QVBoxLayout();
	layout->addLayout(formLayout);

	auto* titleLayout = new QHBoxLayout();
	titleEdit = new QLineEdit();
	titleLayout->addWidget(new QLabel("标题:"));
	titleLayout->addWidget(titleEdit);

	auto* authorLayout = new QHBoxLayout();
	authorEdit = new QLineEdit();
	authorLayout->addWidget(new QLabel("作者:"));
	authorLayout->addWidget(authorEdit);

	auto* publishLayout = new QHBoxLayout();
	publisherEdit = new QLineEdit();
	publishLayout->addWidget(new QLabel("出版社:"));
	publishLayout->addWidget(publisherEdit);

	auto* priceLayout = new QHBoxLayout();
	priceSpinBox = new QDoubleSpinBox();
	priceLayout->addWidget(new QLabel("价格:"));
	priceLayout->addWidget(priceSpinBox);

	auto* buttonLayout = new QHBoxLayout();
	layout->addLayout(buttonLayout);

	okButton = new QPushButton("ok");
	cancelButton = new QPushButton("cacel");
	buttonLayout->addWidget(okButton);
	buttonLayout->addWidget(cancelButton);
}

void BookEditDialog::setBook(const BookDTO& book) {
	titleEdit->setText(QString::fromStdString(book.title));
	authorEdit->setText(QString::fromStdString(book.author));
	publisherEdit->setText(QString::fromStdString(book.publisher));
	priceSpinBox->setValue(book.price);
}

BookDTO BookEditDialog::getBook() const {
	BookDTO book;
	book.title = titleEdit->text().toStdString();
	book.author = authorEdit->text().toStdString();
	book.publisher = publisherEdit->text().toStdString();
	book.price = priceSpinBox->value();
	return book;
}

void BookEditDialog::updateOkButtonState()
{
	bool ok = !titleEdit->text().trimmed().isEmpty() && !authorEdit->text().trimmed().isEmpty() && !publisherEdit->text().trimmed().isEmpty();

	okButton->setEnabled(ok);
}