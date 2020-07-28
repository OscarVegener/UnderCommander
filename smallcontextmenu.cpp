#include "smallcontextmenu.h"

SmallContextMenu::SmallContextMenu(QObject *parent) : QObject(parent)
{
    menu = new QMenu();
    newMenu = new QMenu("New");

    NewFileAction = new QAction(tr("&New File"), this);
    NewFileAction->setToolTip("Create new file");

    NewFolderAction = new QAction(tr("&New Folder"), this);
    NewFolderAction->setToolTip("Create new folder");

    PasteToRootAction = new QAction(tr("&Paste to root"), this);
    PasteToRootAction->setToolTip("Paste file/folder in current folder");

    InfoAction = new QAction(tr("&Properties"), this);
    InfoAction->setToolTip("Show info about file/folder");

    newMenu->addAction(NewFileAction);
    newMenu->addAction(NewFolderAction);
    menu->addMenu(newMenu);
    menu->addAction(PasteToRootAction);
    menu->addAction(InfoAction);
}

SmallContextMenu::~SmallContextMenu()
{
    delete newMenu;
    delete menu;
}

QAction *SmallContextMenu::getNewFileAction() const
{
    return NewFileAction;
}

QAction *SmallContextMenu::getNewFolderAction() const
{
    return NewFolderAction;
}

QAction *SmallContextMenu::getPasteToRootAction() const
{
    return PasteToRootAction;
}

QAction *SmallContextMenu::getInfoAction() const
{
    return InfoAction;
}
