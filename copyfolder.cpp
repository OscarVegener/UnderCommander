#include "copyfolder.h"
#include "ui_copyfolder.h"

copyFolder::copyFolder(const int index, const QString &sPath, const QString &dPath, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::copyFolder)
{
    ui->setupUi(this);
    switch (index) {
        case 0: ui->pushButton->setText("To right panel"); break;
        case 1: ui->pushButton->setText("To left panel"); break;
    }
    this->sPath = sPath;
    this->dPath = dPath;
    ui->lineEdit->setText(sPath);
}

copyFolder::~copyFolder()
{
    delete ui;
}

void copyFolder::on_pushButton_clicked()
{
    ui->lineEdit_2->setText(dPath);
}
