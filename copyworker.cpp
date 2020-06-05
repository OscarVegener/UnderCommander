#include "copyworker.h"

CopyWorker::CopyWorker(const QString &src, const QString &dst, const copy_options &op, QObject *parent) : QObject(parent)
{
    source = src;
    destination = dst;
    options = op;
}

void CopyWorker::start_copying()
{
    error_code error;
    if (is_directory(source.toStdString())){
        QFileInfo fileInfo;
        fileInfo.setFile(source);
        QString dirName = fileInfo.fileName();
        QDir dir(destination);
        dir.mkdir(dirName);
        fileInfo.setFile(destination + "/" + dirName);
        copy(source.toStdString(), fileInfo.absoluteFilePath().toStdString(), options, error);
    }
    else{
        copy(source.toStdString(), destination.toStdString(), options, error);
    }
    emit copying_finished();
    QString string;
    string.fromStdString(error.message());
    qDebug() << string;
}

void CopyWorker::start_moving()
{
    error_code error_copy;
    error_code error_delete;
    if (is_directory(source.toStdString())){
        QFileInfo fileInfo;
        fileInfo.setFile(source);
        QString dirName = fileInfo.fileName();
        QDir dir(destination);
        dir.mkdir(dirName);
        fileInfo.setFile(destination + "/" + dirName);
        copy(source.toStdString(), fileInfo.absoluteFilePath().toStdString(), options, error_copy);
    }
    else{
        copy(source.toStdString(), destination.toStdString(), options, error_copy);
    }
    qDebug() << "moving";
    remove_all(source.toStdString(), error_delete);
    emit copying_finished();
    QString string_copy;
    QString string_delete;
    string_copy.fromStdString(error_copy.message());
    string_delete.fromStdString(error_delete.message());
    qDebug() << string_copy;
    qDebug() << string_delete;
}
