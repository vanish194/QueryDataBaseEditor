#ifndef UPDATESENSOR_H
#define UPDATESENSOR_H

#include <QDialog>
#include "databaseaction.h"

namespace Ui {
class UpdateSensor;
}

class UpdateSensor : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateSensor(QWidget *parent = nullptr);
    ~UpdateSensor();
public slots:
    void recieve_data_name(QString& sensor_name_);

    void receive_data_base_action(DataBaseAction *data_base_action2);

private slots:
    void on_pushButton_INPUT_clicked();

    void on_pushButton_CLEAN_clicked();

private:
    Ui::UpdateSensor *ui;
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

    void search_current_data();
    void completion_data();

    void updating_data();
};

#endif // UPDATESENSOR_H
