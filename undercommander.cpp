#include "undercommander.h"
#include "ui_undercommander.h"
//#include "modelviewcontroller.h"
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
                                             "C:\\",
                                             this);

//    //Show disks on left side
//    drivesModelLeft = new QDirModel(this); //todo
//    drivesModelLeft->setFilter(QDir::Drives);
//    ui->comboBoxLeft->setModel(drivesModelLeft);
//    //drivesModelLeft->refresh();

//    //Show disks on right side
//    drivesModelRight = new QDirModel(this); //todo
//    drivesModelRight->setFilter(QDir::Drives);
//    ui->comboBoxRight->setModel(drivesModelRight);

//    //Setting timer to check if new disks connected
//    timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, this, &UnderCommander::updateDiskList);
//    timer->start(500);

//    //Root path on left
//    ui->textEditLeft->setText(ui->comboBoxLeft->currentText()+"/");
//    textEditLeftCurrent = ui->textEditLeft->text();

//    //Root path on right
//    ui->textEditRight->setText(ui->comboBoxRight->currentText()+"/");
//    textEditRightCurrent = ui->textEditRight->text();

//    //Setting up left panel
//    leftModel = new QFileSystemModel(this);
//    leftModel->setReadOnly(false);
//    ui->leftView->setModel(leftModel);
//    ui->leftView->setRootIndex(leftModel->setRootPath(ui->textEditLeft->text()));
//    leftModel->setFilter(QDir::AllEntries);
//    leftCurrent = ui->textEditLeft->text();
//    leftStack.push(ui->textEditLeft->text());
//    ui->leftView->setContextMenuPolicy(Qt::CustomContextMenu);
//    connect(ui->leftView, &FSView::customContextMenuRequested, this, &UnderCommander::on_customMenuRequestedLeft);
//    ui->leftView->setDragEnabled(true);
//    ui->leftView->setAcceptDrops(true);
//    ui->leftView->setDropIndicatorShown(true);
//    ui->leftView->init();
//    customIconProvider *iconProvider = new customIconProvider();
//    leftModel->setIconProvider(iconProvider);

//    //Setting up ContextMenu for left panel
//    createLeftContextMenu();
//    createSmallLeftContextMenu();

//    //Setting up right panel
//    rightModel = new QFileSystemModel(this);
//    rightModel->setReadOnly(false);
//    ui->rightView->setModel(rightModel);
//    ui->rightView->setRootIndex(rightModel->setRootPath(ui->textEditRight->text()));
//    rightModel->setFilter(QDir::AllEntries);
//    rightCurrent = ui->textEditRight->text();
//    rightStack.push(ui->textEditRight->text());
//    ui->rightView->setContextMenuPolicy(Qt::CustomContextMenu);
//    connect(ui->rightView, &FSView::customContextMenuRequested, this, &UnderCommander::on_customMenuRequestedRight);
//    ui->rightView->setDragEnabled(true);
//    ui->rightView->setAcceptDrops(true);
//    ui->rightView->setDropIndicatorShown(true);
//    ui->rightView->init();

//    //Setting up ContextMenu for right panel
//    createRightContextMenu();
//    createSmallRightContextMenu();

//    saveTextEditsSettings();
//    initBackForwardButtons();
    initPalettes();
    //createTabs();
}

UnderCommander::~UnderCommander()
{
//    clearMemoryLeftContextMenu();
//    clearMemorySmallLeftContextMenu();
//    clearMemoryRightContextMenu();
//    clearMemorySmallRightContextMenu();
    delete ui;
}

//void UnderCommander::ifUserGoesToAnotherDiskLeft(){
//    //if user goes to another disk
//    QString path = leftModel->rootPath();
//    QString comboPath;
//    comboPath.push_back(path.at(0));
//    comboPath.push_back(path.at(1));
//    int comboIndex = ui->comboBoxLeft->findText(comboPath);
//    ui->comboBoxLeft->setCurrentIndex(comboIndex);
//}

//void UnderCommander::ifUserGoesToAnotherDiskRight(){
//    QString path = rightModel->rootPath();
//    QString comboPath;
//    comboPath.push_back(path.at(0));
//    comboPath.push_back(path.at(1));
//    int comboIndex = ui->comboBoxRight->findText(comboPath);
//    ui->comboBoxRight->setCurrentIndex(comboIndex);
//}

//copy_options UnderCommander::askForCopyOptions()
//{
//    copy_options options = copy_options::recursive;
//    QMessageBox::StandardButton reply;
//    reply = QMessageBox::question(this, "Copying files...", "Overwrite existing files?", QMessageBox::Yes | QMessageBox::No);
//    if (reply == QMessageBox::Yes){
//        options = options | copy_options::overwrite_existing;
//    }
//    else{
//        reply = QMessageBox::question(this, "Copying files...", "Update existing files"
//                                                                "(replace the existing file only if it is older than the file being copied)?",
//                                      QMessageBox::Yes | QMessageBox::No);
//        if (reply == QMessageBox::Yes){
//            options = options | copy_options::update_existing;
//        }
//        else{
//            options = options | copy_options::skip_existing;
//        }
//    }
//    reply = QMessageBox::question(this, "Copying files...", "Copy simlinks?", QMessageBox::Yes | QMessageBox::No);
//    if (reply == QMessageBox::Yes){
//        options = options | copy_options::copy_symlinks;
//    }
//    else{
//        reply = QMessageBox::question(this, "Copying files...", "Create simlinks instead of copying?", QMessageBox::Yes | QMessageBox::No);
//        if (reply == QMessageBox::Yes){
//            options = options | copy_options::create_symlinks;
//        }
//        else{
//            options = options | copy_options::skip_symlinks;
//        }
//    }
//    return options;
//}

//void UnderCommander::displayLeft(QModelIndex index)
//{
//    QString iPath = leftModel->fileInfo(index).absoluteFilePath();
//    if (!infoPath.contains(iPath)){
//        infoPath.push_back(iPath);
//        info *window = new info(this, iPath);
//        connect(window, &info::removePathFromList, this, &UnderCommander::deleteInfoPath);
//        window->setWindowFlags(window->windowFlags() & ~Qt::WindowContextHelpButtonHint);
//        window->setModal(false);
//        window->setAttribute(Qt::WA_DeleteOnClose);
//        window->show();
//    }
//    else {
//        QApplication::beep();
//    }
//}

//void UnderCommander::leftCopy()
//{
//    QModelIndexList indexList = ui->leftView->selectionModel()->selectedIndexes();
//    QModelIndexList mimeList;
//    foreach (QModelIndex idx, indexList){
//        if(leftModel->fileInfo(idx).isFile()){
//            mimeList.push_back(idx);
//        }
//    }
//    QMimeData *data = leftModel->mimeData(mimeList);
//    QApplication::clipboard()->setMimeData(data);
//}

//void UnderCommander::clearMemoryLeftContextMenu()
//{
//    delete leftInfoAction;
//    delete leftRenameAction;
//    delete leftDeleteAction;
//    delete leftPasteRootAction;
//    delete leftPasteAction;
//    delete leftCopyFolderFilesAction;
//    delete leftCopyAction;
//    delete leftCutAction;
//    delete leftNewFolderAction;
//    delete leftNewFileAction;
//    delete leftPrintAction;
//    delete leftOpenAction;
//    delete newLeftMenu;
//    delete leftContextMenu;
//}

//void UnderCommander::createLeftContextMenu()
//{
//    leftContextMenu = new QMenu(this);
//    newLeftMenu = new QMenu("New", this);

//    leftOpenAction = new QAction(tr("&Open"), this);
//    leftOpenAction->setToolTip("Open new folder/file");
//    connect(leftOpenAction, &QAction::triggered, this, &UnderCommander::leftContextOpen);

//    leftPrintAction = new QAction(tr("&Print file"), this);
//    leftOpenAction->setToolTip("Print selected file");
//    connect(leftPrintAction, &QAction::triggered, this, &UnderCommander::leftContextPrint);

//    leftNewFileAction = new QAction(tr("&New File"), this);
//    leftNewFileAction->setToolTip("Create new file");
//    connect(leftNewFileAction, &QAction::triggered, this, &UnderCommander::leftContextNewFile);

//    leftNewFolderAction = new QAction(tr("&New Folder"), this);
//    leftNewFolderAction->setToolTip("Create new folder");
//    connect(leftNewFolderAction, &QAction::triggered, this, &UnderCommander::leftContextNewFolder);

//    leftCutAction = new QAction(tr("&Cut"), this);
//    leftCutAction->setToolTip("Cut folder/file");
//    connect(leftCutAction, &QAction::triggered, this, &UnderCommander::leftContextCut);

//    leftCopyAction = new QAction(tr("&Copy files to clipboard"), this);
//    leftCopyAction->setToolTip("Copy files to clipboard");
//    connect(leftCopyAction, &QAction::triggered, this, &UnderCommander::leftContextCopy);

//    leftCopyFolderFilesAction = new QAction(tr("&Copy"), this);
//    leftCopyFolderFilesAction->setToolTip("Copy file/folder to another place");
//    connect(leftCopyFolderFilesAction, &QAction::triggered, this, &UnderCommander::leftContextCopyFolderFiles);

//    leftPasteAction = new QAction(tr("&Paste"), this);
//    leftPasteAction->setToolTip("Paste file/folder in selected folder");
//    connect(leftPasteAction, &QAction::triggered, this, &UnderCommander::leftContextPaste);

//    leftPasteRootAction = new QAction(tr("&Paste to root"), this);
//    leftPasteRootAction->setToolTip("Paste file/folder in current folder");
//    connect(leftPasteRootAction, &QAction::triggered, this, &UnderCommander::leftContextPasteRoot);

//    leftDeleteAction = new QAction(tr("&Delete"), this);
//    leftDeleteAction->setToolTip("Delete file/folder");
//    connect(leftDeleteAction, &QAction::triggered, this, &UnderCommander::leftContextDelete);

//    leftRenameAction = new QAction(tr("&Rename"), this);
//    leftRenameAction->setToolTip("Rename file/folder");
//    connect(leftRenameAction, &QAction::triggered, this, &UnderCommander::leftContextRename);

