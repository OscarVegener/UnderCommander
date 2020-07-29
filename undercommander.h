#ifndef UNDERCOMMANDER_H
#define UNDERCOMMANDER_H

#define stackLimit 5

#include <QMainWindow>
#include <QDir>
#include <QFileSystemModel>
#include <QUrl>
#include <QDesktopServices>
#include <QDirModel>
#include <QStack>
#include <QTimer>
#include <QMessageBox>
#include <QMenu>
#include <QClipboard>
#include <QMimeData>
#include <QPrinter>
#include <QPrintDialog>
#include <QProcess>
#include <QFileDialog>
#include "tabs.h"
#include "copyingstatuswindow.h"

#include "modelviewcontroller.h"


#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui { class UnderCommander; }
QT_END_NAMESPACE

class UnderCommander : public QMainWindow
{
    Q_OBJECT

public:
    friend class FSView;
    UnderCommander(QWidget *parent = nullptr);
    ~UnderCommander();
private slots:
    void on_leftView_clicked(const QModelIndex &index);

    void on_rightView_clicked(const QModelIndex &index);

    void on_leftView_doubleClicked(const QModelIndex &index);

    void on_rightView_doubleClicked(const QModelIndex &index);

    void on_pushButtonLeft_clicked();

    void on_textEditLeft_textChanged();

    void on_textEditRight_textChanged();

    void on_pushButtonRight_clicked();

    void on_backLeft_clicked();

    void on_backRight_clicked();

    void on_forwardLeft_clicked();

    void on_forwardRight_clicked();

    //left context menu

    void leftContextNewFile();

    void leftContextNewFolder();

    void leftContextCut();

    void leftContextCopy();

    void leftContextCopyFolderFiles();

    void leftContextPaste();

    void leftContextPasteRoot();

    void leftContextDelete();

    void leftContextInfo();

    void smallLeftContextNewFile();

    void smallLeftContextNewFolder();

    void smallLeftContextInfo();

    //Right context menu

    void rightContextNewFile();

    void rightContextNewFolder();

    void rightContextCut();

    void rightContextCopy();

    void rightContextCopyFolderFiles();

    void rightContextPaste();

    void rightContextPasteRoot();

    void rightContextDelete();

    void rightContextInfo();

    void smallRightContextNewFile();

    void smallRightContextNewFolder();

    void smallRightContextInfo();
//

    void deleteInfoPath(const QString path);

    void on_actionDark_triggered();

    void on_actionDefault_triggered();

    void on_actionShow_only_files_triggered();

    void on_actionShow_only_folders_triggered();

    void on_actionShow_only_files_2_triggered();

    void on_actionShow_only_folders_2_triggered();

    void on_actionShow_files_and_folders_triggered();

    void on_actionShow_files_and_folders_2_triggered();

    void on_actionCreate_tab_triggered();

    void on_actionNew_right_tab_triggered();

    //Tabs

    void tabBarLeftClick(int index);

    void tabBarRightClick(int index);

    void on_actionEnable_tabs_triggered();

    void on_actionExit_triggered();

    void customTabMenuLeft(QPoint pos);

    void customTabMenuRight(QPoint pos);

    void deleteTabLeft();

    void deleteTabRight();

    void on_actionNew_file_triggered();

    void on_actionNew_folder_triggered();

    void on_actionNew_file_3_triggered();

    void on_actionNew_folder_2_triggered();

    void on_actionOpen_directory_left_triggered();

    void on_actionOpen_directory_right_triggered();

    void on_actionEnable_size_column_triggered();

    void on_actionEnable_date_column_triggered();

    void on_actionEnable_size_column_2_triggered();

    void on_actionEnable_date_column_2_triggered();

    void on_actionEnable_type_column_triggered();

    void on_actionEnable_type_column_2_triggered();

    void on_comboBoxLeft_activated(const QString &arg1);

    void on_comboBoxRight_activated(const QString &arg1);

    void on_leftView_activated(const QModelIndex &index);

private:
    Ui::UnderCommander *ui;

    QFileSystemModel *leftModel;
    QFileSystemModel *rightModel;
    QDirModel *drivesModelLeft;
    QDirModel *drivesModelRight;

