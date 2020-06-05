#include "newfolder.h"
#include "ui_newfolder.h"

newfolder::newfolder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newfolder)
{
    ui->setupUi(this);
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    regExp = new QRegExp;
    regExp->setPattern("^[a-zA-Zа-яА-Я0-9]{100}$");
    regExpValidator = new QRegExpValidator(*regExp, this);
    ui->lineEdit->setValidator(regExpValidator);
}

newfolder::~newfolder()
{
    delete regExp;
    delete regExpValidator;
    delete ui;
}

void newfolder::on_buttonBox_accepted()
{
    if (ui->lineEdit->text().isEmpty()){
        return;
    }
    pathName = ui->lineEdit->text();
    accepted = true;
}
