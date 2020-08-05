#include "modelviewcontroller.h"

ModelViewController::ModelViewController(QFileSystemModel *fsModel,
                                    QDirModel *driveModel,
                                    QLineEdit *displayedPath,
                                    QComboBox *driveBox,
                                    QPushButton *forwardButton,
                                    QPushButton *backButton,
                                    QPushButton *goButton,
                                    FSView *fsViewModel,
                                    QMainWindow *window,
                                    QString defaultPath,
                                    QObject *parent) : QObject(parent)
{
    Id = count++;
    if (fsModel != nullptr &&
        driveModel != nullptr &&
        displayedPath != nullptr &&
        driveBox != nullptr &&
        forwardButton != nullptr &&
        backButton != nullptr &&
        goButton != nullptr &&
        fsViewModel != nullptr &&
        window != nullptr)
    {
        FsModel = fsModel;
        DriveModel = driveModel;
        DisplayedPathLineEdit = displayedPath;
        DriveBox = driveBox;
        ForwardButton = forwardButton;
        BackButton = backButton;
        GoButton = goButton;
        FsViewModel = fsViewModel;
        Window = window;
    }
    else{
        emit ArgumentIsNullSignal(createIdMessage("Some arguments in ModelViewController's constructor is Null."));
    }
    if (!defaultPath.isNull() && QDir(defaultPath).exists()){
        DefaultPath = defaultPath;
    }
    else{
        emit IncorrectDefaultPathSignal(createIdMessage("Current default path does not exist."));
    }
    initFsModel();
    initDriveModel();
    initContextMenus();
    initBackForwardNavigation();
}

int ModelViewController::count = 0;

bool ModelViewController::contextCutFlag = 0;

QStringList ModelViewController::copyPaths;

QStringList ModelViewController::infoPaths;

QFileSystemModel *ModelViewController::getFsModel() const
{
    return FsModel;
}

void ModelViewController::setFsModel(QFileSystemModel *value)
{
    FsModel = value;
}

QDirModel *ModelViewController::getDriveModel() const
{
    return DriveModel;
}

void ModelViewController::setDriveModel(QDirModel *value)
{
    DriveModel = value;
}

QLineEdit *ModelViewController::getDisplayedPath() const
{
    return DisplayedPathLineEdit;
}

void ModelViewController::setDisplayedPath(QLineEdit *value)
{
    DisplayedPathLineEdit = value;
}

QComboBox *ModelViewController::getDriveBox() const
{
    return DriveBox;
}

void ModelViewController::setDriveBox(QComboBox *value)
{
    DriveBox = value;
}

QPushButton *ModelViewController::getForwardButton() const
{
    return ForwardButton;
}

void ModelViewController::setForwardButton(QPushButton *value)
{
    ForwardButton = value;
}

QPushButton *ModelViewController::getBackButton() const
{
    return BackButton;
}

void ModelViewController::setBackButton(QPushButton *value)
{
    BackButton = value;
}

QPushButton *ModelViewController::getGoButton() const
{
    return GoButton;
}

void ModelViewController::setGoButton(QPushButton *value)
{
    GoButton = value;
}

FSView *ModelViewController::getFsViewModel() const
{
    return FsViewModel;
}

void ModelViewController::setFsViewModel(FSView *value)
{
    FsViewModel = value;
}

QString ModelViewController::getDefaultPath() const
{
    return DefaultPath;
}

void ModelViewController::setDefaultPath(const QString &value)
{
    DefaultPath = value;
}

int ModelViewController::getId() const
{
    return Id;
}

int ModelViewController::getForwardStackLimit() const
{
    return forwardStackLimit;
}

void ModelViewController::setForwardStackLimit(int value)
{
    forwardStackLimit = value;
}

int ModelViewController::getBackStackLimit() const
{
    return backStackLimit;
}

void ModelViewController::setBackStackLimit(int value)
{
    backStackLimit = value;
}

