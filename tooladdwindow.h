#ifndef TOOLADDWINDOW_H
#define TOOLADDWINDOW_H

#include <QDialog>
#include <QFileDialog>
#include "databaseaction.h"
namespace Ui {
class ToolAddWindow;
}

class ToolAddWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ToolAddWindow(QWidget *parent = nullptr);
    ~ToolAddWindow();

private slots:

    void on_pushButton_CLEAN_clicked();

    void on_pushButton_INPUT_clicked();

    void on_pushButton_3_clicked();

    void on_spinBox_outer_diametr_valueChanged(int arg1);

    void on_spinBox_inner_diametr_valueChanged(int arg1);

    void on_ToolAddWindow_finished();

private:
    Ui::ToolAddWindow *ui;
    QString tool_name;
    QString description;
    QString lenght;
    QString outer_diametr;
    QString inner_diametr;
    QByteArray image;
    QString produser_name;

    int tool_description_id;
    int tool_id;
    int produser_id;
    QList<QString> list_produsers;
    DataBaseAction* data_base_action;
    void input_tool();
    void input_produser();
    void input_tool_description();

public slots:
    void receive_data_base_action(DataBaseAction *data_base_action2);
    void refreshed_bd_slot();
signals:
    void refreshing_bd();
};

#endif // TOOLADDWINDOW_H
