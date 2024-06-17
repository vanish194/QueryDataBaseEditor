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
    int main_mnemonic_id;
    int company_id;
    int additional_mnemonic_id;
    int additional_mnemonic_unit_id;
    int conversion_formula_id;

    QString conversion_formula;
    QString additional_mnemonic_name;
    QString additional_mnemonic_unit_name;
    QString company_name;
    QString main_mnemonic_name;

    QList<QString> list_company_name;
    QList<QString> list_main_mnemonic_name;

    DataBaseAction* data_base_action;
    Ui::AdditionalMnemonicAddWindow *ui;

    void input_conversion_formula();
    void input_company();
    void input_additional_mnemonic();
    void input_additional_mnemonic_unit();

public slots:
    void receive_data_base_action(DataBaseAction *data_base_action2);
private slots:
    void on_pushButton_INPUT_clicked();
    void on_pushButton_CLEAN_clicked();
};

#endif // ADDITIONALMNEMONICADDWINDOW_H
