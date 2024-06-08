#include "widget.h"
#include "ui_widget.h"

#include <cmath>
#include <QScreen>
#include <QGraphicsEffect>
#include <QGraphicsView>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>

QList<QGraphicsEllipseItem *> points;
const int maxPoints = 1;//Количество макс точек
bool dialogShow = false; //Проверяет было ли вызвано ранее окна ввода радиуса
int newRadius = 50, insade;
QPoint center1(498,517);//Центр Qt координат

Widget::Widget(QWidget *parent) : QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QFont times("Times",10,QFont::Bold);
    QString text;
    QPen penBlack(Qt::black);

    scene = new QGraphicsScene(500,0,500,500,this);//создаем сцену)

    scene->addItem(new my((scene->sceneRect().width() ),0 ) );//elipse

    scene->addItem(new my((scene->sceneRect().width() - scene->sceneRect().width() / 5 ),
                          scene->sceneRect().width() / 10) );//elipse

    scene->addItem(new my((scene->sceneRect().width() - scene->sceneRect().width() / 2.5 ),
                          scene->sceneRect().width() / 5) );//elipse

    scene->addItem(new my((scene->sceneRect().width() / 2.5 ),
                          (scene->sceneRect().width() / 3.3 ) ) );//elipse

    scene->addItem(new my((scene->sceneRect().width() / 6 ),
                          (scene->sceneRect().width() / 2.4 ) ) );//elipse


    while  (alfa!=360){

        x1=radius*(cos(Pi/180.0*alfa));
        x1=cx-x1;

        y1=radius*(sin(Pi/180.0*alfa));
        y1=cy-y1;

        x2=radius2*(cos(Pi/180.0*alfaa));
        x2=cx-x2;

        y2=radius2*(sin(Pi/180.0*alfaa));
        y2=cy-y2;
        text=QString::number(alfa);

        scene->addText(text,times)->setPos(y2-18,x2-14);

        //scene->addLine(y1,x1,y2,x2,penBlack); //не знаю как сделать

        alfa+=10.0;
        alfaa-=10;
    }

    while  (alfa1!=360){

        alfa1+=5.0;

        x1=radius*(cos(Pi/180.0*alfa1));
        x1=cx-x1;

        y1=radius*(sin(Pi/180.0*alfa1));
        y1=cy-y1;

        x2=radius3*(cos(Pi/180.0*alfa1));
        x2=cx-x2;

        y2=radius3*(sin(Pi/180.0*alfa1));
        y2=cy-y2;

        scene->addLine(y1,x1,y2,x2,penBlack);
    }

    while  (alfa2!=360){

        alfa2+=1.0;

        x1=radius*(cos(Pi/180.0*alfa2));
        x1=cx-x1;

        y1=radius*(sin(Pi/180.0*alfa2));
        y1=cy-y1;

        x2=radius4*(cos(Pi/180.0*alfa2));
        x2=cx-x2;

        y2=radius4*(sin(Pi/180.0*alfa2));
        y2=cy-y2;

        scene->addLine(y1,x1,y2,x2,penBlack);
    }
    ui->graphicsView->setScene(scene);//Устанавливаем сцену

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout, this, &Widget::Timeout);

    if (!dialogShow){//Вызывает окно для вычисления максимального радиуса
        bool ok;
        newRadius = QInputDialog::getInt(nullptr, "Number", "Enter:", 50, 1, 100, 1, &ok);
        if (ok){
            dialogShow = true;
        }
    }
}

my::my(int size,int state):QGraphicsEllipseItem(0)
{
    QColor color = QColor (170,170,170);//задали цвет
    setBrush(color);//установили цвет
    setRect(state,state,size,size);//
    //setPos(400,400);//позиция

}

void Widget::mousePressEvent(QMouseEvent *event)
{
    QPointF pos = event->pos();//Перемещения точек (вычисление координат)
//    qDebug() << event->pos();

    int radius_elipse = 250;
    int dx=center1.x() - event->x();
    int dy=center1.y() - event->y();
    insade = dx * dx + dy * dy <= radius_elipse * radius_elipse;//для проверки того что точка внутри окружности

    int centerX = 0;//Отображения нормальных координат
    int centerY = 0;
    QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(centerX - newRadius, centerY - newRadius, 2 * newRadius, 2*newRadius);
    circle->setBrush(Qt::gray);
    qreal sclFact = static_cast<qreal> (newRadius) / static_cast<qreal>(radius_elipse);
    QTransform transform;
    transform.scale(sclFact,sclFact);
    circle->setTransform(transform);
    QPointF itemPos = circle->mapToScene(event->pos());
    int itemPos1=center1.x() * sclFact-itemPos.x();
    int itemPoss=center1.y() * sclFact-itemPos.y();
    qDebug() << "Точка: " << -itemPos1 << itemPoss;

    if (insade == 1){//Удаление последней точки
        if (points.size() >= maxPoints){
            QGraphicsEllipseItem *oldestPoint = points.first();
            scene->removeItem(oldestPoint);
            delete oldestPoint;
            points.removeFirst();
        }
        QGraphicsEllipseItem *point = new QGraphicsEllipseItem(-250,-270,3,3);
        point->setBrush(Qt::red);
        scene->addItem(point);
        points.append(point);
        point->setPos(pos);
    }
    pointCoord = event->pos();//для перемещения точек (передача координат)
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked(bool isRun) //поменять название
{
    if (isRun){
        timer->start(1000);
        foreach (QGraphicsEllipseItem* point, points){
            pointPos = point->scenePos();
        }
    } else
        timer ->stop();
}

void Widget::Timeout()
{
    static int seconds = 0;
    movePoints(pointCoord);
    qDebug() << "Seconds: "<< seconds++;
}

void Widget::movePoints(QPointF &pointCoord)
{
    foreach (QGraphicsEllipseItem *point, points){
        QPointF newPos;

        qreal dx = QRandomGenerator::global()->bounded(-100,100);//случайное премещение точек в пределе [-100,100)
        qreal dy = -1*QRandomGenerator::global()->bounded(-100,100);

        qDebug() << "Смещение: " << dx << dy;

        newPos = QPointF(dx,dy) + pointCoord;
        dx = dx + pointCoord.x();
        dy = dy + pointCoord.y();

        qreal distance = QLineF(center1, newPos).length();//Расчёт дистанции от центра до новой точки
//        qDebug() << "Дистанция:" << distance;

        if (distance <= 250){//Проверка того что новая точка будет в окружности
            point->setPos(dx,dy);
            qDebug() << "Старая: " << pointCoord;
            qDebug() << "Новая: " << newPos;
            pointCoord = newPos;
        }
    }
}
