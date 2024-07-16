#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "customquerymodel.h"
#include <QSqlDatabase>
#include <QFileDialog>
#include <QSqlError>
#include <customtableview.h>
#include <QSqlQuery>
#include "databaseaction.h"
#include "blobimagedelegate.h"
#include "adding.h"
#include "customtableview.h"
#include <QTableView>
#include <QStandardItemModel>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>
#include "updatetool.h"
#include "updatesensor.h"
#include "updatemainmnemonic.h"
#include "updateadditionalmnemonic.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_Database_triggered();


    void on_pushButton_save_clicked();

    void on_pushButton_cancel_clicked();
    void on_pushButton_add_clicked();
    void recieve_tree_view_context_menu(const int&level,const int&action_code);

signals:
    void send_data_base_connection(DataBaseAction* data_base_action);
    void send_window1(QWidget *window);
    void send_window2(QWidget *window);
    void send_window3(QWidget *window);
    void send_window4(QWidget *window);

    void send_data_name(QString& tool_name);

private:
    Ui::MainWindow* ui;
    DataBaseAction data_base_action;
    BlobImageDelegate* blobDelegate;
    Adding* window_adding;

    AdditionalMnemonicAddWindow* additional_mnemonic_add_window;
    MainMnemonicAddWindow* main_mnemonic_add_window;
    ToolAddWindow* tool_add_window;
    SensorAddWindow*sensor_add_window;

    UpdateToolWindow* update_tool_window;
    UpdateSensor* update_sensor_window;
    UpdateMainMnemonic* update_main_mnemonic_window;
    UpdateAdditionalMnemonic* update_additional_mnemonic_window;

    void connecting();
};
#endif // MAINWINDOW_H
