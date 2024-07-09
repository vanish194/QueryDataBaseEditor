#ifndef CUSTOMTREEVIEW_H
#define CUSTOMTREEVIEW_H

#include <QTreeView>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>

class CustomTreeView : public QTreeView
{
    Q_OBJECT

public:
    CustomTreeView(QWidget *parent = nullptr) : QTreeView(parent)
    {
        setContextMenuPolicy(Qt::CustomContextMenu);
        connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
    }

private slots:
    void showContextMenu(const QPoint &pos)
    {
        QMenu contextMenu(tr("Context Menu"), this);

        QAction *addAction = contextMenu.addAction("Add");
        QAction *editAction = contextMenu.addAction("Edit");
        QAction *removeAction = contextMenu.addAction("Remove");

        connect(addAction, SIGNAL(triggered()), this, SLOT(onAdd()));
        connect(editAction, SIGNAL(triggered()), this, SLOT(onEdit()));
        connect(removeAction, SIGNAL(triggered()), this, SLOT(onRemove()));

        contextMenu.exec(mapToGlobal(pos));
    }

    void onAdd()
    {
        // Действия при выборе "Add"
        qDebug() << "Add clicked";
    }

    void onEdit()
    {
        // Действия при выборе "Edit"
        qDebug() << "Edit clicked";
    }

    void onRemove()
    {
        // Действия при выборе "Remove"
        qDebug() << "Remove clicked";
    }
};
#endif // CUSTOMTREEVIEW_H
