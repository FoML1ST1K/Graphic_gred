#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QTimer>
#include <QPainter>
#include <QPoint>
#include "math.h"
#include <QPropertyAnimation>
#include <QDesktopWidget>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QFont>

#include <QApplication>
#include <QInputDialog>

#include <QRandomGenerator>

namespace Ui {
class Widget;
}

class my : public  QGraphicsEllipseItem
{

public:
     my(int size, int state);
};

class Widget : public QWidget
{
    Q_OBJECT

public:
   explicit Widget(QWidget *parent = 0);
    ~Widget();
   QGraphicsScene* scene;

   my *elips;

   double Pi=3.14159265,y1=40.5,y2=40.5,x1=20.0,x2=30.7,
   radius=250,radius2=285,radius3=265,radius4=260,cx=250,cy=250,alfa=0.0,alfaa=360.0,alfa1=0.0,alfa2=0.0;

   void mousePressEvent(QMouseEvent *event);
private slots:
   void on_pushButton_clicked(bool isRun); //изменить название
   void Timeout();

public:
   void movePoints(QPointF &pointCoord);
   QPointF pointCoord;

private:
    Ui::Widget *ui;
    QTimer *timer;
    QPushButton *pushButton;
    QPointF pointPos;

    //my *square;//создаем квадрат
};

#endif // WIDGET_H
