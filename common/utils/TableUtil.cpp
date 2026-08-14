#include "TableUtil.h"
#include <QHeaderView>

void TableUtil::init(QTableWidget* table)
{
    table->setSelectionBehavior(QAbstractItemView::SelectRows);// 设置选择行为：点击任意单元格时，默认选中该单元格所在的整行

    table->setSelectionMode(QAbstractItemView::SingleSelection);// 设置选择模式：限制为单选，一次只能选中一行（禁止Ctrl多选）

    table->setEditTriggers(QAbstractItemView::NoEditTriggers);// 设置编辑触发：关闭所有编辑功能，使表格成为纯粹的只读展示列表

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);// 设置水平表头（列名）：所有列宽自动均匀拉伸，填满整个表格的横向空间，防止列太窄

    table->verticalHeader()->setVisible(false);// 设置垂直表头（左侧的默认行号列）：将其隐藏，保持UI视觉简洁，不显示 1, 2, 3... 等行号
}