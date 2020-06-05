#ifndef INFO_H
#define INFO_H

#include <QDialog>
#include <QFileInfo>
#include <QDateTime>
#include <QDir>
#include <QThread>
#include <QCloseEvent>
#include <QProgressBar>
#include "calcsize.h"
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
signals:
    void startCalcSizeUC(const QFileInfo fileInfo);
    void removePathFromList(const QString path);
};

#endif // INFO_H
