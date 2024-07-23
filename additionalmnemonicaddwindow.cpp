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
    delete ui;
}

void AdditionalMnemonicAddWindow::input_conversion_formula()
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

void AdditionalMnemonicAddWindow::input_company()
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

void AdditionalMnemonicAddWindow::input_additional_mnemonic()
{
    main_mnemonic_name = ui->comboBox_main_mnemonic_name->currentText();
    QString condition = "main_mnemonic_name =\"" + main_mnemonic_name + "\"";
    main_mnemonic_id = data_base_action->id_exist_data("main_mnemonic_id",
                                                       "main_mnemonics",
                                                       condition);
    additional_mnemonic_name = ui->lineEdit_addidional_mnemonic_name->text();
    additional_mnemonic_id = data_base_action->id_minimal_for_input("additional_mnemonic_id",
                                                                    "additional_mnemonics");
    data_base_action->insert_additional_mnemonics(additional_mnemonic_id,
                                                  additional_mnemonic_name,
                                                  company_id,
                                                  main_mnemonic_id,
                                                  derived_unit_id);
    data_base_action->database_refresh();
}

void AdditionalMnemonicAddWindow::input_additional_mnemonic_unit()
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

bool AdditionalMnemonicAddWindow::check_formula()
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
        return true;
    }

    return false;
}
void AdditionalMnemonicAddWindow::receive_data_base_action(DataBaseAction *data_base_action2)
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

void AdditionalMnemonicAddWindow::refreshed_bd_slot()
{
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

void AdditionalMnemonicAddWindow::on_pushButton_INPUT_clicked()
{
    input_company();
    input_additional_mnemonic_unit();
    input_conversion_formula();
    input_additional_mnemonic();

    ui->label_input_info->setText("additional mnemonic Added");
    ui->label_input_info->setStyleSheet("color: green");
    data_base_action->database_refresh();
    emit refreshing_bd();
}

void AdditionalMnemonicAddWindow::on_pushButton_CLEAN_clicked()
{
    ui->label_input_info->setText("");
    ui->comboBox_main_mnemonic_name->setCurrentText("");
    ui->comboBox_company_name->setCurrentText("");
    ui->comboBox_derived_unit->setCurrentText("");
    ui->lineEdit_coversion_formula->setText("");
}

void AdditionalMnemonicAddWindow::on_comboBox_main_mnemonic_name_currentTextChanged(
    const QString &arg1)
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

void AdditionalMnemonicAddWindow::on_lineEdit_unit_info_textChanged()
{
    if (check_formula()) {
        ui->lineEdit_coversion_formula->setReadOnly(true);
        ui->lineEdit_coversion_formula->setStyleSheet("background-color: lightgray");
    } else {
        ui->lineEdit_coversion_formula->setReadOnly(false);
        ui->lineEdit_coversion_formula->setStyleSheet("background-color: white");
    }
}

void AdditionalMnemonicAddWindow::on_comboBox_derived_unit_currentTextChanged()
{
    if (check_formula()) {
        ui->lineEdit_coversion_formula->setReadOnly(true);
        ui->lineEdit_coversion_formula->setStyleSheet("background-color: lightgray");
    } else {
        ui->lineEdit_coversion_formula->setReadOnly(false);
        ui->lineEdit_coversion_formula->setStyleSheet("background-color: white");
    }
}

void AdditionalMnemonicAddWindow::on_AdditionalMnemonicAddWindow_finished()
{
    ui->label_input_info->setText("");
    ui->comboBox_main_mnemonic_name->setCurrentText("");
    ui->comboBox_company_name->setCurrentText("");
    ui->comboBox_derived_unit->setCurrentText("");
    ui->lineEdit_coversion_formula->setText("");
    emit refreshing_bd();
}
