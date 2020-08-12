#ifndef COPYWORKER_H
#define COPYWORKER_H

#include <QObject>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QThread>
#include <QMessageBox>
#include <filesystem>
#include <QDebug>

using namespace std;

using namespace std::filesystem;

class CopyWorker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool Stop READ Stop WRITE setStop NOTIFY StopChanged)
    Q_PROPERTY(bool Pause READ Pause WRITE setPause NOTIFY PauseChanged)
public:
    explicit CopyWorker(const QString &src, const QString &dst, QDialog *window, QObject *parent = nullptr);

    bool Stop() const;
    bool Pause() const;

    void setOptions(const copy_options &value);
    void setMergeFolders(int value);

private:
    QDialog *Window;
    QString source;
    QString destination;
    copy_options options = copy_options::copy_symlinks | copy_options::overwrite_existing;
    int mergeFolders = QMessageBox::Yes;
    void copy_recursively(const QString &source, const QString &destination, error_code &code);
    void pause();

    bool m_Stop;
    bool m_Pause;

public slots:
    void start_copying();
    void start_moving();
    void setStop(bool Stop);
    void setPause(bool Pause);

signals:
    void copying_finished();
    void StopChanged(bool Stop);
    void PauseChanged(bool Pause);
    void errorSignal(const QString &message);
    void askForCopyOptionsOverwriteFile(const QString &source, const QString &destination);
    void askForCopyOptionsMergeFolders(const QString &source, const QString &destination);
};

#endif // COPYWORKER_H
