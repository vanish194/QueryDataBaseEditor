#include "sensoraddwindow.h"
#include "ui_sensoraddwindow.h"

SensorAddWindow::SensorAddWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SensorAddWindow)
{
    ui->setupUi(this);
}

SensorAddWindow::~SensorAddWindow()
{
    delete ui;
}
