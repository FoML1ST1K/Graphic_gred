#include "widget.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    int size_y,size_x;
    QRect razmer = QApplication::desktop()->screenGeometry();

    size_x=razmer.width();
    size_y=razmer.height();

    qDebug()<<size_x<<"::"<<size_y ;

    w.show();
    w.resize(size_x,size_y);

    return a.exec();

}
