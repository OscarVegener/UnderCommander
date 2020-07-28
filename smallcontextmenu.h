#ifndef SMALLCONTEXTMENU_H
#define SMALLCONTEXTMENU_H

#include <QObject>
#include <QMenu>

class SmallContextMenu : public QObject
{
    Q_OBJECT
public:
    explicit SmallContextMenu(QObject *parent = nullptr);
    ~SmallContextMenu();

    QAction *getNewFileAction() const;

    QAction *getNewFolderAction() const;

    QAction *getPasteToRootAction() const;

    QAction *getInfoAction() const;

private:
    QMenu *menu;
    QMenu *newMenu;
    QAction *NewFileAction;
    QAction *NewFolderAction;
    QAction *PasteToRootAction;
    QAction *InfoAction;
signals:

};

#endif // SMALLCONTEXTMENU_H