//    leftInfoAction = new QAction(tr("&Properties"));
//    leftInfoAction->setToolTip("Show info about file/folder");
//    connect(leftInfoAction, &QAction::triggered, this, &UnderCommander::leftContextInfo);

//    newLeftMenu->addAction(leftNewFileAction);
//    newLeftMenu->addAction(leftNewFolderAction);
//    leftContextMenu->addAction(leftOpenAction);
//    leftContextMenu->addAction(leftPrintAction);
//    leftContextMenu->addMenu(newLeftMenu);
//    leftContextMenu->addAction(leftCutAction);
//    leftContextMenu->addAction(leftCopyAction);
//    leftContextMenu->addAction(leftCopyFolderFilesAction);
//    leftContextMenu->addAction(leftPasteAction);
//    leftContextMenu->addAction(leftPasteRootAction);
//    leftContextMenu->addAction(leftDeleteAction);
//    leftContextMenu->addAction(leftRenameAction);
//    leftContextMenu->addAction(leftInfoAction);
//}

//void UnderCommander::clearMemorySmallLeftContextMenu()
//{
//    delete smallLeftInfoAction;
//    delete smallLeftPasteAction;
//    delete smallLeftNewFolderAction;
//    delete smallLeftNewFileAction;
//    delete smallNewLeftMenu;
//    delete smallLeftContextMenu;
//}

//void UnderCommander::createSmallLeftContextMenu()
//{
//    smallLeftContextMenu = new QMenu(this);
//    smallNewLeftMenu = new QMenu("New", this);

//    smallLeftNewFileAction = new QAction(tr("&New File"), this);
//    smallLeftNewFileAction->setToolTip("Create new file");
//    connect(smallLeftNewFileAction, &QAction::triggered, this, &UnderCommander::smallLeftContextNewFile);

//    smallLeftNewFolderAction = new QAction(tr("&New Folder"), this);
//    smallLeftNewFolderAction->setToolTip("Create new folder");
//    connect(smallLeftNewFolderAction, &QAction::triggered, this, &UnderCommander::smallLeftContextNewFolder);

//    smallLeftPasteAction = new QAction(tr("&Paste to root"), this);
//    smallLeftPasteAction->setToolTip("Paste file/folder in current folder");
//    connect(smallLeftPasteAction, &QAction::triggered, this, &UnderCommander::leftContextPasteRoot);

//    smallLeftInfoAction = new QAction(tr("&Properties"));
//    smallLeftInfoAction->setToolTip("Show info about file/folder");
//    connect(smallLeftInfoAction, &QAction::triggered, this, &UnderCommander::smallLeftContextInfo);

//    smallNewLeftMenu->addAction(smallLeftNewFileAction);
//    smallNewLeftMenu->addAction(smallLeftNewFolderAction);
//    smallLeftContextMenu->addMenu(smallNewLeftMenu);
//    smallLeftContextMenu->addAction(smallLeftPasteAction);
//    smallLeftContextMenu->addAction(smallLeftInfoAction);
//}

//void UnderCommander::displayRight(QModelIndex index)
//{
//    QString iPath = rightModel->fileInfo(index).absoluteFilePath();
//    if (!infoPath.contains(iPath)){
//        infoPath.push_back(iPath);
//        info *window = new info(this, iPath);
//        connect(window, &info::removePathFromList, this, &UnderCommander::deleteInfoPath);
//        window->setWindowFlags(window->windowFlags() & ~Qt::WindowContextHelpButtonHint);
//        window->setModal(false);
//        window->setAttribute(Qt::WA_DeleteOnClose);
//        window->show();
//    }
//    else {
//        QApplication::beep();
//    }
//}

//void UnderCommander::rightCopy()
//{
//    QModelIndexList indexList = ui->rightView->selectionModel()->selectedIndexes();
//    QModelIndexList mimeList;
//    foreach (QModelIndex idx, indexList){
//        if(rightModel->fileInfo(idx).isFile()){
//            mimeList.push_back(idx);
//        }
//    }
//    QMimeData *data = rightModel->mimeData(mimeList);
//    QApplication::clipboard()->setMimeData(data);
//}

//void UnderCommander::clearMemoryRightContextMenu()
//{
//    delete rightInfoAction;
//    delete rightRenameAction;
//    delete rightDeleteAction;
//    delete rightPasteRootAction;
//    delete rightPasteAction;
//    delete rightCopyFolderFilesAction;
//    delete rightCopyAction;
//    delete rightCutAction;
//    delete rightNewFolderAction;
//    delete rightNewFileAction;
//    delete rightPrintAction;
//    delete rightOpenAction;
//    delete newRightMenu;
//    delete rightContextMenu;
//}

//void UnderCommander::createRightContextMenu()
//{
//    rightContextMenu = new QMenu(this);
//    newRightMenu = new QMenu("New", this);

//    rightOpenAction = new QAction(tr("&Open"), this);
//    rightOpenAction->setToolTip("Open new folder/file");
//    connect(rightOpenAction, &QAction::triggered, this, &UnderCommander::rightContextOpen);

//    rightPrintAction = new QAction(tr("&Print file"), this);
//    rightOpenAction->setToolTip("Print selected file");
//    connect(rightPrintAction, &QAction::triggered, this, &UnderCommander::rightContextPrint);

//    rightNewFileAction = new QAction(tr("&New File"), this);
//    rightNewFileAction->setToolTip("Create new file");
//    connect(rightNewFileAction, &QAction::triggered, this, &UnderCommander::rightContextNewFile);

//    rightNewFolderAction = new QAction(tr("&New Folder"), this);
//    rightNewFolderAction->setToolTip("Create new folder");
//    connect(rightNewFolderAction, &QAction::triggered, this, &UnderCommander::rightContextNewFolder);

//    rightCutAction = new QAction(tr("&Cut"), this);
//    rightCutAction->setToolTip("Cut folder/file");
//    connect(rightCutAction, &QAction::triggered, this, &UnderCommander::rightContextCut);

//    rightCopyAction = new QAction(tr("&Copy files to clipboard"), this);
//    rightCopyAction->setToolTip("Copy files to clipboard");
//    connect(rightCopyAction, &QAction::triggered, this, &UnderCommander::rightContextCopy);

//    rightCopyFolderFilesAction = new QAction(tr("&Copy"), this);
//    rightCopyFolderFilesAction->setToolTip("Copy file/folder to another place");
//    connect(rightCopyFolderFilesAction, &QAction::triggered, this, &UnderCommander::rightContextCopyFolderFiles);

//    rightPasteAction = new QAction(tr("&Paste"), this);
//    rightPasteAction->setToolTip("Paste file/folder in selected folder");
//    connect(rightPasteAction, &QAction::triggered, this, &UnderCommander::rightContextPaste);

//    rightPasteRootAction = new QAction(tr("&Paste to root"), this);
//    rightPasteRootAction->setToolTip("Paste file/folder in current folder");
//    connect(rightPasteRootAction, &QAction::triggered, this, &UnderCommander::rightContextPasteRoot);

//    rightDeleteAction = new QAction(tr("&Delete"), this);
//    rightDeleteAction->setToolTip("Delete file/folder");
//    connect(rightDeleteAction, &QAction::triggered, this, &UnderCommander::rightContextDelete);

//    rightRenameAction = new QAction(tr("&Rename"), this);
//    rightRenameAction->setToolTip("Rename file/folder");
//    connect(rightRenameAction, &QAction::triggered, this, &UnderCommander::rightContextRename);

//    rightInfoAction = new QAction(tr("&Properties"));
//    rightInfoAction->setToolTip("Show info about file/folder");
//    connect(rightInfoAction, &QAction::triggered, this, &UnderCommander::rightContextInfo);

//    newRightMenu->addAction(rightNewFileAction);
//    newRightMenu->addAction(rightNewFolderAction);
//    rightContextMenu->addAction(rightOpenAction);
//    rightContextMenu->addAction(rightPrintAction);
//    rightContextMenu->addMenu(newRightMenu);
//    rightContextMenu->addAction(rightCutAction);
//    rightContextMenu->addAction(rightCopyAction);
//    rightContextMenu->addAction(rightCopyFolderFilesAction);
//    rightContextMenu->addAction(rightPasteAction);
//    rightContextMenu->addAction(rightPasteRootAction);
//    rightContextMenu->addAction(rightDeleteAction);
//    rightContextMenu->addAction(rightRenameAction);
//    rightContextMenu->addAction(rightInfoAction);
//}

//void UnderCommander::clearMemorySmallRightContextMenu()
//{
//    delete smallRightInfoAction;
//    delete smallRightPasteAction;
//    delete smallRightNewFolderAction;
//    delete smallRightNewFileAction;
//    delete smallNewRightMenu;
//    delete smallRightContextMenu;
//}

//void UnderCommander::createSmallRightContextMenu()
//{
//    smallRightContextMenu = new QMenu(this);
//    smallNewRightMenu = new QMenu("New", this);

//    smallRightNewFileAction = new QAction(tr("&New File"), this);
//    smallRightNewFileAction->setToolTip("Create new file");
//    connect(smallRightNewFileAction, &QAction::triggered, this, &UnderCommander::smallRightContextNewFile);

//    smallRightNewFolderAction = new QAction(tr("&New Folder"), this);
//    smallRightNewFolderAction->setToolTip("Create new folder");
//    connect(smallRightNewFolderAction, &QAction::triggered, this, &UnderCommander::smallRightContextNewFolder);

//    smallRightPasteAction = new QAction(tr("&Paste to root"), this);
//    smallRightPasteAction->setToolTip("Paste file/folder in current folder");
//    connect(smallRightPasteAction, &QAction::triggered, this, &UnderCommander::rightContextPasteRoot);

//    smallRightInfoAction = new QAction(tr("&Properties"));
//    smallRightInfoAction->setToolTip("Show info about file/folder");
//    connect(smallRightInfoAction, &QAction::triggered, this, &UnderCommander::smallRightContextInfo);

//    smallNewRightMenu->addAction(smallRightNewFileAction);
//    smallNewRightMenu->addAction(smallRightNewFolderAction);
//    smallRightContextMenu->addMenu(smallNewRightMenu);
//    smallRightContextMenu->addAction(smallRightPasteAction);
//    smallRightContextMenu->addAction(smallRightInfoAction);
//}