void ModelViewController::open(const QModelIndex index)
{
    QFileInfo fileInfo = FsModel->fileInfo(index);
    if (backStack.count() == backStackLimit){
        backStack.clear();
        backStack.push(DefaultPath);
        emit StackLimitReachedSignal("backStack limit reached, stack is cleared!");
    }
    if  (fileInfo.isDir() && backStack.count() >=1 && !BackButton->isEnabled()){
        BackButton->setEnabled(true);
    }
    if (fileInfo.fileName() == "."){
        if (restoredPathFlag){
            clearForwardStack();
        }
        backStack.push(FsModel->filePath(FsViewModel->rootIndex()));
        QModelIndex newIndex = FsModel->index(FsModel->rootPath());
        FsViewModel->setRootIndex(newIndex);
        emit rootIndexChanged(newIndex);
    }
    else if(fileInfo.fileName()== ".."){
        if (restoredPathFlag){
            clearForwardStack();
        }
        backStack.push(FsModel->filePath(FsViewModel->rootIndex()));
        QModelIndex newIndex = FsViewModel->rootIndex().parent();
        FsViewModel->setRootIndex(newIndex);
        emit rootIndexChanged(newIndex);
    }
    else if(fileInfo.isDir()){
        if (restoredPathFlag){
            clearForwardStack();
        }
        backStack.push(FsModel->filePath(FsViewModel->rootIndex()));
        QModelIndex newIndex = FsModel->index(fileInfo.canonicalFilePath());
        FsViewModel->setRootIndex(newIndex);
        emit rootIndexChanged(newIndex);
    }
    else if(fileInfo.isFile()){
        openFile(FsModel->fileInfo(index).absoluteFilePath());
    }
}

void ModelViewController::select(const QModelIndex index)
{
    if (index.isValid()){
        QFileInfo fileInfo = FsModel->fileInfo(index);
        if (fileInfo.fileName() != "." && fileInfo.fileName() != ".."){
            DisplayedPathLineEdit->setText(FsModel->filePath(index));
        }
        else DisplayedPathLineEdit->setText(currentPath);
    }
    else{
        FsViewModel->selectionModel()->clearSelection();
    }
}

void ModelViewController::back()
{
    if (forwardStack.count() == forwardStackLimit){
        clearForwardStack();
        emit WarningSignal(createIdMessage("forwardStack limit reached, stack is cleared!"));
    }
    if (!backStack.isEmpty() && backStack.count() != 1){
        QString path = backStack.pop();
        if (!QDir(path).exists()){
            resetBackForwardNavigation();
            emit WarningSignal(createIdMessage("Previous path does not exist!"));
        }
        else{
            restoredPathFlag = true;
            forwardStack.push(FsModel->filePath(FsViewModel->rootIndex()));
            if (forwardStack.count() > 0 && !ForwardButton->isEnabled()){
                ForwardButton->setEnabled(true);
            }
            QModelIndex index = FsModel->index(path);
            FsViewModel->setRootIndex(index);
            emit rootIndexChanged(index);
            if (backStack.count() <= 1){
                BackButton->setEnabled(false);
            }
        }
    }
    qDebug() << FsModel->filePath(FsViewModel->rootIndex());
    qDebug() << FsModel->rootPath();
}

void ModelViewController::forward()
{
    if (backStack.count() == backStackLimit){
        backStack.clear();
        backStack.push(DefaultPath);
        emit StackLimitReachedSignal("backStack limit reached, stack is cleared!");
    }
    if (!forwardStack.isEmpty()){
        QString path = forwardStack.pop();
        if (!QDir(path).exists()){
            resetBackForwardNavigation();
            emit WarningSignal(createIdMessage("Path does not exist!"));
        }
        else{
            restoredPathFlag = true;
            backStack.push(FsModel->filePath(FsViewModel->rootIndex()));
            if (forwardStack.isEmpty()){
                ForwardButton->setEnabled(false);
            }
            QModelIndex index = FsModel->index(path);
            FsViewModel->setRootIndex(index);
            emit rootIndexChanged(index);
            if (backStack.count() > 1 && !BackButton->isEnabled()){
                BackButton->setEnabled(true);
            }
        }
    }
    qDebug() << FsModel->filePath(FsViewModel->rootIndex());
    qDebug() << FsModel->rootPath();
}

