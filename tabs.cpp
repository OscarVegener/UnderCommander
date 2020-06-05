#include "tabs.h"

tabs::tabs()
{

}

void tabs::setCurrentTab(int c){
    currentTab = c;
}

void tabs::createTab(const QString name)
{
    paths.push_back(name);
    //qDebug() << name;
    QFileInfo fileInfo;
    fileInfo.setFile(name);
    if (fileInfo.fileName() != ""){
        this->addTab(fileInfo.fileName());
    }
    else{
        QString newName;
        newName.push_back(name.at(0));
        newName.push_back(name.at(1));
        this->addTab(newName);
    }

}

QString tabs::savedPath(int index)
{
    QString path = paths.takeAt(index);
    paths.insert(index, path);
    return path;
}

void tabs::resetTab(int index, QString name)
{
    paths.removeAt(index);
    paths.insert(index, name);
    QFileInfo fileInfo;
    fileInfo.setFile(name);
    if (fileInfo.fileName() != ""){
        this->setTabText(currentTab, fileInfo.fileName());
    }
    else{
        QString newName = name;
        newName.remove("/");
        this->setTabText(currentTab, newName);
    }
}

void tabs::deleteTab(int index)
{
    paths.removeAt(index);
    this->removeTab(index);
}

int tabs::getCurrentTab()
{
    return currentTab;
}

void tabs::changeTabName(const QString &name)
{
    QFileInfo fileInfo;
    fileInfo.setFile(name);
    paths.removeAt(currentTab);
    paths.insert(currentTab, name);
    //qDebug() << paths;
    if (fileInfo.fileName() != ""){
        this->setTabText(currentTab, fileInfo.fileName());
    }
    else{
        QString newName = name;
        newName.remove("/");
        this->setTabText(currentTab, newName);
    }
}

void tabs::wheelEvent(QWheelEvent *event)
{
    event->ignore();
}

void tabs::init(const QString name)
{
    this->setExpanding(false);
    this->setSelectionBehaviorOnRemove(SelectLeftTab);
    this->createTab(name);
}
