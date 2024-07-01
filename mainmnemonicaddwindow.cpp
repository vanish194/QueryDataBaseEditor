#include "mainmnemonicaddwindow.h"
#include "ui_mainmnemonicaddwindow.h"

MainMnemonicAddWindow::MainMnemonicAddWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainMnemonicAddWindow)
{
    ui->setupUi(this);
}

MainMnemonicAddWindow::~MainMnemonicAddWindow()
{
    delete ui;
}

void MainMnemonicAddWindow::input_main_mnemonic()
{
    main_mnemonic_name=ui->lineEdit_main_mnemonic_name->text();
    main_mnemonic_description=ui->lineEdit_main_mnemonic_description->text();
    main_mnemonic_id=data_base_action->id_minimal_for_input("main_mnemonic_id","main_mnemonics");
    QString sensor_name=ui->comboBox_sensor_name->currentText();
    QString condition="sensor_name =\""+sensor_name+"\"";
    sensor_id=data_base_action->id_exist_data("sensor_id","sensors",condition);
    data_base_action->insert_main_mnemonics(main_mnemonic_id,main_mnemonic_name,main_mnemonic_description,sensor_id,unit_id);
    data_base_action->database_refresh();
}

void MainMnemonicAddWindow::input_type_of_unit()
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

void MainMnemonicAddWindow::input_unit()
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
void MainMnemonicAddWindow::receive_data_base_action(DataBaseAction *data_base_action2)
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

void MainMnemonicAddWindow::refreshed_bd_slot()
{
    qDebug()<<"slotrefMM";
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

void MainMnemonicAddWindow::on_pushButton_INPUT_clicked()
{
    input_type_of_unit();
    input_unit();
    input_main_mnemonic();
    ui->label_input_info->setText("Main mnemonic Added");
    ui->label_input_info->setStyleSheet("color: green");
    emit refreshing_bd();
}


void MainMnemonicAddWindow::on_pushButton_CLEAN_clicked()
{

}


void MainMnemonicAddWindow::on_comboBox_type_of_unit_currentTextChanged(const QString &arg1)
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


void MainMnemonicAddWindow::on_MainMnemonicAddWindow_finished()
{
    emit refreshing_bd();
}

