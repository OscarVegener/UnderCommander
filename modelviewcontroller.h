#ifndef MODELVIEWCONTROLLER_H
#define MODELVIEWCONTROLLER_H

#define defaultPathValue "C:\\"
#define NavigationStackLimit 100
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
#include <QMessageBox>
#include "fsview.h"
#include "contextmenu.h"
#include "smallcontextmenu.h"
#include "newfile.h"
#include "newfolder.h"
#include "copyingstatuswindow.h"
#include "info.h"
#include <QDebug>

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
    void back();
    void forward();
    void go(const QString path);
    void changeDrive(const QString path);

    //Resets all to basic state
    void resetModelViewController(); //todo

private:

    void openFile(const QString &path);
    void pasteToRoot(const QString &root);
    void deleteInfoPath(const QString &path);
    void clearCurrentIndexSelection();

    QFileSystemModel *FsModel;
    QDirModel *DriveModel;
    QLineEdit *DisplayedPathLineEdit;
    QComboBox *DriveBox;
    QPushButton *ForwardButton;
    QPushButton *BackButton;
    QPushButton *GoButton;
    FSView *FsViewModel;
    QString DefaultPath;
    int Id;
    static int count;
    QMainWindow *Window;
    QString createIdMessage(QString m);

    QString currentPath;
    QString displayedPathCurrent;

    //Navigation back and forward
    QTimer *timer;
    QStack<QString> backStack;
    QStack<QString> forwardStack;
    int backStackLimit = NavigationStackLimit;
    int forwardStackLimit = NavigationStackLimit;

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

    //Context menu
    ContextMenu *conMenu;
    SmallContextMenu *smallConMenu;
    static bool contextCutFlag;
    static QStringList copyPaths;
    copy_options askForCopyOptions();
    static QStringList infoPaths;

private slots:
    void on_rootIndexChanged(const QModelIndex &index);
    void on_currentChanged(const QModelIndex &current, const QModelIndex &previous);
    void on_customMenuRequested(const QPoint &pos);
    void updateDiskList();
    void deselect();

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
    void rootIndexChanged(const QModelIndex &index);
    void indexErrorSignal(const QString &message);
    void ArgumentIsNullSignal(const QString &message);
    void ArgumentIsInvalid(const QString &message);
    void IncorrectDefaultPathSignal(const QString &message);
    void StatusBarMessageSignal(const QString &message);
    void IncorrectIdSignal(const QString &message);
    void StackLimitReachedSignal(const QString &message);
    void WarningSignal(const QString &message);
    void creatingFileErrorSignal(const QString &message);
    void creatingFolderErrorSignal(const QString &message);
    void removingFilesErrorSignal(const QString &message);
    void propertiesWarningSignal(const QString &message);
    void setClipboardDataSignal(QMimeData *data);
};

#endif // MODELVIEWCONTROLLER_H
