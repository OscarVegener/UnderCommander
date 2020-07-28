#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QObject>
#include <QMenu>

class ContextMenu : public QObject
{
    Q_OBJECT
public:
    explicit ContextMenu(QObject *parent = nullptr);
    ~ContextMenu();

    QAction *getOpenAction() const;

    QAction *getPrintAction() const;

    QAction *getNewFileAction() const;

    QAction *getNewFolderAction() const;

    QAction *getCutAction() const;

    QAction *getCopyAction() const;

    QAction *getCopyToClipboardAction() const;

    QAction *getPasteAction() const;

    QAction *getPasteToRootAction() const;

    QAction *getDeleteAction() const;

    QAction *getRenameAction() const;

    QAction *getInfoAction() const;

private:
    QMenu *menu;
    QMenu *newMenu;
    QAction *OpenAction;
    QAction *PrintAction;
    QAction *NewFileAction;
    QAction *NewFolderAction;
    QAction *CutAction;
    QAction *CopyAction;
    QAction *CopyToClipboardAction;
    QAction *PasteAction;
    QAction *PasteToRootAction;
    QAction *DeleteAction;
    QAction *RenameAction;
    QAction *InfoAction;
};

#endif // CONTEXTMENU_H
