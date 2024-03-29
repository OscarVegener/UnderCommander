#ifndef INFO_H
#define INFO_H

#include <QDialog>
#include <QFileInfo>
#include <QDateTime>
#include <QDir>
#include <QThread>
#include <QCloseEvent>
#include <QProgressBar>
#include <QDir>
#include "calcsize.h"
//#include "windowsexplorerproperties.h"
#include <QDebug>

namespace Ui {
class info;
}

class info : public QDialog
{
    Q_OBJECT

public:
    explicit info(QWidget *parent = nullptr, QString path = nullptr);
    ~info();
public slots:
    void on_calculatingFinishedUC(const QString size);

private:
    Ui::info *ui;
    QFileInfo fileInfo;
    calcSize *calc;
    QThread *thread;
    QString infoPath;
    QProgressBar *progressBar;
    bool pause = false;

    void pauseCalculatingSize();
    void unpauseCalculatingSize();

signals:
    void startCalcSizeUC(const QFileInfo fileInfo);
    void removePathFromList(const QString &path);
private slots:
    void on_propertiesButton_clicked();
    void on_pauseResume_clicked();
};

#endif // INFO_H
