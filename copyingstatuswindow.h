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
    bool skip() const
    {
        return m_skip;
    }
    void setOptions(const copy_options &op){
        options = op;
    }

    virtual void closeEvent(QCloseEvent *e) override;

public slots:
    void copying_finished_slot();
    void setSkip(bool skip)
    {
        if (m_skip == skip)
            return;
        m_skip = skip;
        emit skipChanged(m_skip);
    }

signals:
    void skipChanged(bool skip);
    void ArgumentIsInvalid(const QString &message);

private:
    Ui::CopyingStatusWindow *ui;
    copy_options options = copy_options::recursive;
    QThread *thread;
    CopyWorker *worker;
    bool m_skip;
    QString windowTitle = "Copying files...";
    bool CutFlag;
    bool copyingFinished = false;
};

#endif // COPYINGSTATUSWINDOW_H
