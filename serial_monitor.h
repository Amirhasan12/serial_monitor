#ifndef SERIAL_MONITOR_H
#define SERIAL_MONITOR_H

#include <QMainWindow>
#include <iostream>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class Serial_Monitor; }
QT_END_NAMESPACE

class Serial_Monitor : public QMainWindow
{
    Q_OBJECT

public:
    Serial_Monitor(QWidget *parent = nullptr);
    ~Serial_Monitor();

private:
    Ui::Serial_Monitor *ui;

    QSerialPort serial;
    QSerialPortInfo seril_info;


private slots:
    void Send(void);
    void ReadData(void);
    void OpenPort(void);
    void ClosePort(void);
    void Clear_Send(void);
    void Clear_Read(void);
    void Refresh(void);
};
#endif // SERIAL_MONITOR_H
