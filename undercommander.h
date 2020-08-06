#ifndef UNDERCOMMANDER_H
#define UNDERCOMMANDER_H

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
    void on_rightView_clicked(const QModelIndex &index);

    void on_pushButtonLeft_clicked();

    void on_pushButtonRight_clicked();

    void on_backLeft_clicked();

    void on_backRight_clicked();

    void on_forwardLeft_clicked();

    void on_forwardRight_clicked();

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

    void on_actionEnable_tabs_triggered();

    void on_actionExit_triggered();

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

    void on_leftView_clicked(const QModelIndex &index);

    void on_rightView_activated(const QModelIndex &index);

    /*******************************/
    void setClipboardData(QMimeData *data);

private:
    Ui::UnderCommander *ui;
    QFileSystemModel *leftModel;
    QFileSystemModel *rightModel;
    QDirModel *drivesModelLeft;
    QDirModel *drivesModelRight;
    ModelViewController *leftController;
    ModelViewController *rightController;
    QString defaultPath;
    //Theme
    int curPalette = 0;
    QPalette defaultPalette;
    QPalette darkPalette;
    //Tabs
    tabs *tabBarLeft;
    tabs *tabBarRight;
    void createTabs();
    QMenu *leftTabMenu;
    QMenu *rightTabMenu;
    QAction *deleteTabLeftAction;
    QAction *deleteTabRightAction;
    void createTabMenuLeft();
    void createTabMenuRight();

    void initPalettes();
};

#endif // UNDERCOMMANDER_H
