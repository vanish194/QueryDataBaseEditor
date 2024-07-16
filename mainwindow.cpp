#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    window_adding=new Adding;
    tool_add_window=new ToolAddWindow;
    void send_window(QWidget *tool_add_window);
    sensor_add_window=new SensorAddWindow;
    void send_window(QWidget *sensor_add_window);
    additional_mnemonic_add_window=new AdditionalMnemonicAddWindow;
    void send_window(QWidget *additional_mnemonic_add_window);
    main_mnemonic_add_window=new MainMnemonicAddWindow;
    void send_window(QWidget *main_mnemonic_add_window);

    update_tool_window=new UpdateToolWindow;
    update_sensor_window=new UpdateSensor;
    update_main_mnemonic_window=new UpdateMainMnemonic;
    update_additional_mnemonic_window=new UpdateAdditionalMnemonic;


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
    QString fileName=QFileDialog::getOpenFileName(this,"Choose file",QDir::homePath(),"");
    data_base_action.database_connecting(fileName);
    ui->tableView->setModel(data_base_action.model1);
    ui->treeView->setModel(data_base_action.treemodel);
    BlobImageDelegate* blobDelegate=new BlobImageDelegate;
    blobDelegate->column_index=blobDelegate->column_fiend_index(ui->tableView,"image");//выбрать столбец с изображением если надо несколько, то переделать в массив и в blobimagedelegate
    ui->tableView->setItemDelegate(blobDelegate);
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

void MainWindow::recieve_tree_view_context_menu(const int &hierarchy_level, const int &action_code)
{
    emit send_data_base_connection(&data_base_action);
    switch (action_code) {
    case 0://Add
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
        break;//Edit
    case 1:

        switch (hierarchy_level)        {
        case 0:{

            QModelIndex index= ui->treeView->currentIndex();
            if(!index.isValid())
            {
                qDebug()<<"InValidindex";
                break;
            }
            QString tool_name=index.data().toString();
            send_data_name(tool_name);
            update_tool_window->setModal(true);
            update_tool_window->exec();
            break;
        }
        case 1:{
            QModelIndex index= ui->treeView->currentIndex();
            if(!index.isValid())
            {
                qDebug()<<"InValidindex";
                break;
            }
            QString sensor_name=index.data().toString();
            send_data_name(sensor_name);
            update_sensor_window->setModal(true);
            update_sensor_window->exec();
            break;
        }
        case 2:{
            QModelIndex index= ui->treeView->currentIndex();
            if(!index.isValid())
            {
                qDebug()<<"InValidindex";
                break;
            }
            QString main_mnemonic_name=index.data().toString();
            send_data_name(main_mnemonic_name);
            update_main_mnemonic_window->setModal(true);
            update_main_mnemonic_window->exec();
            break;
        }

        case 3:{
            QModelIndex index= ui->treeView->currentIndex();
            if(!index.isValid())
            {
                qDebug()<<"InValidindex";
                break;
            }
            QString main_mnemonic_name=index.data().toString();
            send_data_name(main_mnemonic_name);
            update_additional_mnemonic_window->setModal(true);
            update_additional_mnemonic_window->exec();
            break;
        }

        }

        break;//Remove
    case 2:
        QString condition;
        QString value=ui->treeView->currentIndex().data().toString();
        switch (hierarchy_level) {
        case 0:
            int tool_id;
            condition="tool_name =\""+value+"\"";
            tool_id=data_base_action.id_exist_data("tool_id","tools",condition);
            data_base_action.remove_tools(tool_id);
            qDebug()<<"removet";
            data_base_action.database_refresh();
            break;
        case 1:
            int sensor_id;
            condition="sensor_name =\""+value+"\"";
            sensor_id=data_base_action.id_exist_data("sensor_id","sensors",condition);
            qDebug()<<"removes";
            data_base_action.remove_sensors(sensor_id);
            data_base_action.database_refresh();
            break;
        case 2:
            int main_mnemonic_id;
            condition="main_mnemonic_name =\""+value+"\"";
            main_mnemonic_id=data_base_action.id_exist_data("main_mnemonic_id","main_mnemonics",condition);
            qDebug()<<"removemm";
            data_base_action.remove_main_mnemonics(main_mnemonic_id);
            data_base_action.database_refresh();
            break;
        case 3:
            int additional_mnemonic_id;
            condition="additional_mnemonic_name =\""+value+"\"";
            additional_mnemonic_id=data_base_action.id_exist_data("additional_mnemonic_id","additional_mnemonics",condition);
            qDebug()<<"removeam";
            data_base_action.remove_additional_mnemonics(additional_mnemonic_id);
            data_base_action.database_refresh();
            break;
        }

        break;
    }
}

