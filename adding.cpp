#include "adding.h"
#include "ui_adding.h"

Adding::Adding(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Adding)
{
    ui->setupUi(this);
}

Adding::~Adding()
{
    delete ui;
}

void Adding::on_pushButton_clicked()
{
    tool_add_window->setModal(true);
    tool_add_window->exec();
}

void Adding::on_pushButton_2_clicked()
{
    sensor_add_window->setModal(true);
    sensor_add_window->exec();
}

void Adding::on_pushButton_3_clicked()
{
    additional_mnemonic_add_window->setModal(true);
    additional_mnemonic_add_window->exec();
}

void Adding::on_pushButton_4_clicked()
{
    main_mnemonic_add_window->setModal(true);
    main_mnemonic_add_window->exec();
}
