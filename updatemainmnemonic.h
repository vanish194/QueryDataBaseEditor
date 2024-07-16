#ifndef UPDATEMAINMNEMONIC_H
#define UPDATEMAINMNEMONIC_H

#include <QDialog>
#include "databaseaction.h"

namespace Ui {
class UpdateMainMnemonic;
}

class UpdateMainMnemonic : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateMainMnemonic(QWidget *parent = nullptr);
    ~UpdateMainMnemonic();
public slots:

    void recieve_data_name(QString& main_mnemonic);

    void receive_data_base_action(DataBaseAction *data_base_action2);

private slots:
    void on_pushButton_INPUT_clicked();

    void on_pushButton_CLEAN_clicked();
    void on_comboBox_type_of_unit_currentTextChanged(const QString &arg1);

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
    DataBaseAction* data_base_action;


    void input_main_mnemonic();
    void input_type_of_unit();
    void input_unit();
    Ui::UpdateMainMnemonic *ui;
    void search_current_data();
    void completion_data();

    void updating_data();
};

#endif // UPDATEMAINMNEMONIC_H
