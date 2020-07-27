#include "modelviewmanager.h"

ModelViewManager::ModelViewManager(QFileSystemModel *fsModel,
                                    QDirModel *driveModel,
                                    QLineEdit *displayedPath,
                                    QComboBox *driveBox,
                                    QPushButton *forwardButton,
                                    QPushButton *backButton,
                                    QPushButton *goButton,
                                    FSView *fsViewModel)
{

}

QFileSystemModel *ModelViewManager::getFsModel() const
{
    return FsModel;
}

void ModelViewManager::setFsModel(QFileSystemModel *value)
{
    FsModel = value;
}

QDirModel *ModelViewManager::getDriveModel() const
{
    return DriveModel;
}

void ModelViewManager::setDriveModel(QDirModel *value)
{
    DriveModel = value;
}

QLineEdit *ModelViewManager::getDisplayedPath() const
{
    return DisplayedPath;
}

void ModelViewManager::setDisplayedPath(QLineEdit *value)
{
    DisplayedPath = value;
}

QComboBox *ModelViewManager::getDriveBox() const
{
    return DriveBox;
}

void ModelViewManager::setDriveBox(QComboBox *value)
{
    DriveBox = value;
}

QPushButton *ModelViewManager::getForwardButton() const
{
    return ForwardButton;
}

void ModelViewManager::setForwardButton(QPushButton *value)
{
    ForwardButton = value;
}

QPushButton *ModelViewManager::getBackButton() const
{
    return BackButton;
}

void ModelViewManager::setBackButton(QPushButton *value)
{
    BackButton = value;
}

QPushButton *ModelViewManager::getGoButton() const
{
    return GoButton;
}

void ModelViewManager::setGoButton(QPushButton *value)
{
    GoButton = value;
}

FSView *ModelViewManager::getFsViewModel() const
{
    return FsViewModel;
}

void ModelViewManager::setFsViewModel(FSView *value)
{
    FsViewModel = value;
}
