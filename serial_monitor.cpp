#include "serial_monitor.h"
#include "ui_serial_monitor.h"

Serial_Monitor::Serial_Monitor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Serial_Monitor)
{
    ui->setupUi(this);
    connect(&serial,SIGNAL(readyRead()),this,SLOT(ReadData()));

    ui->com->clear();
    Q_FOREACH(seril_info, QSerialPortInfo::availablePorts())
    {
        ui->com->addItem(seril_info.portName());
    }
}

Serial_Monitor::~Serial_Monitor()
{
    ClosePort();
    delete ui;
}

void Serial_Monitor::Refresh(void)
{
    ClosePort();
    ui->com->clear();
    Q_FOREACH(seril_info, QSerialPortInfo::availablePorts())
    {

            ui->com->addItem(seril_info.portName());
            qDebug() <<"Refresh Com Port" << endl;
     }

}

void Serial_Monitor::OpenPort(void)
{
QString baud_rate = ui->baud_rate->itemText(ui->baud_rate->currentIndex());
QString data=ui->data_size->itemText(ui->data_size->currentIndex());
QString satatus_parity=ui->parity->itemText(ui->parity->currentIndex());
QString stop=ui->stop_bit->itemText(ui->stop_bit->currentIndex());


    serial.setPortName(ui->com->itemText(ui->com->currentIndex()));


    serial.setBaudRate(baud_rate.toInt() , QSerialPort::Input);

    if(data.toInt() == 7)
       serial.setDataBits(serial.Data7);

    else if(data.toInt() == 8)
       serial.setDataBits(serial.Data8);

    if(satatus_parity == "none")
        serial.setParity(serial.NoParity);

    else if(satatus_parity == "even")
        serial.setParity(serial.EvenParity);

    else if(satatus_parity == "odd")
        serial.setParity(serial.OddParity);

    if(stop == "one")
        serial.setStopBits(serial.OneStop);
    else
     serial.setStopBits(serial.TwoStop);


    qDebug() << baud_rate << endl;
    qDebug() << data << endl;
    qDebug() << satatus_parity << endl;
    qDebug() << stop << endl;

    if(serial.open(QIODevice::ReadWrite))
         qDebug() <<"com port open"<<endl;


    else
    {
        qDebug() <<"com port is busy"<<endl;
        ClosePort();
        QMessageBox::information(this, "Error", "port is Busy");
    }


}

void Serial_Monitor::ClosePort(void)
{
    serial.close();
    qDebug() <<"com port closed"<<endl;
}

void Serial_Monitor::Send(void)
{
    if (serial.isOpen())
    {
        QString data=ui->text_send->toPlainText();
        QByteArray DataSend;
        DataSend.append(data);
        serial.write(DataSend);
        qDebug() <<"send..."<<endl;
    }
    qDebug() <<"send..."<<endl;


}

void Serial_Monitor::ReadData(void)
{
    QByteArray data_read=serial.readAll();
    ui->text_read->insertHtml("<font color=\"red\">" + data_read +"</font>" + "<br>");
}

void Serial_Monitor::Clear_Send(void)
{
    ui->text_send->clear();
    qDebug() <<"clear text"<<endl;
}

void Serial_Monitor::Clear_Read(void)
{
    ui->text_read->clear();
    qDebug() <<"clear text_read"<<endl;
}
