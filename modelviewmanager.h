#ifndef MODELVIEWMANAGER_H
#define MODELVIEWMANAGER_H

#include <QFileSystemModel>
#include <QDirModel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include "fsview.h"

class ModelViewManager
{
public:
    ModelViewManager(QFileSystemModel *fsModel,
                     QDirModel *driveModel,
                     QLineEdit *displayedPath,
                     QComboBox *driveBox,
                     QPushButton *forwardButton,
                     QPushButton *backButton,
                     QPushButton *goButton,
                     FSView *fsViewModel);

    QFileSystemModel *getFsModel() const;
    void setFsModel(QFileSystemModel *value);

    QDirModel *getDriveModel() const;
    void setDriveModel(QDirModel *value);

    QLineEdit *getDisplayedPath() const;
    void setDisplayedPath(QLineEdit *value);

    QComboBox *getDriveBox() const;
    void setDriveBox(QComboBox *value);

    QPushButton *getForwardButton() const;
    void setForwardButton(QPushButton *value);

    QPushButton *getBackButton() const;
    void setBackButton(QPushButton *value);

    QPushButton *getGoButton() const;
    void setGoButton(QPushButton *value);

    FSView *getFsViewModel() const;
    void setFsViewModel(FSView *value);

private:
    QFileSystemModel *FsModel;
    QDirModel *DriveModel;
    QLineEdit *DisplayedPath;
    QComboBox *DriveBox;
    QPushButton *ForwardButton;
    QPushButton *BackButton;
    QPushButton *GoButton;
    FSView *FsViewModel;
};

#endif // MODELVIEWMANAGER_H
