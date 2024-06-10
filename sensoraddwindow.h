#ifndef SENSORADDWINDOW_H
#define SENSORADDWINDOW_H

#include <QDialog>
#include "databaseaction.h"
namespace Ui {
class SensorAddWindow;
}

class SensorAddWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SensorAddWindow(QWidget *parent = nullptr);
    ~SensorAddWindow();

private:
    Ui::SensorAddWindow *ui;
};

#endif // SENSORADDWINDOW_H
