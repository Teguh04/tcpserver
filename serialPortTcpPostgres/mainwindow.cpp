#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include <QSerialPort>
#include <QSqlQueryModel>
#include <QtCore>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

    //port setting
    QSettings settings("config/config.ini", QSettings::IniFormat);
    settings.beginGroup("AIS");
    const QStringList childKeys = settings.childKeys();
    QStringList values;
    foreach (const QString &childKey, childKeys){
        values << settings.value(childKey).toString();
    }
    settings.endGroup();

    //connect to serial port
    ui->setupUi(this);
    port = new QSerialPort(this);
    port->setBaudRate(values[0].toInt());

    if(values[1].toInt() == 5){
        port->setDataBits(QSerialPort::Data5);
    } else if(values[1].toInt() == 6){
        port->setDataBits(QSerialPort::Data6);
    } else if(values[1].toInt() == 7){
        port->setDataBits(QSerialPort::Data7);
    } else if(values[1].toInt() == 8){
        port->setDataBits(QSerialPort::Data8);
    } else {
        qDebug() << "Serial Port Not Connected";
        exit(0);
    }

    if(values[2].toInt() == 0){
        port->setParity(QSerialPort::NoParity);
    } else if(values[2].toInt() == 2){
        port->setParity(QSerialPort::EvenParity);
    } else if(values[2].toInt() == 3){
        port->setParity(QSerialPort::OddParity);
    } else if(values[2].toInt() == 4){
        port->setParity(QSerialPort::SpaceParity);
    } else if(values[2].toInt() == 5){
        port->setParity(QSerialPort::MarkParity);
    } else if(values[2].toInt() == -1){
        port->setParity(QSerialPort::UnknownParity);
    } else {
        qDebug() << "Serial Port Not Connected";
        exit(0);
    }

    port->setPortName(values[3]);

    if(values[4].toInt() == 1){
        port->setStopBits(QSerialPort::OneStop);
    } else if(values[4].toInt() == 2){
        port->setStopBits(QSerialPort::TwoStop);
    } else if(values[4].toInt() == 3){
        port->setStopBits(QSerialPort::OneAndHalfStop);
    } else if(values[4].toInt() == -1){
        port->setStopBits(QSerialPort::UnknownStopBits);
    } else {
        qDebug() << "Serial Port Not Connected";
        exit(0);
    }

    if (port->open(QIODevice::ReadWrite)){
        qDebug() << "Serial Port Connected";
    }else{
        qDebug() << "Serial Port Not Connected";
        exit(0);
    }

    //connect to database postgres
    connection();

    socket = new QTcpSocket(this);
    server = new QTcpServer(this);

    //signal slot
    connect(ui->pushButton,SIGNAL(clicked()), this, SLOT(serialRecieved()));
    connect(server, SIGNAL(newConnection()),this, SLOT(newConnection()));

    //active server
    if(!server->listen(QHostAddress::Any, 1234)){
        qDebug() << "Server could not start";
        exit(0);
    }else{
        qDebug() << "Server started!";
    }
}

void MainWindow::newConnection(){

    //get client name
    list.append(server->nextPendingConnection());
    QString line = QString::fromUtf8(list.last()->readLine()).trimmed();
    if(line == ""){
        ui->textEdit_2->append("cannot detect client");
    }else{
        ui->textEdit_2->append(line);
    }

}

MainWindow::~MainWindow(){
    delete ui;
    port->close();
}

void MainWindow::serialRecieved(){
    port->open(QIODevice::ReadWrite);

    //buffer for port->readAll()
    static QByteArray byteArray;
    byteArray += port->readAll();

    if(!QString(byteArray).contains("\n")){
        return;
    }

    QString data = QString::fromLatin1(byteArray).remove("\r").remove("\n");
    byteArray.clear();

    QMutex lineMutex;

    lineMutex.lock();
    if(ui->textEdit->toPlainText().length()>=3000){
        ui->textEdit->clear();
    }

    //display data from serial port to text edit
    ui->textEdit->append(data + "\n");

    //save data from serial port to database postgres
    this->model = new QSqlQueryModel();
    model->setQuery("INSERT INTO serialport(data) VALUES('"+ data +"');");
    model->setQuery("SELECT COUNT(data) FROM serialport;");

    //display count data from database to ui
    ui->tableView->setModel(model);
    lineMutex.unlock();

    //write data from serial port to client
    if(list.isEmpty()){
        return;
    }else{
        lineMutex.lock();
        for(int i = 0; i < list.size(); i++){
            list.at(i)->write(data.toUtf8());
            list.at(i)->flush();
        }
        lineMutex.unlock();
    }

}

void MainWindow::on_pushButton_clicked(){
    connect(port,SIGNAL(readyRead()), this, SLOT(serialRecieved()));
}


void MainWindow::on_pushButton_2_clicked(){
    ui->textEdit->clear();

    //close port
    port->close();
    for(int i = 0; i < list.size(); i++){
        list.at(i)->write("Stopped from Server");
        list.at(i)->flush();
    }

    ui->textEdit->clear();
    ui->textEdit->append("Stopped");
}
