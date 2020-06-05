#ifndef COPYFOLDER_H
#define COPYFOLDER_H

#include <QDialog>

namespace Ui {
class copyFolder;
}

class copyFolder : public QDialog
{
    Q_OBJECT

public:
    explicit copyFolder(const int index, const QString &sPath, const QString &dPath, QWidget *parent = nullptr);
    ~copyFolder();

private slots:
    void on_pushButton_clicked();

private:
    Ui::copyFolder *ui;
    QString sPath;
    QString dPath;
    int index;
};

#endif // COPYFOLDER_H