//void UnderCommander::createTabs()
//{
//    createTabMenuLeft();
//    tabBarLeft = new tabs(ui->comboBoxLeft->currentText());
//    tabBarLeft->setContextMenuPolicy(Qt::CustomContextMenu);
//    connect(leftModel, &QFileSystemModel::rootPathChanged, tabBarLeft, &tabs::changeTabName);
//    connect(tabBarLeft, &tabs::tabBarClicked, this, &UnderCommander::tabBarLeftClick);
//    connect(tabBarLeft, &tabs::customContextMenuRequested, this, &UnderCommander::customTabMenuLeft);
//    ui->verticalLayout->insertWidget(1, tabBarLeft);
//    tabBarLeft->hide();

//    createTabMenuRight();
//    tabBarRight = new tabs(ui->comboBoxRight->currentText());
//    tabBarRight->setContextMenuPolicy(Qt::CustomContextMenu);
//    connect(rightModel, &QFileSystemModel::rootPathChanged, tabBarRight, &tabs::changeTabName);
//    connect(tabBarRight, &tabs::tabBarClicked, this, &UnderCommander::tabBarRightClick);
//    connect(tabBarRight, &tabs::customContextMenuRequested, this, &UnderCommander::customTabMenuRight);
//    ui->verticalLayout_2->insertWidget(1, tabBarRight);
//    tabBarRight->hide();
//}

//void UnderCommander::createTabMenuLeft()
//{
//    leftTabMenu = new QMenu(this);
//    deleteTabLeftAction = new QAction(tr("Delete tab"), this);
//    deleteTabLeftAction->setToolTip("Delete current selected tab");
//    connect(deleteTabLeftAction, &QAction::triggered, this, &UnderCommander::deleteTabLeft);
//    leftTabMenu->addAction(deleteTabLeftAction);
//}

//void UnderCommander::createTabMenuRight()
//{
//    rightTabMenu = new QMenu(this);
//    deleteTabRightAction = new QAction(tr("Delete tab"), this);
//    deleteTabRightAction->setToolTip("Delete current selected tab");
//    connect(deleteTabRightAction, &QAction::triggered, this, &UnderCommander::deleteTabRight);
//    rightTabMenu->addAction(deleteTabRightAction);
//}

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

//void UnderCommander::changeLeftRootPath(const QString &path)
//{
//    clearLeftForwardStack();
//    leftStack.push(leftModel->rootPath());
//    ui->leftView->setRootIndex(leftModel->setRootPath(path));
//    leftCurrent = path;
//    ui->textEditLeft->setText(path);
//    QString comboPath;
//    comboPath.push_back(path.at(0));
//    comboPath.push_back(path.at(1));
//    int index = ui->comboBoxLeft->findText(comboPath);
//    ui->comboBoxLeft->setCurrentIndex(index);
//    if  (leftStack.count() >=1 && !ui->backLeft->isEnabled()){
//        ui->backLeft->setEnabled(true);
//    }
//}

//void UnderCommander::changeRightRootPath(const QString &path)
//{
//    clearRightForwardStack();
//    rightStack.push(rightModel->rootPath());
//    ui->rightView->setRootIndex(rightModel->setRootPath(path));
//    rightCurrent = path;
//    ui->textEditRight->setText(path);
//    QString comboPath;
//    comboPath.push_back(path.at(0));
//    comboPath.push_back(path.at(1));
//    int index = ui->comboBoxRight->findText(comboPath);
//    ui->comboBoxRight->setCurrentIndex(index);
//    if  (rightStack.count() >=1 && !ui->backRight->isEnabled()){
//        ui->backRight->setEnabled(true);
//    }
//}

//void UnderCommander::resetBackForwardLeft()
//{
//    ui->backLeft->setEnabled(false);
//    leftStack.clear();
//    leftStack.push_back(leftModel->rootPath());
//    clearLeftForwardStack();
//}

//void UnderCommander::resetBackForwardRight()
//{
//    ui->backRight->setEnabled(false);
//    rightStack.clear();
//    rightStack.push_back(rightModel->rootPath());
//    clearRightForwardStack();
//}

//void UnderCommander::clearLeftForwardStack(){
//    forwardLeftStack.clear();
//    if (ui->forwardLeft->isEnabled()){
//        ui->forwardLeft->setEnabled(false);
//    }
//    restoredPathFlagLeft = false;
//}

//void UnderCommander::clearRightForwardStack(){
//    forwardRightStack.clear();
//    if  (ui->forwardRight->isEnabled()){
//        ui->forwardRight->setEnabled(false);
//    }
//    restoredPathFlagRight = false;
//}

void UnderCommander::initBackForwardButtons(){
//    ui->backLeft->setEnabled(false);
//    ui->backRight->setEnabled(false);
//    ui->forwardLeft->setEnabled(false);
//    ui->forwardRight->setEnabled(false);
}

//void UnderCommander::saveTextEditsSettings(){
//    textEditLeftFont = ui->textEditLeft->font();
//    //textEditLeftColor = ui->textEditLeft->textColor();
//    textEditRightFont = ui->textEditRight->font();
//    //textEditRightColor = ui->textEditRight->textColor();
//}

void UnderCommander::updateDiskList(){
//    drivesModelLeft->refresh();
//    drivesModelRight->refresh();
}

void UnderCommander::on_leftView_clicked(const QModelIndex &index)
{
//    QFileInfo fileInfo = leftModel->fileInfo(index);
//    if (fileInfo.fileName() != "." && fileInfo.fileName() != ".."){
//        ui->textEditLeft->setText(leftModel->filePath(index));
//    }
//    else ui->textEditLeft->setText(leftCurrent);
    leftController->select(index);
}

void UnderCommander::on_rightView_clicked(const QModelIndex &index)
{
//    QFileInfo fileInfo = rightModel->fileInfo(index);
//    if (fileInfo.fileName() != "." && fileInfo.fileName() != ".."){
//        ui->textEditRight->setText(rightModel->filePath(index));
//    }
//    else ui->textEditRight->setText(rightCurrent);
}

void UnderCommander::on_leftView_doubleClicked(const QModelIndex &index)
{
//    QFileInfo fileInfo = leftModel->fileInfo(index);
//    if (leftStack.count() == stackLimit){
//        leftStack.clear();
//        leftStack.push(ui->comboBoxLeft->currentText()+"/");
//        QMessageBox::information(this, "UnderCommander", "LeftStack limit reached, stack is cleared!");
//    }
//    if  (fileInfo.isDir() && leftStack.count() >=1 && !ui->backLeft->isEnabled()){
//        ui->backLeft->setEnabled(true);
//    }
//    if (fileInfo.fileName() == "."){
//        if (restoredPathFlagLeft){
//            clearLeftForwardStack();
//        }
//        leftStack.push(leftModel->rootPath());
//        ui->leftView->setRootIndex(leftModel->setRootPath(ui->comboBoxLeft->currentText()+"/"));
//        ui->textEditLeft->setText(ui->comboBoxLeft->currentText()+"/");
//        textEditLeftCurrent = ui->textEditLeft->text();
//        leftCurrent = leftModel->rootPath();
//    }
//    else if(fileInfo.fileName()== ".."){
//        if (restoredPathFlagLeft){
//            clearLeftForwardStack();
//        }
//        leftStack.push(leftModel->rootPath());
//        QDir dir = fileInfo.dir();
//        dir.cdUp();
//        ui->leftView->setRootIndex(leftModel->setRootPath(dir.absolutePath()));
//        ui->textEditLeft->setText(leftModel->rootPath());
//        //if user goes to another disk
//        ifUserGoesToAnotherDiskLeft();

//        textEditLeftCurrent = ui->textEditLeft->text();
//        leftCurrent = leftModel->rootPath();
//    }
//    else if(fileInfo.isDir()){
//        if (restoredPathFlagLeft){
//            clearLeftForwardStack();
//        }
//        leftStack.push(leftModel->rootPath());
//        ui->leftView->setRootIndex(leftModel->setRootPath(leftModel->filePath(index)));
//        ui->textEditLeft->setText(leftModel->rootPath());
//        //if user goes to another disk
//        ifUserGoesToAnotherDiskLeft();

//        textEditLeftCurrent = ui->textEditLeft->text();
//        leftCurrent=leftModel->rootPath();
//    }
//    else if(fileInfo.isFile()){
//        QString filePath = leftModel->fileInfo(index).absoluteFilePath();
//        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
//    }
    leftController->open(index);
}

void UnderCommander::on_rightView_doubleClicked(const QModelIndex &index)
{
//    QFileInfo fileInfo = rightModel->fileInfo(index);
//    if (rightStack.count() == stackLimit){
//        rightStack.clear();
//        rightStack.push(ui->comboBoxRight->currentText()+"/");
//        QMessageBox::information(this, "UnderCommander", "RightStack limit reached, stack is cleared!");
//    }
//    if  (fileInfo.isDir() && rightStack.count() >=1 && !ui->backRight->isEnabled()){
//        ui->backRight->setEnabled(true);
//    }
//    if (fileInfo.fileName() == "."){
//        if (restoredPathFlagRight){
//            clearRightForwardStack();
//        }
//        rightStack.push(rightModel->rootPath());
//        ui->rightView->setRootIndex(rightModel->setRootPath(ui->comboBoxRight->currentText()+"/"));
//        ui->textEditRight->setText(ui->comboBoxRight->currentText()+"/");
//        textEditRightCurrent = ui->textEditRight->text();
//        rightCurrent = rightModel->rootPath();
//    }
//    else if(fileInfo.fileName()== ".."){
//        if (restoredPathFlagRight){
//            clearRightForwardStack();
//        }
//        rightStack.push(rightModel->rootPath());
//        QDir dir = fileInfo.dir();
//        dir.cdUp();
//        ui->rightView->setRootIndex(rightModel->setRootPath(dir.absolutePath()));
//        ui->textEditRight->setText(rightModel->rootPath());
//        //if user goes to another disk
//        ifUserGoesToAnotherDiskRight();

//        textEditRightCurrent = ui->textEditRight->text();
//        rightCurrent = rightModel->rootPath();
//    }
//    else if(fileInfo.isDir()){
//        if (restoredPathFlagRight){
//            clearRightForwardStack();
//        }
//        rightStack.push(rightModel->rootPath());
//        ui->rightView->setRootIndex(rightModel->setRootPath(rightModel->filePath(index)));
//        ui->textEditRight->setText(rightModel->rootPath());
//        //if user goes to another disk
//        ifUserGoesToAnotherDiskRight();

//        textEditRightCurrent = ui->textEditRight->text();
//        rightCurrent=rightModel->rootPath();
//    }
//    else if(fileInfo.isFile()){
//        QString filePath = rightModel->fileInfo(index).absoluteFilePath();
//        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
//    }
}

