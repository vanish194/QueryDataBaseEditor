#ifndef ADDITIONALMNEMONICADDWINDOW_H
#define ADDITIONALMNEMONICADDWINDOW_H

#include <QDialog>
#include "databaseaction.h"
namespace Ui {
class AdditionalMnemonicAddWindow;
}

class AdditionalMnemonicAddWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AdditionalMnemonicAddWindow(QWidget *parent = nullptr);
    ~AdditionalMnemonicAddWindow();

private:
    int inital_unit_id = -1;
    int derived_unit_id = -1;
    int main_mnemonic_id;
    int formula_id;
    int company_id;
    int additional_mnemonic_id;
    int type_id;

    QString type_name;
    QString formula;
    QString additional_mnemonic_name;
    QString derived_unit_name;
    QString inital_unit_name;
    QString company_name;
    QString main_mnemonic_name;

    QList<QString> list_derived_unit;
    QList<QString> list_company_name;
    QList<QString> list_main_mnemonic_name;

    DataBaseAction *data_base_action;
    Ui::AdditionalMnemonicAddWindow *ui;

    void input_conversion_formula();
    void input_company();
    void input_additional_mnemonic();
    void input_additional_mnemonic_unit();

    bool check_formula();

public slots:
    void receive_data_base_action(DataBaseAction *data_base_action2);
    void refreshed_bd_slot();
signals:
    void refreshing_bd();
private slots:
    void on_pushButton_INPUT_clicked();
    void on_pushButton_CLEAN_clicked();
    void on_comboBox_main_mnemonic_name_currentTextChanged(const QString &arg1);
    void on_lineEdit_unit_info_textChanged();
    void on_comboBox_derived_unit_currentTextChanged();
    void on_AdditionalMnemonicAddWindow_finished();
};

#endif // ADDITIONALMNEMONICADDWINDOW_H
