#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSqlQueryModel>
#include <QTcpSocket>
#include <QTcpServer>

namespace Ui{
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QSerialPort *port;
    QList<QTcpSocket*> list;

public slots:
    void serialRecieved();
    void newConnection();
    void on_pushButton_clicked();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QSqlQueryModel *model;
    QTcpSocket *socket;
    QTcpServer *server;
};

#endif // MAINWINDOW_H
