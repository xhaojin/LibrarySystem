#pragma once

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QHeaderView>

#include "dto/CategoryDTO.h"
#include "ui/dialogs/CategoryEditDialog.h"
#include "base/BasePage.h"
#include "common/utils/TableUtil.h"
#include "core/ApplicationContext.h"

class CategoryPage : public BasePage
{
	Q_OBJECT

public:
	explicit CategoryPage(ApplicationContext& context, QWidget* parent = nullptr);
	void refresh() override; //刷新表格

private:
	void setupUI();
	void setConnections();
	void refreshCategoriesTable(const std::vector<CategoryDTO>& categories); //刷新分类表格
	void addCategory(); //添加分类
	void updateCategory(); //更新分类
	void removeCategory(); //删除分类
	void onFindByNameClicked(); //按分类名称查找

private:
	ApplicationContext& m_context;

	QPushButton* refreshCategoryButton; //刷新

	QPushButton* searchButton; //按分类名称搜索按钮
	QLineEdit* searchEdit; //搜索框

	QPushButton* addCategoryButton; //添加分类
	QPushButton* removeCategoryButton; //删除分类
	QPushButton* updateCategoryButton; //更新分类

	QTableWidget* categoryTable; //分类表格
};