void UnderCommander::on_comboBoxLeft_activated(int index)
{
//    QString path = ui->comboBoxLeft->currentText() + "/";
//    if (path != leftModel->rootPath()){
//        clearLeftForwardStack();
//        leftStack.push(leftModel->rootPath());
//        ui->leftView->setRootIndex(leftModel->setRootPath(path));
//        leftCurrent = path;
//        ui->textEditLeft->setText(path);
//        if  (leftStack.count() >=1 && !ui->backLeft->isEnabled()){
//            ui->backLeft->setEnabled(true);
//        }
//    }
}

void UnderCommander::on_comboBoxRight_activated(int index)
{
//    QString path = ui->comboBoxRight->currentText() + "/";
//    if (path != rightModel->rootPath()){
//        clearRightForwardStack();
//        rightStack.push(rightModel->rootPath());
//        ui->rightView->setRootIndex(rightModel->setRootPath(path));
//        rightCurrent = path;
//        ui->textEditRight->setText(path);
//        if  (rightStack.count() >=1 && !ui->backRight->isEnabled()){
//            ui->backRight->setEnabled(true);
//        }
//    }
}

void UnderCommander::on_pushButtonLeft_clicked()
{
    leftController->go(ui->textEditLeft->text());
//    QString path = ui->textEditLeft->text();
//    QDir dir(path);
//    QFileInfo fileInfo = leftModel->fileInfo(leftModel->index(path));
//    if (dir.exists() &&
//            dir.absolutePath() != leftModel->rootPath() &&
//            fileInfo.fileName() != "."
//            && fileInfo.fileName() != "..")
//    {
//        clearLeftForwardStack();
//        leftStack.push(leftModel->rootPath());
//        ui->leftView->setRootIndex(leftModel->setRootPath(path));
//        leftCurrent = path;
//        ui->textEditLeft->setText(path);
//        QString comboPath;
//        comboPath.push_back(path.at(0));
//        comboPath.push_back(path.at(1));
//        int index = ui->comboBoxLeft->findText(comboPath);
//        ui->comboBoxLeft->setCurrentIndex(index);
//        if  (leftStack.count() >=1 && !ui->backLeft->isEnabled()){
//            ui->backLeft->setEnabled(true);
//        }
//    }
//    else if (leftModel->fileInfo(leftModel->index(path)).isFile()){
//        QDesktopServices::openUrl(QUrl::fromLocalFile(path));
//    }
//    else if (dir.absolutePath() != leftModel->rootPath()){
//        ui->textEditLeft->setText(textEditLeftCurrent);
//        QApplication::beep();
//        QMessageBox::warning(this, "UnderCommander",
//                             "Can't find the path(left panel)."
//                             " Check spelling and try again!");
//    }
}

void UnderCommander::on_textEditLeft_textChanged()
{
   //ui->textEditLeft->setTextColor(textEditLeftColor);
   //ui->textEditLeft->setCurrentFont(textEditLeftFont);
    ui->textEditLeft->clearFocus();
}

void UnderCommander::on_textEditRight_textChanged()
{
    //ui->textEditRight->setTextColor(textEditRightColor);
    //ui->textEditRight->setCurrentFont(textEditRightFont);
    ui->textEditRight->clearFocus();
}

void UnderCommander::on_pushButtonRight_clicked()
{
//    QString path = ui->textEditRight->text();
//    QDir dir(path);
//    QFileInfo fileInfo = rightModel->fileInfo(rightModel->index(path));
//    if (dir.exists() &&
//            dir.absolutePath() != rightModel->rootPath() &&
//            fileInfo.fileName() != "."
//            && fileInfo.fileName() != "..")
//    {
//        clearRightForwardStack();
//        rightStack.push(rightModel->rootPath());
//        ui->rightView->setRootIndex(rightModel->setRootPath(path));
//        rightCurrent = path;
//        ui->textEditRight->setText(path);
//        QString comboPath;
//        comboPath.push_back(path.at(0));
//        comboPath.push_back(path.at(1));
//        int index = ui->comboBoxRight->findText(comboPath);
//        ui->comboBoxRight->setCurrentIndex(index);
//        if  (rightStack.count() >=1 && !ui->backRight->isEnabled()){
//            ui->backRight->setEnabled(true);
//        }
//    }
//    else if (rightModel->fileInfo(rightModel->index(path)).isFile()){
//        QDesktopServices::openUrl(QUrl::fromLocalFile(path));
//    }
//    else if (dir.absolutePath() != rightModel->rootPath()){
//        ui->textEditRight->setText(textEditRightCurrent);
//        QApplication::beep();
//        QMessageBox::warning(this, "UnderCommander",
//                             "Can't find the path(right panel)."
//                             " Check spelling and try again!");
//    }
}

void UnderCommander::on_backLeft_clicked()
{
//    if (!leftStack.isEmpty() && leftStack.count() != 1){
//        QString path = leftStack.pop();
//        if (!QDir(path).exists()){
//            resetBackForwardLeft();
//            QApplication::beep();
//            QMessageBox::warning(this, "UnderCommander", "Previous path does not exist!");
//        }
//        else{
//            restoredPathFlagLeft = true;
//            forwardLeftStack.push(leftModel->rootPath());
//            if (forwardLeftStack.count() > 0 && !ui->forwardLeft->isEnabled()){
//                ui->forwardLeft->setEnabled(true);
//            }
//            ui->leftView->setRootIndex(leftModel->setRootPath(path));
//            ui->textEditLeft->setText(path);
//            //if user goes to another disk
//            ifUserGoesToAnotherDiskLeft();

//            textEditLeftCurrent = ui->textEditLeft->text();
//            leftCurrent=leftModel->rootPath();
//            if (leftStack.count() <= 1){
//                ui->backLeft->setEnabled(false);
//            }
//        }
//    }
    leftController->back();
}

void UnderCommander::on_backRight_clicked()
{
//    if (!rightStack.isEmpty() && rightStack.count() != 1){
//        QString path = rightStack.pop();
//        if (!QDir(path).exists()){
//            resetBackForwardRight();
//            QApplication::beep();
//            QMessageBox::warning(this, "UnderCommander", "Previous path does not exist!");
//        }
//        else{
//            restoredPathFlagRight = true;
//            forwardRightStack.push(rightModel->rootPath());
//            if (forwardRightStack.count() > 0 && !ui->forwardRight->isEnabled()){
//                ui->forwardRight->setEnabled(true);
//            }
//            ui->rightView->setRootIndex(rightModel->setRootPath(path));
//            ui->textEditRight->setText(path);
//            //if user goes to another disk
//            ifUserGoesToAnotherDiskRight();

//            textEditRightCurrent = ui->textEditRight->text();
//            rightCurrent=rightModel->rootPath();
//            if (rightStack.count() <= 1){
//                ui->backRight->setEnabled(false);
//            }
//        }
//    }
}


void UnderCommander::on_forwardLeft_clicked()
{
//    if (!forwardLeftStack.isEmpty()){
//        QString path = forwardLeftStack.pop();
//        if (!QDir(path).exists()){
//            resetBackForwardLeft();
//            QApplication::beep();
//            QMessageBox::warning(this, "UnderCommander", "Path does not exist!");
//        }
//        else{
//            restoredPathFlagLeft = true;
//            if (forwardLeftStack.isEmpty()){
//                ui->forwardLeft->setEnabled(false);
//            }
//            leftStack.push(leftModel->rootPath());
//            ui->leftView->setRootIndex(leftModel->setRootPath(path));
//            ui->textEditLeft->setText(path);
//            //if user goes to another disk
//            ifUserGoesToAnotherDiskLeft();

//            textEditLeftCurrent = ui->textEditRight->text();
//            leftCurrent = leftModel->rootPath();
//            if (leftStack.count() > 1 && !ui->backLeft->isEnabled()){
//                ui->backLeft->setEnabled(true);
//            }
//            ui->textEditLeft->clearFocus();
//            ui->textEditRight->clearFocus();
//        }
//    }
    leftController->forward();
}

void UnderCommander::on_forwardRight_clicked()
{
//    if (!forwardRightStack.isEmpty()){
//        QString path = forwardRightStack.pop();
//        if (!QDir(path).exists()){
//            resetBackForwardRight();
//            QApplication::beep();
//            QMessageBox::warning(this, "UnderCommander", "Path does not exist!");
//        }
//        else{
//            restoredPathFlagRight = true;
//            if (forwardRightStack.isEmpty()){
//                ui->forwardRight->setEnabled(false);
//            }
//            rightStack.push(rightModel->rootPath());
//            ui->rightView->setRootIndex(rightModel->setRootPath(path));
//            ui->textEditRight->setText(path);
//            //if user goes to another disk
//            ifUserGoesToAnotherDiskRight();

//            textEditRightCurrent = ui->textEditRight->text();
//            rightCurrent = rightModel->rootPath();
//            if (rightStack.count() > 1 && !ui->backRight->isEnabled()){
//                ui->backRight->setEnabled(true);
//            }
//            ui->textEditLeft->clearFocus();
//            ui->textEditRight->clearFocus();
//        }
//    }
}

//Left context menu

