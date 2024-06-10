#ifndef MAINMNEMONICADDWINDOW_H
#define MAINMNEMONICADDWINDOW_H

#include <QDialog>
#include "databaseaction.h"
namespace Ui {
class MainMnemonicAddWindow;
}

class MainMnemonicAddWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainMnemonicAddWindow(QWidget *parent = nullptr);
    ~MainMnemonicAddWindow();

private:
    Ui::MainMnemonicAddWindow *ui;
};

#endif // MAINMNEMONICADDWINDOW_H
