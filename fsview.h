#ifndef FSVIEW_H
#define FSVIEW_H

#include <QTreeView>
#include <QDragEnterEvent>
#include <QAbstractItemView>
#include <QHeaderView>

#include "undercommander.h"

class FSView : public QTreeView
{
public:
    FSView(QWidget *parent = nullptr) : QTreeView(parent) {}
    void init();
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    virtual void dropEvent(QDropEvent *e) override;
};

#endif // FSVIEW_H
