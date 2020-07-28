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
        emit ArgumentIsNullSignal("Some arguments in ModelViewController's constructor is Null.");
    }
    if (!defaultPath.isNull() && QDir(defaultPath).exists()){
        DefaultPath = defaultPath;
    }
    else{
        emit IncorrectDefaultPathSignal("Current default path does not exist.");
    }
    Id = count++;
}

int ModelViewController::count = 0;

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
        backStack.push(FsModel->rootPath());
        FsModel->setRootPath(DriveBox->currentText()+"/");
    }
    else if(fileInfo.fileName()== ".."){
        if (restoredPathFlag){
            clearForwardStack();
        }
        backStack.push(FsModel->rootPath());
        QDir dir = fileInfo.dir();
        dir.cdUp();
        FsModel->setRootPath(dir.absolutePath());
    }
    else if(fileInfo.isDir()){
        if (restoredPathFlag){
            clearForwardStack();
        }
        backStack.push(FsModel->rootPath());
        FsModel->setRootPath(FsModel->filePath(index));
    }
    else if(fileInfo.isFile()){
        openFile(FsModel->fileInfo(index).absoluteFilePath());
    }
}

void ModelViewController::select(const QModelIndex index)
{
    QFileInfo fileInfo = FsModel->fileInfo(index);
    if (fileInfo.fileName() != "." && fileInfo.fileName() != ".."){
        DisplayedPathLineEdit->setText(FsModel->filePath(index));
    }
    else DisplayedPathLineEdit->setText(currentPath);
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
            forwardStack.push(FsModel->rootPath());
            if (forwardStack.count() > 0 && !ForwardButton->isEnabled()){
                ForwardButton->setEnabled(true);
            }
            FsModel->setRootPath(path);
            if (backStack.count() <= 1){
                BackButton->setEnabled(false);
            }
        }
    }
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
            backStack.push(FsModel->rootPath());
            if (forwardStack.isEmpty()){
                ForwardButton->setEnabled(false);
            }
            FsModel->setRootPath(path);
            if (backStack.count() > 1 && !BackButton->isEnabled()){
                BackButton->setEnabled(true);
            }
        }
    }
}

void ModelViewController::go(const QString path)
{
    QDir dir(path);
    QFileInfo fileInfo = FsModel->fileInfo(FsModel->index(path));
    if (dir.exists() &&
            dir.absolutePath() != FsModel->rootPath() &&
            fileInfo.fileName() != "."
            && fileInfo.fileName() != "..")
    {
        clearForwardStack();
        backStack.push(FsModel->rootPath());
        FsModel->setRootPath(path);
        if  (backStack.count() >=1 && !BackButton->isEnabled()){
            BackButton->setEnabled(true);
        }
    }
    else if (FsModel->fileInfo(FsModel->index(path)).isFile()){
        openFile(path);
    }
    else if (dir.absolutePath() != FsModel->rootPath()){
        DisplayedPathLineEdit->setText(displayedPathCurrent);
        emit WarningSignal(createIdMessage("Can't find the path provided. Check spelling and try again!"));
    }
}

void ModelViewController::changeDrive(const QString path)
{
    QString newPath = path + "/";
    if (newPath != FsModel->rootPath()){
        clearForwardStack();
        backStack.push(FsModel->rootPath());
        FsModel->setRootPath(path);
        if  (backStack.count() >=1 && !BackButton->isEnabled()){
            BackButton->setEnabled(true);
        }
    }
}

void ModelViewController::openFile(const QString path)
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

QString ModelViewController::createIdMessage(QString m)
{
    return "{" + QString::number(Id) + "} " + m;
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
    connect(FsModel, &QFileSystemModel::rootPathChanged, this, &ModelViewController::on_rootPathChanged);
    FsModel->setReadOnly(false);
    FsViewModel->setModel(FsModel);
    FsViewModel->setRootIndex(FsModel->setRootPath(DefaultPath));
    FsModel->setFilter(QDir::AllEntries);
    backStack.push(DefaultPath);

    FsViewModel->setDragEnabled(true);
    FsViewModel->setAcceptDrops(true);
    FsViewModel->setDropIndicatorShown(true);
    FsViewModel->init();

    //ui->leftView->setContextMenuPolicy(Qt::CustomContextMenu);
    //connect(ui->leftView, &FSView::customContextMenuRequested, this, &UnderCommander::on_customMenuRequestedLeft);
}

//todo
void ModelViewController::initContextMenus()
{
    //ContextMenu
    conMenu = new ContextMenu(this);

    //SmallContextMenu
    smallConMenu = new SmallContextMenu(this);
}

void ModelViewController::initBackForwardNavigation()
{
    BackButton->setEnabled(false);
    ForwardButton->setEnabled(false);
}

void ModelViewController::on_rootPathChanged(const QString &newPath)
{
    FsViewModel->setRootIndex(FsModel->index(FsModel->rootPath()));
    DisplayedPathLineEdit->setText(FsModel->rootPath());
    QString comboPath;
    comboPath.push_back(newPath.at(0));
    comboPath.push_back(newPath.at(1));
    if (DriveBox->currentText() != comboPath){
        DriveBox->setCurrentIndex(DriveBox->findText(comboPath));
    }
    displayedPathCurrent = DisplayedPathLineEdit->text();
    currentPath = FsModel->rootPath();
}

void ModelViewController::updateDiskList()
{
    DriveModel->refresh();
}