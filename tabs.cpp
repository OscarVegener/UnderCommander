#include "tabs.h"

tabs::tabs(const QString name, ModelViewController *controller, const QString defaultPath, QWidget *parent) : QTabBar(parent){
    if (controller != nullptr){
        Controller = controller;
        DefaultPath = defaultPath;
        tabMenu = new QMenu(this);
        Id = objectCount++;
        deleteAction = new QAction(tr("Delete tab"), this);
        connect(deleteAction, &QAction::triggered, this, &tabs::contextDeleteTab);
        tabMenu->addAction(deleteAction);
        setContextMenuPolicy(Qt::CustomContextMenu);
        connect(this, &tabs::tabBarClicked, this, &tabs::tabClicked);
        connect(this, &tabs::customContextMenuRequested, this, &tabs::showContextMenu);
        hide();
        init(name);
    }
    else{
        emit argumentIsNullSignal(createIdMessage("Argument in \"tabs\" is nullptr."));
    }
}

int tabs::objectCount= 0;

void tabs::setCurrentTab(int c){
    currentTab = c;
}

void tabs::createTab(const QString name)
{
    paths.push_back(name);
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
    removeTab(index);
}

int tabs::getCurrentTab() const
{
    return currentTab;
}

void tabs::changeTabName(const QString &name)
{
    QFileInfo fileInfo;
    fileInfo.setFile(name);
    paths.removeAt(currentTab);
    paths.insert(currentTab, name);
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

ModelViewController *tabs::getController() const
{
    return Controller;
}

void tabs::setController(ModelViewController *value)
{
    Controller = value;
}

QString tabs::getDefaultPath() const
{
    return DefaultPath;
}

void tabs::setDefaultPath(const QString &value)
{
    DefaultPath = value;
}

void tabs::tabClicked(int index)
{
    if (index >= 0){
        setCurrentIndex(index);
        setCurrentTab(index);
        QString path = savedPath(index);
        QDir dir(path);
        if (dir.exists()){
            Controller->go(path);
        }
        else{
            Controller->go(DefaultPath);
            emit incorrectPathSignal(path);
        }
    }
}

void tabs::showContextMenu(QPoint pos)
{
    if (count() == 1){
        deleteAction->setEnabled(false);
    }
    else{
        deleteAction->setEnabled(true);
    }
    tabMenu->popup(QCursor::pos());
}

void tabs::contextDeleteTab()
{
    deleteTab(currentIndex());
    int index = currentIndex();
    setCurrentTab(index);
    QString path = savedPath(index);
    QDir dir(path);
    if (dir.exists()){
        Controller->go(path);
    }
    else{
        Controller->go(DefaultPath);
        emit incorrectPathSignal(path);
    }
}

QString tabs::createIdMessage(QString m)
{
    return "{Id: " + QString::number(Id) + "} " + m;
}
