#include "ui/MainWindow.h"

MainWindow::MainWindow(UIController& controller,QWidget* parent): QMainWindow(parent),controller(controller)
{
    setupUI();

    setupPermissions();

    refreshBooksTable();
}

void MainWindow::setupUI()
{
    auto* centralWidget = new QWidget(this);

    setCentralWidget(centralWidget);

    auto* mainLayout = new QVBoxLayout(centralWidget);

    //------------------------
    // 用户ID
    //------------------------

    auto* userLayout = new QHBoxLayout();

    userLayout->addWidget(new QLabel("User ID:"));

    userIdEdit = new QLineEdit();

    userLayout->addWidget(userIdEdit);

    mainLayout->addLayout(userLayout);

    //------------------------
    // 图书ID
    //------------------------

    auto* bookLayout = new QHBoxLayout();

    bookLayout->addWidget( new QLabel("Book ID:"));

    bookIdEdit = new QLineEdit();

    bookLayout->addWidget(bookIdEdit);

    mainLayout->addLayout(bookLayout);

    //------------------------
    // 按钮
    //------------------------

    auto* buttonLayout = new QHBoxLayout();

    borrowButton = new QPushButton("Borrow");

    returnButton = new QPushButton("Return");

    refreshButton = new QPushButton("Refresh");

    sortPriceButton = new QPushButton("Sort by Price");

    sortTitleButton = new QPushButton("Sort by Title");

    buttonLayout->addWidget(borrowButton);
    buttonLayout->addWidget(returnButton);
    buttonLayout->addWidget(refreshButton);
    buttonLayout->addWidget(sortPriceButton);
    buttonLayout->addWidget(sortTitleButton);

    mainLayout->addLayout(buttonLayout);

    //------------------------
    // 搜索
    //------------------------

    auto* searchLayout = new QHBoxLayout();

    searchLayout->addWidget(new QLabel("Search:"));
    
    searchEdit = new QLineEdit();

    searchButton = new QPushButton("Search");

    searchLayout->addWidget(searchEdit);
    searchLayout->addWidget(searchButton);

    mainLayout->addLayout(searchLayout);

    //------------------------
    // 表格
    //------------------------

    bookTable = new QTableWidget();

    mainLayout->addWidget(bookTable);

    setWindowTitle( "Library System");

    resize(900, 600);

    bookTable->setColumnCount(5);

    bookTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 设置列宽自适应

    bookTable->setHorizontalHeaderLabels({"Book ID","Title","Author","Price","Status"});

    // 连接信号和槽

    connect(borrowButton,&QPushButton::clicked,this,&MainWindow::onBorrowClicked);

    connect(returnButton,&QPushButton::clicked,this,&MainWindow::onReturnClicked);

    connect(refreshButton,&QPushButton::clicked,this,&MainWindow::refreshBooksTable);

    connect(searchButton,&QPushButton::clicked,this,&MainWindow::onFindByTitleClicked);

    connect(bookTable,&QTableWidget::cellClicked,this,&MainWindow::onTableCellClicked);

    connect(sortPriceButton,&QPushButton::clicked,this,&MainWindow::onSortPriceClicked);

    connect(sortTitleButton,&QPushButton::clicked,this,&MainWindow::onSortTitleClicked);
 
}

void MainWindow::setupPermissions() {
    auto role = SessionManager::currentUser().role;
    borrowButton->setVisible(true);
    returnButton->setVisible(true);
    refreshButton->setVisible(true);
    searchButton->setVisible(true);
    sortPriceButton->setVisible(true);
    sortTitleButton->setVisible(true);
}

void MainWindow::refreshBooksTable() {
    showBooks(controller.getAllBooks());
}

void MainWindow::onBorrowClicked()
{
    int userId = userIdEdit->text().toInt();

    int bookId = bookIdEdit->text().toInt();

    try
    {
        controller.borrowBook(userId,bookId);

        refreshBooksTable();

        QMessageBox::information(this,"成功","借书成功");

        userIdEdit->clear();
        bookIdEdit->clear();
    }
    catch (const std::exception& e)
    {
        QMessageBox::warning(this,"借书失败",e.what());
    }
}

void MainWindow::onReturnClicked()
{
    int userId = userIdEdit->text().toInt();

    int bookId = bookIdEdit->text().toInt();

    try
    {
        controller.returnBook(userId,bookId);

        refreshBooksTable();

        QMessageBox::information(this,"成功","还书成功");

        userIdEdit->clear();
        bookIdEdit->clear();
    }
    catch (const std::exception& e)
    {
        QMessageBox::warning(this,"还书失败",e.what());
    }
}

void MainWindow::onFindByTitleClicked() {
    QString keyword = searchEdit->text();
    searchEdit->clear();
    auto books = controller.searchBooksByTitle(keyword.toStdString());
    showBooks(books);
}

void MainWindow::onTableCellClicked(int row, int column) {
    if (column == 0) // Book ID列
    {
        auto* item = bookTable->item(row, 0);
        if (item)
        {
            int bookId = item->text().toInt();
            bookIdEdit->setText(QString::number(bookId));
        }
    }
}

void MainWindow::showBooks(const std::vector<BookDTO>& books)
{
    bookTable->clearContents();

    bookTable->setRowCount(static_cast<int>(books.size()));

    for (int row = 0; row < books.size(); ++row)
    {
        const auto& book = books[row];

        bookTable->setItem(row, 0,new QTableWidgetItem(QString::number(book.id)));

        bookTable->setItem(row, 1,new QTableWidgetItem(QString::fromStdString(book.title)));

        bookTable->setItem(row, 2,new QTableWidgetItem(QString::fromStdString(book.author)));

        bookTable->setItem(row, 3,new QTableWidgetItem(QString::number(book.price)));

        bookTable->setItem(row, 4,new QTableWidgetItem(book.isBorrowed ?"已借出" :"可借阅"));
    }
}

void MainWindow::onSortPriceClicked(){
    try
    {
        auto books = controller.getBooksSortedByPrice();
        showBooks(books);
    }
    catch (const std::exception& e)
    {
        QMessageBox::warning(this, "", e.what());
    }
}

void MainWindow::onSortTitleClicked(){
    auto books = controller.getBooksSortedByTitle();
    showBooks(books);
}