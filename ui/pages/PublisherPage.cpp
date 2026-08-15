#include "PublisherPage.h"

PublisherPage::PublisherPage(ApplicationContext& context,QWidget* parent): BasePage(parent),m_context(context)
{
    setupUI();
    setConnections();
    refresh();
}

void PublisherPage::setupUI()
{
    auto* publisherLayout = new QVBoxLayout(this);

    publisherLayout->addWidget(new QLabel("出版社管理"));

    // =========================
    // 顶部工具栏
    // =========================

    auto* toolbar = new QHBoxLayout;

    refreshPublisherButton = new QPushButton("刷新");

    searchEdit = new QLineEdit;

    searchEdit->setPlaceholderText("请输入出版社名称");

    searchButton = new QPushButton("搜索");

    addPublisherButton = new QPushButton("新增");

    updatePublisherButton = new QPushButton("修改");

    removePublisherButton = new QPushButton("删除");

    // =========================
    // 表格
    // =========================

    publisherTable = new QTableWidget(this);

    TableUtil::init(publisherTable);

    publisherTable->setColumnCount(4);

    publisherTable->setHorizontalHeaderLabels({"ID","出版社名称","联系方式","官网"});

    // =========================
    // 布局
    // =========================

    toolbar->addWidget(new QLabel("出版社名称:"));
    toolbar->addWidget(searchEdit);
    toolbar->addWidget(searchButton);
    toolbar->addWidget(refreshPublisherButton);

    toolbar->addStretch();

    toolbar->addWidget(addPublisherButton);
    toolbar->addWidget(updatePublisherButton);
    toolbar->addWidget(removePublisherButton);

    publisherLayout->addLayout(toolbar);

    publisherLayout->addWidget(publisherTable);
}

void PublisherPage::setConnections()
{
    connect(refreshPublisherButton,&QPushButton::clicked,this,&PublisherPage::refresh);

    connect(searchButton,&QPushButton::clicked,this,&PublisherPage::onFindByNameClicked);

    connect(searchEdit,&QLineEdit::returnPressed,this,&PublisherPage::onFindByNameClicked);

    connect(addPublisherButton,&QPushButton::clicked,this,&PublisherPage::addPublisher);

    connect(updatePublisherButton,&QPushButton::clicked,this,&PublisherPage::updatePublisher);

    connect(removePublisherButton,&QPushButton::clicked,this,&PublisherPage::removePublisher);
}

void PublisherPage::refresh()
{
    auto publishers = m_context.publisherController().getAllPublishers();

    refreshPublishersTable(publishers);
}

void PublisherPage::refreshPublishersTable(const std::vector<PublisherDTO>& publishers)
{
    publisherTable->clearContents();

    publisherTable->setRowCount(static_cast<int>(publishers.size()));

    for (int row = 0; row < publishers.size(); ++row)
    {
        const auto& publisher = publishers[row];

        publisherTable->setItem(row,0,new QTableWidgetItem(QString::number(publisher.id)));

        publisherTable->setItem(row,1,new QTableWidgetItem(QString::fromStdString(publisher.name)));

        publisherTable->setItem(row,2,new QTableWidgetItem(QString::fromStdString(publisher.contact)));

        publisherTable->setItem(row,3,new QTableWidgetItem(QString::fromStdString(publisher.website)));
    }
}

void PublisherPage::addPublisher()
{
    PublisherEditDialog publisherEditDialog(this); //出版社编辑对话框
    publisherEditDialog.setWindowTitle("添加出版社");
    if (publisherEditDialog.exec() != QDialog::Accepted)
        return;
    try
    {
        if (m_context.publisherController().addPublisher(publisherEditDialog.getPublisher()))
        {
            showInfo("添加成功");
            refresh();
        }
        else
        {
            showWarning("添加失败");
        }
    }
    catch (const std::exception& e)
    {
        showError(e.what());
    }
}

void PublisherPage::updatePublisher()
{
    auto items = publisherTable->selectedItems();
    if (items.isEmpty())
    {
        showWarning("请先选择一个出版社");
        return;
    }
    int row = publisherTable->currentRow();
    int publisherId = publisherTable->item(row, 0)->text().toInt();
    auto publisher = m_context.publisherController().findPublisherById(publisherId);

    PublisherEditDialog publisherEditDialog(this);
    publisherEditDialog.setWindowTitle("修改出版社");
    publisherEditDialog.setPublisher(publisher);

    if (publisherEditDialog.exec() != QDialog::Accepted)
        return;

    PublisherDTO dto = publisherEditDialog.getPublisher();
    dto.id = publisherId;

    try
    {
        if (m_context.publisherController().updatePublisher(dto))
        {
            showInfo("修改成功");
            refresh();
        }
        else
        {
            showWarning("修改失败");
        }
    }
    catch (const std::exception& e)
    {
        showError(e.what());
    }
}

void PublisherPage::removePublisher()
{
    auto items = publisherTable->selectedItems();
    if (items.isEmpty())
    {
        showWarning("请先选择一个出版社");
        return;
    }
    int row = publisherTable->currentRow();
    int publisherId = publisherTable->item(row, 0)->text().toInt();
    auto publisher = m_context.publisherController().findPublisherById(publisherId);

    if (!confirmDelete(publisher.name.c_str())) {
        return;
    }

    try
    {
        if (m_context.publisherController().removePublisher(publisherId))
        {
            showInfo("删除成功");
            refresh();
        }
        else
        {
            showWarning("删除失败");
        }
    }
    catch (const std::exception& e)
    {
        showError(e.what());
    }
}

void PublisherPage::onFindByNameClicked()
{
    QString keyword = searchEdit->text();
    searchEdit->clear();
    auto publishers = m_context.publisherController().findPublishers(keyword.toStdString());
    refreshPublishersTable(publishers);
}