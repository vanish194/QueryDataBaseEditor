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
    void on_treeView_doubleClicked(const QModelIndex &index);

signals:
    void send_data_base_connection(DataBaseAction* data_base_action);
    void send_window1(QWidget *window);
    void send_window2(QWidget *window);
    void send_window3(QWidget *window);
    void send_window4(QWidget *window);
private:
    Ui::MainWindow* ui;
    DataBaseAction data_base_action;
    BlobImageDelegate* blobDelegate;
    Adding* window_adding;

    AdditionalMnemonicAddWindow* additional_mnemonic_add_window;
    MainMnemonicAddWindow* main_mnemonic_add_window;
    ToolAddWindow* tool_add_window;
    SensorAddWindow*sensor_add_window;
    void connecting();
};
#endif // MAINWINDOW_H
