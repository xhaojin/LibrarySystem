#pragma once

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QHeaderView>

#include "dto/PublisherDTO.h"
//#include "ui/dialogs/PublisherEditDialog.h"
#include "base/BasePage.h"
#include "common/utils/TableUtil.h"
#include "core/ApplicationContext.h"

class PublisherPage : public BasePage
{
	Q_OBJECT

public:
	explicit PublisherPage(ApplicationContext& context, QWidget* parent = nullptr);
	void refresh() override; //刷新表格

private:
	void setupUI();
	void setConnections();
	void refreshPublishersTable(const std::vector<PublisherDTO>& publishers); //刷新出版社表格
	void addPublisher(); //添加出版社
	void updatePublisher(); //更新出版社
	void removePublisher(); //删除出版社
	void onFindByNameClicked(); //按出版社名称查找

private:
	ApplicationContext& m_context;

	QPushButton* refreshPublisherButton; //刷新

	QPushButton* searchButton; //按出版社名称搜索按钮
	QLineEdit* searchEdit; //搜索框

	QPushButton* addPublisherButton; //添加出版社
	QPushButton* removePublisherButton; //删除出版社
	QPushButton* updatePublisherButton; //更新出版社

	QTableWidget* publisherTable; //出版社表格
};