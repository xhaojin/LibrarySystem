#include "BorrowPage.h"

BorrowPage::BorrowPage(ApplicationContext& context, QWidget* parent) :m_context(context), BasePage(parent)
{
	setupUI();
	setConnections();
	loadUsers();
	loadBooks();
	loadBorrowRecords();
	refresh();
}

void BorrowPage::setupUI() {
    auto* mainLayout = new QVBoxLayout(this);

    // =====================================================
    // 借书
    // =====================================================

    auto* borrowGroup = new QGroupBox("借书", this);

    auto* borrowLayout = new QFormLayout(borrowGroup);

    m_userComboBox = new QComboBox(this);

    m_bookComboBox = new QComboBox(this);

    m_borrowOperatorComboBox = new QComboBox(this);

    m_dueDateEdit = new QDateEdit(this);

    m_dueDateEdit->setCalendarPopup(true);

    m_dueDateEdit->setDate(QDate::currentDate().addMonths(1));

    m_borrowRemarkEdit = new QLineEdit(this);

    m_borrowButton = new QPushButton("借书", this);

    borrowLayout->addRow("用户：",m_userComboBox);

    borrowLayout->addRow("图书：",m_bookComboBox);

    borrowLayout->addRow("操作员：",m_borrowOperatorComboBox);

    borrowLayout->addRow("应还日期：",m_dueDateEdit);

    borrowLayout->addRow("备注：",m_borrowRemarkEdit);

    borrowLayout->addRow("",m_borrowButton);

    mainLayout->addWidget(borrowGroup);

    // =====================================================
    // 还书
    // =====================================================

    auto* returnGroup = new QGroupBox("还书", this);

    auto* returnLayout = new QFormLayout(returnGroup);

    m_borrowRecordComboBox = new QComboBox(this);

    m_returnOperatorComboBox = new QComboBox(this);

    m_returnRemarkEdit = new QLineEdit(this);

    m_returnButton = new QPushButton("还书", this);

    returnLayout->addRow("借阅记录：",m_borrowRecordComboBox);

    returnLayout->addRow("操作员：",m_returnOperatorComboBox);

    returnLayout->addRow("备注：",m_returnRemarkEdit);

    returnLayout->addRow("",m_returnButton);

    mainLayout->addWidget(returnGroup);

    // =====================================================
    // 借阅记录
    // =====================================================

    auto* recordGroup = new QGroupBox("借阅记录", this);

    auto* recordLayout = new QVBoxLayout(recordGroup);

    m_refreshButton = new QPushButton("刷新", this);

    recordLayout->addWidget(m_refreshButton);

    m_recordTable = new QTableWidget(this);

    m_recordTable->setColumnCount(8);

    m_recordTable->setHorizontalHeaderLabels({
        "ID",
        "用户",
        "图书",
        "副本",
        "借阅时间",
        "应还时间",
        "归还时间",
        "状态"
        });

    TableUtil::init(m_recordTable);

    recordLayout->addWidget(m_recordTable);

    mainLayout->addWidget(recordGroup);

    mainLayout->setStretch(2,1);
}

void BorrowPage::setConnections()
{
    connect(m_borrowButton,&QPushButton::clicked,this,&BorrowPage::onBorrowClicked);

    connect(m_returnButton,&QPushButton::clicked,this,&BorrowPage::onReturnClicked);

    connect(m_refreshButton, &QPushButton::clicked, this, [this]() {refresh();});
}

void BorrowPage::refresh()
{
    loadUsers();
    loadBooks();
    loadBorrowRecords();
	//if (m_context.sessionManager().isAdmin()) {
	//	refreshBorrowRecordsTable(m_context.borrowController().getAllBorrowRecords());
	//}
	//else {
	//	refreshBorrowRecordsTable(m_context.borrowController().findBorrowRecordByNameAndBookTitle(m_context.sessionManager().currentUser().name,""));
	//}
}

void BorrowPage::refreshBorrowRecordsTable(const std::vector<BorrowRecordDTO>& records)
{
	//borrowRecordTable->clearContents();

	//borrowRecordTable->setRowCount(static_cast<int>(records.size()));

	//for (int row = 0; row < records.size(); ++row)
	//{
	//	const auto& re = records[row];

	//	borrowRecordTable->setItem(row, 0, new QTableWidgetItem(QString::number(re.id)));

	//	borrowRecordTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(re.username)));

	//	borrowRecordTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(re.bookTitle)));

	//	borrowRecordTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(re.borrowTime)));

	//	borrowRecordTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(re.returnTime)));
	//}
    loadBorrowRecords();
}

void BorrowPage::loadUsers()
{
    m_userComboBox->clear();

    m_borrowOperatorComboBox->clear();

    m_returnOperatorComboBox->clear();

    try
    {
        auto users = m_context.userController().getAllUsers();

        for (const auto& user : users)
        {
            QString text = QString::fromStdString(std::to_string(user.id)+ " - "+ user.name);

            m_userComboBox->addItem(text,QVariant::fromValue(static_cast<qlonglong>(user.id)));

            m_borrowOperatorComboBox->addItem(text,QVariant::fromValue(static_cast<qlonglong>(user.id)));

            m_returnOperatorComboBox->addItem(text,QVariant::fromValue(static_cast<qlonglong>(user.id)));
        }
    }
    catch (const std::exception& e)
    {
        showError("错误");
    }
}

