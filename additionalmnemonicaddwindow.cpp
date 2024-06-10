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