void ModelViewController::go(const QString path)
{
    if(!path.isEmpty()){
        QDir dir(path);
        QFileInfo fileInfo;
        fileInfo.setFile(path);
        if (dir.exists() &&
            dir.absolutePath() != FsModel->filePath(FsViewModel->rootIndex()) &&
            (dir.absolutePath() + "/") != FsModel->filePath(FsViewModel->rootIndex()) &&
            fileInfo.fileName() != "." &&
            fileInfo.fileName() != "..")
        {
            clearForwardStack();
            backStack.push(FsModel->filePath(FsViewModel->rootIndex()));
            QString comboPath;
            comboPath.push_back(fileInfo.canonicalFilePath().at(0));
            comboPath.push_back(fileInfo.canonicalFilePath().at(1));
            if (DriveBox->currentText() != comboPath){
                DriveBox->setCurrentIndex(DriveBox->findText(comboPath));
            }
            FsModel->setRootPath(comboPath + "\\");
            QModelIndex newIndex = FsModel->index(fileInfo.canonicalFilePath());
            FsViewModel->setRootIndex(newIndex);
            emit rootIndexChanged(newIndex);
            if  (backStack.count() >=1 && !BackButton->isEnabled()){
                BackButton->setEnabled(true);
            }
        }
        else if (FsModel->fileInfo(FsModel->index(path)).isFile()){
            openFile(path);
        }
        else if (dir.absolutePath() != FsModel->filePath(FsViewModel->rootIndex())){
            DisplayedPathLineEdit->setText(displayedPathCurrent);
            emit WarningSignal(createIdMessage("Can't find the path provided. Check spelling and try again!"));
        }
    }
    else{
        DisplayedPathLineEdit->setText(displayedPathCurrent);
        emit ArgumentIsInvalid(createIdMessage("Argument for \"go\" function is invalid."));
    }
}

void ModelViewController::changeDrive(const QString path)
{
    QString newPath = path + "/";
    if (newPath != FsModel->rootPath()){
        clearForwardStack();
        backStack.push(FsModel->filePath(FsViewModel->rootIndex()));
        FsModel->setRootPath(newPath);
        QModelIndex newIndex = FsModel->index(path);
        FsViewModel->setRootIndex(newIndex);
        emit rootIndexChanged(newIndex);
        if  (backStack.count() >=1 && !BackButton->isEnabled()){
            BackButton->setEnabled(true);
        }
    }
}

void ModelViewController::resetModelViewController()
{

}

void ModelViewController::openFile(const QString &path)
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void ModelViewController::pasteToRoot(const QString &root)
{
    if(exists(root.toStdString())){
        copy_options options = askForCopyOptions();
        foreach (QString source, copyPaths){
            if (exists(source.toStdString())){
                CopyingStatusWindow *window = new CopyingStatusWindow(source, root, contextCutFlag);
                window->setOptions(options);
                window->setSkip(true);
                window->setModal(true);
                window->setAttribute(Qt::WA_DeleteOnClose);
                window->exec();
            }
        }
    }
}

void ModelViewController::deleteInfoPath(const QString &path)
{
    infoPaths.removeAt(infoPaths.indexOf(path));
}

void ModelViewController::clearCurrentIndexSelection()
{
    DisplayedPathLineEdit->setText(currentPath);
    displayedPathCurrent = DisplayedPathLineEdit->text();
    QModelIndex newIndex;
    FsViewModel->selectionModel()->clearSelection();
    FsViewModel->selectionModel()->setCurrentIndex(newIndex, QItemSelectionModel::Select);
}

QString ModelViewController::createIdMessage(QString m)
{
    return "{Id: " + QString::number(Id) + "} " + m;
}

