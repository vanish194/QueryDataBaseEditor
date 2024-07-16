#include "updatetool.h"
#include "ui_updatetool.h"

UpdateToolWindow::UpdateToolWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UpdateToolWindow)
{
    ui->setupUi(this);
    ui->spinBox_outer_diameter->setMaximum(500);
    ui->spinBox_inner_diameter->setMaximum(500);
    ui->spinBox_inner_diameter->setSuffix("mm");
    ui->spinBox_outer_diameter->setSuffix("mm");

}

UpdateToolWindow::~UpdateToolWindow()
{
    delete ui;
}

void UpdateToolWindow::recieve_data_name(QString &tool_name_)
{
    tool_name=tool_name_;
    search_current_data();
    completion_data();
}


void UpdateToolWindow::receive_data_base_action(DataBaseAction *data_base_action2)
{
    data_base_action=data_base_action2;
    qDebug()<<"slot2";
    list_produsers.clear();
    ui->comboBox->clear();
    list_produsers= data_base_action->get_unique_values("produser_name","produsers");
    foreach (const QString &value, list_produsers) {
        ui->comboBox->addItem(value);    }
    ui->comboBox->setCurrentText(produser_name);
}


void UpdateToolWindow::on_pushButton_3_clicked()
{
    qDebug()<<"Clicked 2";
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Choice File", "/path/to/default/directory", "Images (*.png)");
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
    qDebug()<<"Clicked 2";
}

void UpdateToolWindow::search_current_data()
{
    QString condition="tool_name= \"" + tool_name +"\"";
    tool_id=data_base_action->id_exist_data("tool_id","tools",condition);

    condition="tool_id = "+QString::number(tool_id)+"";
    tool_description_id=data_base_action->id_exist_data("tool_description_id","tools",condition);

    condition="tool_description_id = "+QString::number(tool_description_id)+"";
    description=data_base_action->find_with_condition("description","tool_descriptions",condition);
    length=data_base_action->find_with_condition("length","tool_descriptions",condition);

    outer_diameter=data_base_action->find_with_condition("outer_diameter","tool_descriptions",condition);
    inner_diameter=data_base_action->find_with_condition("inner_diameter","tool_descriptions",condition);
    //image  :(((
    produser_id=data_base_action->id_exist_data("produser_id","tool_descriptions",condition);
    condition="produser_id = \""+QString::number(produser_id)+"\"";
    produser_name=data_base_action->find_with_condition("produser_name","produsers",condition);
}

void UpdateToolWindow::completion_data()
{
    ui->lineEdit_tool_name->setText(tool_name);
    ui->lineEdit_description->setText(description);
    ui->lineEdit_legth->setText(length);
    qDebug()<<outer_diameter;
    int o_d=outer_diameter.left(outer_diameter.length() - 2).toInt();
    ui->spinBox_outer_diameter->setValue(o_d);
    int i_d=outer_diameter.left(inner_diameter.length() - 2).toInt();
    ui->spinBox_inner_diameter->setValue(i_d);
    ui->comboBox->setCurrentText(produser_name);
}

void UpdateToolWindow::updating_data()
{
    tool_name=ui->lineEdit_tool_name->text();
    description=ui->lineEdit_description->text();
    length=ui->lineEdit_legth->text();
    outer_diameter=ui->spinBox_outer_diameter->text();
    inner_diameter=ui->spinBox_inner_diameter->text();
    // id инициализированы в процессе поиска значений выше. image по отдельной кнопке обновляет значение
}
void UpdateToolWindow::on_spinBox_outer_diameter_valueChanged(int arg1)
{
    if(ui->spinBox_outer_diameter->value()<ui->spinBox_inner_diameter->value())
    {
        ui->spinBox_inner_diameter->setValue(arg1);
    }
}


void UpdateToolWindow::on_spinBox_inner_diameter_valueChanged(int arg1)
{
    if(ui->spinBox_outer_diameter->value()<ui->spinBox_inner_diameter->value())
    {
        ui->spinBox_outer_diameter->setValue(arg1);
    }
}


void UpdateToolWindow::on_pushButton_INPUT_clicked()
{
    input_produser();
    updating_data();
    data_base_action->update_tool(tool_id,tool_name,tool_description_id,description,length,outer_diameter,
                                  inner_diameter,image,produser_id);
    data_base_action->database_refresh();
    ui->label_input_info->setText("Tool Update");
    receive_data_base_action(data_base_action);

}


void UpdateToolWindow::on_pushButton_CLEAN_clicked()
{
    completion_data();
    ui->label_input_info->setText("");
}

void UpdateToolWindow::input_produser()
{
    produser_name=ui->comboBox->currentText();
    // логика поиска существующих
    qDebug()<<"preinput produser";
    if(ui->comboBox->findText(produser_name)==-1)  {
        qDebug()<<"prodeser_name not exist";
        produser_id=data_base_action->id_minimal_for_input("produser_id","produsers");
        data_base_action->insert_produsers(produser_id,produser_name);

    }
    else    {
        qDebug()<<"prodeser_name exist";
        QString condition="produser_name =\""+produser_name+"\"";
        produser_id=data_base_action->id_exist_data("produser_id","produsers",condition);

    }
    data_base_action->database_refresh();
    qDebug()<<"input produser";
}
