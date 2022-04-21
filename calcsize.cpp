#include "calcsize.h"

bool calcSize::Finished() const
{
    return m_Finished;
}

bool calcSize::Stop() const
{
    return m_Stop;
}

bool calcSize::Pause() const
{
    return m_Pause;
}

qint64 calcSize::dirSize(QString dirPath) {
    if (Stop()){
        return 0;
    }
    qint64 size = 0;
    QDir dir(dirPath);
    //calculate total size of current directories' files
    QDir::Filters fileFilters = QDir::Files|QDir::System|QDir::Hidden;
    for(QString filePath : dir.entryList(fileFilters)) {
        if (Stop()){
            return 0;
        }
        while(Pause()){
            QThread::sleep(1);
        }
        QFileInfo fi(dir, filePath);
        size+= fi.size();
    }
    //add size of child directories recursively
    QDir::Filters dirFilters = QDir::Dirs|QDir::NoDotAndDotDot|QDir::System|QDir::Hidden;
    for(QString childDirPath : dir.entryList(dirFilters)){
        if (Stop()){
            return 0;
        }
        while(Pause()){
            QThread::sleep(1);
        }
        size+= dirSize(dirPath + QDir::separator() + childDirPath);
    }
    return size;
}

QString calcSize::formatSize(qint64 size) {
    QStringList units = {"Bytes", "KB", "MB", "GB", "TB", "PB"};
    int i;
    double outputSize = size;
    for(i = 0; i < units.size()-1; i++) {
        if(outputSize < 1024) break;
        outputSize = outputSize/1024;
    }
    return QString("%0 %1").arg(outputSize, 0, 'f', 2).arg(units[i]);
}

void calcSize::displaySizeUC(const QFileInfo fileInfo)
{
    setFinished(false);
    QString size;
    if (fileInfo.isFile()){
        size = formatSize(fileInfo.size());
        setFinished(true);
        if (!Stop()){
            emit calculatingFinishedUC(size);
        }
    }
    else if(fileInfo.isDir()){
        size = formatSize(dirSize(fileInfo.absoluteFilePath()));
        setFinished(true);
        if (!Stop()){
            emit calculatingFinishedUC(size);
        }
    }
}

void calcSize::setFinished(bool Finished)
{
    if (m_Finished == Finished)
        return;

    m_Finished = Finished;
    emit FinishedChanged(m_Finished);
}

void calcSize::setStop(bool Stop)
{
    if (m_Stop == Stop)
        return;

    m_Stop = Stop;
    emit StopChanged(m_Stop);
}

void calcSize::setPause(bool Pause)
{
    if (m_Pause == Pause)
        return;

    m_Pause = Pause;
    emit PauseChanged(m_Pause);
}
