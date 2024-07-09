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
        connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(show_context_menu(const QPoint&)));
    }

private:
    void set_heasers();
private slots:
    void show_context_menu(const QPoint &pos)
    {
        QMenu context_menu(tr("Context Menu"), this);

        QAction *add_action = context_menu.addAction("Add");
        QAction *edit_action = context_menu.addAction("Edit");
        QAction *remove_action = context_menu.addAction("Remove");

        connect(add_action, SIGNAL(triggered()), this, SLOT(on_add()));
        connect(edit_action, SIGNAL(triggered()), this, SLOT(on_edit()));
        connect(remove_action, SIGNAL(triggered()), this, SLOT(on_remove()));

        context_menu.exec(mapToGlobal(pos));
    }

    void on_add()
    {
        // Действия при выборе "Add"
        qDebug() << "Add clicked";
    }

    void on_edit()
    {
        // Действия при выборе "Edit"
        qDebug() << "Edit clicked";
    }

    void on_remove()
    {
        // Действия при выборе "Remove"
        qDebug() << "Remove clicked";
    }
};
#endif // CUSTOMTREEVIEW_H
