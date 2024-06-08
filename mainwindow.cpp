#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QMessageBox>
#include <QGraphicsEffect>
#include <QDebug>
#include <QMessageBox>
#include </usr/include/syslog.h>

int testResult = 2;
int state_btn[4] = {};
int state_km[2] = {};
double step_test = 0.0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QScreen *screen = QGuiApplication::primaryScreen();
    timer = new QTimer();
    mainWindowSize = screen->geometry();
    QSize sizebtn = QSize( mainWindowSize.width()/7, mainWindowSize.height()/6);
    this->setWindowTitle("MOUSE TEST");
    this->resize( mainWindowSize.width(), mainWindowSize.height());
    this->setAttribute( Qt::WA_Hover, true );
    btn1 = new Label( "firstPosition",  "background-color:rgb( 133, 220, 80  );", "Первая позиция: наведите курсор мыши",  sizebtn);
    btn2 = new Label( "secondPosition", "background-color:rgb( 220, 180, 233 );", "Вторая позиция: наведите курсор мыши",  sizebtn);
    btn3 = new Label( "thirdPosition",  "background-color:rgb( 180, 220, 133 );", "Третья позиция: наведите курсор мыши",  sizebtn);
    btn4 = new Label( "fourthPosition", "background-color:rgb( 220, 133, 80  );", "Четвертая позиция: наведите курсор мыши", sizebtn);

    ui->topSpacer->addWidget( btn1 );
    ui->topSpacer->addStretch();
    ui->topSpacer->addWidget( btn2 );
    ui->bottomSpacer->addWidget( btn3 );
    ui->bottomSpacer->addStretch();
    ui->bottomSpacer->addWidget( btn4 );

    ui->note ->setStyleSheet("background-color:rgba(110, 110, 110, 0);\n border-style: solid;\n border-width: 1px;\n border-radius: 5px;\n border-color: rgba(80, 210, 255, 0);\n color: rgb(255, 255, 255);\n");
    ui->title->setStyleSheet("background-color:rgba(110, 110, 110, 0);\n border-style: solid;\n border-width: 1px;\n border-radius: 5px;\n border-color: rgba(80, 210, 255, 0);\n");
    ui->progressBar->setStyleSheet("border-style: solid;\n border-width: 1px;\n border-radius: 5px;\n border-color: rgba(80, 210, 255, 0);\n");
    ui->titleBackground->setFixedWidth(mainWindowSize.width()/4);
    ui->progressBar->setAlignment(Qt::AlignCenter );
    ui->verticalLayout->setAlignment(Qt::AlignCenter);

    addGraphics( ui->progressBar, 1 );
    addGraphics( ui->exitButton, 1 );
    addGraphics( ui->titleBackground, 1 );
    addGraphics(btn1, 0);
    addGraphics(btn2, 0);
    addGraphics(btn3, 0);
    addGraphics(btn4, 0);
    ui->rkm->hide();
    ui->lkm->hide();
    ui->rkm->setFixedHeight(mainWindowSize.height()/8);
    ui->lkm->setFixedHeight(mainWindowSize.height()/8);
    connect(timer, SIGNAL(timeout()),this,SLOT(test_km()));
    timer->start(500);
    ui->note->setText("Наведите курсор мыши на 4 позиции в углах экранна");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addGraphics(QWidget *wgt, int check)
{
    QGraphicsDropShadowEffect* effect;
    effect=new QGraphicsDropShadowEffect();


    if(check == 1)
    {

        wgt->setStyleSheet("background-color:rgba(110, 110, 110, 226);  color:rgb(230, 230, 215);");
        //wgt->setStyleSheet("background-color: qlineargradient(spread:repeat, x1:0, y1:0, x2:1, y2:1, stop:0.341463 rgba(254, 208, 199, 36), stop:0.629268 rgba(255, 255, 177, 34), stop:0.970732 rgba(255, 255, 255, 85));\n border-style: solid;\nborder-width: 1px;\nborder-radius: 5px;\n border-color: rgba(6, 242, 7, 0);\n color:rgb(255, 255, 255);");
        effect->setBlurRadius(120.0);
        effect->setOffset(8);
        effect->setColor(QColor(255, 255, 255, 210));
    }
    if(check == 0)
    {
        effect->setBlurRadius(220.0);
        effect->setOffset(7);
        effect->setColor(QColor(0, 0, 0, 255));
        wgt->setStyleSheet("background-color:rgba(153, 153, 153, 255);\n color:rgba(127, 227, 250, 255);\n border-style: outset;\nborder-width: 1px;\nborder-radius: 3px;\n border-color: rgba(127, 227, 250, 175);\n font-weight: bold; font-size:11pt;\n");
    }
    if (check == 2)
    {
        effect->setBlurRadius(25.0);
        effect->setOffset(8);
        effect->setColor(QColor(8, 241, 29, 250));
        wgt->setStyleSheet("background-color:rgba(55, 255, 61, 85); \n border-style: solid;\nborder-width: 1px;\nborder-radius: 5px;\n border-color: rgba(6, 242, 7, 230);\n color:rgb(255, 255, 255);");
    }

    wgt->setGraphicsEffect(effect);

}