void ModelViewController::clearForwardStack()
{
    forwardStack.clear();
    if (ForwardButton->isEnabled()){
        ForwardButton->setEnabled(false);
    }
    restoredPathFlag = false;
    emit StatusBarMessageSignal(createIdMessage("ForwardStack is cleared."));
}

void ModelViewController::resetBackForwardNavigation()
{
    BackButton->setEnabled(false);
    backStack.clear();
    backStack.push_back(FsModel->rootPath());
    clearForwardStack();
    emit StatusBarMessageSignal(createIdMessage("There was some errors. BackForwardNavigation is reset."));
}

void ModelViewController::saveTextEditsSettings()
{
    lineEditFont = DisplayedPathLineEdit->font();
}

//Checks for new drives connected
void ModelViewController::initDriveModel()
{
    DriveModel->setFilter(QDir::Drives);
    DriveBox->setModel(DriveModel);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ModelViewController::updateDiskList);
    timer->start(500);
}

void ModelViewController::initFsModel()
{
    FsModel->setReadOnly(false);
    FsViewModel->setModel(FsModel);
    FsViewModel->setRootIndex(FsModel->setRootPath(DefaultPath));
    FsModel->setFilter(QDir::AllEntries);
    backStack.push(DefaultPath);
    currentPath = DefaultPath;
    displayedPathCurrent = DefaultPath;
    DisplayedPathLineEdit->setText(DefaultPath);
    connect(FsViewModel->selectionModel(), &QItemSelectionModel::currentChanged, this, &ModelViewController::on_currentChanged);
    connect(this, &ModelViewController::rootIndexChanged, this, &ModelViewController::on_rootIndexChanged);
    connect(FsViewModel, &FSView::selectionClearedSignal, this, &ModelViewController::deselect);
    FsViewModel->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(FsViewModel, &FSView::customContextMenuRequested, this, &ModelViewController::on_customMenuRequested);
    FsViewModel->setDragEnabled(true);
    FsViewModel->setAcceptDrops(true);
    FsViewModel->setDropIndicatorShown(true);
    FsViewModel->init();
}

void ModelViewController::initContextMenus()
{
    //ContextMenu
    conMenu = new ContextMenu(this);
    connect(conMenu->getOpenAction(), &QAction::triggered, this, &ModelViewController::contextOpen);
    connect(conMenu->getPrintAction(), &QAction::triggered, this, &ModelViewController::contextPrint);
    connect(conMenu->getNewFileAction(), &QAction::triggered, this, &ModelViewController::contextNewFile);
    connect(conMenu->getNewFolderAction(), &QAction::triggered, this, &ModelViewController::contextNewFolder);
    connect(conMenu->getCutAction(), &QAction::triggered, this, &ModelViewController::contextCut);
    connect(conMenu->getCopyAction(), &QAction::triggered, this, &ModelViewController::contextCopy);
    connect(conMenu->getCopyToClipboardAction(), &QAction::triggered, this, &ModelViewController::contextCopyToClipboard);
    connect(conMenu->getPasteAction(), &QAction::triggered, this, &ModelViewController::contextPaste);
    connect(conMenu->getPasteToRootAction(), &QAction::triggered, this, &ModelViewController::contextPasteToRoot);
    connect(conMenu->getDeleteAction(), &QAction::triggered, this, &ModelViewController::contextDelete);
    connect(conMenu->getRenameAction(), &QAction::triggered, this, &ModelViewController::contextRename);
    connect(conMenu->getInfoAction(), &QAction::triggered, this, &ModelViewController::contextInfo);
    //SmallContextMenu
    smallConMenu = new SmallContextMenu(this);
    connect(smallConMenu->getNewFileAction(), &QAction::triggered, this, &ModelViewController::contextNewFile);
    connect(smallConMenu->getNewFolderAction(), &QAction::triggered, this, &ModelViewController::contextNewFolder);
    connect(smallConMenu->getPasteToRootAction(), &QAction::triggered, this, &ModelViewController::contextPasteToRoot);
    connect(smallConMenu->getInfoAction(), &QAction::triggered, this, &ModelViewController::contextInfo);
}

