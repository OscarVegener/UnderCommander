#ifndef NEWFILE_H
#define NEWFILE_H

#include <QDialog>
#include <QMessageBox>
#include <QValidator>
#include <QRegExpValidator>
#include <QRegExp>
//#include "undercommander.h"

namespace Ui {
class newfile;
}

class newfile : public QDialog
{
    Q_OBJECT

public:
    explicit newfile(QWidget *parent = nullptr);
    ~newfile();

    QString getFileName(){
        return fileName;
    }

    bool isAccepted(){
        return accepted;
    }

private slots:

    void on_buttonBox_accepted();

private:
    Ui::newfile *ui;
    QString fileName;
    bool accepted = false;
    QValidator *regExpValidator1;
    QValidator *regExpValidator2;
    QRegExp *regExp1;
    QRegExp *regExp2;
};

#endif // NEWFILE_H
