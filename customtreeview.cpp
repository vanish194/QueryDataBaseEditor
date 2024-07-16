#include "customtreeview.h"

CustomTreeView::CustomTreeView(QWidget *parent) : QTreeView(parent)
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(show_context_menu(const QPoint&)));
}

int CustomTreeView::selected_index()
{

    QModelIndex index= this->currentIndex();
    if(!index.isValid())
    {
        qDebug()<<"InValidindex";
        return -1;
    }
    QString index_data=index.data().toString();
    qDebug()<<index_data;
    qDebug() << "Row: " << index.row();
    qDebug() << "Column: " << index.column();
    int hierarchy_level = 0; // Устанавливаем начальное значение уровня иерархии

    QModelIndex parentIndex = index.parent();
    while (parentIndex.isValid()) {
        parentIndex = parentIndex.parent(); // Переходим к родительскому элементу
        hierarchy_level++; // Увеличиваем уровень иерархии
    }

    qDebug() << "Hierarchy level: " << hierarchy_level;
    return hierarchy_level;
}

#include "customtreeview.h"
