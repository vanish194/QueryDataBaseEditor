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
    Ui::AdditionalMnemonicAddWindow *ui;
};

#endif // ADDITIONALMNEMONICADDWINDOW_H
