#ifndef FSVIEW_H
#define FSVIEW_H

#include <QTreeView>
#include <QDragEnterEvent>
#include <QAbstractItemView>
#include <QHeaderView>

class FSView : public QTreeView
{
    Q_OBJECT
public:
    FSView(QWidget *parent = nullptr) : QTreeView(parent) {}
    void init();
private:
    virtual void mousePressEvent(QMouseEvent *event) override;
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    virtual void dropEvent(QDropEvent *e) override;
signals:
    void selectionClearedSignal();
};

#endif // FSVIEW_H
