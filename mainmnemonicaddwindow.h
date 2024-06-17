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
    int main_mnemonic_id;
    int main_mnemonic_unit_id;
    int sensor_id;
    QString main_mnemonic_name;
    QString main_mnemonic_description;
    QString main_mnemonic_unit_name;
    QString main_mnemonic_unit_description;
    QList<QString> list_sensor_name;
    DataBaseAction* data_base_action;

    Ui::MainMnemonicAddWindow *ui;
    void input_main_mnemonic();
    void input_main_mnemonic_unit();

public slots:
    void receive_data_base_action(DataBaseAction *data_base_action2);
private slots:
    void on_pushButton_INPUT_clicked();
    void on_pushButton_CLEAN_clicked();
};

#endif // MAINMNEMONICADDWINDOW_H