void BorrowPage::loadBooks()
{
    m_bookComboBox->clear();

    try
    {
        auto books = m_context.bookController().getAllBooks();

        for (const auto& book : books)
        {
            QString text =QString::fromStdString(std::to_string(book.id)+ " - "+ book.title);

            m_bookComboBox->addItem(text,QVariant::fromValue(static_cast<qlonglong>(book.id)));
        }
    }
    catch (const std::exception& e)
    {
        showError("错误");
    }
}

void BorrowPage::loadBorrowRecords()
{
    m_recordTable->setRowCount(0);

    m_borrowRecordComboBox->clear();

    try
    {
        auto records = m_context.borrowController().getAllBorrowRecords();

        for (const auto& record : records)
        {
            const int row = m_recordTable->rowCount();

            m_recordTable->insertRow(row);

            m_recordTable->setItem(row,0,new QTableWidgetItem(QString::number(record.id)));

            m_recordTable->setItem(row,1,new QTableWidgetItem(QString::number(record.userId)));

            m_recordTable->setItem(row,2,new QTableWidgetItem(QString::number(record.copyId)));

            m_recordTable->setItem(row,3,new QTableWidgetItem(QString::number(record.operatorId)));

            m_recordTable->setItem(row,4,new QTableWidgetItem(QString::fromStdString(record.borrowTime)));

            m_recordTable->setItem(row,5,new QTableWidgetItem(QString::fromStdString(record.dueTime)));

            m_recordTable->setItem(row,6,new QTableWidgetItem(QString::fromStdString(record.returnTime)));

            QString statusText;

            switch (record.status)
            {
            case 0:
                statusText = "借阅中";
                break;

            case 1:
                statusText = "已归还";
                break;

            case 2:
                statusText = "逾期";
                break;

            default:
                statusText = "未知";
                break;
            }

            m_recordTable->setItem(row,7,new QTableWidgetItem(statusText));

            // 添加到还书下拉框
            if (record.status != 1)
            {
                QString text = QString("记录 %1 - 用户 %2 - 副本 %3")
                    .arg(record.id)
                    .arg(record.userId)
                    .arg(record.copyId);

                m_borrowRecordComboBox->addItem(text,QVariant::fromValue(static_cast<qlonglong>(record.id)));
            }
        }
    }
    catch (const std::exception& e)
    {
        showInfo("错误");
    }
}

void BorrowPage::onBorrowClicked()
{
    if (m_userComboBox->currentIndex() < 0)
    {
        showInfo("请选择用户");

        return;
    }

    if (m_bookComboBox->currentIndex() < 0)
    {
        showInfo("请选择图书");

        return;
    }

    if (m_borrowOperatorComboBox->currentIndex() < 0)
    {
        showInfo("请选择操作员");

        return;
    }

    const std::int64_t userId = m_userComboBox->currentData() .toLongLong();

    const std::int64_t bookId = m_bookComboBox->currentData().toLongLong();

    const std::int64_t operatorId = m_borrowOperatorComboBox->currentData().toLongLong();

    const QString dueDate = m_dueDateEdit->date().toString("yyyy-MM-dd")+ " 23:59:59";

    const std::string remark = m_borrowRemarkEdit->text().toStdString();

    try
    {
        bool success = m_context.borrowController().borrowBook(
                userId,
                bookId,
                operatorId,
                dueDate.toStdString(),
                remark);

        if (!success)
        {
            showInfo("借书失败,没有可借副本，或者用户不存在");

            return;
        }

        showInfo("借书成功！");

        m_borrowRemarkEdit->clear();

        loadBorrowRecords();
    }
    catch (const std::exception& e)
    {
        showInfo("借书异常");
    }
}

void BorrowPage::onReturnClicked()
{
    if (m_borrowRecordComboBox->currentIndex() < 0)
    {
        showInfo("请选择借阅记录");

        return;
    }

    if (m_returnOperatorComboBox->currentIndex() < 0)
    {
        showInfo("请选择操作员");

        return;
    }

    const std::int64_t borrowRecordId = m_borrowRecordComboBox->currentData().toLongLong();

    const std::int64_t operatorId = m_returnOperatorComboBox->currentData().toLongLong();

    const std::string remark = m_returnRemarkEdit->text().toStdString();

    try
    {
        bool success = m_context.borrowController().returnBook(
                borrowRecordId,
                operatorId,
                remark);

        if (!success)
        {
            showInfo("借阅记录不存在，或者已经归还");

            return;
        }

        showInfo("还书成功");

        m_returnRemarkEdit->clear();

        loadBorrowRecords();
    }
    catch (const std::exception& e)
    {
        showError("还书异常");
    }
}