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
    DataBaseAction *data_base_action;
    QList<QString> list_tool_name;
    QList<QString> list_method_name;

    QString sensor_name;
    QString sensor_description;
    QString offset;
    QString method_name;
    QString tool_name;

    int sensor_id;
    int method_id;
    int tool_id;
    int sensor_description_id;
    void input_sensor();
    void input_method();
    void input_sensor_description();
public slots:
    void receive_data_base_action(DataBaseAction *data_base_action2);
private slots:
    void on_pushButton_INPUT_clicked();
    void on_pushButton_CLEAN_clicked();
};

#endif // SENSORADDWINDOW_H
