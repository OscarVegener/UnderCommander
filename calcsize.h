#ifndef CALCSIZE_H
#define CALCSIZE_H

#include <QObject>
#include <QFileInfo>
#include <QDir>
#include <QThread>

class calcSize : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool Finished READ Finished WRITE setFinished NOTIFY FinishedChanged)
    Q_PROPERTY(bool Stop READ Stop WRITE setStop NOTIFY StopChanged)
    Q_PROPERTY(bool Pause READ Pause WRITE setPause NOTIFY PauseChanged)

public:
    bool Finished() const;
    bool Stop() const;
    bool Pause() const;

private:
    qint64 dirSize(QString dirPath);
    QString formatSize(qint64 size);
    QFileInfo fileInfo;

    bool m_Finished;
    bool m_Stop;
    bool m_Pause;

public slots:
    void displaySizeUC(const QFileInfo fileInfo);

    void setFinished(bool Finished);
    void setStop(bool Stop);
    void setPause(bool Pause);

signals:
    void calculatingFinishedUC(const QString size);
    void FinishedChanged(bool Finished);
    void StopChanged(bool Stop);
    void PauseChanged(bool Pause);
};

#endif // CALCSIZE_H
