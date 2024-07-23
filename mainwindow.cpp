#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    window_adding = new Adding;
    tool_add_window = new ToolAddWindow;
    void send_window(QWidget * tool_add_window);
    sensor_add_window = new SensorAddWindow;
    void send_window(QWidget * sensor_add_window);
    additional_mnemonic_add_window = new AdditionalMnemonicAddWindow;
    void send_window(QWidget * additional_mnemonic_add_window);
    main_mnemonic_add_window = new MainMnemonicAddWindow;
    void send_window(QWidget * main_mnemonic_add_window);

    update_tool_window = new UpdateToolWindow;
    update_sensor_window = new UpdateSensor;
    update_main_mnemonic_window = new UpdateMainMnemonic;
    update_additional_mnemonic_window = new UpdateAdditionalMnemonic;

    setting_view_menu();
    gerse_logo_setup();
    connecting();
}

MainWindow::~MainWindow()
{
    delete update_additional_mnemonic_window;
    delete update_main_mnemonic_window;
    delete update_sensor_window;
    delete update_tool_window;
    delete window_adding;
    delete tool_add_window;
    delete sensor_add_window;
    delete additional_mnemonic_add_window;
    delete main_mnemonic_add_window;
    delete ui;
}

void MainWindow::on_actionOpen_Database_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choose file", QDir::homePath(), "");
    data_base_action.database_connecting(fileName);

    ui->tableView->setModel(data_base_action.model1);
    ui->treeView->setModel(data_base_action.treemodel);
    setting_tableview();

    emit send_data_base_connection(&data_base_action);
}

void MainWindow::on_pushButton_save_clicked()
{
    data_base_action.database_upload();
}

void MainWindow::on_pushButton_cancel_clicked()
{
    data_base_action.database_rollback();
    data_base_action.database_refresh();
}

void MainWindow::on_pushButton_add_clicked()
{
    emit send_window1(tool_add_window);
    emit send_window2(sensor_add_window);
    emit send_window3(additional_mnemonic_add_window);
    emit send_window4(main_mnemonic_add_window);

    window_adding->setModal(true);
    window_adding->exec();
}

void MainWindow::recieve_tree_view_context_menu(const int &hierarchy_level,
                                                CustomTreeView::signaltype action_code)
{
    emit send_data_base_connection(&data_base_action);
    switch (action_code) {
    case CustomTreeView::Add: //Add
        switch (hierarchy_level) {
        case 0:
            tool_add_window->setModal(true);
            tool_add_window->exec();
            break;
        case 1:
            sensor_add_window->setModal(true);
            sensor_add_window->exec();
            break;
        case 2:
            main_mnemonic_add_window->setModal(true);
            main_mnemonic_add_window->exec();
            break;
        case 3:
            additional_mnemonic_add_window->setModal(true);
            additional_mnemonic_add_window->exec();
            break;
        }
        break; //Edit
    case CustomTreeView::Edit:

        switch (hierarchy_level) {
        case 0: {
            QModelIndex index = ui->treeView->currentIndex();
            if (!index.isValid()) {
                qDebug() << "InValidindex";
                break;
            }
            QString tool_name = index.data().toString();
            send_data_name(tool_name);
            update_tool_window->setModal(true);
            update_tool_window->exec();
            break;
        }
        case 1: {
            QModelIndex index = ui->treeView->currentIndex();
            if (!index.isValid()) {
                qDebug() << "InValidindex";
                break;
            }
            QString sensor_name = index.data().toString();
            send_data_name(sensor_name);
            update_sensor_window->setModal(true);
            update_sensor_window->exec();
            break;
        }
        case 2: {
            QModelIndex index = ui->treeView->currentIndex();
            if (!index.isValid()) {
                qDebug() << "InValidindex";
                break;
            }
            QString main_mnemonic_name = index.data().toString();
            send_data_name(main_mnemonic_name);
            update_main_mnemonic_window->setModal(true);
            update_main_mnemonic_window->exec();
            break;
        }

        case 3: {
            QModelIndex index = ui->treeView->currentIndex();
            if (!index.isValid()) {
                qDebug() << "InValidindex";
                break;
            }
            QString main_mnemonic_name = index.data().toString();
            send_data_name(main_mnemonic_name);
            update_additional_mnemonic_window->setModal(true);
            update_additional_mnemonic_window->exec();
            break;
        }
        }

        break; //Remove
    case CustomTreeView::Remove:
        QString condition;
        QString value = ui->treeView->currentIndex().data().toString();
        switch (hierarchy_level) {
        case 0:
            int tool_id;
            condition = "tool_name =\"" + value + "\"";
            tool_id = data_base_action.id_exist_data("tool_id", "tools", condition);
            data_base_action.remove_tools(tool_id);
            qDebug() << "remove_tools";
            data_base_action.database_refresh();
            break;
        case 1:
            int sensor_id;
            condition = "sensor_name =\"" + value + "\"";
            sensor_id = data_base_action.id_exist_data("sensor_id", "sensors", condition);
            qDebug() << "remove_sensors";
            data_base_action.remove_sensors(sensor_id);
            data_base_action.database_refresh();
            break;
        case 2:
            int main_mnemonic_id;
            condition = "main_mnemonic_name =\"" + value + "\"";
            main_mnemonic_id = data_base_action.id_exist_data("main_mnemonic_id",
                                                              "main_mnemonics",
                                                              condition);
            qDebug() << "remove_main_mnemonics";
            data_base_action.remove_main_mnemonics(main_mnemonic_id);
            data_base_action.database_refresh();
            break;
        case 3:
            int additional_mnemonic_id;
            condition = "additional_mnemonic_name =\"" + value + "\"";
            additional_mnemonic_id = data_base_action.id_exist_data("additional_mnemonic_id",
                                                                    "additional_mnemonics",
                                                                    condition);
            qDebug() << "remove_additional_mnemonics";
            data_base_action.remove_additional_mnemonics(additional_mnemonic_id);
            data_base_action.database_refresh();
            break;
        }

        break;
    }
}

