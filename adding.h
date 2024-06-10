#ifndef ADDING_H
#define ADDING_H

#include <QWidget>
#include <QDialog>
#include "additionalmnemonicaddwindow.h"
#include "mainmnemonicaddwindow.h"
#include "tooladdwindow.h"
#include "sensoraddwindow.h"

namespace Ui {
class Adding;
}

class Adding : public QDialog
{
    Q_OBJECT

public:
    explicit Adding(QWidget *parent = nullptr);
    ~Adding();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Adding *ui;
    AdditionalMnemonicAddWindow* additional_mnemonic_add_window;
    MainMnemonicAddWindow* main_mnemonic_add_window;
    ToolAddWindow* tool_add_window;
    SensorAddWindow *sensor_add_window;
public slots:
    void take_window1(QWidget *window) {
        tool_add_window = qobject_cast<ToolAddWindow *>(window);
    }
    void take_window2(QWidget *window) {
        sensor_add_window = qobject_cast<SensorAddWindow *>(window);
    }
    void take_window3(QWidget *window) {
        additional_mnemonic_add_window = qobject_cast<AdditionalMnemonicAddWindow *>(window);
    }
    void take_window4(QWidget *window) {
        main_mnemonic_add_window = qobject_cast<MainMnemonicAddWindow*>(window);
    }
};

#endif // ADDING_H
