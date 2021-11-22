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
    recv->bind(SPORT);
    connect(recv,SIGNAL(readyRead()),this,SLOT(recived()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::check_sender_bytes(QByteArray str)
//{
//    UINT16 header= 0x8765;
//    UINT16 footer= 0x4321;
//    UINT16 u32CmdId= CONNECT_COMMAND;

//    QByteArray sendBuffer;

//    sendBuffer[0]= 0x87;
//    sendBuffer[1]= 0x65;
//    int offset=0+2;

//    __bswap_16 (u32CmdId);
//    memcpy(sendBuffer.data()+offset, (void*)&u32CmdId, 2);
//    offset+= 2;


//    sendBuffer[offset]= 0x43;
//    offset+=1;
//    sendBuffer[offset]= 0x21;

//    if(str[0]==sendBuffer[0]&&str[1]==sendBuffer[1])

//   ui->label_2->setText( str.mid(2,2).toHex());
//   ui->label_4->setText(str.mid(4,26));

//}


void MainWindow::on_pushButton_clicked()
{
   QByteArray datagram;

   datagram.append("hello world");
    quint32 data1=send->writeDatagram(datagram,QHostAddress::LocalHost,RPORT);
    qDebug()<<data1;
}

void MainWindow::recived()
{
    bool res=recv->hasPendingDatagrams();
    QHostAddress addr(QHostAddress("192.168.137.1"));
    quint16 port=SPORT;
    QByteArray datagram,str;

    struct packet;
    if(res)
   {
    datagram.resize(recv->pendingDatagramSize());
       recv->readDatagram(datagram.data(),datagram.size(),&addr,&port);
//       qDebug()<<datagram.toHex();

        UINT16 cmdId;
        UINT8* parser= (char*)&cmdId;
        int cmdIdOffset=1;
//        qDebug()<<datagram.data()+1;
        memcpy(&cmdId, datagram.data()+2, 2);

        switch(cmdId){
            case CONNECT_COMMAND:
                sendAck(cmdId);
            break;
        default:
            qDebug()<<"fuckk noor";
        }

    }
}

void MainWindow::sendAck(unsigned int cmdId){
    UINT16 header;
    UINT16 footer;

    UINT8 ack= ACK;

    header= HEADER;
    footer= FOOTER;

    UINT8 sendBuffer[MAX_SIZE];

    UINT8* sendPtr= sendBuffer;
    int offset=0;

    memcpy(&sendPtr[offset], &header, 2);
    offset+=2;

    memcpy(&sendPtr[offset], &cmdId, 2);
    offset+=2;

    memcpy(&sendPtr[offset], &ack, 1);
    offset+=1;

    memcpy(&sendPtr[offset], &footer, 2);
    offset+=2;

    int writtenBytes= send->writeDatagram((char*)sendBuffer,
                                          offset,
                                          QHostAddress(SONU_ADDR),
                                          RPORT);

    qDebug()<<"WrittenBytes:"<<writtenBytes;
}
