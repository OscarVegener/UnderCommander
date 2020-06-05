#ifndef NEWFOLDER_H
#define NEWFOLDER_H

#include <QDialog>
#include <QValidator>
#include <QRegExpValidator>
#include <QRegExp>

namespace Ui {
class newfolder;
}

class newfolder : public QDialog
{
    Q_OBJECT

public:
    explicit newfolder(QWidget *parent = nullptr);
    ~newfolder();

    QString getPathName(){
        return pathName;
    }

    bool isAccepted(){
        return accepted;
    }

private slots:
    void on_buttonBox_accepted();

private:
    Ui::newfolder *ui;

    QString pathName;
    bool accepted = false;
    QValidator *regExpValidator;
    QRegExp *regExp;
};

#endif // NEWFOLDER_H
