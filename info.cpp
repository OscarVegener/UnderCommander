#include "info.h"
#include "ui_info.h"
//#include "windowsexplorerproperties.h"

info::info(QWidget *parent, QString path) :
    QDialog(parent),
    ui(new Ui::info)
{
    ui->setupUi(this);
    QDir dir;
    if (!path.isEmpty() && dir.exists(path)){
        infoPath = path;
        setFixedSize(400, 300);
        fileInfo.setFile(path);
        ui->lineName->setText(fileInfo.fileName());
        if (fileInfo.isFile()){
            ui->lineKind->setText(fileInfo.suffix() + " file");
        }
        else if(fileInfo.isDir()){
            ui->lineKind->setText("Folder");
        }
        ui->lineLocation->setText(fileInfo.path());
        QDateTime accessed = fileInfo.lastRead();
        QDateTime modified = fileInfo.lastModified();
        ui->lineAccessed->setText(accessed.toString());
        ui->lineModified->setText(modified.toString());

        ui->checkReadable->setAttribute(Qt::WA_TransparentForMouseEvents);
        ui->checkWritable->setAttribute(Qt::WA_TransparentForMouseEvents);
        ui->checkExecutable->setAttribute(Qt::WA_TransparentForMouseEvents);
        ui->checkSymLink->setAttribute(Qt::WA_TransparentForMouseEvents);
        if (fileInfo.isReadable()){
            ui->checkReadable->setCheckState(Qt::Checked);
        }
        if (fileInfo.isWritable()){
            ui->checkWritable->setCheckState(Qt::Checked);
        }
        if (fileInfo.isFile()){
            if (fileInfo.isExecutable()){
                ui->checkExecutable->setCheckState(Qt::Checked);
            }
        }
        else{
            ui->checkExecutable->setEnabled(false);
        }
        if (fileInfo.isSymLink()){
            ui->checkSymLink->setCheckState(Qt::Checked);
        }
        //setting up thread for size calculating
        calc = new calcSize();
        thread = new QThread(this);
        calc->setStop(false);
        calc->moveToThread(thread);
        connect(thread, &QThread::finished, calc, &calcSize::deleteLater);
        connect(this, &info::startCalcSizeUC, calc, &calcSize::displaySizeUC);
        connect(calc, &calcSize::calculatingFinishedUC, this, &info::on_calculatingFinishedUC);
        thread->start();
        emit startCalcSizeUC(fileInfo);
        if (!calc->Finished()){
            progressBar = new QProgressBar(this);
            ui->lineSize->hide();
            ui->horizontalLayout_5->addWidget(progressBar);
            progressBar->setFormat("");
            progressBar->setMinimum(0);
            progressBar->setMaximum(0);
        }
    }
}

info::~info()
{
    if (!calc->Finished()){
        calc->setStop(true);
        calc->setPause(false);
        thread->quit();
        thread->wait();
    }
    else{
        thread->quit();
    }
    emit removePathFromList(infoPath);
    delete ui;
}

void info::on_calculatingFinishedUC(const QString size)
{
    progressBar->hide();
    ui->pauseResume->hide();
    ui->lineSize->show();
    ui->lineSize->setText(size);
}

void info::pauseCalculatingSize()
{
    calc->setPause(true);
    ui->pauseResume->setIcon(QIcon(":/icons/resume.png"));
    progressBar->setMinimum(0);
    progressBar->setMaximum(100);
    progressBar->setValue(100);
    pause = true;
}

void info::unpauseCalculatingSize()
{
    calc->setPause(false);
    ui->pauseResume->setIcon(QIcon(":/icons/pause.png"));
    progressBar->setMinimum(0);
    progressBar->setMaximum(0);
    progressBar->setValue(0);
    pause = false;
}

void info::on_propertiesButton_clicked()
{
    if (!calc->Finished() && !calc->Pause()){
        pauseCalculatingSize();
    }
//    WindowsExplorerProperties window(infoPath);
//    window.exec();
}

void info::on_pauseResume_clicked()
{
    if (pause){
        unpauseCalculatingSize();
    }
    else{
        pauseCalculatingSize();
    }
}
