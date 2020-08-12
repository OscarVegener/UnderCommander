#include "copyworker.h"

CopyWorker::CopyWorker(const QString &src, const QString &dst, QDialog *window, QObject *parent) : QObject(parent)
{
    if (window != nullptr && !src.isEmpty() && !dst.isEmpty()){
        Window = window;
        source = src;
        destination = dst;
    }
}

bool CopyWorker::Stop() const
{
    return m_Stop;
}

bool CopyWorker::Pause() const
{
    return m_Pause;
}

void CopyWorker::setOptions(const copy_options &value)
{
    options = value;
}

void CopyWorker::setMergeFolders(int value)
{
    mergeFolders = value;
}

void CopyWorker::copy_recursively(const QString &source, const QString &destination, error_code &code)
{
    QDir dir(source);
    QFileInfoList list = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
    for (int i = 0; i < list.count(); ++i){
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.isFile()){
            while(Pause()){
                QThread::sleep(1);
            }
            if (Stop()){
                return;
            }
            QString newFilePath = destination + "/" + fileInfo.fileName();
            qDebug() << "newFilePath: " << newFilePath;
            if (QFile::exists(newFilePath)){
                emit askForCopyOptionsOverwriteFile(fileInfo.absoluteFilePath(), newFilePath);
                pause();
            }
            copy(fileInfo.canonicalFilePath().toStdString(), destination.toStdString(), options, code);
            if (code.value() != 0){
                return;
            }
        }
        else if (fileInfo.isDir()){
            QString dstPath = destination + "/" + fileInfo.fileName();
            QString srcPath = source + "/" + fileInfo.fileName();
            QDir newDir(dstPath);
            if (!newDir.exists()){
                if(!newDir.mkpath(dstPath)){
                    code.assign(1, generic_category());
                    return;
                }
            }
            else {
                emit askForCopyOptionsMergeFolders(srcPath, dstPath);
                pause();
                if (mergeFolders == QMessageBox::No){
                    continue;
                }
            }
            copy_recursively(fileInfo.canonicalFilePath(), dstPath, code);
        }
    }
}

void CopyWorker::pause()
{
    setPause(true);
    while(Pause()){
        QThread::sleep(1);
    }
}

void CopyWorker::start_copying()
{
    error_code error;
    QFileInfo fileInfo;
    fileInfo.setFile(source);
    if (is_directory(source.toStdString())){
        QString dirName = fileInfo.fileName();
        QDir dir(destination);
        dir.mkdir(dirName);
        fileInfo.setFile(destination + "/" + dirName);
        copy_recursively(source, fileInfo.absoluteFilePath(), error);
    }
    else{
        QString newFilePath = destination + "/" + fileInfo.fileName();
        if (QFile::exists(newFilePath)){
            emit askForCopyOptionsOverwriteFile(fileInfo.absoluteFilePath(), newFilePath);
            pause();
        }
        copy(source.toStdString(), destination.toStdString(), options, error);
    }
    if (error.value() != 0){
        emit errorSignal("Something happened during operation. Code: " + QString::number(error.value()) +
                         " Message: " + QString::fromStdString((error.message())));
    }
    emit copying_finished();
}

void CopyWorker::start_moving()
{
    error_code error_copy;
    error_code error_delete;
    QFileInfo fileInfo;
    fileInfo.setFile(source);
    if (is_directory(source.toStdString())){
        QString dirName = fileInfo.fileName();
        QDir dir(destination);
        dir.mkdir(dirName);
        fileInfo.setFile(destination + "/" + dirName);
        copy_recursively(source, fileInfo.absoluteFilePath(), error_copy);
    }
    else{
        QString newFilePath = destination + "/" + fileInfo.fileName();
        if (QFile::exists(newFilePath)){
            emit askForCopyOptionsOverwriteFile(fileInfo.absoluteFilePath(), newFilePath);
            pause();
        }
        copy(source.toStdString(), destination.toStdString(), options, error_copy);
    }
    if (error_copy.value() != 0){
        emit errorSignal("Something happened during operation. Code: " + QString::number(error_copy.value()) +
                         " Message: " + QString::fromStdString((error_copy.message())));
    }
    remove_all(source.toStdString(), error_delete);
    if (error_delete.value() != 0){
        emit errorSignal("Something happened during operation. Code: " + QString::number(error_delete.value()) +
                         " Message: " + QString::fromStdString((error_delete.message())));
    }
    emit copying_finished();
}

void CopyWorker::setStop(bool Stop)
{
    if (m_Stop == Stop)
        return;

    m_Stop = Stop;
    emit StopChanged(m_Stop);
}

void CopyWorker::setPause(bool Pause)
{
    if (m_Pause == Pause)
        return;

    m_Pause = Pause;
    emit PauseChanged(m_Pause);
}
