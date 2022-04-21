#include "newfile.h"
#include "ui_newfile.h"

newfile::newfile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newfile)
{
    ui->setupUi(this);
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    regExp1 = new QRegExp;
    regExp1->setPattern("^[a-zA-Zа-яА-Я0-9]{100}$");
    regExpValidator1 = new QRegExpValidator(*regExp1, this);
    ui->lineEdit->setValidator(regExpValidator1);
    regExp1 = new QRegExp;
    regExp1->setPattern("^[a-zA-Zа-яА-Я0-9]{100}$");
    regExpValidator1 = new QRegExpValidator(*regExp1, this);
    regExp2 = new QRegExp;
    regExp2->setPattern("^[a-zA-Zа-яА-Я0-9]{10}$");
    regExpValidator2 = new QRegExpValidator(*regExp1, this);
    ui->extEdit->setValidator(regExpValidator2);
}

newfile::~newfile()
{
    delete regExp1;
    delete regExp2;
    delete ui;
}

void newfile::on_buttonBox_accepted()
{
    if (ui->lineEdit->text().isEmpty()){
        return;
    }
    if (ui->extEdit->text().isEmpty()){
        fileName = ui->lineEdit->text();
        accepted = true;
        return;
    }
    else {
        fileName = ui->lineEdit->text() +"." + ui->extEdit->text();
        accepted = true;
        return;
    }
}
