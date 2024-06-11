#include "tooladdwindow.h"
#include "ui_tooladdwindow.h"

ToolAddWindow::ToolAddWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ToolAddWindow)
{

    ui->setupUi(this);


}

ToolAddWindow::~ToolAddWindow()
{

    delete ui;
}

void ToolAddWindow::on_pushButton_clicked()
{
    input_tool();
}


void ToolAddWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("double CLICK");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
    ui->lineEdit_6->setText("");
    ui->lineEdit_7->setText("");
    image={};
}

void ToolAddWindow::receive_data_base_action(DataBaseAction *data_base_action2)
{

    QVariantList list_produsers;
    data_base_action=data_base_action2;
    qDebug()<<"slot2";
    list_produsers= data_base_action->get_unique_values("produser_name","produsers");
    foreach (const QVariant &value, list_produsers) {
        ui->comboBox->addItem(value.toString());
    }
}

void ToolAddWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->lineEdit->setText(arg1);
}

void ToolAddWindow::input_tool()
{
    if (ui->comboBox->findText(ui->lineEdit->text()) <= 0)
    {
        input_produser();
    }
    tool_name=ui->lineEdit_7->text();
    description=ui->lineEdit_6->text();
    lenght=ui->lineEdit_5->text();
    outer_diametr=ui->lineEdit_4->text();
    inner_diametr=ui->lineEdit_3->text();
    //image;
    produser_name=ui->lineEdit->text();
    int produser_id;
    produser_id=data_base_action->find_id_where_condition("produser_id","produsers","produser_name = \"" +produser_name +"\"");
    qDebug()<<produser_id;
    data_base_action->insert_tool_descriptions(description,lenght,outer_diametr,inner_diametr,image,produser_id);
    data_base_action->database_refresh();
    int description_id;
    //data_base_action->insert_tools();
}

void ToolAddWindow::input_produser()
{
    data_base_action->insert_produsers(produser_name);
    data_base_action->database_refresh();
}



void ToolAddWindow::on_pushButton_3_clicked()
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

