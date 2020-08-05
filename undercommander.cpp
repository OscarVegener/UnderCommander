#include "undercommander.h"
#include "ui_undercommander.h"
#include "newfile.cpp"
#include "newfolder.h"
#include "info.h"

UnderCommander::UnderCommander(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UnderCommander)
{
    ui->setupUi(this);

    leftModel = new QFileSystemModel(this);
    rightModel = new QFileSystemModel(this);
    drivesModelLeft = new QDirModel(parent = this);
    drivesModelRight = new QDirModel(parent = this);
    leftController = new ModelViewController(leftModel,
                                             drivesModelLeft,
                                             ui->textEditLeft,
                                             ui->comboBoxLeft,
                                             ui->forwardLeft,
                                             ui->backLeft,
                                             ui->pushButtonLeft,
                                             ui->leftView,
                                             this,
                                             "C:/",
                                             this);
    connect(leftController, &ModelViewController::setClipboardDataSignal, this, &UnderCommander::setClipboardData);
    rightController = new ModelViewController(rightModel,
                                              drivesModelRight,
                                              ui->textEditRight,
                                              ui->comboBoxRight,
                                              ui->forwardRight,
                                              ui->backRight,
                                              ui->pushButtonRight,
                                              ui->rightView,
                                              this,
                                              "C:/",
                                              this);
    connect(rightController, &ModelViewController::setClipboardDataSignal, this, &UnderCommander::setClipboardData);
    ui->rightWidget->hide();
    initPalettes();
    createTabs();
}

UnderCommander::~UnderCommander()
{
    delete ui;
}

void UnderCommander::createTabs()
{
    createTabMenuLeft();
    tabBarLeft = new tabs(ui->comboBoxLeft->currentText());
    tabBarLeft->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(leftModel, &QFileSystemModel::rootPathChanged, tabBarLeft, &tabs::changeTabName);
    connect(tabBarLeft, &tabs::tabBarClicked, this, &UnderCommander::tabBarLeftClick);
    connect(tabBarLeft, &tabs::customContextMenuRequested, this, &UnderCommander::customTabMenuLeft);
    ui->verticalLayout->insertWidget(1, tabBarLeft);
    tabBarLeft->hide();

    createTabMenuRight();
    tabBarRight = new tabs(ui->comboBoxRight->currentText());
    tabBarRight->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(rightModel, &QFileSystemModel::rootPathChanged, tabBarRight, &tabs::changeTabName);
    connect(tabBarRight, &tabs::tabBarClicked, this, &UnderCommander::tabBarRightClick);
    connect(tabBarRight, &tabs::customContextMenuRequested, this, &UnderCommander::customTabMenuRight);
    ui->verticalLayout_2->insertWidget(1, tabBarRight);
    tabBarRight->hide();
}

void UnderCommander::createTabMenuLeft()
{
    leftTabMenu = new QMenu(this);
    deleteTabLeftAction = new QAction(tr("Delete tab"), this);
    deleteTabLeftAction->setToolTip("Delete current selected tab");
    connect(deleteTabLeftAction, &QAction::triggered, this, &UnderCommander::deleteTabLeft);
    leftTabMenu->addAction(deleteTabLeftAction);
}

void UnderCommander::createTabMenuRight()
{
    rightTabMenu = new QMenu(this);
    deleteTabRightAction = new QAction(tr("Delete tab"), this);
    deleteTabRightAction->setToolTip("Delete current selected tab");
    connect(deleteTabRightAction, &QAction::triggered, this, &UnderCommander::deleteTabRight);
    rightTabMenu->addAction(deleteTabRightAction);
}