void MainWindow::set_treemodel_headers()
{
    data_base_action.treemodel->setHeaderData(0, Qt::Horizontal, "tools");
    data_base_action.treemodel->setHeaderData(1, Qt::Horizontal, "sensors");
    data_base_action.treemodel->setHeaderData(2, Qt::Horizontal, "main mnemonics");
    data_base_action.treemodel->setHeaderData(3, Qt::Horizontal, "additional mnemonics");
}

void MainWindow::gerse_logo_setup()
{
    QPixmap pix(":/new/prefix1/Logo_Gerse.png");
    int w = ui->space_for_logo->width();
    int h = ui->space_for_logo->height();
    ui->space_for_logo->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
}

void MainWindow::connecting()
{
    connect(this, &MainWindow::send_window1, window_adding, &Adding::take_window1);
    connect(this, &MainWindow::send_window2, window_adding, &Adding::take_window2);
    connect(this, &MainWindow::send_window3, window_adding, &Adding::take_window3);
    connect(this, &MainWindow::send_window4, window_adding, &Adding::take_window4);

    connect(this,
            &MainWindow::send_data_base_connection,
            tool_add_window,
            &ToolAddWindow::receive_data_base_action);
    connect(this,
            &MainWindow::send_data_base_connection,
            sensor_add_window,
            &SensorAddWindow::receive_data_base_action);
    connect(this,
            &MainWindow::send_data_base_connection,
            additional_mnemonic_add_window,
            &AdditionalMnemonicAddWindow::receive_data_base_action);
    connect(this,
            &MainWindow::send_data_base_connection,
            main_mnemonic_add_window,
            &MainMnemonicAddWindow::receive_data_base_action);

    connect(this,
            &MainWindow::send_data_base_connection,
            update_tool_window,
            &UpdateToolWindow::receive_data_base_action);
    connect(this,
            &MainWindow::send_data_base_connection,
            update_sensor_window,
            &UpdateSensor::receive_data_base_action);
    connect(this,
            &MainWindow::send_data_base_connection,
            update_main_mnemonic_window,
            &UpdateMainMnemonic::receive_data_base_action);
    connect(this,
            &MainWindow::send_data_base_connection,
            update_additional_mnemonic_window,
            &UpdateAdditionalMnemonic::receive_data_base_action);

    connect(this,
            &MainWindow::send_data_name,
            update_tool_window,
            &UpdateToolWindow::recieve_data_name);
    connect(this,
            &MainWindow::send_data_name,
            update_sensor_window,
            &UpdateSensor::recieve_data_name);
    connect(this,
            &MainWindow::send_data_name,
            update_main_mnemonic_window,
            &UpdateMainMnemonic::recieve_data_name);
    connect(this,
            &MainWindow::send_data_name,
            update_additional_mnemonic_window,
            &UpdateAdditionalMnemonic::recieve_data_name);

    connect(tool_add_window,
            &ToolAddWindow::refreshing_bd,
            tool_add_window,
            &ToolAddWindow::refreshed_bd_slot);
    connect(tool_add_window,
            &ToolAddWindow::refreshing_bd,
            sensor_add_window,
            &SensorAddWindow::refreshed_bd_slot);
    connect(tool_add_window,
            &ToolAddWindow::refreshing_bd,
            main_mnemonic_add_window,
            &MainMnemonicAddWindow::refreshed_bd_slot);
    connect(tool_add_window,
            &ToolAddWindow::refreshing_bd,
            additional_mnemonic_add_window,
            &AdditionalMnemonicAddWindow::refreshed_bd_slot);
    connect(sensor_add_window,
            &SensorAddWindow::refreshing_bd,
            tool_add_window,
            &ToolAddWindow::refreshed_bd_slot);
    connect(sensor_add_window,
            &SensorAddWindow::refreshing_bd,
            sensor_add_window,
            &SensorAddWindow::refreshed_bd_slot);
    connect(sensor_add_window,
            &SensorAddWindow::refreshing_bd,
            main_mnemonic_add_window,
            &MainMnemonicAddWindow::refreshed_bd_slot);
    connect(sensor_add_window,
            &SensorAddWindow::refreshing_bd,
            additional_mnemonic_add_window,
            &AdditionalMnemonicAddWindow::refreshed_bd_slot);
    connect(main_mnemonic_add_window,
            &MainMnemonicAddWindow::refreshing_bd,
            tool_add_window,
            &ToolAddWindow::refreshed_bd_slot);
    connect(main_mnemonic_add_window,
            &MainMnemonicAddWindow::refreshing_bd,
            sensor_add_window,
            &SensorAddWindow::refreshed_bd_slot);
    connect(main_mnemonic_add_window,
            &MainMnemonicAddWindow::refreshing_bd,
            main_mnemonic_add_window,
            &MainMnemonicAddWindow::refreshed_bd_slot);
    connect(main_mnemonic_add_window,
            &MainMnemonicAddWindow::refreshing_bd,
            additional_mnemonic_add_window,
            &AdditionalMnemonicAddWindow::refreshed_bd_slot);
    connect(additional_mnemonic_add_window,
            &AdditionalMnemonicAddWindow::refreshing_bd,
            tool_add_window,
            &ToolAddWindow::refreshed_bd_slot);
    connect(additional_mnemonic_add_window,
            &AdditionalMnemonicAddWindow::refreshing_bd,
            sensor_add_window,
            &SensorAddWindow::refreshed_bd_slot);
    connect(additional_mnemonic_add_window,
            &AdditionalMnemonicAddWindow::refreshing_bd,
            main_mnemonic_add_window,
            &MainMnemonicAddWindow::refreshed_bd_slot);
    connect(additional_mnemonic_add_window,
            &AdditionalMnemonicAddWindow::refreshing_bd,
            additional_mnemonic_add_window,
            &AdditionalMnemonicAddWindow::refreshed_bd_slot);

    connect(ui->treeView,
            &CustomTreeView::context_menu_signal,
            this,
            &MainWindow::recieve_tree_view_context_menu);
}

