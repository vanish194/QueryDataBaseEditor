#ifndef CUSTOMQUERYMODEL_H
#define CUSTOMQUERYMODEL_H

#include <QSqlQueryModel>

class CustomQueryModel : public QSqlQueryModel
{
public:
    explicit CustomQueryModel(QObject *parent = nullptr);
};

#endif // CUSTOMQUERYMODEL_H
