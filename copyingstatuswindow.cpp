#include "copyingstatuswindow.h"
#include "ui_copyingstatuswindow.h"

CopyingStatusWindow::CopyingStatusWindow(const QString &source, const QString &destination, const bool cutFlag, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CopyingStatusWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    ui->lineEdit->setText(source);
    ui->lineEdit_2->setText(destination);
    if (!skip()){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Copying files...", "Overwrite existing files?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes){
            options = options | copy_options::overwrite_existing;
        }
        else{
            reply = QMessageBox::question(this, "Copying files...", "Update existing files"
                                                                    "(replace the existing file only if it is older than the file being copied)?",
                                          QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes){
                options = options | copy_options::update_existing;
            }
            else{
                options = options | copy_options::skip_existing;
            }
        }
        reply = QMessageBox::question(this, "Copying files...", "Copy simlinks?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes){
            options = options | copy_options::copy_symlinks;
        }
        else{
            reply = QMessageBox::question(this, "Copying files...", "Create simlinks instead of copying?", QMessageBox::Yes | QMessageBox::No);
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
    if(cutFlag){
        connect(thread, &QThread::started, worker, &CopyWorker::start_moving);
        this->setWindowTitle("Moving files...");
    }
    else{
        connect(thread, &QThread::started, worker, &CopyWorker::start_copying);
    }
    connect(worker, &CopyWorker::copying_finished, this, &CopyingStatusWindow::copying_finished_slot);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(0);
    thread->start();
}

CopyingStatusWindow::~CopyingStatusWindow()
{
    thread->quit();
    thread->wait();
    delete ui;
}

void CopyingStatusWindow::copying_finished_slot()
{
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(100);
    this->close();
}
