#ifndef CUSTOMTABLEVIEW_H
#define CUSTOMTABLEVIEW_H

#include <QTableView>
#include <QHeaderView>
#include "blobimagedelegate.h"
class CustomTableView : public QTableView
{
public:
    CustomTableView();

    void blob_tableview_init();
};

#endif // CUSTOMTABLEVIEW_H