void UnderCommander::on_customMenuRequestedLeft(QPoint pos)
{
//    QModelIndex index = ui->leftView->indexAt(pos);
//    QFileInfo fileInfo = leftModel->fileInfo(index);
//    if (ui->leftView->selectionModel()->isSelected(index) && fileInfo.fileName() != "." && fileInfo.fileName() != ".."){
//        leftPrintAction->setEnabled(true);
//        if (!fileInfo.isFile()){
//            leftPrintAction->setEnabled(false);
//        }
//        leftCopyAction->setEnabled(false);
//        QModelIndexList list = ui->leftView->selectionModel()->selectedIndexes();
//        bool atLeastOneFile = false;
//        foreach (QModelIndex idx, list){
//            if (leftModel->fileInfo(idx).isFile()){
//                atLeastOneFile = true;
//                break;
//            }
//        }
//        if (atLeastOneFile){
//            leftCopyAction->setEnabled(true);
//        }
//        leftPrintAction->setEnabled(false);
//        if (fileInfo.completeSuffix() == "txt"){
//            leftPrintAction->setEnabled(true);
//        }
//        leftPasteAction->setEnabled(false);
//        if (fileInfo.isDir() && !copyPaths.isEmpty()){
//            leftPasteAction->setEnabled(true);
//        }
//        leftPasteRootAction->setEnabled(false);
//        if (!copyPaths.isEmpty()){
//            leftPasteRootAction->setEnabled(true);
//        }
//        leftContextMenu->popup(ui->leftView->viewport()->mapToGlobal(pos));
//        ui->textEditLeft->setText(leftModel->filePath(index));
//    }
//    else if (fileInfo.fileName() != "." && fileInfo.fileName() != "..")
//    {
//        smallLeftPasteAction->setEnabled(false);
//        if (!copyPaths.isEmpty()){
//            smallLeftPasteAction->setEnabled(true);
//        }
//        smallLeftContextMenu->popup(ui->leftView->viewport()->mapToGlobal(pos));
//    }
}

void UnderCommander::leftContextOpen()
{
//    QModelIndex index = ui->leftView->currentIndex();
//    QFileInfo fileInfo = leftModel->fileInfo(index);
//    if (ui->leftView->selectionModel()->isSelected(index) && fileInfo.isDir())
//    {
//        if (leftStack.count() == stackLimit){
//            leftStack.clear();
//            leftStack.push(ui->comboBoxLeft->currentText()+"/");
//            QMessageBox::information(this, "UnderCommander", "LeftStack limit reached, stack is cleared!");
//        }
//        if  (fileInfo.isDir() && leftStack.count() >=1 && !ui->backLeft->isEnabled()){
//            ui->backLeft->setEnabled(true);
//        }
//        if (restoredPathFlagLeft){
//            clearLeftForwardStack();
//        }
//        leftStack.push(leftModel->rootPath());
//        ui->leftView->setRootIndex(leftModel->setRootPath(leftModel->filePath(index)));
//        ui->textEditLeft->setText(leftModel->rootPath());
//        //if user goes to another disk
//        ifUserGoesToAnotherDiskLeft();

//        textEditLeftCurrent = ui->textEditLeft->text();
//        leftCurrent=leftModel->rootPath();
//    }
//    else if(ui->leftView->selectionModel()->isSelected(index) && fileInfo.isFile()){
//        ui->textEditLeft->setText(leftModel->filePath(index));
//        QString filePath = leftModel->fileInfo(index).absoluteFilePath();
//        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
//    }
}

void UnderCommander::leftContextPrint()
{
//    QFileInfo fileInfo = leftModel->fileInfo(ui->leftView->currentIndex());
//    QProcess *printProcess = new QProcess(this);
//    QStringList arguments;
//    arguments << "/p" << fileInfo.absoluteFilePath();
//    printProcess->start("C:\\Windows\\notepad.exe", arguments);
}

void UnderCommander::leftContextNewFile()
{
//    QModelIndex index = ui->leftView->currentIndex();
//    QFileInfo fileInfo = leftModel->fileInfo(index);
//    newfile window;
//    window.setModal(true);
//    window.setWindowFlags(window.windowFlags() & ~Qt::WindowContextHelpButtonHint);
//    window.exec();
//    if (window.isAccepted()){
//        if (fileInfo.isFile()){
//            newFileName = leftModel->rootPath() + "/" + window.getFileName();
//            if (QFile::exists(newFileName)){
//                QApplication::beep();
//                QMessageBox::warning(this, "UnderCommander", "File already exists!");
//            }
//            else {
//                QFile file(newFileName);
//                if (file.open(QIODevice::WriteOnly)){
//                    //ui->textEdit->setText("Succesfully: " + file.fileName());
//                    file.close();
//                }
//                else{
//                    QApplication::beep();
//                    QMessageBox::warning(this, "UnderCommander", "File was not created. Probably you don't have permission?");
//                    //ui->textEdit->setText("File was not created");
//                }
//            }
//        }
//        else if(fileInfo.isDir()){
//            newFileName = leftModel->filePath(index) + "/" + window.getFileName();
//            if (QFile::exists(newFileName)){
//                QApplication::beep();
//                QMessageBox::warning(this, "UnderCommander", "File already exists!");
//            }
//            else {
//                QFile file(newFileName);
//                if (file.open(QIODevice::WriteOnly)){
//                    //ui->textEdit->setText("Succesfully: " + file.fileName());
//                    file.close();
//                }
//                else{
//                    QApplication::beep();
//                    QMessageBox::warning(this, "UnderCommander", "File was not created. Probably you don't have permission?");
//                    //ui->textEdit->setText("File was not created");
//                }
//            }
//        }
//    }
    //else ui->textEdit->setText("Not accepted");
}

void UnderCommander::leftContextNewFolder()
{
//    QModelIndex index = ui->leftView->currentIndex();
//    QFileInfo fileInfo = leftModel->fileInfo(index);
//    newfolder window;
//    window.setModal(true);
//    window.setWindowFlags(window.windowFlags() & ~Qt::WindowContextHelpButtonHint);
//    window.exec();
//    if (window.isAccepted()){
//        if (fileInfo.isFile()){
//            newFolderName = window.getPathName();
//            if (QDir(leftModel->rootPath() + "/" + newFolderName).exists()){
//                QApplication::beep();
//                QMessageBox::warning(this, "UnderCommander", "Folder already exists!");
//            }
//            else{
//                QDir currentDir(leftModel->rootPath());
//                //ui->textEdit->setText(currentDir.absolutePath());
//                if (currentDir.mkdir(newFolderName)){
//                    //ui->textEdit->setText(currentDir.absolutePath() +"/" + newFolderName);
//                }
//                else{
//                    QApplication::beep();
//                    QMessageBox::warning(this, "UnderCommander", "Folder was not created. Probably you don't have permission?");
//                    //ui->textEdit->setText("Folder was not created");
//                }
//            }
//        }
//        else if(fileInfo.isDir()){
//            newFolderName = window.getPathName();
//            if (QDir(leftModel->filePath(index) + "/" + newFolderName).exists()){
//                QApplication::beep();
//                QMessageBox::warning(this, "UnderCommander", "Folder already exists!");
//            }
//            else{
//                QDir currentDir(leftModel->filePath(index));
//                //ui->textEdit->setText(currentDir.absolutePath());
//                if (currentDir.mkdir(newFolderName)){
//                    //ui->textEdit->setText(currentDir.absolutePath() +"/" + newFolderName);
//                }
//                else{
//                    QApplication::beep();
//                    QMessageBox::warning(this, "UnderCommander", "Folder was not created. Probably you don't have permission?");
//                    //ui->textEdit->setText("Folder was not created");
//                }
//            }
//        }
//    }
}

void UnderCommander::leftContextCut()
{
//    contextCutFlag = true;
//    copyPaths.clear();
//    QModelIndexList list = ui->leftView->selectionModel()->selectedRows();
//    foreach (QModelIndex idx, list){
//        copyPaths.push_back(leftModel->fileInfo(idx).absoluteFilePath());
//    }
//    qDebug() << copyPaths;
}

void UnderCommander::leftContextCopy()
{
    //leftCopy();
}

void UnderCommander::leftContextCopyFolderFiles()
{
//    contextCutFlag = false;
//    copyPaths.clear();
//    QModelIndexList list = ui->leftView->selectionModel()->selectedRows();
//    foreach (QModelIndex idx, list){
//        copyPaths.push_back(leftModel->fileInfo(idx).absoluteFilePath());
//    }
//    qDebug() << copyPaths;
}

void UnderCommander::leftContextPaste()
{
//    QModelIndex index = ui->leftView->currentIndex();
//    QString dest = leftModel->fileInfo(index).absoluteFilePath();
//    copy_options options = askForCopyOptions();
//    foreach (QString item, copyPaths){
//        if (exists(item.toStdString())){
//            CopyingStatusWindow *window = new CopyingStatusWindow(item, dest, contextCutFlag);
//            window->setOptions(options);
//            window->setSkip(true);
//            window->setModal(true);
//            window->setAttribute(Qt::WA_DeleteOnClose);
//            window->exec();
//        }
//    }
}

void UnderCommander::leftContextPasteRoot()
{
//    QModelIndex index = ui->leftView->rootIndex();
//    QString dest = leftModel->fileInfo(index).absoluteFilePath();
//    copy_options options = askForCopyOptions();
//    foreach (QString item, copyPaths){
//        if (exists(item.toStdString())){
//            CopyingStatusWindow *window = new CopyingStatusWindow(item, dest, contextCutFlag);
//            window->setOptions(options);
//            window->setSkip(true);
//            window->setModal(true);
//            window->setAttribute(Qt::WA_DeleteOnClose);
//            window->exec();
//        }
//    }
}

