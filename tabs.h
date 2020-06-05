#ifndef TABS_H
#define TABS_H

#include <QTabBar>
#include <QFileInfo>
#include <QDebug>
#include <QWheelEvent>

class tabs : public QTabBar
{
public:
    tabs();
    tabs(const QString name, QWidget *parent = nullptr) : QTabBar(parent){
        init(name);
    }
    void setCurrentTab(int c);
    void createTab(const QString name);
    QString savedPath(int index);
    void resetTab(int index, QString name);
    void deleteTab(int index);
    int getCurrentTab();
public slots:
    void changeTabName(const QString &name);
private:
    virtual void wheelEvent(QWheelEvent *event) override;
    void init(const QString name);
    int currentTab = 0;
    QStringList paths;
};

#endif // TABS_H

