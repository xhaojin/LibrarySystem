#pragma once

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QHeaderView>
#include <QListWidget>
#include <QComboBox>
#include <QDate>
#include <QFormLayout>
#include <QGroupBox>

#include <cstdint>
#include <vector>

#include "ui/pages/base/BasePage.h"
#include "common/utils/TableUtil.h"
#include "core/ApplicationContext.h"

class BorrowPage : public BasePage
{
    Q_OBJECT

public:
    explicit BorrowPage(ApplicationContext& context,QWidget* parent = nullptr);

    void refresh() override;

private:
    void setupUI();

    void setConnections();

    // =====================================================
    // 数据加载
    // =====================================================

    void loadUsers(const QString& keyword = "");

    void loadBooks(const QString& keyword = "");

    void loadBorrowRecords();

    void loadCurrentBorrowRecords(std::int64_t userId);

    // =====================================================
    // 表格刷新
    // =====================================================

    void refreshBorrowRecordsTable(const std::vector<BorrowRecordViewDTO>& records);

    void refreshCurrentBorrowTable(const std::vector<BorrowRecordViewDTO>& records);

    // =====================================================
    // UI 辅助
    // =====================================================

    void clearUserSelection();

    void clearBookSelection();

    void clearReturnUserSelection();

private slots:

    // =====================================================
    // 借书
    // =====================================================

    void onUserSearch();

    void onUserSelected(QListWidgetItem* item);

    void onBookSearch();

    void onBookSelected(QListWidgetItem* item);

    void onBorrowClicked();

    // =====================================================
    // 还书
    // =====================================================

    void onReturnUserSearch();

    void onReturnUserSelected(QListWidgetItem* item);

    // =====================================================
    // 借阅记录
    // =====================================================

    void onRecordSearch();

    // =====================================================
    // 刷新
    // =====================================================

    void onRefreshClicked();

private:

    ApplicationContext& m_context;

    // =====================================================
    // 借书
    // =====================================================

    // 用户搜索
    QLineEdit* m_userSearchEdit;

    QPushButton* m_userSearchButton;

    QListWidget* m_userSearchList;

    QLabel* m_selectedUserLabel;

    // 当前选择的用户 ID
    std::int64_t m_selectedUserId = 0;

    // 图书搜索
    QLineEdit* m_bookSearchEdit;

    QPushButton* m_bookSearchButton;

    QListWidget* m_bookSearchList;

    QLabel* m_selectedBookLabel;

    // 当前选择的图书 ID
    std::int64_t m_selectedBookId = 0;

    // 应还日期
    QDateEdit* m_dueDateEdit;

    // 备注
    QLineEdit* m_borrowRemarkEdit;

    // 借书按钮
    QPushButton* m_borrowButton;

    // =====================================================
    // 还书
    // =====================================================

    QLineEdit* m_returnUserSearchEdit;

    QPushButton* m_returnUserSearchButton;

    QListWidget* m_returnUserSearchList;

    QLabel* m_selectedReturnUserLabel;

    std::int64_t m_selectedReturnUserId = 0;

    // 当前借阅
    QTableWidget* m_currentBorrowTable;

    // =====================================================
    // 借阅记录
    // =====================================================

    QLineEdit* m_recordSearchEdit;

    QComboBox* m_statusComboBox;

    QPushButton* m_recordSearchButton;

    QPushButton* m_refreshButton;

    QTableWidget* m_recordTable;
};