void ModelViewController::initBackForwardNavigation()
{
    BackButton->setEnabled(false);
    ForwardButton->setEnabled(false);
}

copy_options ModelViewController::askForCopyOptions()
{
    copy_options options = copy_options::recursive;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(Window, "Copying files...", "Overwrite existing files?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes){
        options = options | copy_options::overwrite_existing;
    }
    else{
        reply = QMessageBox::question(Window, "Copying files...", "Update existing files"
                                                                "(replace the existing file only"
                                                                  " if it is older than the file being copied)?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes){
            options = options | copy_options::update_existing;
        }
        else{
            options = options | copy_options::skip_existing;
        }
    }
    reply = QMessageBox::question(Window, "Copying files...", "Copy simlinks?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes){
        options = options | copy_options::copy_symlinks;
    }
    else{
        reply = QMessageBox::question(Window, "Copying files...", "Create simlinks instead of copying?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes){
            options = options | copy_options::create_symlinks;
        }
        else{
            options = options | copy_options::skip_symlinks;
        }
    }
    return options;
}

void ModelViewController::on_rootIndexChanged(const QModelIndex &index)
{
    if (index.isValid()){
        QString newPath = FsModel->filePath(index);
        qDebug() << "newPath(rootIndex changed): " << newPath;
        DisplayedPathLineEdit->setText(newPath);
        QString comboPath;
        comboPath.push_back(newPath.at(0));
        comboPath.push_back(newPath.at(1));
        qDebug() << "RootPath: " << FsModel->rootPath();
        qDebug() << "ComboPath: " << comboPath;
        if (FsModel->rootPath() != (comboPath + "/")){
            FsModel->setRootPath(comboPath + "/");
        }
        if (DriveBox->currentText() != comboPath){
            int driveIndex;
            if((driveIndex =  DriveBox->findText(comboPath)) != -1){
                qDebug() << "DriveIndex: "<< driveIndex;
                DriveBox->setCurrentIndex(driveIndex);
            }
            else{
                emit indexErrorSignal(createIdMessage("Can't find index for current drive."));
            }
        }
        displayedPathCurrent = DisplayedPathLineEdit->text();
        currentPath = newPath;
    }
    else{
        emit indexErrorSignal(createIdMessage("Index error happened when changing root"));
    }
}

void ModelViewController::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    select(current);
}

void ModelViewController::on_customMenuRequested(const QPoint &pos)
{
    QModelIndex index = FsViewModel->indexAt(pos);
    if (index.isValid()){
        select(index);
    }
    QFileInfo fileInfo = FsModel->fileInfo(index);
    //Show Context menu
    if (FsViewModel->selectionModel()->isSelected(index) && fileInfo.fileName() != "." && fileInfo.fileName() != ".."){
        if (fileInfo.completeSuffix() == "txt"){
            conMenu->getPrintAction()->setEnabled(true);
        }
        else{
            conMenu->getPrintAction()->setEnabled(false);
        }
        //Gets all selected indexes
        QModelIndexList list = FsViewModel->selectionModel()->selectedIndexes();
        bool atLeastOneFile = false;
        foreach (QModelIndex idx, list){
            if (FsModel->fileInfo(idx).isFile()){
                atLeastOneFile = true;
                break;
            }
        }
        //CopyToClipboard action works only for files
        if (atLeastOneFile){
            conMenu->getCopyToClipboardAction()->setEnabled(true);
        }
        else{
            conMenu->getCopyToClipboardAction()->setEnabled(false);
        }
        //Using Paste action, we can paste only to dir
        if (fileInfo.isDir() && !copyPaths.isEmpty()){
            conMenu->getPasteAction()->setEnabled(true);
        }
        else{
            conMenu->getPasteAction()->setEnabled(false);
        }
        //We can paste to root anytime if copyPaths is not empty
        if (!copyPaths.isEmpty()){
            conMenu->getPasteToRootAction()->setEnabled(true);
        }
        else{
            conMenu->getPasteToRootAction()->setEnabled(false);
        }
        conMenu->getMenu()->popup(FsViewModel->viewport()->mapToGlobal(pos));
    }
    //Show small context menu
    else if (fileInfo.fileName() != "." && fileInfo.fileName() != "..")
    {
        //We can paste to root anytime if copyPaths is not empty
        if (!copyPaths.isEmpty()){
            smallConMenu->getPasteToRootAction()->setEnabled(true);
        }
        else{
            smallConMenu->getPasteToRootAction()->setEnabled(false);
        }
        smallConMenu->getMenu()->popup(FsViewModel->viewport()->mapToGlobal(pos));
    }
}