void UnderCommander::initPalettes()
{
    defaultPalette = qApp->palette();
    darkPalette.setColor(QPalette::Window,QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText,Qt::white);
    darkPalette.setColor(QPalette::Disabled,QPalette::WindowText,QColor(127,127,127));
    darkPalette.setColor(QPalette::Base,QColor(42,42,42));
    darkPalette.setColor(QPalette::AlternateBase,QColor(66,66,66));
    darkPalette.setColor(QPalette::ToolTipBase,Qt::white);
    darkPalette.setColor(QPalette::ToolTipText,Qt::white);
    darkPalette.setColor(QPalette::Text,Qt::white);
    darkPalette.setColor(QPalette::Disabled,QPalette::Text,QColor(127,127,127));
    darkPalette.setColor(QPalette::Dark,QColor(35,35,35));
    darkPalette.setColor(QPalette::Shadow,QColor(20,20,20));
    darkPalette.setColor(QPalette::Button,QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText,Qt::white);
    darkPalette.setColor(QPalette::Disabled,QPalette::ButtonText,QColor(127,127,127));
    darkPalette.setColor(QPalette::BrightText,Qt::red);
    darkPalette.setColor(QPalette::Link,QColor(42,130,218));
    darkPalette.setColor(QPalette::Highlight,QColor(42,130,218));
    darkPalette.setColor(QPalette::Disabled,QPalette::Highlight,QColor(80,80,80));
    darkPalette.setColor(QPalette::HighlightedText,Qt::white);
    darkPalette.setColor(QPalette::Disabled,QPalette::HighlightedText,QColor(127,127,127));
}

void UnderCommander::on_leftView_clicked(const QModelIndex &index)
{
    leftController->select(index);
}

void UnderCommander::on_rightView_clicked(const QModelIndex &index)
{
    rightController->select(index);
}

void UnderCommander::on_pushButtonLeft_clicked()
{
    leftController->go(ui->textEditLeft->text());
}

void UnderCommander::on_pushButtonRight_clicked()
{
    rightController->go(ui->textEditRight->text());
}

void UnderCommander::on_backLeft_clicked()
{
    leftController->back();
}

void UnderCommander::on_backRight_clicked()
{
    rightController->back();
}


void UnderCommander::on_forwardLeft_clicked()
{
    leftController->forward();
}

void UnderCommander::on_forwardRight_clicked()
{
    rightController->forward();
}

//Menubar

void UnderCommander::on_actionDark_triggered()
{
    if (curPalette != 1){
        qApp->setPalette(darkPalette);
        curPalette = 1;
    }
}

void UnderCommander::on_actionDefault_triggered()
{
    if (curPalette != 0){
        qApp->setPalette(defaultPalette);
        curPalette = 0;
    }
}

void UnderCommander::on_actionShow_only_files_triggered()
{
    //QModelIndexList list = ui->leftView->selectionModel()->selectedIndexes();
    //ui->leftView->selectionModel()->reset();
    if (leftModel->filter() != QDir::Files){
        leftModel->setFilter(QDir::Files);
    }
}

void UnderCommander::on_actionShow_only_folders_triggered()
{
    if (leftModel->filter() != QDir::Dirs){
        leftModel->setFilter(QDir::Dirs);
    }
}

void UnderCommander::on_actionShow_only_files_2_triggered()
{
    if (rightModel->filter() != QDir::Files){
        rightModel->setFilter(QDir::Files);
    }
}

void UnderCommander::on_actionShow_only_folders_2_triggered()
{
    if (rightModel->filter() != QDir::Dirs){
        rightModel->setFilter(QDir::Dirs);
    }
}

void UnderCommander::on_actionShow_files_and_folders_triggered()
{
    if (leftModel->filter() != QDir::AllEntries){
        leftModel->setFilter(QDir::AllEntries);
    }
}

void UnderCommander::on_actionShow_files_and_folders_2_triggered()
{
    if (rightModel->filter() != QDir::AllEntries){
        rightModel->setFilter(QDir::AllEntries);
    }
}

void UnderCommander::on_actionCreate_tab_triggered()
{
    tabBarLeft->createTab(leftController->getDefaultPath());
}

void UnderCommander::on_actionNew_right_tab_triggered()
{
    tabBarRight->createTab(rightController->getDefaultPath());
}

void UnderCommander::tabBarLeftClick(int index)
{
    if (index >= 0){
        //qDebug() << index;
        tabBarLeft->setCurrentIndex(index);
        tabBarLeft->setCurrentTab(index);
        QString path = tabBarLeft->savedPath(index);
        leftController->go(path);
//        QDir dir(path);
//        if (dir.exists()){
//            ui->leftView->setRootIndex(leftModel->setRootPath(path));
//            leftCurrent = path;
//            ui->textEditLeft->setText(path);
//            QString comboPath;
//            comboPath.push_back(path.at(0));
//            comboPath.push_back(path.at(1));
//            int index = ui->comboBoxLeft->findText(comboPath);
//            ui->comboBoxLeft->setCurrentIndex(index);
//        }
//        else{
//            path = ui->comboBoxLeft->currentText() + "/";
//            ui->leftView->setRootIndex(leftModel->setRootPath(path));
//            leftCurrent = path;
//            ui->textEditLeft->setText(path);
//            tabBarLeft->resetTab(index, path);
//            QApplication::beep();
//            QMessageBox::warning(this, "UnderCommander", "Folder was removed!");
//            tabBarLeft->setCurrentTab(index);
//            tabBarLeft->setCurrentIndex(index);
//        }
        //qDebug() << path;
    }
}

