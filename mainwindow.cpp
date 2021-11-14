#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<string.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    send=new QUdpSocket();
    recv=new QUdpSocket();
    recv->bind(QHostAddress::LocalHost,5000);
    connect(recv,SIGNAL(readyRead()),this,SLOT(recived()));

}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_clicked()
{
    UINT8* data="hello friends chai peelo";

    UINT16 header= 0x8765;
    UINT16 footer= 0x4321;
    UINT16 u32CmdId= CONNECT_COMMAND;


//   UINT8* buffer[4]={(char*)&header,(char*)&cmdId,data,(char*)&footer};
    QByteArray sendBuffer;

    sendBuffer[0]= 0x87;
    sendBuffer[1]= 0x65;
    int offset=0+2;

    __bswap_16 (u32CmdId);
    memcpy(sendBuffer.data()+offset, (void*)&u32CmdId, 2);
    offset+= 2;


    sendBuffer[offset]= 0x43;
    offset+=1;
    sendBuffer[offset]= 0x21;

    qDebug()<<"data:"<<sendBuffer.toHex();
    quint32 data1=send->writeDatagram(sendBuffer,QHostAddress::LocalHost,1234);
}

void MainWindow::recived()
{
    bool res=recv->hasPendingDatagrams();
    QHostAddress addr(QHostAddress::LocalHost);
    quint16 port=5000;
    struct packet pt;
    if(res)
   {
       QByteArray datagram;
       datagram.resize(recv->pendingDatagramSize());


//       recv->readDatagram((char*)&pt,datagram.size(),&addr,&port);
//               qDebug()<<pt.name<<endl;
//       qDebug()<<pt.a;
      recv->readDatagram(datagram.data(),datagram.size(),&addr,&port);
      qDebug()<<datagram.data();
      QString string=datagram.data();


    }
}

