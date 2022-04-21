#ifndef COPYINGSTATUSWINDOW_H
#define COPYINGSTATUSWINDOW_H

#include <QDialog>
#include <QThread>
#include <QMessageBox>
#include <QCloseEvent>
#include "copyworker.h"

namespace Ui {
class CopyingStatusWindow;
}

class CopyingStatusWindow : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(bool skip READ skip WRITE setSkip NOTIFY skipChanged)

public:
    explicit CopyingStatusWindow(const QString &source, const QString &destination, const bool cutFlag, QWidget *parent = nullptr);
    ~CopyingStatusWindow();
    bool skip() const;

    virtual void closeEvent(QCloseEvent *e) override;

public slots:
    void copying_finished_slot();
    void setSkip(bool skip);

private slots:
    void askForCopyOptionsOverwriteFile(const QString &source, const QString &destination);
    void askForCopyOptionsMergeFolders(const QString &source, const QString &destination);
    void on_PauseChanged(bool value);

    void on_pauseResume_clicked();

signals:
    void skipChanged(bool skip);
    void ArgumentIsInvalid(const QString &message);

private:
    Ui::CopyingStatusWindow *ui;
    copy_options options = copy_options::copy_symlinks | copy_options::overwrite_existing;
    QThread *thread;
    CopyWorker *worker;
    bool m_skip;
    QString windowTitle = "Copying files...";
    bool CutFlag;
    bool copyingFinished = false;
    bool pause = false;
    void pauseOperation();
    void unPauseOperation();
};

#endif // COPYINGSTATUSWINDOW_H
