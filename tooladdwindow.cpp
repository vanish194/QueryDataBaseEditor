#include "tooladdwindow.h"
#include "ui_tooladdwindow.h"

ToolAddWindow::ToolAddWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ToolAddWindow)
{
    ui->setupUi(this);
    ui->spinBox_outer_diameter->setMaximum(500);
    ui->spinBox_inner_diameter->setMaximum(500);
    ui->spinBox_inner_diameter->setSuffix("mm");
    ui->spinBox_outer_diameter->setSuffix("mm");
}

ToolAddWindow::~ToolAddWindow()
{
    delete ui;
}

void ToolAddWindow::on_pushButton_INPUT_clicked()
{
    input_produser();
    input_tool_description();
    input_tool();
    ui->label_input_info->setText("Tool Added");
    ui->label_input_info->setStyleSheet("color: green");
    data_base_action->database_refresh();
    emit refreshing_bd();
}

void ToolAddWindow::on_pushButton_CLEAN_clicked()
{
    ui->lineEdit_2->setText("");
    ui->spinBox_outer_diameter->setValue(0);
    ui->spinBox_inner_diameter->setValue(0);
    ui->lineEdit_legth->setText("");
    ui->lineEdit_description->setText("");
    ui->lineEdit_tool_name->setText("");
    image = {};
    ui->label_input_info->setText("");
}

void ToolAddWindow::receive_data_base_action(DataBaseAction *data_base_action2)
{
    data_base_action = data_base_action2;
    list_produsers.clear();
    ui->comboBox->clear();
    list_produsers = data_base_action->get_unique_values("produser_name", "produsers");
    foreach (const QString &value, list_produsers) {
        ui->comboBox->addItem(value);
    }
}

void ToolAddWindow::refreshed_bd_slot()
{
    list_produsers.clear();
    ui->comboBox->clear();
    list_produsers = data_base_action->get_unique_values("produser_name", "produsers");
    foreach (const QString &value, list_produsers) {
        ui->comboBox->addItem(value);
    }
}

void ToolAddWindow::input_tool()
{
    tool_name = ui->lineEdit_tool_name->text();
    tool_id = data_base_action->id_minimal_for_input("tool_id", "tools");
    data_base_action->insert_tools(tool_id, tool_name, tool_description_id);
    qDebug() << "input tool";
    data_base_action->database_refresh();
}

void ToolAddWindow::input_produser()
{
    produser_name = ui->comboBox->currentText();
    // логика поиска существующих
    if (ui->comboBox->findText(produser_name) == -1) {
        qDebug() << "prodeser_name not exist";
        produser_id = data_base_action->id_minimal_for_input("produser_id", "produsers");
        data_base_action->insert_produsers(produser_id, produser_name);

    } else {
        qDebug() << "prodeser_name exist";
        QString condition = "produser_name =\"" + produser_name + "\"";
        produser_id = data_base_action->id_exist_data("produser_id", "produsers", condition);
    }
    data_base_action->database_refresh();
    qDebug() << "input produser";
    data_base_action->database_refresh();
}

void ToolAddWindow::input_tool_description()
{
    tool_description_id = data_base_action->id_minimal_for_input("tool_description_id",
                                                                 "tool_descriptions");
    description = ui->lineEdit_description->text();
    length = ui->lineEdit_legth->text();
    outer_diameter = ui->spinBox_outer_diameter->text();
    inner_diameter = ui->spinBox_inner_diameter->text();
    //image присваивается в функции void ToolAddWindow::on_pushButton_3_clicked()
    //produser id в функции input_produser
    data_base_action->insert_tool_descriptions(tool_description_id,
                                               description,
                                               length,
                                               outer_diameter,
                                               inner_diameter,
                                               image,
                                               produser_id);
    data_base_action->database_refresh();
    qDebug() << "input tool_description";
    data_base_action->database_refresh();
}

void ToolAddWindow::on_pushButton_3_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr,
                                                    "Choice File",
                                                    "/path/to/default/directory",
                                                    "Images (*.png)");
    if (filePath.isEmpty()) {
        qDebug() << "FileEmpty";
        ui->lineEdit_2->setText("WrongData");
    }

    // Открываем выбранный файл
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "WrongData";
        ui->lineEdit_2->setText("WrongData");
    }
    ui->lineEdit_2->setText(filePath);
    // Считываем данные из файла
    image = file.readAll();
    file.close();
}

void ToolAddWindow::on_spinBox_outer_diameter_valueChanged(int arg1)
{
    if (ui->spinBox_outer_diameter->value() < ui->spinBox_inner_diameter->value()) {
        ui->spinBox_inner_diameter->setValue(arg1);
    }
}

void ToolAddWindow::on_spinBox_inner_diameter_valueChanged(int arg1)
{
    if (ui->spinBox_outer_diameter->value() < ui->spinBox_inner_diameter->value()) {
        ui->spinBox_outer_diameter->setValue(arg1);
    }
}

void ToolAddWindow::on_ToolAddWindow_finished()
{
    emit refreshing_bd();
    ui->lineEdit_2->setText("");
    ui->spinBox_outer_diameter->setValue(0);
    ui->spinBox_inner_diameter->setValue(0);
    ui->lineEdit_legth->setText("");
    ui->lineEdit_description->setText("");
    ui->lineEdit_tool_name->setText("");
    image = {};
    ui->label_input_info->setText("");
}
