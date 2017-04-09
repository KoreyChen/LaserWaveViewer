#include "laserviewer.h"
#include "ui_laserviewer.h"


LaserViewer::LaserViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LaserViewer)
{
    ui->setupUi(this);

    //设置背景色
    ui->WaveWidget->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(48,47,47));//暗灰色
    ui->WaveWidget->setPalette(palette);
    //隐藏可吸附工具条
    //ui->mainToolBar->hide();

    //设置背景色
    ui->OpenCloseButton->setAutoFillBackground(true);

    //创建串口相关实体
    serialPort =new QSerialPort();
    serialInfo =new QSerialPortInfo();
    if(serialInfo->isNull())
    {
        foreach (*serialInfo, QSerialPortInfo::availablePorts())
        {
            qDebug() << "Name        : " << serialInfo->portName();
            qDebug() << "Description : " << serialInfo->description();
            qDebug() << "Manufacturer: " << serialInfo->manufacturer();
            QString comname= (serialInfo->portName())+" ("+(serialInfo->description())+')';
            ui->ComNumComboBox->addItem(comname);
        }
    }
    recevieDataCount=0;
    ui->recevieCountLabel->setText(" ");

    //消息窗口
    msgLabel = new QLabel;
    msgLabel->setMinimumSize(msgLabel->sizeHint());
    msgLabel->setAlignment(Qt::AlignHCenter);
    ui->statusBar->addWidget(msgLabel);
    ui->statusBar->setStyleSheet(QString("QStatusBar::item{border: 0px}"));


    //画图
    painter  = new WavePainterWidget();

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setMargin(0); //设置边框大小
    gridLayout->setSpacing(0);//设置间距
    gridLayout->addWidget(painter, 0, 0);
    ui->WaveWidget->setLayout(gridLayout);//添加到窗口中



}

LaserViewer::~LaserViewer()
{
    delete ui;
}

void LaserViewer::DrawWaveform()
{
    int hight = ui->WaveWidget->geometry().height();
    int width = ui->WaveWidget->geometry().width();


    ui->recevieTextEdit->append("H:"+QString::number(hight,10));
    ui->recevieTextEdit->append("W:"+QString::number(width,10));

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));//没有这句的话，那么每次运行都会产生相同的随机数，那也就不叫随机数了。
    for(int i=0;i<1024;i++)
    {
        painter->WavePoint[i] = qrand()%256;;
    }
    painter->repaint();
    //ui->WaveWidget->repaint();
}

int LaserViewer::DrawHightConvertY(int hight)
{
     int M_hight = ui->WaveWidget->geometry().height();
     return  (M_hight-hight);
}


void LaserViewer::paintEvent(QPaintEvent *)
{

//        QPainter painter(ui->WaveWidget);
//        //QPainter painter(this);
//        // 反走样
//        painter.setRenderHint(QPainter::Antialiasing, true);
//        // 设置画笔颜色
//        painter.setPen(QColor(0, 160, 230));
//        // 绘制直线
//        painter.drawLine(0,0,100,100);
}














void LaserViewer::on_OpenCloseButton_clicked()
{
    if(ui->OpenCloseButton->text()=="Open")
    {
        try
        {

            QString str=ui->ComNumComboBox->currentText();
            QString comname=str.mid(0,4);
            comname.replace(" ","");
            comName=comname;

            str = ui->BaudNumComboBox->currentText();
            bool ok;
            comBaudRate = str.toInt(&ok,10); //comBaudRate=57600;

            comStopBits=QSerialPort::OneStop;//1停止位
            comDataParity=QSerialPort::EvenParity;//偶校验
            comDataBits=QSerialPort::Data8;
            comReadBufferSize=4096;
            //设置串口
            serialPort->setPortName(comName);
            serialPort->setBaudRate(comBaudRate);
            serialPort->setDataBits(comDataBits);
            serialPort->setParity(comDataParity);
            serialPort->setStopBits(comStopBits);
            serialPort->setFlowControl(QSerialPort::NoFlowControl);
            serialPort->setReadBufferSize(comReadBufferSize);
            if(serialPort->isOpen())
            {
                  msgLabel->setText("该串口已打开，请重新选择其他串口！");
            }else
            {
                if(serialPort->open(QSerialPort::ReadWrite))
                {
                      ui->OpenCloseButton->setText("Close");

                      connect(serialPort,SIGNAL(readyRead()),this,SLOT(SerialPortReadSlot()));

//                      QPalette palette;
//                      palette.setColor(QPalette::ButtonText, QColor(125,200,125));//绿色
//                      ui->OpenCloseButton->setPalette(palette);
                        ui->OpenCloseButton->setStyleSheet("background-color: rgb(125,200,125)");
                      msgLabel->setText("串口已打开,波特率="+str+",偶校验,1停止位,8数据位,无流控");
                }else
                {
                    msgLabel->setText("串口打开失败");
                }
            }
        }
        catch(QString exception)
        {
              QMessageBox *message=new QMessageBox();
              message->setText(exception);
              message->show();
        }

    }else if(ui->OpenCloseButton->text()=="Close")
    {
        try
        {
            if(serialPort->isOpen())
            {
                serialPort->close();
                ui->OpenCloseButton->setText("Open");
//                QPalette palette;
//                palette.setColor(QPalette::ButtonText, QColor(255,255,255));//白色
//                ui->OpenCloseButton->setPalette(palette);
                //ui->OpenCloseButton->setStyleSheet("background-color: rgb(230,230,230)");
                ui->OpenCloseButton->setStyleSheet("");
                ui->OpenCloseButton->setContextMenuPolicy(Qt::DefaultContextMenu);
                msgLabel->setText("串口已关闭");
            }
        }
        catch(QString exception)
        {
              QMessageBox *message=new QMessageBox();
              message->setText(exception);
              message->show();
        }
    }
}
void LaserViewer::SerialPortReadSlot()
{
    QByteArray recevieDataArry = serialPort->readAll();
    recevieDataCount += recevieDataArry.count();
    //ui->recevieTextEdit->append(temp);//自动换行
    ui->recevieTextEdit->moveCursor(QTextCursor::End);
    if(ui->HexShowCheckBox->isChecked()==false)
    {
        ui->recevieTextEdit->insertPlainText(recevieDataArry);
    }else
    {
        QString str;
        foreach(unsigned char ch,recevieDataArry)
        {
                if(ch<16)
                    str +='0'+QString::number(ch,16).toUpper()+' ';
                else
                str +=QString::number(ch,16).toUpper()+' ';
        }
         ui->recevieTextEdit->insertPlainText(str);
    }
    ui->recevieCountLabel->setText(QString::number(recevieDataCount,10));
}

void LaserViewer::on_ClearButton_clicked()
{
    recevieDataCount=0;
    ui->recevieCountLabel->setText(" ");
    ui->recevieTextEdit->clear();
}




void LaserViewer::on_pushButton_clicked()
{
    DrawWaveform();
}
