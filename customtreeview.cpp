#include "customtreeview.h"

CustomTreeView::CustomTreeView(QWidget *parent)
    : QTreeView(parent)
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,
            &CustomTreeView::customContextMenuRequested,
            this,
            &CustomTreeView::show_context_menu);
}

int CustomTreeView::selected_index()
{
    QModelIndex index = this->currentIndex();
    if (!index.isValid()) {
        qDebug() << "InValidindex";
        return -1;
    }
    QString index_data = index.data().toString();
    int hierarchy_level = 0;
    QModelIndex parentIndex = index.parent();
    while (parentIndex.isValid()) {
        parentIndex = parentIndex.parent();
        hierarchy_level++;
    }
    return hierarchy_level;
}

#include "customtreeview.h"
