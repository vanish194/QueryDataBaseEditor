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
