#include "updatesensor.h"
#include "ui_updatesensor.h"

UpdateSensor::UpdateSensor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UpdateSensor)
{
    ui->setupUi(this);
    ui->doubleSpinBox_offset->setMaximum(50.0);
    ui->doubleSpinBox_offset->setSuffix("m");
}

UpdateSensor::~UpdateSensor()
{
    delete ui;
}

void UpdateSensor::recieve_data_name(QString &sensor_name_)
{
    sensor_name = sensor_name_;
    search_current_data();
    completion_data();
}

void UpdateSensor::receive_data_base_action(DataBaseAction *data_base_action2)
{
    data_base_action = data_base_action2;
    list_method_name.clear();
    ui->comboBox_method_name->clear();
    list_method_name = data_base_action->get_unique_values("method_name", "methods");
    foreach (const QString &value, list_method_name) {
        ui->comboBox_method_name->addItem(value);
    }
    list_tool_name.clear();
    ui->comboBox_tool_name->clear();
    list_tool_name = data_base_action->get_unique_values("tool_name", "tools");
    foreach (const QString &value, list_tool_name) {
        ui->comboBox_tool_name->addItem(value);
    }
}

void UpdateSensor::on_pushButton_INPUT_clicked()
{
    input_method();
    updating_data();
    data_base_action->update_sensor(sensor_id,
                                    sensor_name,
                                    tool_id,
                                    method_id,
                                    sensor_description_id,
                                    sensor_description,
                                    offset);
    data_base_action->database_refresh();
    ui->label_input_info->setText("Sensor Update");
    receive_data_base_action(data_base_action);
}

void UpdateSensor::on_pushButton_CLEAN_clicked()
{
    completion_data();
    ui->label_input_info->setText("");
}

void UpdateSensor::input_method()
{
    method_name = ui->comboBox_method_name->currentText();
    if (ui->comboBox_method_name->findText(method_name) == -1) {
        method_id = data_base_action->id_minimal_for_input("method_id", "methods");
        data_base_action->insert_methods(method_id, method_name);
        qDebug() << "method_name not exist";
    } else {
        QString condition = " method_name =\"" + method_name + "\"";
        method_id = data_base_action->id_exist_data("method_id", "methods", condition);
        qDebug() << "method_name exist";
    }
    data_base_action->database_refresh();
}

void UpdateSensor::search_current_data()
{
    QString condition = "sensor_name= \"" + sensor_name + "\"";
    sensor_id = data_base_action->id_exist_data("sensor_id", "sensors", condition);

    condition = "sensor_id = " + QString::number(sensor_id) + "";
    sensor_description_id = data_base_action->id_exist_data("sensor_description_id",
                                                            "sensors",
                                                            condition);
    tool_id = data_base_action->id_exist_data("tool_id", "sensors", condition);
    method_id = data_base_action->id_exist_data("method_id", "sensors", condition);

    condition = "tool_id = \"" + QString::number(tool_id) + "\"";
    tool_name = data_base_action->find_with_condition("tool_name", "tools", condition);

    condition = "method_id = \"" + QString::number(method_id) + "\"";
    method_name = data_base_action->find_with_condition("method_name", "methods", condition);

    condition = "sensor_description_id = " + QString::number(sensor_description_id) + "";
    sensor_description = data_base_action->find_with_condition("sensor_description",
                                                               "sensor_descriptions",
                                                               condition);
    offset = data_base_action->find_with_condition("offset", "sensor_descriptions", condition);
}

void UpdateSensor::completion_data()
{
    ui->comboBox_tool_name->setCurrentText(tool_name);
    ui->comboBox_method_name->setCurrentText(method_name);
    ui->lineEdit_sensor_name->setText(sensor_name);
    ui->lineEdit_sensor_description->setText(sensor_description);
    double o_v = offset.left(offset.length() - 1).toDouble();
    ui->doubleSpinBox_offset->setValue(o_v);
}

void UpdateSensor::updating_data()
{
    tool_name = ui->comboBox_tool_name->currentText();
    QString condition = " tool_name =\"" + tool_name + "\"";
    tool_id = data_base_action->id_exist_data("tool_id", "tools", condition);
    sensor_name = ui->lineEdit_sensor_name->text();
    sensor_description = ui->lineEdit_sensor_description->text();
    offset = ui->doubleSpinBox_offset->text();
}
