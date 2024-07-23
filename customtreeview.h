#ifndef CUSTOMTREEVIEW_H
#define CUSTOMTREEVIEW_H

#include <QAction>
#include <QMenu>
#include <QMouseEvent>
#include <QTreeView>

class CustomTreeView : public QTreeView
{
    Q_OBJECT

public:
    CustomTreeView(QWidget *parent = nullptr);
    enum signaltype { Add, Edit, Remove };

private:
    int selected_index();
private slots:
    void show_context_menu(const QPoint &pos)
    {
        QMenu context_menu(tr("Context Menu"), this);

        QAction *add_action = context_menu.addAction("Add");
        QAction *edit_action = context_menu.addAction("Edit");
        QAction *remove_action = context_menu.addAction("Remove");

        connect(add_action, &QAction::triggered, this, &CustomTreeView::on_add);
        connect(edit_action, &QAction::triggered, this, &CustomTreeView::on_edit);
        connect(remove_action, &QAction::triggered, this, &CustomTreeView::on_remove);

        context_menu.exec(mapToGlobal(pos));
    }

    void on_add()
    {
        // Действия при выборе "Add"
        qDebug() << "Add clicked";
        int hierarchy_level = selected_index();
        if (hierarchy_level != -1) {
            emit context_menu_signal(hierarchy_level, signaltype::Add);
        }
    }

    void on_edit()
    {
        // Действия при выборе "Edit"
        qDebug() << "Edit clicked";
        int hierarchy_level = selected_index();
        if (hierarchy_level != -1) {
            emit context_menu_signal(hierarchy_level, signaltype::Edit);
        }
    }

    void on_remove()
    {
        // Действия при выборе "Remove"
        qDebug() << "Remove clicked";
        int hierarchy_level = selected_index();
        if (hierarchy_level != -1) {
            emit context_menu_signal(hierarchy_level, signaltype::Remove);
        }
    }
signals:
    void context_menu_signal(const int &hierarchy_level, signaltype signal_code);
};
#endif // CUSTOMTREEVIEW_H