void UnderCommander::leftContextDelete() //to do
{
//    //QModelIndexList list = ui->leftView->selectionModel()->selectedIndexes();
//    QModelIndexList list = ui->leftView->selectionModel()->selectedRows();
//    if (list.count() > 1){
//        QFileInfo fileInfo;
//        foreach (const QModelIndex &index, list){
//            fileInfo = leftModel->fileInfo(index);
//            if (fileInfo.isDir()){
//                QMessageBox::StandardButton reply;
//                QString questionString = "Are you sure you want to delete this folder(" + fileInfo.fileName() +")?";
//                reply = QMessageBox::question(this, "Delete folder", questionString, QMessageBox::Yes | QMessageBox::YesToAll | QMessageBox::No);
//                if (reply == QMessageBox::YesToAll){
//                    //ui->textEdit->setText("All items has been deleted");
//                    list = ui->leftView->selectionModel()->selectedIndexes();
//                    foreach (const QModelIndex &deleteIndex2, list){
//                        fileInfo = leftModel->fileInfo(deleteIndex2);
//                        //ui->textEdit->setText(ui->textEdit->toPlainText() + " " +QString::number(deleteIndex.row()));
//                        if (fileInfo.isDir()){
//                            QDir dir(fileInfo.absoluteFilePath());
//                            if(dir.exists()){
//                                if (dir.removeRecursively()){
//                                    //ui->textEdit->setText("folder deleted");
//                                }
//                                else{
//                                    QApplication::beep();
//                                    QString messageString = "Folder(" + fileInfo.fileName() + ") was not deleted. Probably you don't have permission or folder is open in another program.";
//                                    QMessageBox::warning(this, "UnderCommander", messageString);
//                                }
//                            }
//                        }
//                        else if(fileInfo.isFile()){
//                            if (exists(fileInfo.absoluteFilePath().toStdString())){
//                                if (QFile::remove(fileInfo.absoluteFilePath())){
//                                    //ui->textEdit->setText("file deleted");
//                                }
//                                else{
//                                    QApplication::beep();
//                                    QString messageString = "File(" + fileInfo.fileName() + ") was not deleted. Probably you don't have permission or file is open in another program.";
//                                    QMessageBox::warning(this, "UnderCommander", messageString);
//                                }
//                            }
//                        }
//                    }
//                    ui->textEditLeft->setText(leftModel->rootPath());
//                    break;
//                }
//                if (reply == QMessageBox::Yes){
//                    QDir dir(fileInfo.absoluteFilePath());
//                    if (dir.exists()){
//                        if (dir.removeRecursively()){
//                            //ui->textEdit->setText("folder deleted");
//                            ui->textEditLeft->setText(leftModel->rootPath());
//                        }
//                        else{
//                            QApplication::beep();
//                            QString messageString = "Folder(" + fileInfo.fileName() + ") was not deleted. Probably you don't have permission or folder is open in another program.";
//                            QMessageBox::warning(this, "UnderCommander", messageString);
//                        }
//                    }
//                }
//            }
//            else if (fileInfo.isFile()){
//                QMessageBox::StandardButton reply;
//                QString questionString = "Are you sure you want to delete this file(" + fileInfo.fileName() +")?";
//                reply = QMessageBox::question(this, "Delete file", questionString, QMessageBox::Yes | QMessageBox::YesToAll | QMessageBox::No);
//                if (reply == QMessageBox::YesToAll){
//                    list = ui->leftView->selectionModel()->selectedIndexes();
//                    //ui->textEdit->setText("All items has been deleted");
//                    foreach (const QModelIndex &deleteIndex1, list){
//                        fileInfo = leftModel->fileInfo(deleteIndex1);
//                        if(fileInfo.isDir()){
//                            QDir dir(fileInfo.absoluteFilePath());
//                            if (dir.exists()){
//                                if (dir.removeRecursively()){
//                                    //ui->textEdit->setText("folder deleted");
//                                }
//                                else{
//                                    QApplication::beep();
//                                    QString messageString = "Folder(" + fileInfo.fileName() + ") was not deleted. Probably you don't have permission or folder is open in another program.";
//                                    QMessageBox::warning(this, "UnderCommander", messageString);
//                                }
//                            }
//                        }
//                        else if (fileInfo.isFile()){
//                            if (exists(fileInfo.absoluteFilePath().toStdString())){
//                                if (QFile::remove(fileInfo.absoluteFilePath())){
//                                    //ui->textEdit->setText("file deleted");
//                                }
//                                else{
//                                    QApplication::beep();
//                                    QString messageString = "File(" + fileInfo.fileName() + ") was not deleted. Probably you don't have permission or file is open in another program.";
//                                    QMessageBox::warning(this, "UnderCommander", messageString);
//                                }
//                            }
//                        }
//                    }
//                    ui->textEditLeft->setText(leftModel->rootPath());
//                    break;
//                }
//                if (reply == QMessageBox::Yes){
//                    if (exists(fileInfo.absoluteFilePath().toStdString())){
//                        if (QFile::remove(fileInfo.absoluteFilePath())){
//                            //ui->textEdit->setText("file deleted");
//                            ui->textEditLeft->setText(leftModel->rootPath());
//                        }
//                        else{
//                            QApplication::beep();
//                            QString messageString = "File(" + fileInfo.fileName() + ") was not deleted. Probably you don't have permission or file is open in another program.";
//                            QMessageBox::warning(this, "UnderCommander", messageString);
//                        }
//                    }
//                }
//            }
//        }
//    }
//    else if (list.count() == 1){
//        QModelIndex index = ui->leftView->currentIndex();
//        QFileInfo fileInfo = leftModel->fileInfo(index);
//        if (fileInfo.isDir()){
//            QMessageBox::StandardButton reply;
//            QString questionString = "Are you sure you want to delete this folder(" + fileInfo.fileName() +")?";
//            reply = QMessageBox::question(this, "Delete folder", questionString, QMessageBox::Yes | QMessageBox::No);
//            if (reply == QMessageBox::Yes){
//                QDir dir(fileInfo.absoluteFilePath());
//                if (dir.exists()){
//                    if (dir.removeRecursively()){
//                        //ui->textEdit->setText("folder deleted");
//                        ui->textEditLeft->setText(leftModel->rootPath());
//                    }
//                    else{
//                        QApplication::beep();
//                        QString messageString = "Folder(" + fileInfo.fileName() + ") was not deleted. Probably you don't have permission or folder is open in another program.";
//                        QMessageBox::warning(this, "UnderCommander", messageString);
//                    }
//                }
//            }
//        }
//        else if (fileInfo.isFile()){
//            QMessageBox::StandardButton reply;
//            QString questionString = "Are you sure you want to delete this file(" + fileInfo.fileName() +")?";
//            reply = QMessageBox::question(this, "Delete file", questionString, QMessageBox::Yes | QMessageBox::No);
//            if (reply == QMessageBox::Yes){
//                if (exists(fileInfo.absoluteFilePath().toStdString())){
//                    if (QFile::remove(fileInfo.absoluteFilePath())){
//                        //ui->textEdit->setText("file deleted");
//                        ui->textEditLeft->setText(leftModel->rootPath());
//                    }
//                    else{
//                        QApplication::beep();
//                        QString messageString = "File(" + fileInfo.fileName() + ") was not deleted. Probably you don't have permission or file is open in another program.";
//                        QMessageBox::warning(this, "UnderCommander", messageString);
//                    }
//                }
//            }
//        }
//    }
}

void UnderCommander::leftContextRename()
{
//    QModelIndex index = ui->leftView->currentIndex();
//    ui->leftView->edit(index);
//    ui->textEditLeft->setText(leftModel->rootPath());
}

void UnderCommander::leftContextInfo()
{
    //displayLeft(ui->leftView->currentIndex());
}

void UnderCommander::smallLeftContextNewFile()
{
//    QModelIndex index = ui->leftView->rootIndex();
//    newfile window;
//    window.setModal(true);
//    window.setWindowFlags(window.windowFlags() & ~Qt::WindowContextHelpButtonHint);
//    window.exec();
//    if (window.isAccepted()){
//        newFileName = leftModel->filePath(index) + "/" + window.getFileName();
//        if (QFile::exists(newFileName)){
//            QApplication::beep();
//            QMessageBox::warning(this, "UnderCommander", "File already exists!");
//        }
//        else {
//            QFile file(newFileName);
//            if (file.open(QIODevice::WriteOnly)){
//                //ui->textEdit->setText("Succesfully: " + file.fileName());
//                file.close();
//            }
//            else{
//                QApplication::beep();
//                QMessageBox::warning(this, "UnderCommander", "File was not created. Probably you don't have permission?");
//                //ui->textEdit->setText("File was not created");
//            }
//        }
//    }
}

void UnderCommander::smallLeftContextNewFolder()
{
//    //QModelIndex index = ui->leftView->rootIndex();
//    newfolder window;
//    window.setModal(true);
//    window.setWindowFlags(window.windowFlags() & ~Qt::WindowContextHelpButtonHint);
//    window.exec();
//    if (window.isAccepted()){
//        newFolderName = window.getPathName();
//        if (QDir(leftModel->rootPath() + "/" + newFolderName).exists()){
//            QApplication::beep();
//            QMessageBox::warning(this, "UnderCommander", "Folder already exists!");
//        }
//        else{
//            QDir currentDir(leftModel->rootPath());
//            //ui->textEdit->setText(currentDir.absolutePath());
//            if (currentDir.mkdir(newFolderName)){
//                //ui->textEdit->setText(currentDir.absolutePath() +"/" + newFolderName);
//            }
//            else{
//                QApplication::beep();
//                QMessageBox::warning(this, "UnderCommander", "Folder was not created. Probably you don't have permission?");
//                //ui->textEdit->setText("Folder was not created");
//            }
//        }
//    }
}

void UnderCommander::smallLeftContextInfo()
{
    //displayLeft(ui->leftView->rootIndex());
}

//Right context menu