    ModelViewController *leftController;
    ModelViewController *rightController;

    QString defaultPath;
    //QTimer *timer;
    //QString leftCurrent;
    //QString rightCurrent;
    //QString textEditLeftCurrent;
    //QString textEditRightCurrent;
    //Navigation back and forward
    //QStack<QString> leftStack;
    //QStack<QString> rightStack;
    //QStack<QString> forwardLeftStack;
    //QStack<QString> forwardRightStack;
    //bool restoredPathFlagLeft = false;
    //bool restoredPathFlagRight = false;
    //void clearLeftForwardStack();
    //void clearRightForwardStack();

    //QTextEdit save settings
    //QColor textEditLeftColor;
    //QColor textEditRightColor;
    //QFont textEditLeftFont;
    //QFont textEditRightFont;

    //void saveTextEditsSettings();

    //Change disk in comboBox
    //void ifUserGoesToAnotherDiskLeft();
    //void ifUserGoesToAnotherDiskRight();
/**********************************************CONTEXT MENU*/
    //Context menu info

    //QStringList infoPath;

    //bool contextCutFlag;

    //QStringList copyPaths;
    //copy_options askForCopyOptions();
    //Left Context Menu
    //QMenu *leftContextMenu;
    //QMenu *newLeftMenu;
    //QAction *leftOpenAction;
    //QAction *leftPrintAction;
//    QAction *leftNewFileAction;
//    QAction *leftNewFolderAction;
//    QAction *leftCutAction;
//    QAction *leftCopyAction;
//    QAction *leftCopyFolderFilesAction;
//    QAction *leftPasteAction;
//    QAction *leftPasteRootAction;
//    QAction *leftDeleteAction;
//    QAction *leftRenameAction;
//    QAction *leftInfoAction;

//    void displayLeft(QModelIndex index);
//    void leftCopy();
//    void clearMemoryLeftContextMenu();
//    void createLeftContextMenu();

    //Small left context menu
//    QMenu *smallLeftContextMenu;
//    QMenu *smallNewLeftMenu;
//    QAction *smallLeftNewFileAction;
//    QAction *smallLeftNewFolderAction;
//    QAction *smallLeftPasteAction;
//    QAction *smallLeftInfoAction;

//    void clearMemorySmallLeftContextMenu();
//    void createSmallLeftContextMenu();

    //Right Context Menu
//    QMenu *rightContextMenu;
//    QMenu *newRightMenu;
//    QAction *rightOpenAction;
//    QAction *rightPrintAction;
//    QAction *rightNewFileAction;
//    QAction *rightNewFolderAction;
//    QAction *rightCutAction;
//    QAction *rightCopyAction;
//    QAction *rightCopyFolderFilesAction;
//    QAction *rightPasteAction;
//    QAction *rightPasteRootAction;
//    QAction *rightDeleteAction;
//    QAction *rightRenameAction;
//    QAction *rightInfoAction;

//    void displayRight(QModelIndex index);
//    void rightCopy();
//    void clearMemoryRightContextMenu();
//    void createRightContextMenu();

    //Small right context menu
//    QMenu *smallRightContextMenu;
//    QMenu *smallNewRightMenu;
//    QAction *smallRightNewFileAction;
//    QAction *smallRightNewFolderAction;
//    QAction *smallRightPasteAction;
//    QAction *smallRightInfoAction;

//    void clearMemorySmallRightContextMenu();
//    void createSmallRightContextMenu();

    //Create new file/folder
//    QString newFileName;
//    QString newFolderName;

    //Theme
    int curPalette = 0;
    QPalette defaultPalette;
    QPalette darkPalette;


    //Tabs
//    tabs *tabBarLeft;
//    tabs *tabBarRight;
//    void createTabs();
//    QMenu *leftTabMenu;
//    QMenu *rightTabMenu;
//    QAction *deleteTabLeftAction;
//    QAction *deleteTabRightAction;
//    void createTabMenuLeft();
//    void createTabMenuRight();

    void initPalettes();

//    void changeLeftRootPath(const QString &path);
//    void changeRightRootPath(const QString &path);

//    void resetBackForwardLeft();
//    void resetBackForwardRight();
};

#endif // UNDERCOMMANDER_H
