#include "contextmenu.h"

ContextMenu::ContextMenu(QObject *parent) : QObject(parent)
{
    menu = new QMenu();
    newMenu = new QMenu("New");

    OpenAction = new QAction(tr("&Open"), this);
    OpenAction->setToolTip("Open new folder/file");

    PrintAction = new QAction(tr("&Print file"), this);
    OpenAction->setToolTip("Print selected file");

    NewFileAction = new QAction(tr("&New File"), this);
    NewFileAction->setToolTip("Create new file");

    NewFolderAction = new QAction(tr("&New Folder"), this);
    NewFolderAction->setToolTip("Create new folder");

    CutAction = new QAction(tr("&Cut"), this);
    CutAction->setToolTip("Cut folder/file");

    CopyToClipboardAction = new QAction(tr("&Copy files to clipboard"), this);
    CopyToClipboardAction->setToolTip("Copy files to clipboard");

    CopyAction = new QAction(tr("&Copy"), this);
    CopyAction->setToolTip("Copy file/folder to another place");

    PasteAction = new QAction(tr("&Paste"), this);
    PasteAction->setToolTip("Paste file/folder in selected folder");

    PasteToRootAction = new QAction(tr("&Paste to root"), this);
    PasteToRootAction->setToolTip("Paste file/folder in current folder");

    DeleteAction = new QAction(tr("&Delete"), this);
    DeleteAction->setToolTip("Delete file/folder");

    RenameAction = new QAction(tr("&Rename"), this);
    RenameAction->setToolTip("Rename file/folder");

    InfoAction = new QAction(tr("&Properties"), this);
    InfoAction->setToolTip("Show info about file/folder");

    newMenu->addAction(NewFileAction);
    newMenu->addAction(NewFolderAction);
    menu->addAction(OpenAction);
    menu->addAction(PrintAction);
    menu->addMenu(newMenu);
    menu->addAction(CutAction);
    menu->addAction(CopyAction);
    menu->addAction(CopyToClipboardAction);
    menu->addAction(PasteAction);
    menu->addAction(PasteToRootAction);
    menu->addAction(DeleteAction);
    menu->addAction(RenameAction);
    menu->addAction(InfoAction);
}

ContextMenu::~ContextMenu()
{
    delete newMenu;
    delete menu;
}

QAction *ContextMenu::getOpenAction() const
{
    return OpenAction;
}

QAction *ContextMenu::getPrintAction() const
{
    return PrintAction;
}

QAction *ContextMenu::getNewFileAction() const
{
    return NewFileAction;
}

QAction *ContextMenu::getNewFolderAction() const
{
    return NewFolderAction;
}

QAction *ContextMenu::getCutAction() const
{
    return CutAction;
}

QAction *ContextMenu::getCopyAction() const
{
    return CopyAction;
}

QAction *ContextMenu::getCopyToClipboardAction() const
{
    return CopyToClipboardAction;
}

QAction *ContextMenu::getPasteAction() const
{
    return PasteAction;
}

QAction *ContextMenu::getPasteToRootAction() const
{
    return PasteToRootAction;
}

QAction *ContextMenu::getDeleteAction() const
{
    return DeleteAction;
}

QAction *ContextMenu::getRenameAction() const
{
    return RenameAction;
}

QAction *ContextMenu::getInfoAction() const
{
    return InfoAction;
}

QMenu *ContextMenu::getMenu() const
{
    return menu;
}
