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
    int sensor_id;
    int unit_id;
    int type_id;
    QString type_name;
    QString unit_name;
    QString sensor_name;
    QString main_mnemonic_name;
    QString main_mnemonic_description;
    QList<QString> list_sensor_name;
    QList<QString> list_type_name;
    QList<QString> list_unit_name;
    DataBaseAction *data_base_action;

    Ui::MainMnemonicAddWindow *ui;
    void input_main_mnemonic();
    void input_type_of_unit();
    void input_unit();

public slots:
    void receive_data_base_action(DataBaseAction *data_base_action2);
    void refreshed_bd_slot();
signals:
    void refreshing_bd();
private slots:
    void on_pushButton_INPUT_clicked();
    void on_pushButton_CLEAN_clicked();
    void on_comboBox_type_of_unit_currentTextChanged(const QString &arg1);
    void on_MainMnemonicAddWindow_finished();
};

#endif // MAINMNEMONICADDWINDOW_H
