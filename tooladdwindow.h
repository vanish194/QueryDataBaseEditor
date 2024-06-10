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
    void on_lineEdit_2_selectionChanged();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::ToolAddWindow *ui;
    QString tool_name;
    QString description;
    QString lenght;
    QString outer_diametr;
    QString inner_diametr;
    QByteArray image;
    QString produser_name;
    DataBaseAction* data_base_action;

    void input_tool();
    void input_produser();

public slots:
    void receive_data_base_action(DataBaseAction *data_base_action2);
};

#endif // TOOLADDWINDOW_H