void MainWindow::graphicsBtn(QGridLayout *glayout)
{

    const int count_wgt = glayout -> count();

    QGraphicsDropShadowEffect* effect[count_wgt];

    for(int f = 0; f < count_wgt; f++)
    {

        effect[f] = new QGraphicsDropShadowEffect();
        QLabel *btn = (QLabel*) glayout -> itemAt(f) -> widget();
        if( (btn->objectName() != "win") && (btn->objectName() != "win2"))
        {
            effect[f]->setBlurRadius(20.0);
            effect[f]->setOffset(3);
            effect[f]->setColor(QColor(10, 10, 10, 170));
            btn->setStyleSheet("background-color:rgba(197, 197, 197, 255);\n color:rgb(30, 30, 70);");
            btn -> setGraphicsEffect(effect[f]);
        }
    }

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //ui->point->setText( QString("%d").number(event->pos().x()) + ", "+ QString("%d").number(event->pos().y()) );
    qDebug() << ( QString("%d").number(event->pos().x()) + ", "+ QString("%d").number(event->pos().y()) );
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event->pos();//вот это

    if(event->buttons() == Qt::RightButton)
    {
        addGraphics(  ui->rkm, 2);

        state_km[0] = 1;
        step_test ++;

    }
    if(event->buttons() == Qt::LeftButton)
    {
        addGraphics(  ui->lkm, 2);

        state_km[1] = 1;
        step_test++;
    }

}

void MainWindow::test_km()
{
    if( (state_btn[0] == 1) & (state_btn[1] == 1) & (state_btn[2] == 1) & (state_btn[3] == 1) & (step_test < 5) )
    {
        ui->note->setText("Последовательно щелкните правой и левой кнопками манипувлятора");
        step_test ++;
        ui->rkm->show();
        ui->lkm->show();
    }

    ui->progressBar->setValue(step_test*(14.28571428571429));

    if( ui->progressBar->value() >= 100 )
    {
        ui->note->setText( "Тест успешно завершен" );
        testResult = 1;

    }
}

void MainWindow::on_exitButton_clicked()
{
    if(state_km[1] == 0)
        syslog(LOG_USER, "%s", "ERROR  test mouse: LeftButton ");
    if(state_km[0] == 0)
        syslog(LOG_USER, "%s", "ERROR  test mouse: RightButton ");
    if((state_btn[0] != 1) & (state_btn[1] != 1) & (state_btn[2] != 1) & (state_btn[3] != 1) )
        syslog(LOG_USER, "%s", "ERROR  test mouse: move event ");
    exit (testResult);
}

Label::Label(QString objName, QString color, QString title, QSize size)
{
    this->setObjectName( objName );
    this->setText( title );
    this->setFocusPolicy( Qt::NoFocus );
    this->setFixedSize(size);
    this->setWordWrap(true);
    this->setAlignment(Qt::AlignCenter);

}

void Label::enterEvent(QEvent *e)
{
    qDebug() << "enter " << this->objectName();

    this->hide();
    if(this->objectName() == "firstPosition")
    {
        state_btn[0]=1;
    }
    if(this->objectName() == "secondPosition")
    {
        state_btn[1]=1;
    }
    if(this->objectName() == "thirdPosition")
    {
        state_btn[2]=1;
    }
    if(this->objectName() == "fourthPosition")
    {
        state_btn[3]=1;
    }

    step_test ++;

}

void Label::leaveEvent(QEvent *e)
{
    qDebug() << "leave " << this->objectName();
}


