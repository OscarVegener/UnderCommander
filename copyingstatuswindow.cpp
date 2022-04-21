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
        ui->progressBar->setFormat("");
        if (cutFlag){
            windowTitle = "Moving files...";
        }
        worker = new CopyWorker(source, destination, this);
        thread = new QThread(this);
        worker->moveToThread(thread);
        connect(worker, &CopyWorker::askForCopyOptionsMergeFolders, this, &CopyingStatusWindow::askForCopyOptionsMergeFolders);
        connect(worker, &CopyWorker::askForCopyOptionsOverwriteFile, this, &CopyingStatusWindow::askForCopyOptionsOverwriteFile);
        connect(worker, &CopyWorker::PauseChanged, this, &CopyingStatusWindow::on_PauseChanged);
        connect(thread, &QThread::finished, worker, &CopyWorker::deleteLater);
        this->setWindowTitle(windowTitle);
        if(cutFlag){
            connect(thread, &QThread::started, worker, &CopyWorker::start_moving);
        }
        else{
            connect(thread, &QThread::started, worker, &CopyWorker::start_copying);
        }
        connect(worker, &CopyWorker::copying_finished, this, &CopyingStatusWindow::copying_finished_slot);
        worker->setStop(false);
        worker->setPause(false);
        //worker->setOptions(askForCopyOptions());
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
        worker->setStop(true);
        worker->setPause(false);
        thread->quit();
        thread->wait();
    }
    else{
        thread->quit();
    }
    delete ui;
}

bool CopyingStatusWindow::skip() const
{
    return m_skip;
}

void CopyingStatusWindow::closeEvent(QCloseEvent *e)
{
    if(thread->isRunning()){
        worker->setPause(false);
        worker->setStop(true);
        if(CutFlag){
            QApplication::beep();
            QMessageBox::warning(this, windowTitle, "UnderCommander is moving files at the moment. \n"
                                                    "Stoping it can lead to errors and file corrupting.");
        }
        else{
            QApplication::beep();
            QMessageBox::warning(this, windowTitle, "UnderCommander is copying files at the moment. \n"
                                                    "Stoping it can lead to errors and file corrupting.");
        }
        e->ignore();
    }
    else{
        e->accept();
    }
}

void CopyingStatusWindow::askForCopyOptionsOverwriteFile(const QString &source, const QString &destination)
{
    copy_options options = copy_options::copy_symlinks | copy_options::overwrite_existing;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, windowTitle, "Overwrite " + source +"\nwith " + destination + " ?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes){
        options = options | copy_options::overwrite_existing;
    }
    else{
        reply = QMessageBox::question(this, windowTitle, "Update existing files"
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
    worker->setOptions(options);
    worker->setPause(false);
}

void CopyingStatusWindow::askForCopyOptionsMergeFolders(const QString &source, const QString &destination)
{
    QString message = "Merge " + source + "\nand " + destination + " ?";
    worker->setMergeFolders(QMessageBox::question(this, windowTitle, message, QMessageBox::Yes | QMessageBox::No));
    worker->setPause(false);
}

void CopyingStatusWindow::on_PauseChanged(bool value)
{
    if(value){
        pauseOperation();
    }
    else{
        unPauseOperation();
    }
}

void CopyingStatusWindow::pauseOperation()
{
    ui->pauseResume->setIcon(QIcon(":/icons/resume.png"));
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(100);
    pause = true;
}

void CopyingStatusWindow::unPauseOperation()
{
    ui->pauseResume->setIcon(QIcon(":/icons/pause.png"));
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(0);
    ui->progressBar->setValue(0);
    pause = false;
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

void CopyingStatusWindow::setSkip(bool skip)
{
    if (m_skip == skip)
        return;
    m_skip = skip;
    emit skipChanged(m_skip);
}

void CopyingStatusWindow::on_pauseResume_clicked()
{
    if (pause){
        worker->setPause(false);
    }
    else{
        worker->setPause(true);
    }
}
