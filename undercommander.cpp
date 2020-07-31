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
//    rightController = new ModelViewController(rightModel,
//                                              drivesModelRight,
//                                              ui->textEditRight,
//                                              ui->comboBoxRight,
//                                              ui->forwardRight,
//                                              ui->backRight,
//                                              ui->pushButtonRight,
//                                              ui->rightView,
//                                              this,
//                                              "C:\\",
//                                              this);
    //ui->rightView->setModel(rightModel);
    //rightModel->setRootPath(rightModel->myComputer().toString());
    initPalettes();
    //createTabs();
}

UnderCommander::~UnderCommander()
{
    //delete leftController;
    delete ui;
}

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

void UnderCommander::on_leftView_clicked(const QModelIndex &index)
{
    leftController->select(index);
}

void UnderCommander::on_rightView_clicked(const QModelIndex &index)
{
    //rightController->select(index);
}

void UnderCommander::on_rightView_doubleClicked(const QModelIndex &index)
{
    //rightController->open(index);
    //ui->rightView->setRootIndex(index);
}

void UnderCommander::on_pushButtonLeft_clicked()
{
    leftController->go(ui->textEditLeft->text());
}

void UnderCommander::on_pushButtonRight_clicked()
{
    //rightController->go(ui->textEditRight->text());
}

void UnderCommander::on_backLeft_clicked()
{
    leftController->back();
}

void UnderCommander::on_backRight_clicked()
{
    //rightController->back();
}


void UnderCommander::on_forwardLeft_clicked()
{
    leftController->forward();
}

void UnderCommander::on_forwardRight_clicked()
{
    //rightController->forward();
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

void UnderCommander::on_comboBoxRight_activated(const QString &arg1)
{
    //rightController->changeDrive(arg1);
}

void UnderCommander::on_leftView_activated(const QModelIndex &index)
{
    leftController->open(index);
}

