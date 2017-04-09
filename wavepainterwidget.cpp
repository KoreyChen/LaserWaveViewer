#include "wavepainterwidget.h"

WavePainterWidget::WavePainterWidget(QWidget *parent) : QWidget(parent)
{
   this->resize(1024, 256);
    //setWindowTitle(tr("Paint Demo"));
    // pix = new QPixmap(size());    //这个pixmap对象用来接受准备绘制到空间的内容
    //pix->fill(Qt::white);        //填充这个图片的背景是白色
}

void WavePainterWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::red);
//    painter.drawLine(0, 0, 1024, 256);
//    painter.setPen(Qt::blue);
//    painter.drawRect(10, 10, 100, 100);
//    painter.setPen(QPen(Qt::green, 5));
//    painter.setBrush(Qt::blue);
//    painter.drawEllipse(50, 50, 100, 100);

//    for(int i=0;i<1024;i++)
//    {
//        WavePoint[i] = i/5;
//    }

    for(int i=0;i<1024;i++)
    {
         if(WavePoint[i]>256)
             WavePoint[i]=256;
         painter.drawPoint(i,256-WavePoint[i]);
         //qDebug() << WavePoint[i] ;
    }


   // painter.drawPixmap(QPoint(0, 0), *pix);     //重0,0开始绘制这个图片

}

