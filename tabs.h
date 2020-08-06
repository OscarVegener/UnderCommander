#ifndef TABS_H
#define TABS_H

#include <QTabBar>
#include <QFileInfo>
#include <QDebug>
#include <QWheelEvent>
#include <QMenu>
#include <QDir>
#include "modelviewcontroller.h"

class tabs : public QTabBar
{
    Q_OBJECT
public:
    tabs(const QString name, ModelViewController *controller, const QString defaultPath = "C:\\", QWidget *parent = nullptr);

    QString getDefaultPath() const;
    void setDefaultPath(const QString &value);

    void createTab(const QString name);

    ModelViewController *getController() const;
    void setController(ModelViewController *value);

public slots:
    void changeTabName(const QString &name);
private:
    virtual void wheelEvent(QWheelEvent *event) override;
    void init(const QString name);
    int currentTab = 0;
    QStringList paths;
    QMenu *tabMenu;
    QAction *deleteAction;
    QString DefaultPath;
    ModelViewController *Controller;
    int Id;
    static int objectCount;
    void setCurrentTab(int c);
    QString savedPath(int index);
    void resetTab(int index, QString name);
    void deleteTab(int index);
    int getCurrentTab() const;
    void tabClicked(int index);
    void showContextMenu(QPoint pos);

    void contextDeleteTab();
    QString createIdMessage(QString m);
signals:
    void argumentIsNullSignal(const QString &message);
    void incorrectPathSignal(const QString &path);
    void changePathSignal(const QString &path);
};

#endif // TABS_H