void UnderCommander::on_customMenuRequestedRight(QPoint pos)
{
//    QModelIndex index = ui->rightView->indexAt(pos);
//    QFileInfo fileInfo = rightModel->fileInfo(index);
//    if (ui->rightView->selectionModel()->isSelected(index) && fileInfo.fileName() != "." && fileInfo.fileName() != ".."){
//        rightPrintAction->setEnabled(true);
//        if (!fileInfo.isFile()){
//            rightPrintAction->setEnabled(false);
//        }
//        rightCopyAction->setEnabled(false);
//        QModelIndexList list = ui->rightView->selectionModel()->selectedIndexes();
//        bool atLeastOneFile = false;
//        foreach (QModelIndex idx, list){
//            if (rightModel->fileInfo(idx).isFile()){
//                atLeastOneFile = true;
//                break;
//            }
//        }
//        if (atLeastOneFile){
//            rightCopyAction->setEnabled(true);
//        }
//        rightPrintAction->setEnabled(false);
//        if (fileInfo.completeSuffix() == "txt"){
//            rightPrintAction->setEnabled(true);
//        }
//        rightPasteAction->setEnabled(false);
//        if (fileInfo.isDir() && !copyPaths.isEmpty()){
//            rightPasteAction->setEnabled(true);
//        }
//        rightPasteRootAction->setEnabled(false);
//        if (!copyPaths.isEmpty()){
//            rightPasteRootAction->setEnabled(true);
//        }
//        rightContextMenu->popup(ui->rightView->viewport()->mapToGlobal(pos));
//        ui->textEditRight->setText(rightModel->filePath(index));
//    }
//    else if (fileInfo.fileName() != "." && fileInfo.fileName() != "..")
//    {
//        smallRightPasteAction->setEnabled(false);
//        if (!copyPaths.isEmpty()){
//            smallRightPasteAction->setEnabled(true);
//        }
//        smallRightContextMenu->popup(ui->rightView->viewport()->mapToGlobal(pos));
//    }
}

void UnderCommander::rightContextOpen()
{
//    QModelIndex index = ui->rightView->currentIndex();
//    QFileInfo fileInfo = rightModel->fileInfo(index);
//    if (ui->rightView->selectionModel()->isSelected(index) && fileInfo.isDir())
//    {
//        if (rightStack.count() == stackLimit){
//            rightStack.clear();
//            rightStack.push(ui->comboBoxRight->currentText()+"/");
//            QMessageBox::information(this, "UnderCommander", "RightStack limit reached, stack is cleared!");
//        }
//        if  (fileInfo.isDir() && rightStack.count() >=1 && !ui->backRight->isEnabled()){
//            ui->backRight->setEnabled(true);
//        }
//        if (restoredPathFlagRight){
//            clearRightForwardStack();
//        }
//        rightStack.push(rightModel->rootPath());
//        ui->rightView->setRootIndex(rightModel->setRootPath(rightModel->filePath(index)));
//        ui->textEditRight->setText(rightModel->rootPath());
//        //if user goes to another disk
//        ifUserGoesToAnotherDiskRight();

//        textEditRightCurrent = ui->textEditRight->text();
//        rightCurrent=rightModel->rootPath();
//    }
//    else if(ui->rightView->selectionModel()->isSelected(index) && fileInfo.isFile()){
//        ui->textEditRight->setText(rightModel->filePath(index));
//        QString filePath = rightModel->fileInfo(index).absoluteFilePath();
//        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
//    }
}

void UnderCommander::rightContextPrint()
{
//    QFileInfo fileInfo = rightModel->fileInfo(ui->rightView->currentIndex());
//    QProcess *printProcess = new QProcess(this);
//    QStringList arguments;
//    arguments << "/p" << fileInfo.absoluteFilePath();
//    printProcess->start("C:\\Windows\\notepad.exe", arguments);
}

void UnderCommander::rightContextNewFile()
{
//    QModelIndex index = ui->rightView->currentIndex();
//    QFileInfo fileInfo = rightModel->fileInfo(index);
//    newfile window;
//    window.setModal(true);
//    window.setWindowFlags(window.windowFlags() & ~Qt::WindowContextHelpButtonHint);
//    window.exec();
//    if (window.isAccepted()){
//        if (fileInfo.isFile()){
//            newFileName = rightModel->rootPath() + "/" + window.getFileName();
//            if (QFile::exists(newFileName)){
//                QApplication::beep();
//                QMessageBox::warning(this, "UnderCommander", "File already exists!");
//            }
//            else {
//                QFile file(newFileName);
//                if (file.open(QIODevice::WriteOnly)){
//                    //ui->textEdit->setText("Succesfully: " + file.fileName());
//                    file.close();
//                }
//                else{
//                    QApplication::beep();
//                    QMessageBox::warning(this, "UnderCommander", "File was not created. Probably you don't have permission?");
//                    //ui->textEdit->setText("File was not created");
//                }
//            }
//        }
//        else if(fileInfo.isDir()){
//            newFileName = rightModel->filePath(index) + "/" + window.getFileName();
//            if (QFile::exists(newFileName)){
//                QApplication::beep();
//                QMessageBox::warning(this, "UnderCommander", "File already exists!");
//            }
//            else {
//                QFile file(newFileName);
//                if (file.open(QIODevice::WriteOnly)){
//                    //ui->textEdit->setText("Succesfully: " + file.fileName());
//                    file.close();
//                }
//                else{
//                    QApplication::beep();
//                    QMessageBox::warning(this, "UnderCommander", "File was not created. Probably you don't have permission?");
//                    //ui->textEdit->setText("File was not created");
//                }
//            }
//        }
//    }
//    //else ui->textEdit->setText("Not accepted");
}

void UnderCommander::rightContextNewFolder()
{
//    QModelIndex index = ui->rightView->currentIndex();
//    QFileInfo fileInfo = rightModel->fileInfo(index);
//    newfolder window;
//    window.setModal(true);
//    window.setWindowFlags(window.windowFlags() & ~Qt::WindowContextHelpButtonHint);
//    window.exec();
//    if (window.isAccepted()){
//        if (fileInfo.isFile()){
//            newFolderName = window.getPathName();
//            if (QDir(rightModel->rootPath() + "/" + newFolderName).exists()){
//                QApplication::beep();
//                QMessageBox::warning(this, "UnderCommander", "Folder already exists!");
//            }
//            else{
//                QDir currentDir(rightModel->rootPath());
//                //ui->textEdit->setText(currentDir.absolutePath());
//                if (currentDir.mkdir(newFolderName)){
//                    //ui->textEdit->setText(currentDir.absolutePath() +"/" + newFolderName);
//                }
//                else{
//                    QApplication::beep();
//                    QMessageBox::warning(this, "UnderCommander", "Folder was not created. Probably you don't have permission?");
//                    //ui->textEdit->setText("Folder was not created");
//                }
//            }
//        }
//        else if(fileInfo.isDir()){
//            newFolderName = window.getPathName();
//            if (QDir(rightModel->filePath(index) + "/" + newFolderName).exists()){
//                QApplication::beep();
//                QMessageBox::warning(this, "UnderCommander", "Folder already exists!");
//            }
//            else{
//                QDir currentDir(rightModel->filePath(index));
//                //ui->textEdit->setText(currentDir.absolutePath());
//                if (currentDir.mkdir(newFolderName)){
//                    //ui->textEdit->setText(currentDir.absolutePath() +"/" + newFolderName);
//                }
//                else{
//                    QApplication::beep();
//                    QMessageBox::warning(this, "UnderCommander", "Folder was not created. Probably you don't have permission?");
//                    //ui->textEdit->setText("Folder was not created");
//                }
//            }
//        }
//    }
}

void UnderCommander::rightContextCut()
{
//    contextCutFlag = true;
//    copyPaths.clear();
//    QModelIndexList list = ui->rightView->selectionModel()->selectedRows();
//    foreach (QModelIndex idx, list){
//        copyPaths.push_back(rightModel->fileInfo(idx).absoluteFilePath());
//    }
//    qDebug() << copyPaths;
}

void UnderCommander::rightContextCopy()
{
    //rightCopy();
}

void UnderCommander::rightContextCopyFolderFiles()
{
//    contextCutFlag = false;
//    copyPaths.clear();
//    QModelIndexList list = ui->rightView->selectionModel()->selectedRows();
//    foreach (QModelIndex idx, list){
//        copyPaths.push_back(rightModel->fileInfo(idx).absoluteFilePath());
//    }
//    qDebug() << copyPaths;
}

void UnderCommander::rightContextPaste()
{
//    QModelIndex index = ui->rightView->currentIndex();
//    QString dest = rightModel->fileInfo(index).absoluteFilePath();
//    copy_options options = askForCopyOptions();
//    foreach (QString item, copyPaths){
//        if (exists(item.toStdString())){
//            CopyingStatusWindow *window = new CopyingStatusWindow(item, dest, contextCutFlag);
//            window->setOptions(options);
//            window->setSkip(true);
//            window->setModal(true);
//            window->setAttribute(Qt::WA_DeleteOnClose);
//            window->exec();
//        }
//    }
}

void UnderCommander::rightContextPasteRoot()
{
//    QModelIndex index = ui->rightView->rootIndex();
//    QString dest = rightModel->fileInfo(index).absoluteFilePath();
//    copy_options options = askForCopyOptions();
//    foreach (QString item, copyPaths){
//        if (exists(item.toStdString())){
//            CopyingStatusWindow *window = new CopyingStatusWindow(item, dest, contextCutFlag);
//            window->setOptions(options);
//            window->setSkip(true);
//            window->setModal(true);
//            window->setAttribute(Qt::WA_DeleteOnClose);
//            window->exec();
//        }
//    }
}

