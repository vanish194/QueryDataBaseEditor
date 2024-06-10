#ifndef BLOBIMAGEDELEGATE_H
#define BLOBIMAGEDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QImage>
#include <QTableView>

class BlobImageDelegate : public QStyledItemDelegate
{
public:
    int column_index=-1;

    BlobImageDelegate(QObject *parent = 0) : QStyledItemDelegate(parent) {};
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        if (index.column() == column_index) {
            QByteArray blobData = index.data(Qt::DisplayRole).toByteArray();
            QImage image;
            image.loadFromData(blobData);

            painter->save();
            painter->setRenderHint(QPainter::SmoothPixmapTransform);
            painter->drawImage(option.rect, image);
            painter->restore();

        } else {
            QStyledItemDelegate::paint(painter, option, index);

        }
    }

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        if (index.column() == column_index) {
            QImage image;
            image.loadFromData(index.data(Qt::DisplayRole).toByteArray());
            return image.size();
        }

        return QStyledItemDelegate::sizeHint(option, index);
    }
    int column_fiend_index(const QTableView *tableView, const QString &columnName)
    {
        QHeaderView* header = tableView->horizontalHeader();
        for (int i = 0; i < header->count(); ++i) {
            if (header->model()->headerData(i, Qt::Horizontal).toString() == columnName) {
                return i;
            }
        }
        return -1; // Если столбец с указанным именем не был найден
    }
};
#endif // BLOBIMAGEDELEGATE_H
