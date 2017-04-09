#ifndef WAVEPAINTERWIDGET_H
#define WAVEPAINTERWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QDebug>

class WavePainterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WavePainterWidget(QWidget *parent = 0);

    int WavePoint[1024];

signals:

public slots:

private:

    QPixmap *pix;
    void paintEvent(QPaintEvent *);
};

#endif // WAVEPAINTERWIDGET_H
