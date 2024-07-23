#include "updateadditionalmnemonic.h"
#include "ui_updateadditionalmnemonic.h"

UpdateAdditionalMnemonic::UpdateAdditionalMnemonic(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UpdateAdditionalMnemonic)
{
    ui->setupUi(this);
}

UpdateAdditionalMnemonic::~UpdateAdditionalMnemonic()
{
    delete ui;
}

void UpdateAdditionalMnemonic::on_pushButton_INPUT_clicked()
{
    input_company();
    input_additional_mnemonic_unit();
    input_conversion_formula();
    updating_data();
    data_base_action->update_additional_mnemonic(additional_mnemonic_id,
                                                 additional_mnemonic_name,
                                                 company_id,
                                                 main_mnemonic_id,
                                                 derived_unit_id);
    data_base_action->database_refresh();
    receive_data_base_action(data_base_action);
    completion_data();
}

void UpdateAdditionalMnemonic::on_pushButton_CLEAN_clicked()
{
    completion_data();
}

void UpdateAdditionalMnemonic::recieve_data_name(QString &additional_mnemonic_name_)
{
    additional_mnemonic_name = additional_mnemonic_name_;
    search_current_data();
    completion_data();
}

void UpdateAdditionalMnemonic::receive_data_base_action(DataBaseAction *data_base_action2)
{
    data_base_action = data_base_action2;
    list_company_name.clear();
    ui->comboBox_company_name->clear();
    list_derived_unit.clear();
    ui->comboBox_derived_unit->clear();
    list_main_mnemonic_name.clear();
    ui->comboBox_main_mnemonic_name->clear();
    list_company_name = data_base_action->get_unique_values("company_name", "companies");
    foreach (const QString &value, list_company_name) {
        ui->comboBox_company_name->addItem(value);
    }
    list_main_mnemonic_name = data_base_action->get_unique_values("main_mnemonic_name",
                                                                  "main_mnemonics");
    foreach (const QString &value, list_main_mnemonic_name) {
        ui->comboBox_main_mnemonic_name->addItem(value);
    }
}

void UpdateAdditionalMnemonic::input_conversion_formula()
{
    formula = ui->lineEdit_coversion_formula->text();
    QString condition = "inital_unit_id = \"" + QString::number(inital_unit_id) + "\" AND\
                        derived_unit_id = \""
                        + QString::number(derived_unit_id) + "\" AND\
          formula = \"" + formula
                        + "\"";
    formula_id = data_base_action->id_exist_data("formula_id", "conversion_formulas", condition);
    if (formula_id == -1) {
        formula_id = data_base_action->id_minimal_for_input("formula_id", "conversion_formulas");
        data_base_action->insert_conversion_formulas(formula_id,
                                                     formula,
                                                     inital_unit_id,
                                                     derived_unit_id);
    }
}

void UpdateAdditionalMnemonic::input_company()
{
    company_name = ui->comboBox_company_name->currentText();

    if (ui->comboBox_company_name->findText(company_name) == -1) {
        company_id = data_base_action->id_minimal_for_input("company_id", "companies");
        data_base_action->insert_companies(company_id, company_name);
        qDebug() << "company_name not exist";
    } else {
        QString condition = "company_name =\"" + company_name + "\"";
        company_id = data_base_action->id_exist_data("company_id", "companies", condition);
        qDebug() << "company_name exist";
    }
    data_base_action->database_refresh();
}

void UpdateAdditionalMnemonic::input_additional_mnemonic_unit()
{
    derived_unit_name = ui->comboBox_derived_unit->currentText();
    if (ui->comboBox_derived_unit->findText(derived_unit_name) == -1) {
        derived_unit_id = data_base_action->id_minimal_for_input("unit_id", "units");
        data_base_action->insert_units(derived_unit_id, derived_unit_name, type_id);
        qDebug() << "derived_unit not exist";
    } else {
        QString condition = "unit_name =\"" + derived_unit_name + "\"";
        derived_unit_id = data_base_action->id_exist_data("unit_id", "units", condition);
        qDebug() << "derived_unit exist";
    }
    data_base_action->database_refresh();
}