void ModelViewController::updateDiskList()
{
    DriveModel->refresh();
}

void ModelViewController::deselect()
{
    DisplayedPathLineEdit->setText(currentPath);
    displayedPathCurrent = DisplayedPathLineEdit->text();
}

void ModelViewController::contextOpen()
{
    QModelIndex index = FsViewModel->currentIndex();
    if (FsViewModel->selectionModel()->isSelected(index)){
        open(index);
    }
}

void ModelViewController::contextPrint()
{
    QModelIndex index = FsViewModel->currentIndex();
    if (FsViewModel->selectionModel()->isSelected(index)){
        QFileInfo fileInfo = FsModel->fileInfo(index);
        QProcess *printProcess = new QProcess(this);
        QStringList arguments;
        arguments << "/p" << fileInfo.absoluteFilePath();
        printProcess->start("C:\\Windows\\notepad.exe", arguments);
    }
}

void ModelViewController::contextNewFile()
{
    QModelIndex index = FsViewModel->currentIndex();
    QFileInfo fileInfo = FsModel->fileInfo(index);
    newfile window;
    window.setModal(true);
    window.setWindowFlags(window.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    window.exec();
    if (window.isAccepted()){
        if (fileInfo.isFile()){
            QString newFileName = FsModel->filePath(FsViewModel->rootIndex()) + "/" + window.getFileName();
            qDebug() << "FileName isFile: " << newFileName;
            if (QFile::exists(newFileName)){
                emit creatingFileErrorSignal(createIdMessage("File " + newFileName + " already exists."));
            }
            else {
                QFile file(newFileName);
                if (file.open(QIODevice::WriteOnly)){
                    file.close();
                }
                else{
                    emit creatingFileErrorSignal(createIdMessage("File " + newFileName + "was not created. Probably you don't have permission."));
                }
            }
        }
        else if(fileInfo.isDir()){
            QString newFileName = FsModel->filePath(index) + "/" + window.getFileName();
            qDebug() << "FileName isDir: " << newFileName;
            if (QFile::exists(newFileName)){
                emit creatingFileErrorSignal(createIdMessage("File " + newFileName + " already exists."));
            }
            else {
                QFile file(newFileName);
                if (file.open(QIODevice::WriteOnly)){
                    file.close();
                }
                else{
                    emit creatingFileErrorSignal(createIdMessage("File " + newFileName + "was not created. Probably you don't have permission."));
                }
            }
        }
    }
}

void ModelViewController::contextNewFolder()
{
    QModelIndex index = FsViewModel->currentIndex();
    QFileInfo fileInfo = FsModel->fileInfo(index);
    newfolder window;
    window.setModal(true);
    window.setWindowFlags(window.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    window.exec();
    if (window.isAccepted()){
        if (fileInfo.isFile()){
            QString newFolderName = FsModel->filePath(FsViewModel->rootIndex()) + "/" + window.getPathName();
            qDebug() << "FolderName isFile: " << newFolderName;
            if (QDir(newFolderName).exists()){
                emit creatingFolderErrorSignal(createIdMessage("Folder " + newFolderName + " already exists."));
            }
            else{
                QDir currentDir(FsModel->filePath(FsViewModel->rootIndex()));
                if (!currentDir.mkdir(window.getPathName())){
                    emit creatingFolderErrorSignal(createIdMessage("FFolder " + newFolderName + "was not created."
                                                                                                " Probably you don't have permission."));
                }
            }
        }
        else if(fileInfo.isDir()){
            QString newFolderName = FsModel->filePath(FsViewModel->currentIndex()) + "/" + window.getPathName();
            qDebug() << "FolderName isDir: " << newFolderName;
            if (QDir(newFolderName).exists()){
                emit creatingFolderErrorSignal(createIdMessage("Folder " + newFolderName + " already exists."));
            }
            else{
                QDir parentDir(FsModel->filePath(index));
                if (!parentDir.mkdir(window.getPathName())){
                    emit creatingFolderErrorSignal(createIdMessage("FFolder " + newFolderName + "was not created."
                                                                                                " Probably you don't have permission."));
                }
            }
        }
    }
}

void ModelViewController::contextCut()
{
    contextCutFlag = true;
    copyPaths.clear();
    QModelIndexList list = FsViewModel->selectionModel()->selectedRows();
    foreach (QModelIndex index, list){
        copyPaths.push_back(FsModel->fileInfo(index).absoluteFilePath());
    }
    qDebug() << copyPaths;
}

void ModelViewController::contextCopy()
{
    contextCutFlag = false;
    copyPaths.clear();
    QModelIndexList list = FsViewModel->selectionModel()->selectedRows();
    foreach (QModelIndex index, list){
        copyPaths.push_back(FsModel->fileInfo(index).absoluteFilePath());
    }
    qDebug() << copyPaths;
}

void ModelViewController::contextCopyToClipboard()
{
    QModelIndexList indexList = FsViewModel->selectionModel()->selectedIndexes();
    QModelIndexList mimeList;
    foreach (QModelIndex idx, indexList){
        if(FsModel->fileInfo(idx).isFile()){
            mimeList.push_back(idx);
        }
    }
    QMimeData *data = FsModel->mimeData(mimeList);
    emit setClipboardDataSignal(data);
    //QApplication::clipboard()->setMimeData(data);
}

void ModelViewController::contextPaste()
{
    QModelIndex index = FsViewModel->currentIndex();
    QFileInfo fileInfo = FsModel->fileInfo(index);
    if (fileInfo.isFile()){
        pasteToRoot(FsModel->filePath(FsViewModel->rootIndex()));
    }
    else if(fileInfo.isDir()){
        QString dest = fileInfo.absoluteFilePath();
        copy_options options = askForCopyOptions();
        foreach (QString source, copyPaths){
            if (exists(source.toStdString())){
                CopyingStatusWindow *window = new CopyingStatusWindow(source, dest, contextCutFlag);
                window->setOptions(options);
                window->setSkip(true);
                window->setModal(true);
                window->setAttribute(Qt::WA_DeleteOnClose);
                window->exec();
            }
        }
    }
}

void ModelViewController::contextPasteToRoot()
{
    pasteToRoot(FsModel->filePath(FsViewModel->rootIndex()));
}

void ModelViewController::contextDelete()
{
    QModelIndexList itemsToDelete = FsViewModel->selectionModel()->selectedRows();
    error_code removingError;
    bool skipFlag = false;
    QFileInfo fileInfo;
    foreach(QModelIndex index, itemsToDelete){
        fileInfo = FsModel->fileInfo(index);
        if(fileInfo.isFile()){
            if(!skipFlag){
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(Window, "Delete file", "Are you sure you want to delete this"
                                                                       " \nfile: " + fileInfo.absoluteFilePath() +"?",
                                              QMessageBox::Yes | QMessageBox::YesToAll | QMessageBox::No);
                switch(reply){
                    case QMessageBox::YesToAll:
                        skipFlag = true;
                        remove_all(fileInfo.absoluteFilePath().toStdString(), removingError);
                        if (removingError.value() != 0){
                            emit removingFilesErrorSignal(createIdMessage(QString::fromStdString(removingError.message())));
                        }
                        break;
                    case QMessageBox::No: break;
                    case QMessageBox::Yes:
                        remove_all(fileInfo.absoluteFilePath().toStdString(), removingError);
                        if (removingError.value() != 0){
                            emit removingFilesErrorSignal(createIdMessage(QString::fromStdString(removingError.message())));
                        }
                        break;
                    default: emit removingFilesErrorSignal(createIdMessage("Error receiving answer from user."));
                }
            }
            else{
                remove_all(fileInfo.absoluteFilePath().toStdString(), removingError);
                if (removingError.value() != 0){
                    emit removingFilesErrorSignal(createIdMessage(QString::fromStdString(removingError.message())));
                }
            }
        }
        else if(fileInfo.isDir()){
            if(!skipFlag){
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(Window, "Delete folder", "Are you sure you want to delete this"
                                                                       " \nfolder: " + fileInfo.absoluteFilePath() +"?",
                                              QMessageBox::Yes | QMessageBox::YesToAll | QMessageBox::No);
                switch(reply){
                    case QMessageBox::YesToAll:
                        skipFlag = true;
                        remove_all(fileInfo.absoluteFilePath().toStdString(), removingError);
                        if (removingError.value() != 0){
                            emit removingFilesErrorSignal(createIdMessage(QString::fromStdString(removingError.message())));
                        }
                        break;
                    case QMessageBox::No: break;
                    case QMessageBox::Yes:
                        remove_all(fileInfo.absoluteFilePath().toStdString(), removingError);
                        if (removingError.value() != 0){
                            emit removingFilesErrorSignal(createIdMessage(QString::fromStdString(removingError.message())));
                        }
                        break;
                    default: emit removingFilesErrorSignal(createIdMessage("Error receiving answer from user."));
                }
            }
            else{
                remove_all(fileInfo.absoluteFilePath().toStdString(), removingError);
                if (removingError.value() != 0){
                    emit removingFilesErrorSignal(createIdMessage(QString::fromStdString(removingError.message())));
                }
            }
        }
    }
}

void ModelViewController::contextRename()
{
    QModelIndex index = FsViewModel->currentIndex();
    if (FsViewModel->selectionModel()->isSelected(index)){
        FsViewModel->edit(index);
    }
}

void ModelViewController::contextInfo()
{
    QModelIndex curIndex = FsViewModel->selectionModel()->currentIndex();
    if (FsViewModel->selectionModel()->selectedRows().contains(curIndex)){
        QString infoPath = FsModel->fileInfo(curIndex).absoluteFilePath();
        if (!infoPaths.contains(infoPath)){
            infoPaths.push_back(infoPath);
            info *window = new info(Window, infoPath);
            connect(window, &info::removePathFromList, this, &ModelViewController::deleteInfoPath);
            window->setWindowFlags(window->windowFlags() & ~Qt::WindowContextHelpButtonHint);
            window->setModal(false);
            window->setAttribute(Qt::WA_DeleteOnClose);
            window->show();
        }
        else {
            emit propertiesWarningSignal(createIdMessage("Properties window is already opened for this entry."));
        }
    }
    else{
        clearCurrentIndexSelection();
        QModelIndex index = FsViewModel->rootIndex();
        QString infoPath = FsModel->fileInfo(index).absoluteFilePath();
        if (!infoPaths.contains(infoPath)){
            infoPaths.push_back(infoPath);
            info *window = new info(Window, infoPath);
            connect(window, &info::removePathFromList, this, &ModelViewController::deleteInfoPath);
            window->setWindowFlags(window->windowFlags() & ~Qt::WindowContextHelpButtonHint);
            window->setModal(false);
            window->setAttribute(Qt::WA_DeleteOnClose);
            window->show();
        }
        else {
            emit propertiesWarningSignal(createIdMessage("Properties window is already opened for this entry."));
        }
    }
}
