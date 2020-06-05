#include "fsview.h"

void FSView::init()
{
    this->setIndentation(0);
    this->setSelectionBehavior (QAbstractItemView::SelectRows);
    this->setSortingEnabled(true);
    this->sortByColumn(0, Qt::AscendingOrder);
    this->setItemsExpandable(false);
    this->hideColumn(1);
    this->hideColumn(2);
    this->hideColumn(3);
    this->setUniformRowHeights(true);
    this->setExpandsOnDoubleClick(false);
}

void FSView::dragEnterEvent(QDragEnterEvent *event){
    //FSView::setDragDropOverwriteMode(true);
    event->acceptProposedAction();
}

void FSView::dropEvent(QDropEvent *e)
{
    e->setDropAction(Qt::MoveAction);
    QTreeView::dropEvent(e);
}