bool UpdateAdditionalMnemonic::check_formula()
{
    QString condition = "unit_name =\"" + ui->comboBox_derived_unit->currentText() + "\"";
    derived_unit_id = data_base_action->id_exist_data("unit_id", "units", condition);
    condition = "unit_name =\"" + inital_unit_name + "\"";
    inital_unit_id = data_base_action->id_exist_data("unit_id", "units", condition);
    condition = "inital_unit_id = \"" + QString::number(inital_unit_id) + "\" AND\
                derived_unit_id = \""
                + QString::number(derived_unit_id) + "\"";
    formula_id = data_base_action->id_exist_data("formula_id", "conversion_formulas", condition);

    if (formula_id != -1) {
        condition = "formula_id =\"" + QString::number(formula_id) + "\"";
        formula = data_base_action->find_with_condition("formula", "conversion_formulas", condition);
        ui->lineEdit_coversion_formula->setText(formula);
        qDebug() << "Formula exist";
        return true;
    }

    qDebug() << "Formula not exist";

    return false;
}
void UpdateAdditionalMnemonic::on_comboBox_main_mnemonic_name_currentTextChanged(const QString &arg1)
{
    QString condition = "main_mnemonic_name =\"" + arg1 + "\"";
    inital_unit_id = data_base_action->id_exist_data("unit_id", "main_mnemonics", condition);

    condition = "unit_id =\"" + QString::number(inital_unit_id) + "\"";
    inital_unit_name = data_base_action->find_with_condition("unit_name", "units", condition);

    condition = "unit_id =\"" + QString::number(inital_unit_id) + "\"";
    type_id = data_base_action->id_exist_data("type_id", "units", condition);

    condition = "type_id =\"" + QString::number(type_id) + "\"";
    type_name = data_base_action->find_with_condition("type_name", "types_of_units", condition);

    ui->lineEdit_unit_info->setText(type_name + " / " + inital_unit_name);

    condition = "type_id =\"" + QString::number(type_id) + "\"";
    list_derived_unit.clear();
    ui->comboBox_derived_unit->clear();
    list_derived_unit = data_base_action->get_unique_values_with_condition("unit_name",
                                                                           "units",
                                                                           condition);
    foreach (const QString &value, list_derived_unit) {
        ui->comboBox_derived_unit->addItem(value);
    }
}

void UpdateAdditionalMnemonic::search_current_data()
{
    QString condition = "additional_mnemonic_name= \"" + additional_mnemonic_name + "\"";
    additional_mnemonic_id = data_base_action->id_exist_data("additional_mnemonic_id",
                                                             "additional_mnemonics",
                                                             condition);

    condition = "additional_mnemonic_id = " + QString::number(additional_mnemonic_id) + "";

    company_id = data_base_action->id_exist_data("company_id", "additional_mnemonics", condition);
    main_mnemonic_id = data_base_action->id_exist_data("main_mnemonic_id",
                                                       "additional_mnemonics",
                                                       condition);
    derived_unit_id = data_base_action->id_exist_data("unit_id", "additional_mnemonics", condition);

    condition = "unit_id = " + QString::number(derived_unit_id) + "";
    derived_unit_name = data_base_action->find_with_condition("unit_name", "units", condition);

    type_id = data_base_action->id_exist_data("type_id", "units", condition);

    condition = "type_id = " + QString::number(type_id) + "";
    type_name = data_base_action->find_with_condition("type_name", "types_of_units", condition);

    condition = "main_mnemonic_id = " + QString::number(main_mnemonic_id) + "";
    inital_unit_id = data_base_action->id_exist_data("unit_id", "main_mnemonics", condition);

    condition = "unit_id = " + QString::number(inital_unit_id) + "";
    inital_unit_name = data_base_action->find_with_condition("unit_name", "units", condition);
    main_mnemonic_name = data_base_action->find_with_condition("main_mnemonic_name",
                                                               "main_mnemonics",
                                                               condition);
    condition = "company_id = \"" + QString::number(company_id) + "\"";
    company_name = data_base_action->find_with_condition("company_name", "companies", condition);

    if (!check_formula()) {
        qDebug() << "FAILED  Read Formula for update";
    } else {
        condition = "formula_id = \"" + QString::number(formula_id) + "\"";
        formula = data_base_action->find_with_condition("formula", "conversion_formulas", condition);
        qDebug() << "formulaId" << formula_id << " " << formula;
    }
}

void UpdateAdditionalMnemonic::completion_data()
{
    ui->comboBox_main_mnemonic_name->setCurrentText(main_mnemonic_name);
    ui->lineEdit_unit_info->setText(type_name + " / " + inital_unit_name);
    ui->lineEdit_addidional_mnemonic_name->setText(additional_mnemonic_name);
    ui->comboBox_company_name->setCurrentText(company_name);
    ui->comboBox_derived_unit->setCurrentText(derived_unit_name);
    //conversion_formula
}

void UpdateAdditionalMnemonic::updating_data()
{
    additional_mnemonic_name = ui->lineEdit_addidional_mnemonic_name->text();
}
void UpdateAdditionalMnemonic::on_lineEdit_unit_info_textChanged()
{
    if (check_formula()) {
        ui->lineEdit_coversion_formula->setReadOnly(true);
        ui->lineEdit_coversion_formula->setStyleSheet("background-color: lightgray");
    } else {
        ui->lineEdit_coversion_formula->setReadOnly(false);
        ui->lineEdit_coversion_formula->setStyleSheet("background-color: white");
    }
}

void UpdateAdditionalMnemonic::on_comboBox_derived_unit_currentTextChanged()
{
    if (check_formula()) {
        ui->lineEdit_coversion_formula->setReadOnly(true);
        ui->lineEdit_coversion_formula->setStyleSheet("background-color: lightgray");
    } else {
        ui->lineEdit_coversion_formula->setReadOnly(false);
        ui->lineEdit_coversion_formula->setStyleSheet("background-color: white");
    }
}