void UnderCommander::tabBarRightClick(int index)
{
//    if (index >= 0){
//        //qDebug() << index;
//        tabBarRight->setCurrentIndex(index);
//        tabBarRight->setCurrentTab(index);
//        QString path = tabBarRight->savedPath(index);
//        QDir dir(path);
//        if (dir.exists()){
//            ui->rightView->setRootIndex(rightModel->setRootPath(path));
//            rightCurrent = path;
//            ui->textEditRight->setText(path);
//            QString comboPath;
//            comboPath.push_back(path.at(0));
//            comboPath.push_back(path.at(1));
//            int index = ui->comboBoxRight->findText(comboPath);
//            ui->comboBoxRight->setCurrentIndex(index);
//        }
//        else{
//            path = ui->comboBoxRight->currentText() + "/";
//            ui->rightView->setRootIndex(rightModel->setRootPath(path));
//            rightCurrent = path;
//            ui->textEditRight->setText(path);
//            tabBarRight->resetTab(index, path);
//            QApplication::beep();
//            QMessageBox::warning(this, "UnderCommander", "Folder was removed!");
//            tabBarRight->setCurrentTab(index);
//            tabBarRight->setCurrentIndex(index);
//        }
//        //qDebug() << path;
//    }
}

void UnderCommander::on_actionEnable_tabs_triggered()
{
    if (ui->actionEnable_tabs->isChecked()){
        tabBarLeft->show();
        tabBarRight->show();
    }
    else{
        tabBarLeft->hide();
        tabBarRight->hide();
    }
}

void UnderCommander::on_actionExit_triggered()
{
    QApplication::quit();
}

void UnderCommander::customTabMenuLeft(QPoint pos)
{
    deleteTabLeftAction->setEnabled(true);
    if (tabBarLeft->count() == 1){
        deleteTabLeftAction->setEnabled(false);
    }
    leftTabMenu->popup(QCursor::pos());
}

void UnderCommander::customTabMenuRight(QPoint pos)
{
//    deleteTabRightAction->setEnabled(true);
//    if (tabBarRight->count() == 1){
//        deleteTabRightAction->setEnabled(false);
//    }
//    rightTabMenu->popup(QCursor::pos());
}

void UnderCommander::deleteTabLeft()
{
//    tabBarLeft->deleteTab(tabBarLeft->currentIndex());
//    int index = tabBarLeft->currentIndex();

//    tabBarLeft->setCurrentTab(index);
//    QString path = tabBarLeft->savedPath(index);
//    QDir dir(path);
//    if (dir.exists()){
//        ui->leftView->setRootIndex(leftModel->setRootPath(path));
//        leftCurrent = path;
//        ui->textEditLeft->setText(path);
//        QString comboPath;
//        comboPath.push_back(path.at(0));
//        comboPath.push_back(path.at(1));
//        int index = ui->comboBoxLeft->findText(comboPath);
//        ui->comboBoxLeft->setCurrentIndex(index);
//    }
//    else{
//        path = ui->comboBoxLeft->currentText() + "/";
//        ui->leftView->setRootIndex(leftModel->setRootPath(path));
//        leftCurrent = path;
//        ui->textEditLeft->setText(path);
//        tabBarLeft->resetTab(index, path);
//        QApplication::beep();
//        QMessageBox::warning(this, "UnderCommander", "Folder was removed!");
//        tabBarLeft->setCurrentTab(index);
//        tabBarLeft->setCurrentIndex(index);
//    //qDebug() << path;
//    }
}