void UnderCommander::rightContextDelete()
{
//    QModelIndexList list = ui->rightView->selectionModel()->selectedIndexes();
//    if (list.count() > 1){
//        QFileInfo fileInfo;
//        foreach (const QModelIndex &index, list){
//            fileInfo = rightModel->fileInfo(index);
//            if (fileInfo.isDir()){
//                QMessageBox::StandardButton reply;
//                QString questionString = "Are you sure you want to delete this folder(" + fileInfo.fileName() +")?";
//                reply = QMessageBox::question(this, "Delete folder", questionString, QMessageBox::Yes | QMessageBox::YesToAll | QMessageBox::No);
//                if (reply == QMessageBox::YesToAll){
//                    //ui->textEdit->setText("All items has been deleted");
//                    list = ui->rightView->selectionModel()->selectedIndexes();
//                    foreach (const QModelIndex &deleteIndex2, list){
//                        fileInfo = rightModel->fileInfo(deleteIndex2);
//                        //ui->textEdit->setText(ui->textEdit->toPlainText() + " " +QString::number(deleteIndex.row()));
//                        if (fileInfo.isDir()){
//                            QDir dir(fileInfo.absoluteFilePath());
//                            if(dir.exists()){
//                                if (dir.removeRecursively()){
//                                    //ui->textEdit->setText("folder deleted");
//                                }
//                                else{
//                                    QApplication::beep();
//                                    QString messageString = "Folder(" + fileInfo.fileName() + ") was not deleted. Probably you don't have permission or folder is open in another program.";
//                                    QMessageBox::warning(this, "UnderCommander", messageString);
//                                }
//                            }
//                        }
//                        else if(fileInfo.isFile()){
//                            if (exists(fileInfo.absoluteFilePath().toStdString())){
//                                if (QFile::remove(fileInfo.absoluteFilePath())){
//                                    //ui->textEdit->setText("file deleted");
//                                }
//                                else{
//                                    QApplication::beep();
//                                    QString messageString = "File(" + fileInfo.fileName() + ") was not deleted. Probably you don't have permission or file is open in another program.";
//                                    QMessageBox::warning(this, "UnderCommander", messageString);
//                                }
//                            }
//                        }
//                    }
//                    ui->textEditRight->setText(rightModel->rootPath());
//                    break;
//                }
//                if (reply == QMessageBox::Yes){
//                    QDir dir(fileInfo.absoluteFilePath());
//                    if (dir.exists()){
//                        if (dir.removeRecursively()){
//                            //ui->textEdit->setText("folder deleted");
//                            ui->textEditRight->setText(rightModel->rootPath());
//                        }
//                        else{
//                            QApplication::beep();
//                            QString messageString = "Folder(" + fileInfo.fileName() + ") was not deleted. Probably you don't have permission or folder is open in another program.";
//                            QMessageBox::warning(this, "UnderCommander", messageString);
//                        }
//                    }
//                }
//            }
//            else if (fileInfo.isFile()){
//                QMessageBox::StandardButton reply;
//                QString questionString = "Are you sure you want to delete this file(" + fileInfo.fileName() +")?";
//                reply = QMessageBox::question(this, "Delete file", questionString, QMessageBox::Yes | QMessageBox::YesToAll | QMessageBox::No);
//                if (reply == QMessageBox::YesToAll){
//                    list = ui->rightView->selectionModel()->selectedIndexes();
//                    //ui->textEdit->setText("All items has been deleted");
//                    foreach (const QModelIndex &deleteIndex1, list){
//                        fileInfo = rightModel->fileInfo(deleteIndex1);
//                        if(fileInfo.isDir()){
//                            QDir dir(fileInfo.absoluteFilePath());
//                            if (dir.exists()){
//                                if (dir.removeRecursively()){
//                                    //ui->textEdit->setText("folder deleted");
//                                }
//                                else{
//                                    QApplication::beep();
//                                    QString messageString = "Folder(" + fileInfo.fileName() + ") was not deleted. Probably you don't have permission or folder is open in another program.";
//                                    QMessageBox::warning(this, "UnderCommander", messageString);
//                                }
//                            }
//                        }
//                        else if (fileInfo.isFile()){
//                            if (exists(fileInfo.absoluteFilePath().toStdString())){
//                                if (QFile::remove(fileInfo.absoluteFilePath())){
//                                    //ui->textEdit->setText("file deleted");
//                                }
//                                else{
//                                    QApplication::beep();
//                                    QString messageString = "File(" + fileInfo.fileName() + ") was not deleted. Probably you don't have permission or file is open in another program.";
//                                    QMessageBox::warning(this, "UnderCommander", messageString);
//                                }
//                            }
//                        }
//                    }
//                    ui->textEditRight->setText(rightModel->rootPath());
//                    break;
//                }
//                if (reply == QMessageBox::Yes){
//                    if (exists(fileInfo.absoluteFilePath().toStdString())){
//                        if (QFile::remove(fileInfo.absoluteFilePath())){
//                            //ui->textEdit->setText("file deleted");
//                            ui->textEditRight->setText(rightModel->rootPath());
//                        }
//                        else{
//                            QApplication::beep();
//                            QString messageString = "File(" + fileInfo.fileName() + ") was not deleted. Probably you don't have permission or file is open in another program.";
//                            QMessageBox::warning(this, "UnderCommander", messageString);
//                        }
//                    }
//                }
//            }
//        }
//    }
//    else if (list.count() == 1){
//        QModelIndex index = ui->rightView->currentIndex();
//        QFileInfo fileInfo = rightModel->fileInfo(index);
//        if (fileInfo.isDir()){
//            QMessageBox::StandardButton reply;
//            QString questionString = "Are you sure you want to delete this folder(" + fileInfo.fileName() +")?";
//            reply = QMessageBox::question(this, "Delete folder", questionString, QMessageBox::Yes | QMessageBox::No);
//            if (reply == QMessageBox::Yes){
//                QDir dir(fileInfo.absoluteFilePath());
//                if (dir.exists()){
//                    if (dir.removeRecursively()){
//                        //ui->textEdit->setText("folder deleted");
//                        ui->textEditRight->setText(rightModel->rootPath());
//                    }
//                    else{
//                        QApplication::beep();
//                        QString messageString = "Folder(" + fileInfo.fileName() + ") was not deleted. Probably you don't have permission or folder is open in another program.";
//                        QMessageBox::warning(this, "UnderCommander", messageString);
//                    }
//                }
//            }
//        }
//        else if (fileInfo.isFile()){
//            QMessageBox::StandardButton reply;
//            QString questionString = "Are you sure you want to delete this file(" + fileInfo.fileName() +")?";
//            reply = QMessageBox::question(this, "Delete file", questionString, QMessageBox::Yes | QMessageBox::No);
//            if (reply == QMessageBox::Yes){
//                if (exists(fileInfo.absoluteFilePath().toStdString())){
//                    if (QFile::remove(fileInfo.absoluteFilePath())){
//                        //ui->textEdit->setText("file deleted");
//                        ui->textEditRight->setText(rightModel->rootPath());
//                    }
//                    else{
//                        QApplication::beep();
//                        QString messageString = "File(" + fileInfo.fileName() + ") was not deleted. Probably you don't have permission or file is open in another program.";
//                        QMessageBox::warning(this, "UnderCommander", messageString);
//                    }
//                }
//            }
//        }
//    }
}

void UnderCommander::rightContextRename()
{
//    QModelIndex index = ui->rightView->currentIndex();
//    ui->rightView->edit(index);
//    ui->textEditRight->setText(rightModel->rootPath());
}

void UnderCommander::rightContextInfo()
{
    //displayRight(ui->rightView->currentIndex());
}

void UnderCommander::smallRightContextNewFile()
{
//    QModelIndex index = ui->rightView->rootIndex();
//    newfile window;
//    window.setModal(true);
//    window.setWindowFlags(window.windowFlags() & ~Qt::WindowContextHelpButtonHint);
//    window.exec();
//    if (window.isAccepted()){
//        newFileName = rightModel->filePath(index) + "/" + window.getFileName();
//        if (QFile::exists(newFileName)){
//            QApplication::beep();
//            QMessageBox::warning(this, "UnderCommander", "File already exists!");
//        }
//        else {
//            QFile file(newFileName);
//            if (file.open(QIODevice::WriteOnly)){
//                //ui->textEdit->setText("Succesfully: " + file.fileName());
//                file.close();
//            }
//            else{
//                QApplication::beep();
//                QMessageBox::warning(this, "UnderCommander", "File was not created. Probably you don't have permission?");
//                //ui->textEdit->setText("File was not created");
//            }
//        }
//    }
}

void UnderCommander::smallRightContextNewFolder()
{
//    //QModelIndex index = ui->rightView->rootIndex();
//    newfolder window;
//    window.setModal(true);
//    window.setWindowFlags(window.windowFlags() & ~Qt::WindowContextHelpButtonHint);
//    window.exec();
//    if (window.isAccepted()){
//        newFolderName = window.getPathName();
//        if (QDir(rightModel->rootPath() + "/" + newFolderName).exists()){
//            QApplication::beep();
//            QMessageBox::warning(this, "UnderCommander", "Folder already exists!");
//        }
//        else{
//            QDir currentDir(rightModel->rootPath());
//            //ui->textEdit->setText(currentDir.absolutePath());
//            if (currentDir.mkdir(newFolderName)){
//                //ui->textEdit->setText(currentDir.absolutePath() +"/" + newFolderName);
//            }
//            else{
//                QApplication::beep();
//                QMessageBox::warning(this, "UnderCommander", "Folder was not created. Probably you don't have permission?");
//                //ui->textEdit->setText("Folder was not created");
//            }
//        }
//    }
}

void UnderCommander::smallRightContextInfo()
{
    //displayRight(ui->rightView->rootIndex());
}

void UnderCommander::deleteInfoPath(const QString path)
{
    //infoPath.removeAt(infoPath.indexOf(path));
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
    ui->leftView->selectionModel()->reset();
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
    //tabBarLeft->createTab(ui->comboBoxLeft->currentText() + "/");
}

void UnderCommander::on_actionNew_right_tab_triggered()
{
    //tabBarRight->createTab(ui->comboBoxRight->currentText() + "/");
}

void UnderCommander::tabBarLeftClick(int index)
{
//    if (index >= 0){
//        //qDebug() << index;
//        tabBarLeft->setCurrentIndex(index);
//        tabBarLeft->setCurrentTab(index);
//        QString path = tabBarLeft->savedPath(index);
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
//        //qDebug() << path;
//    }
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
        //tabBarLeft->show();
        //tabBarRight->show();
    }
    else{
        //tabBarLeft->hide();
        //tabBarRight->hide();
    }
}

void UnderCommander::on_actionExit_triggered()
{
    QApplication::quit();
}

void UnderCommander::customTabMenuLeft(QPoint pos)
{
//    deleteTabLeftAction->setEnabled(true);
//    if (tabBarLeft->count() == 1){
//        deleteTabLeftAction->setEnabled(false);
//    }
//    leftTabMenu->popup(QCursor::pos());
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
    smallLeftContextNewFile();
}

void UnderCommander::on_actionNew_folder_triggered()
{
    smallLeftContextNewFolder();
}

void UnderCommander::on_actionNew_file_3_triggered()
{
    smallRightContextNewFile();
}

void UnderCommander::on_actionNew_folder_2_triggered()
{
    smallRightContextNewFolder();
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
