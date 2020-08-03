#ifndef CALCSIZE_H
#define CALCSIZE_H

#include <QObject>
#include <QFileInfo>
#include <QDir>

class calcSize : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool Finished READ Finished WRITE setFinished NOTIFY FinishedChanged)
    Q_PROPERTY(bool Stop READ Stop WRITE setStop NOTIFY StopChanged)

public:
    bool Finished() const;

    bool Stop() const;

private:
    qint64 dirSize(QString dirPath);
    QString formatSize(qint64 size);
    QFileInfo fileInfo;

    bool m_Finished;

    bool m_Stop;

public slots:
    void displaySizeUC(const QFileInfo fileInfo);
    void setFinished(bool Finished);

    void setStop(bool Stop);

signals:
    void calculatingFinishedUC(const QString size);
    void FinishedChanged(bool Finished);
    void StopChanged(bool Stop);
};

#endif // CALCSIZE_H
