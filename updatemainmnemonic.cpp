#include "updatemainmnemonic.h"
#include "ui_updatemainmnemonic.h"

UpdateMainMnemonic::UpdateMainMnemonic(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UpdateMainMnemonic)
{
    ui->setupUi(this);
}

UpdateMainMnemonic::~UpdateMainMnemonic()
{
    delete ui;
}

void UpdateMainMnemonic::recieve_data_name(QString &main_mnemonic_)
{
    main_mnemonic_name=main_mnemonic_;
    search_current_data();
    completion_data();
}

void UpdateMainMnemonic::receive_data_base_action(DataBaseAction *data_base_action2)
{
    data_base_action=data_base_action2;
    list_sensor_name.clear();
    list_type_name.clear();
    list_unit_name.clear();
    ui->comboBox_sensor_name->clear();
    ui->comboBox_type_of_unit->clear();
    ui->comboBox_unit->clear();
    list_sensor_name= data_base_action->get_unique_values("sensor_name","sensors");
    foreach (const QString &value, list_sensor_name) {
        ui->comboBox_sensor_name->addItem(value);
    }
    list_type_name= data_base_action->get_unique_values("type_name","types_of_units");
    foreach (const QString &value, list_type_name) {
        ui->comboBox_type_of_unit->addItem(value);
    }
}

void UpdateMainMnemonic::on_comboBox_type_of_unit_currentTextChanged(const QString &arg1)
{
    QString condition="type_name =\""+arg1+"\"";
    type_id=data_base_action->id_exist_data("type_id","types_of_units",condition);
    condition="type_id =\""+QString::number(type_id)+"\"";
    list_unit_name.clear();
    ui->comboBox_unit->clear();
    list_unit_name=data_base_action->get_unique_values_with_condition("unit_name","units",condition);
    foreach (const QString &value, list_unit_name) {
        ui->comboBox_unit->addItem(value);
    }
}

void UpdateMainMnemonic::input_type_of_unit()
{
    type_name=ui->comboBox_type_of_unit->currentText();
    if(ui->comboBox_type_of_unit->findText(type_name)==-1)  {
        qDebug()<<"type_name not exist";
        type_id=data_base_action->id_minimal_for_input("type_id","types_of_units");
        data_base_action->insert_types_of_units(type_id,type_name);

    }
    else    {
        qDebug()<<"type_name exist";
        QString condition="type_name =\""+type_name+"\"";
        type_id=data_base_action->id_exist_data("type_id","types_of_units",condition);//менять функцию

    }
    data_base_action->database_refresh();
}

void UpdateMainMnemonic::input_unit()
{
    unit_name=ui->comboBox_unit->currentText();
    if(ui->comboBox_unit->findText(unit_name)==-1)  {
        qDebug()<<"unit_name not exist";
        unit_id=data_base_action->id_minimal_for_input("unit_id","units");
        data_base_action->insert_units(unit_id,unit_name,type_id);
    }
    else    {
        qDebug()<<"unit_name exist";
        QString condition="unit_name =\""+unit_name+"\"";
        unit_id=data_base_action->id_exist_data("unit_id","units",condition);//менять функцию
    }
    data_base_action->database_refresh();
}
void UpdateMainMnemonic::on_pushButton_INPUT_clicked()
{
    input_type_of_unit();
    input_unit();
    updating_data();
    data_base_action->update_main_mnemonic(main_mnemonic_id,main_mnemonic_name,main_mnemonic_description,sensor_id,unit_id);
    ui->label_input_info->setText("MainMnemonic Updated");
    data_base_action->database_refresh();
    receive_data_base_action(data_base_action);
}


void UpdateMainMnemonic::on_pushButton_CLEAN_clicked()
{
    completion_data();
    ui->label_input_info->setText("");
}

void UpdateMainMnemonic::search_current_data()
{
    QString condition="main_mnemonic_name= \"" + main_mnemonic_name +"\"";
    main_mnemonic_id=data_base_action->id_exist_data("main_mnemonic_id","main_mnemonics",condition);

    condition="main_mnemonic_id = "+QString::number(main_mnemonic_id)+"";
    main_mnemonic_description=data_base_action->find_with_condition("main_mnemonic_description","main_mnemonics",condition);

    sensor_id=data_base_action->id_exist_data("sensor_id","main_mnemonics",condition);

    unit_id=data_base_action->id_exist_data("unit_id","main_mnemonics",condition);

    condition="unit_id = "+QString::number(unit_id)+"";
    unit_name=data_base_action->find_with_condition("unit_name","units",condition);

    type_id=data_base_action->id_exist_data("type_id","units",condition);

    condition="type_id = "+QString::number(type_id)+"";
    type_name=data_base_action->find_with_condition("type_name","types_of_units",condition);

    condition="sensor_id = "+QString::number(sensor_id)+"";
    sensor_name=data_base_action->find_with_condition("sensor_name","sensors",condition);


}

void UpdateMainMnemonic::completion_data()
{
    ui->comboBox_sensor_name->setCurrentText(sensor_name);
    ui->lineEdit_main_mnemonic_name->setText(main_mnemonic_name);
    ui->lineEdit_main_mnemonic_description->setText(main_mnemonic_description);
    ui->comboBox_type_of_unit->setCurrentText(type_name);
    ui->comboBox_unit->setCurrentText(unit_name);
}

void UpdateMainMnemonic::updating_data()
{
    main_mnemonic_name=ui->lineEdit_main_mnemonic_name->text();
    main_mnemonic_description=ui->lineEdit_main_mnemonic_description->text();
    sensor_name=ui->comboBox_sensor_name->currentText();
    QString condition="sensor_name= \"" + sensor_name +"\"";
    sensor_id=data_base_action->id_exist_data("sensor_id","sensors",condition);
}

