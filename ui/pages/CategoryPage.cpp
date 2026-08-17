#include "CategoryPage.h"

CategoryPage::CategoryPage(ApplicationContext& context, QWidget* parent) : BasePage(parent), m_context(context)
{
    setupUI();
    setConnections();
    refresh();
}

void CategoryPage::setupUI()
{
    auto* categoryLayout = new QVBoxLayout(this);

    categoryLayout->addWidget(new QLabel("分类管理"));

    // =========================
    // 顶部工具栏
    // =========================

    auto* toolbar = new QHBoxLayout;

    refreshCategoryButton = new QPushButton("刷新");

    searchEdit = new QLineEdit;

    searchEdit->setPlaceholderText("请输入分类名称");

    searchButton = new QPushButton("搜索");

    addCategoryButton = new QPushButton("新增");

    updateCategoryButton = new QPushButton("修改");

    removeCategoryButton = new QPushButton("删除");

    // =========================
    // 表格
    // =========================

    categoryTable = new QTableWidget(this);

    TableUtil::init(categoryTable);

    categoryTable->setColumnCount(4);

    categoryTable->setHorizontalHeaderLabels({ "ID","分类名称","排序","描述信息" });

    // =========================
    // 布局
    // =========================

    toolbar->addWidget(new QLabel("分类名称:"));
    toolbar->addWidget(searchEdit);
    toolbar->addWidget(searchButton);
    toolbar->addWidget(refreshCategoryButton);

    toolbar->addStretch();

    toolbar->addWidget(addCategoryButton);
    toolbar->addWidget(updateCategoryButton);
    toolbar->addWidget(removeCategoryButton);

    categoryLayout->addLayout(toolbar);

    categoryLayout->addWidget(categoryTable);
}

void CategoryPage::setConnections()
{
    connect(refreshCategoryButton, &QPushButton::clicked, this, &CategoryPage::refresh);

    connect(searchButton, &QPushButton::clicked, this, &CategoryPage::onFindByNameClicked);

    connect(searchEdit, &QLineEdit::returnPressed, this, &CategoryPage::onFindByNameClicked);

    connect(addCategoryButton, &QPushButton::clicked, this, &CategoryPage::addCategory);

    connect(updateCategoryButton, &QPushButton::clicked, this, &CategoryPage::updateCategory);

    connect(removeCategoryButton, &QPushButton::clicked, this, &CategoryPage::removeCategory);
}

void CategoryPage::refresh()
{
    auto categories = m_context.categoryController().getAllCategories();

    refreshCategoriesTable(categories);
}

void CategoryPage::refreshCategoriesTable(const std::vector<CategoryDTO>& categories)
{
    categoryTable->clearContents();

    categoryTable->setRowCount(static_cast<int>(categories.size()));

    for (int row = 0; row < categories.size(); ++row)
    {
        const auto& category = categories[row];

        categoryTable->setItem(row, 0, new QTableWidgetItem(QString::number(category.id)));

        categoryTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(category.name)));

        categoryTable->setItem(row, 2, new QTableWidgetItem(QString::number(category.sortOrder)));

        categoryTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(category.description)));
    }
}

void CategoryPage::addCategory()
{
    CategoryEditDialog categoryEditDialog(this); //分类编辑对话框
    categoryEditDialog.setWindowTitle("添加分类");
    if (categoryEditDialog.exec() != QDialog::Accepted)
        return;
    try
    {
        if (m_context.categoryController().addCategory(categoryEditDialog.getCategory()))
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

void CategoryPage::updateCategory()
{
    auto items = categoryTable->selectedItems();
    if (items.isEmpty())
    {
        showWarning("请先选择一个分类");
        return;
    }
    int row = categoryTable->currentRow();
    int categoryId = categoryTable->item(row, 0)->text().toInt();
    auto category = m_context.categoryController().findCategoryById(categoryId);

    CategoryEditDialog categoryEditDialog(this);
    categoryEditDialog.setWindowTitle("修改分类");
    categoryEditDialog.setCategory(category);

    if (categoryEditDialog.exec() != QDialog::Accepted)
        return;

    CategoryDTO dto = categoryEditDialog.getCategory();
    dto.id = categoryId;

    try
    {
        if (m_context.categoryController().updateCategory(dto))
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

void CategoryPage::removeCategory()
{
    auto items = categoryTable->selectedItems();
    if (items.isEmpty())
    {
        showWarning("请先选择一个分类");
        return;
    }
    int row = categoryTable->currentRow();
    int categoryId = categoryTable->item(row, 0)->text().toInt();
    auto category = m_context.categoryController().findCategoryById(categoryId);

    if (!confirmDelete(category.name.c_str())) {
        return;
    }

    try
    {
        if (m_context.categoryController().removeCategory(categoryId))
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

void CategoryPage::onFindByNameClicked()
{
    QString keyword = searchEdit->text();
    searchEdit->clear();
    auto categories = m_context.categoryController().findCategories(keyword.toStdString());
    refreshCategoriesTable(categories);
}