void UnderCommander::deleteTabRight()
{
//    tabBarRight->deleteTab(tabBarRight->currentIndex());
//    int index = tabBarRight->currentIndex();

//    tabBarRight->setCurrentTab(index);
//    QString path = tabBarRight->savedPath(index);
//    QDir dir(path);
//    if (dir.exists()){
//        ui->rightView->setRootIndex(rightModel->setRootPath(path));
//        rightCurrent = path;
//        ui->textEditRight->setText(path);
//        QString comboPath;
//        comboPath.push_back(path.at(0));
//        comboPath.push_back(path.at(1));
//        int index = ui->comboBoxRight->findText(comboPath);
//        ui->comboBoxRight->setCurrentIndex(index);
//    }
//    else{
//        path = ui->comboBoxRight->currentText() + "/";
//        ui->rightView->setRootIndex(rightModel->setRootPath(path));
//        rightCurrent = path;
//        ui->textEditRight->setText(path);
//        tabBarRight->resetTab(index, path);
//        QApplication::beep();
//        QMessageBox::warning(this, "UnderCommander", "Folder was removed!");
//        tabBarRight->setCurrentTab(index);
//        tabBarRight->setCurrentIndex(index);
//    //qDebug() << path;
//    }
}

void UnderCommander::on_actionNew_file_triggered()
{
    //smallLeftContextNewFile();
}

void UnderCommander::on_actionNew_folder_triggered()
{
    //smallLeftContextNewFolder();
}

void UnderCommander::on_actionNew_file_3_triggered()
{
    //smallRightContextNewFile();
}

void UnderCommander::on_actionNew_folder_2_triggered()
{
    //smallRightContextNewFolder();
}

void UnderCommander::on_actionOpen_directory_left_triggered()
{
//    QFileDialog dlg(this);
//    dlg.setFileMode(QFileDialog::DirectoryOnly);
//    if (dlg.exec()){
//        QStringList fileNames = dlg.selectedFiles();
//        if (fileNames.empty()){
//            QMessageBox::warning(this, "UnderCommander", "Error opening folder!");
//            return;
//        }
//        //qDebug() << fileNames;
//        QString path = fileNames.takeAt(0);
//        changeLeftRootPath(path);
//    }
}

void UnderCommander::on_actionOpen_directory_right_triggered()
{
//    QFileDialog dlg(this);
//    dlg.setFileMode(QFileDialog::DirectoryOnly);
//    if (dlg.exec()){
//        QStringList fileNames = dlg.selectedFiles();
//        if (fileNames.empty()){
//            QMessageBox::warning(this, "UnderCommander", "Error opening folder!");
//            return;
//        }
//        //qDebug() << fileNames;
//        QString path = fileNames.takeAt(0);
//        changeRightRootPath(path);
//    }
}

void UnderCommander::on_actionEnable_size_column_triggered()
{
    if (!ui->actionEnable_size_column->isChecked()){
        ui->leftView->hideColumn(1);
    }
    else ui->leftView->showColumn(1);
}

void UnderCommander::on_actionEnable_date_column_triggered()
{
    if (!ui->actionEnable_date_column->isChecked()){
        ui->leftView->hideColumn(3);
    }
    else ui->leftView->showColumn(3);
}

void UnderCommander::on_actionEnable_size_column_2_triggered()
{
    if (!ui->actionEnable_size_column_2->isChecked()){
        ui->rightView->hideColumn(1);
    }
    else ui->rightView->showColumn(1);
}

void UnderCommander::on_actionEnable_date_column_2_triggered()
{
    if (!ui->actionEnable_date_column_2->isChecked()){
        ui->rightView->hideColumn(3);
    }
    else ui->rightView->showColumn(3);
}

void UnderCommander::on_actionEnable_type_column_triggered()
{
    if (!ui->actionEnable_type_column->isChecked()){
        ui->leftView->hideColumn(2);
    }
    else ui->leftView->showColumn(2);
}

void UnderCommander::on_actionEnable_type_column_2_triggered()
{
    if (!ui->actionEnable_type_column_2->isChecked()){
        ui->rightView->hideColumn(2);
    }
    else ui->rightView->showColumn(2);
}

void UnderCommander::on_comboBoxLeft_activated(const QString &arg1)
{
    leftController->changeDrive(arg1);
}

void UnderCommander::on_comboBoxRight_activated(const QString &arg1)
{
    rightController->changeDrive(arg1);
}

void UnderCommander::on_leftView_activated(const QModelIndex &index)
{
    leftController->open(index);
}


void UnderCommander::on_rightView_activated(const QModelIndex &index)
{
    rightController->open(index);
}

void UnderCommander::setClipboardData(QMimeData *data)
{
    QApplication::clipboard()->setMimeData(data);
}
