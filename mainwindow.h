#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QUdpSocket>
#include <QMainWindow>
#include<packet.h>

#include <iostream>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//    void check_sender_bytes(QByteArray str);

    void sendAck(unsigned int cmdId);
signals:
    void acknowledgement();



private slots:
    void on_pushButton_clicked();
    void recived();


private:
    Ui::MainWindow *ui;
    QUdpSocket *send;
    QUdpSocket *recv;
};
#endif // MAINWINDOW_H
