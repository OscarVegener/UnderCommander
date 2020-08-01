#include "copyingstatuswindow.h"
#include "ui_copyingstatuswindow.h"

CopyingStatusWindow::CopyingStatusWindow(const QString &source, const QString &destination, const bool cutFlag, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CopyingStatusWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    CutFlag = cutFlag;
    if (!source.isEmpty() && !destination.isEmpty()){
        ui->lineEdit->setText(source);
        ui->lineEdit_2->setText(destination);
        if (cutFlag){
            windowTitle = "Moving files...";
        }
        if (!skip()){
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, windowTitle, "Overwrite existing files?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes){
                options = options | copy_options::overwrite_existing;
            }
            else{
                reply = QMessageBox::question(this, windowTitle, "Update existing files"
                                                                        "(replace the existing file only if it is older than the file being copied)?",
                                              QMessageBox::Yes | QMessageBox::No);
                if (reply == QMessageBox::Yes){
                    options = options | copy_options::update_existing;
                }
                else{
                    options = options | copy_options::skip_existing;
                }
            }
            reply = QMessageBox::question(this, windowTitle, "Copy simlinks?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes){
                options = options | copy_options::copy_symlinks;
            }
            else{
                reply = QMessageBox::question(this, windowTitle, "Create simlinks instead of copying?", QMessageBox::Yes | QMessageBox::No);
                if (reply == QMessageBox::Yes){
                    options = options | copy_options::create_symlinks;
                }
                else{
                    options = options | copy_options::skip_symlinks;
                }
            }
        }
        worker = new CopyWorker(source, destination, options);
        thread = new QThread(this);
        worker->moveToThread(thread);
        connect(thread, &QThread::finished, worker, &CopyWorker::deleteLater);
        this->setWindowTitle(windowTitle);
        if(cutFlag){
            connect(thread, &QThread::started, worker, &CopyWorker::start_moving);
        }
        else{
            connect(thread, &QThread::started, worker, &CopyWorker::start_copying);
        }
        connect(worker, &CopyWorker::copying_finished, this, &CopyingStatusWindow::copying_finished_slot);
        ui->progressBar->setMinimum(0);
        ui->progressBar->setMaximum(0);
        thread->start();
    }
    else{
        emit ArgumentIsInvalid("Invalid source or destination for copying files.");
        copyingFinished = true;
        this->close();
    }
}

CopyingStatusWindow::~CopyingStatusWindow()
{
    if(!copyingFinished){
        thread->quit();
        thread->wait();
    }
    delete ui;
}

void CopyingStatusWindow::closeEvent(QCloseEvent *e)
{
    if(thread->isRunning()){
        if(CutFlag){
            QMessageBox::warning(this, windowTitle, "UnderCommander is moving files at the moment. \n"
                                                    "Stoping it can lead to errors and file corrupting.");
        }
        else{
            QMessageBox::warning(this, windowTitle, "UnderCommander is copying files at the moment. \n"
                                                    "Stoping it can lead to errors and file corrupting.");
        }
        e->ignore();
    }
    else{
        e->accept();
    }
}

void CopyingStatusWindow::copying_finished_slot()
{
    copyingFinished = true;
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(100);
    thread->quit();
    thread->wait();
    this->close();
}