void MainWindow::setting_tableview()
{
    BlobImageDelegate *blobDelegate = new BlobImageDelegate;
    blobDelegate->column_index = blobDelegate->column_find_index(ui->tableView, "image");
    ui->tableView->setItemDelegate(blobDelegate);
}

void MainWindow::setting_view_menu()
{
    ui->actiontools->setChecked(true);
    ui->actionsensors->setChecked(true);
    ui->actionmain_mnemonics->setChecked(true);
    ui->actionadditional_mnemonics->setChecked(true);
}

void MainWindow::on_actiontools_toggled(bool arg1)
{
    if (arg1) {
        qDebug() << "+";
        ui->tableView->setColumnHidden(0, false);
        ui->tableView->setColumnHidden(1, false);
        ui->tableView->setColumnHidden(2, false);
        ui->tableView->setColumnHidden(3, false);
        ui->tableView->setColumnHidden(4, false);
        ui->tableView->setColumnHidden(5, false);
        ui->tableView->setColumnHidden(6, false);

    } else {
        qDebug() << "-";
        ui->tableView->setColumnHidden(0, true);
        ui->tableView->setColumnHidden(1, true);
        ui->tableView->setColumnHidden(2, true);
        ui->tableView->setColumnHidden(3, true);
        ui->tableView->setColumnHidden(4, true);
        ui->tableView->setColumnHidden(5, true);
        ui->tableView->setColumnHidden(6, true);
    }
}

void MainWindow::on_actionsensors_toggled(bool arg1)
{
    if (arg1) {
        qDebug() << "+";
        ui->tableView->setColumnHidden(7, false);
        ui->tableView->setColumnHidden(8, false);
        ui->tableView->setColumnHidden(9, false);
        ui->tableView->setColumnHidden(10, false);
    } else {
        qDebug() << "-";
        ui->tableView->setColumnHidden(7, true);
        ui->tableView->setColumnHidden(8, true);
        ui->tableView->setColumnHidden(9, true);
        ui->tableView->setColumnHidden(10, true);
    }
}

void MainWindow::on_actionmain_mnemonics_toggled(bool arg1)
{
    if (arg1) {
        qDebug() << "+";
        ui->tableView->setColumnHidden(11, false);
        ui->tableView->setColumnHidden(12, false);
        ui->tableView->setColumnHidden(13, false);
        ui->tableView->setColumnHidden(14, false);
    } else {
        qDebug() << "-";
        ui->tableView->setColumnHidden(11, true);
        ui->tableView->setColumnHidden(12, true);
        ui->tableView->setColumnHidden(13, true);
        ui->tableView->setColumnHidden(14, true);
    }
}

void MainWindow::on_actionadditional_mnemonics_toggled(bool arg1)
{
    if (arg1) {
        qDebug() << "+";
        ui->tableView->setColumnHidden(15, false);
        ui->tableView->setColumnHidden(16, false);
        ui->tableView->setColumnHidden(17, false);
    } else {
        qDebug() << "-";
        ui->tableView->setColumnHidden(15, true);
        ui->tableView->setColumnHidden(16, true);
        ui->tableView->setColumnHidden(17, true);
    }
}