void MainWindow::connecting()
{
    connect(this,SIGNAL(send_window1(QWidget*)),window_adding,SLOT(take_window1(QWidget*)));
    connect(this,SIGNAL(send_window2(QWidget*)),window_adding,SLOT(take_window2(QWidget*)));
    connect(this,SIGNAL(send_window3(QWidget*)),window_adding,SLOT(take_window3(QWidget*)));
    connect(this,SIGNAL(send_window4(QWidget*)),window_adding,SLOT(take_window4(QWidget*)));


    connect(this,SIGNAL(send_data_base_connection(DataBaseAction*)),
            tool_add_window,SLOT(receive_data_base_action(DataBaseAction*)));
    connect(this,SIGNAL(send_data_base_connection(DataBaseAction*)),
            sensor_add_window,SLOT(receive_data_base_action(DataBaseAction*)));
    connect(this,SIGNAL(send_data_base_connection(DataBaseAction*)),
            additional_mnemonic_add_window,SLOT(receive_data_base_action(DataBaseAction*)));
    connect(this,SIGNAL(send_data_base_connection(DataBaseAction*)),
            main_mnemonic_add_window,SLOT(receive_data_base_action(DataBaseAction*)));

    connect(this,SIGNAL(send_data_base_connection(DataBaseAction*)),
            update_tool_window,SLOT(receive_data_base_action(DataBaseAction*)));
    connect(this,SIGNAL(send_data_base_connection(DataBaseAction*)),
            update_sensor_window,SLOT(receive_data_base_action(DataBaseAction*)));
    connect(this,SIGNAL(send_data_base_connection(DataBaseAction*)),
            update_main_mnemonic_window,SLOT(receive_data_base_action(DataBaseAction*)));
    connect(this,SIGNAL(send_data_base_connection(DataBaseAction*)),
            update_additional_mnemonic_window,SLOT(receive_data_base_action(DataBaseAction*)));



    connect(this,SIGNAL(send_data_name(QString&)),
            update_tool_window,SLOT(recieve_data_name(QString&)));
    connect(this,SIGNAL(send_data_name(QString&)),
            update_sensor_window,SLOT(recieve_data_name(QString&)));
    connect(this,SIGNAL(send_data_name(QString&)),
            update_main_mnemonic_window,SLOT(recieve_data_name(QString&)));
    connect(this,SIGNAL(send_data_name(QString&)),
            update_additional_mnemonic_window,SLOT(recieve_data_name(QString&)));

    //очень глупое действие.для update было сделано адекватно.
    connect(tool_add_window,SIGNAL(refreshing_bd()),tool_add_window,SLOT(refreshed_bd_slot()));
    connect(tool_add_window,SIGNAL(refreshing_bd()),sensor_add_window,SLOT(refreshed_bd_slot()));
    connect(tool_add_window,SIGNAL(refreshing_bd()),main_mnemonic_add_window,SLOT(refreshed_bd_slot()));
    connect(tool_add_window,SIGNAL(refreshing_bd()),additional_mnemonic_add_window,SLOT(refreshed_bd_slot()));
    connect(sensor_add_window,SIGNAL(refreshing_bd()),tool_add_window,SLOT(refreshed_bd_slot()));
    connect(sensor_add_window,SIGNAL(refreshing_bd()),sensor_add_window,SLOT(refreshed_bd_slot()));
    connect(sensor_add_window,SIGNAL(refreshing_bd()),main_mnemonic_add_window,SLOT(refreshed_bd_slot()));
    connect(sensor_add_window,SIGNAL(refreshing_bd()),additional_mnemonic_add_window,SLOT(refreshed_bd_slot()));
    connect(main_mnemonic_add_window,SIGNAL(refreshing_bd()),tool_add_window,SLOT(refreshed_bd_slot()));
    connect(main_mnemonic_add_window,SIGNAL(refreshing_bd()),sensor_add_window,SLOT(refreshed_bd_slot()));
    connect(main_mnemonic_add_window,SIGNAL(refreshing_bd()),main_mnemonic_add_window,SLOT(refreshed_bd_slot()));
    connect(main_mnemonic_add_window,SIGNAL(refreshing_bd()),additional_mnemonic_add_window,SLOT(refreshed_bd_slot()));
    connect(additional_mnemonic_add_window,SIGNAL(refreshing_bd()),tool_add_window,SLOT(refreshed_bd_slot()));
    connect(additional_mnemonic_add_window,SIGNAL(refreshing_bd()),sensor_add_window,SLOT(refreshed_bd_slot()));
    connect(additional_mnemonic_add_window,SIGNAL(refreshing_bd()),main_mnemonic_add_window,SLOT(refreshed_bd_slot()));
    connect(additional_mnemonic_add_window,SIGNAL(refreshing_bd()),additional_mnemonic_add_window,SLOT(refreshed_bd_slot()));

    connect(ui->treeView,SIGNAL(context_menu_signal(int,int)),this,SLOT(recieve_tree_view_context_menu(int,int)));
}

