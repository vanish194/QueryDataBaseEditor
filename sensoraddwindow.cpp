#include "sensoraddwindow.h"
#include "ui_sensoraddwindow.h"

SensorAddWindow::SensorAddWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SensorAddWindow)
{
    ui->setupUi(this);
    ui->doubleSpinBox_offset->setMaximum(200.0);
}

SensorAddWindow::~SensorAddWindow()
{
    delete ui;
}

void SensorAddWindow::input_sensor()
{
    input_method();
    input_sensor_description();
    sensor_name=ui->lineEdit_sensor_name->text();

    //поиск существующего id
    QString condition=" tool_name =\""+tool_name+"\"";
    tool_id=data_base_action->id_exist_data("tool_id","tools",condition);
    qDebug()<<"tool id found";
    //sensor_id
    sensor_id=data_base_action->id_minimal_for_input("sensor_id","sensors");
    data_base_action->insert_sensors(sensor_id,sensor_name,tool_id,method_id,sensor_description_id);

    data_base_action->database_refresh();

}

void SensorAddWindow::input_method()
{
    method_name=ui->comboBox_method_name->currentText();
    if(ui->comboBox_method_name->findText(method_name)==-1)  {
        method_id=data_base_action->id_minimal_for_input("method_id","methods");
        data_base_action->insert_methods(method_id,method_name);
        qDebug()<<"method_name not exist";
    }
    else    {
        QString condition=" method_name =\""+method_name+"\"";
        method_id=data_base_action->id_exist_data("method_id","methods",condition);
        qDebug()<<"method_name exist";
    }
    data_base_action->database_refresh();
}

void SensorAddWindow::input_sensor_description()
{
    offset=ui->doubleSpinBox_offset->text();
    sensor_description=ui->lineEdit_sensor_name->text();
    sensor_description_id=data_base_action->id_minimal_for_input("sensor_description_id","sensor_descriptions");
    data_base_action->insert_sensor_descriptions(sensor_description_id,sensor_description,offset);
    data_base_action->database_refresh();
}

void SensorAddWindow::receive_data_base_action(DataBaseAction *data_base_action2)
{
    data_base_action=data_base_action2;
    qDebug()<<"slot2";
    list_method_name= data_base_action->get_unique_values("method_name","methods");
    foreach (const QString &value, list_method_name) {
        ui->comboBox_method_name->addItem(value);
    }
    list_tool_name= data_base_action->get_unique_values("tool_name","tools");
    foreach (const QString &value, list_tool_name) {
        ui->comboBox_tool_name->addItem(value);
    }
}


void SensorAddWindow::on_pushButton_INPUT_clicked()
{
    input_sensor();
    ui->label_input_info->setText("Sensor Added");
    ui->label_input_info->setStyleSheet("color: green");
}


void SensorAddWindow::on_pushButton_CLEAN_clicked()
{
    ui->lineEdit_sensor_description->setText("");
    ui->lineEdit_sensor_name->setText("");
    ui->doubleSpinBox_offset->setValue(0.0);
    ui->comboBox_method_name->setCurrentText("");
    ui->label_input_info->setText("");
}

