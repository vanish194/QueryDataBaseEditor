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
    QString condition=" sensor_name =\""+sensor_name+"\"";
    sensor_id=data_base_action->id_exist_data("sensor_id","sensors",condition);
    data_base_action->insert_main_mnemonics(main_mnemonic_id,main_mnemonic_name,main_mnemonic_description,sensor_id);
    data_base_action->database_refresh();
}

void MainMnemonicAddWindow::input_main_mnemonic_unit()
{
    input_main_mnemonic();
    main_mnemonic_unit_name=ui->lineEdit_main_mnemonic_unit_name->text();
    main_mnemonic_unit_description=ui->lineEdit_main_mnemonic_unit_description->text();
    main_mnemonic_unit_id=data_base_action->id_minimal_for_input("main_mnemonic_unit_id","main_mnemonic_units");
    data_base_action->insert_main_mnemonic_units(main_mnemonic_unit_id,main_mnemonic_unit_name,
                                                 main_mnemonic_unit_description,main_mnemonic_id);
    data_base_action->database_refresh();
}

void MainMnemonicAddWindow::receive_data_base_action(DataBaseAction *data_base_action2)
{
    data_base_action=data_base_action2;
    qDebug()<<"slot2";
    list_sensor_name= data_base_action->get_unique_values("sensor_name","sensors");
    foreach (const QString &value, list_sensor_name) {
        ui->comboBox_sensor_name->addItem(value);
    }
}

void MainMnemonicAddWindow::on_pushButton_INPUT_clicked()
{
    input_main_mnemonic_unit();
    ui->label_input_info->setText("Main mnemonic Added");
    ui->label_input_info->setStyleSheet("color: green");
}


void MainMnemonicAddWindow::on_pushButton_CLEAN_clicked()
{
    ui->lineEdit_main_mnemonic_name->setText("");
    ui->lineEdit_main_mnemonic_description->setText("");
    ui->lineEdit_main_mnemonic_unit_name->setText("");
    ui->lineEdit_main_mnemonic_unit_description->setText("");
    ui->label_input_info->setText("");
}

