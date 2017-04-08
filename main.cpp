#include "laserviewer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LaserViewer w;
    w.show();

    return a.exec();
}
