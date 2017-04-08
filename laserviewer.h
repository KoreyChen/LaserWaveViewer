#ifndef LASERVIEWER_H
#define LASERVIEWER_H

#include <QMainWindow>

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QThread>
#include <QTime>
#include <QFileDialog>
#include <QTextCursor>
#include <QLabel>

#include <QFileInfo>
#include <QFile>
#include <iostream>
#include <QByteArray>
#include <QCoreApplication>
#include <QTextStream>
#include <QMessageBox>
#include <QPainter>

namespace Ui {
class LaserViewer;
}

class LaserViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit LaserViewer(QWidget *parent = 0);
    ~LaserViewer();

private slots:
    void on_OpenCloseButton_clicked();
    void SerialPortReadSlot();
    void on_ClearButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::LaserViewer *ui;

    QLabel *msgLabel;
    QSerialPortInfo *serialInfo;
    QSerialPort *serialPort;
    QString comName;
    int comBaudRate;
    QSerialPort::StopBits comStopBits;
    QSerialPort::Parity   comDataParity;
    QSerialPort::DataBits comDataBits;
    int comReadBufferSize;
    int recevieDataCount;


    void DrawWaveform();
    int DrawHightConvertY(int hight);
    void paintEvent(QPaintEvent *event);

};

#endif // LASERVIEWER_H
