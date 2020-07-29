#ifndef MODELVIEWCONTROLLER_H
#define MODELVIEWCONTROLLER_H

#define defaultPathValue "C:\\"
#define StackLimit 100
#include <QObject>
#include <QFileSystemModel>
#include <QDirModel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTimer>
#include <QStack>
#include <QMainWindow>
#include <QDesktopServices>
#include <QProcess>
#include "fsview.h"
#include "contextmenu.h"
#include "smallcontextmenu.h"

class ModelViewController : public QObject
{
    Q_OBJECT
public:
    explicit ModelViewController(QFileSystemModel *fsModel,
                                 QDirModel *driveModel,
                                 QLineEdit *displayedPath,
                                 QComboBox *driveBox,
                                 QPushButton *forwardButton,
                                 QPushButton *backButton,
                                 QPushButton *goButton,
                                 FSView *fsViewModel,
                                 QMainWindow *window,
                                 QString defaultPath = defaultPathValue,
                                 QObject *parent = nullptr);

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

    QString getDefaultPath() const;
    void setDefaultPath(const QString &value);

    int getId() const;

    int getBackStackLimit() const;
    void setBackStackLimit(int value);

    int getForwardStackLimit() const;
    void setForwardStackLimit(int value);

    //basic functions
    void open(const QModelIndex index);
    void select(const QModelIndex index);
    //void deselect(const QModelIndex index);
    void back();
    void forward();
    void go(const QString path);
    void changeDrive(const QString path);

private:

    void openFile(const QString path);

    QFileSystemModel *FsModel;
    QDirModel *DriveModel;
    QLineEdit *DisplayedPathLineEdit;
    QComboBox *DriveBox;
    QPushButton *ForwardButton;
    QPushButton *BackButton;
    QPushButton *GoButton;
    FSView *FsViewModel;
    static int count;
    int Id;
    QMainWindow *Window;
    QString DefaultPath;
    QString createIdMessage(QString m);

    QString currentPath;
    QString displayedPathCurrent;

    //Navigation back and forward
    QTimer *timer;
    QStack<QString> backStack;
    QStack<QString> forwardStack;
    int backStackLimit = StackLimit;
    int forwardStackLimit = StackLimit;

    bool restoredPathFlag = false;

    void clearForwardStack();
    void resetBackForwardNavigation();

    //QLineEdit save settings
    QFont lineEditFont;

    void saveTextEditsSettings();

    //Initialization
    void initDriveModel();
    void initFsModel();
    void initContextMenus();
    void initBackForwardNavigation();

    //Stores paths to copy
    QStringList copyPaths;

    //Context menu
    ContextMenu *conMenu;

    //Small context menu
    SmallContextMenu *smallConMenu;

private slots:
    void on_customMenuRequested(const QPoint &pos);
    void on_rootPathChanged(const QString &newPath);
    void updateDiskList();

    //Context menu slots
    void contextOpen();
    void contextPrint();
    void contextNewFile();
    void contextNewFolder();
    void contextCut();
    void contextCopy();
    void contextCopyToClipboard();
    void contextPaste();
    void contextPasteToRoot();
    void contextDelete();
    void contextRename();
    void contextInfo();

signals:

    void ArgumentIsNullSignal(QString message);
    void IncorrectDefaultPathSignal(QString message);
    void StatusBarMessageSignal(QString message);
    void IncorrectIdSignal(QString message);
    void StackLimitReachedSignal(QString message);
    void WarningSignal(QString message);
};

#endif // MODELVIEWCONTROLLER_H
