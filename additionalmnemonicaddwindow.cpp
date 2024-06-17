#include "additionalmnemonicaddwindow.h"
#include "ui_additionalmnemonicaddwindow.h"

AdditionalMnemonicAddWindow::AdditionalMnemonicAddWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AdditionalMnemonicAddWindow)
{
    ui->setupUi(this);
}

AdditionalMnemonicAddWindow::~AdditionalMnemonicAddWindow()
{
    qDebug()<<"-addmnem";
    delete ui;
}

void AdditionalMnemonicAddWindow::input_conversion_formula()
{
    conversion_formula=ui->lineEdit_coversion_formula->text();
    conversion_formula_id=data_base_action->id_minimal_for_input("conversion_formula_id","conversion_formulas");
    qDebug()<<conversion_formula_id;
    qDebug()<<conversion_formula;
    data_base_action->insert_conversion_formulas(conversion_formula_id,conversion_formula);
    data_base_action->database_refresh();
}

void AdditionalMnemonicAddWindow::input_company()
{
    company_name=ui->comboBox_company_name->currentText();

    if(ui->comboBox_company_name->findText(company_name)==-1)  {
        company_id=data_base_action->id_minimal_for_input("company_id","companies");
        data_base_action->insert_companies(company_id,company_name);
        qDebug()<<"company_name not exist";
    }
    else    {
        QString condition="company_name =\""+company_name+"\"";
        company_id=data_base_action->id_exist_data("company_id","companies",condition);
        qDebug()<<"company_name exist";
    }
    data_base_action->database_refresh();
}

void AdditionalMnemonicAddWindow::input_additional_mnemonic()
{
    input_company();//company_id
    additional_mnemonic_name=ui->lineEdit_addidional_mnemonic_name->text();
    additional_mnemonic_id=data_base_action->id_minimal_for_input("additional_mnemonic_id","additional_mnemonics");
    main_mnemonic_name=ui->comboBox_main_mnemonic_name->currentText();
    QString condition=" main_mnemonic_name =\""+main_mnemonic_name+"\"";
    main_mnemonic_id=data_base_action->id_exist_data("main_mnemonic_id","main_mnemonics",condition);
    qDebug()<<"main_mnemonic id found";
    data_base_action->database_refresh();
}

void AdditionalMnemonicAddWindow::input_additional_mnemonic_unit()
{
    input_conversion_formula();
    input_additional_mnemonic();
    additional_mnemonic_unit_name=ui->lineEdit_additional_mnemonic_unit_name->text();
    additional_mnemonic_unit_id=data_base_action->id_minimal_for_input("additional_mnemonic_unit_id","additional_mnemonic_units");
    data_base_action->insert_additional_mnemonic_units(additional_mnemonic_unit_id,additional_mnemonic_unit_name,additional_mnemonic_id,conversion_formula_id);
    data_base_action->database_refresh();
}
void AdditionalMnemonicAddWindow::receive_data_base_action(DataBaseAction *data_base_action2)
{
    data_base_action=data_base_action2;
    qDebug()<<"slot2";
    list_company_name= data_base_action->get_unique_values("company_name","companies");
    foreach (const QString &value, list_company_name) {
        ui->comboBox_company_name->addItem(value);
    }
    list_main_mnemonic_name= data_base_action->get_unique_values("main_mnemonic_name","main_mnemonics");
    foreach (const QString &value, list_main_mnemonic_name) {
        ui->comboBox_main_mnemonic_name->addItem(value);
    }

}

void AdditionalMnemonicAddWindow::on_pushButton_INPUT_clicked()
{
    input_additional_mnemonic_unit();
    ui->label_input_info->setText("additional mnemonic Added");
    ui->label_input_info->setStyleSheet("color: green");
}


void AdditionalMnemonicAddWindow::on_pushButton_CLEAN_clicked()
{
    ui->lineEdit_addidional_mnemonic_name->setText("");
    ui->lineEdit_additional_mnemonic_unit_name->setText("");
    ui->label_input_info->setText("");
}

