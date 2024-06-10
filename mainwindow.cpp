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
    connect(this,SIGNAL(send_window1(QWidget*)),window_adding,SLOT(take_window1(QWidget*)));
    connect(this,SIGNAL(send_window2(QWidget*)),window_adding,SLOT(take_window2(QWidget*)));
    connect(this,SIGNAL(send_window3(QWidget*)),window_adding,SLOT(take_window3(QWidget*)));
    connect(this,SIGNAL(send_window4(QWidget*)),window_adding,SLOT(take_window4(QWidget*)));

    connect(this,SIGNAL(send_data_base_connection(DataBaseAction*)),
            tool_add_window,SLOT(receive_data_base_action(DataBaseAction*)));
}

MainWindow::~MainWindow()
{
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
    BlobImageDelegate* blobDelegate=new BlobImageDelegate;
    blobDelegate->column_index=blobDelegate->column_fiend_index(ui->tableView,"image");//выбрать столбец с изображением если надо несколько, то переделать в массив и в blobimagedelegate
    ui->tableView->setItemDelegate(blobDelegate);
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
    DataBaseAction* p_data_base=&data_base_action;
    emit send_data_base_connection(p_data_base);
    qDebug()<<"signal1";

    window_adding->setModal(true);
    window_adding->exec();

}

