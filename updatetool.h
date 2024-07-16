    #ifndef UPDATETOOL_H
#define UPDATETOOL_H

#include <QDialog>
#include <QFileDialog>
#include "databaseaction.h"

namespace Ui {
class UpdateToolWindow;
}

class UpdateToolWindow : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateToolWindow(QWidget *parent = nullptr);
    ~UpdateToolWindow();
public slots:

    void recieve_data_name(QString& tool_name);

    void receive_data_base_action(DataBaseAction *data_base_action2);
private slots:


    void on_pushButton_3_clicked();

    void on_spinBox_outer_diameter_valueChanged(int arg1);

    void on_spinBox_inner_diameter_valueChanged(int arg1);

    void on_pushButton_INPUT_clicked();

    void on_pushButton_CLEAN_clicked();

private:


    Ui::UpdateToolWindow *ui;
    QString tool_name;
    QString description;
    QString length;
    QString outer_diameter;
    QString inner_diameter;
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

    void search_current_data();
    void completion_data();

    void updating_data();

};

#endif // UPDATETOOL_H
