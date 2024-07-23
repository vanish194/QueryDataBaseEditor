#ifndef BLOBIMAGEDELEGATE_H
#define BLOBIMAGEDELEGATE_H

#include <QHeaderView>
#include <QImage>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QTableView>

class BlobImageDelegate : public QStyledItemDelegate
{
public:
    int column_index = -1;

    BlobImageDelegate(QObject *parent = nullptr)
        : QStyledItemDelegate(parent)
    {}

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override
    {
        if (index.column() == column_index) {
            QByteArray blobData = index.data(Qt::DisplayRole).toByteArray();
            QImage image;
            if (!blobData.isEmpty() && image.loadFromData(blobData) && !image.isNull()) {
                painter->save();
                painter->setRenderHint(QPainter::SmoothPixmapTransform);
                painter->drawImage(option.rect, image);
                painter->restore();
            } else {
                // Обработка случая, если изображение не загрузилось
                // Например, можно нарисовать пустое или стандартное место
            }
        } else {
            QStyledItemDelegate::paint(painter, option, index);
        }
    }

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        if (index.column() == column_index) {
            QImage image;
            QByteArray blobData = index.data(Qt::DisplayRole).toByteArray();
            if (!blobData.isEmpty() && image.loadFromData(blobData)) {
                return image.size();
            }
        }

        return QStyledItemDelegate::sizeHint(option, index);
    }

    int column_find_index(const QTableView *tableView, const QString &columnName)
    {
        QHeaderView *header = tableView->horizontalHeader();
        for (int i = 0; i < header->count(); ++i) {
            if (header->model()->headerData(i, Qt::Horizontal).toString() == columnName) {
                return i;
            }
        }
        return -1;
    }
};
#endif // BLOBIMAGEDELEGATE_H
