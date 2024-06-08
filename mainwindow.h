#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QHoverEvent>
#include <QTimer>


namespace Ui {
class MainWindow;
class Label;
}
class Label : public QLabel
    {
        Q_OBJECT

    public:
        Label(QString objName, QString color, QString title, QSize size);
        void enterEvent(QEvent *e);
        void leaveEvent(QEvent *e);

    };

class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
        void addGraphics(QWidget *wgt, int check);
        void graphicsBtn(QGridLayout *glayout);
        void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);
        QTimer *timer;
        QGraphicsDropShadowEffect* effectEnd;
        Label *btn1;
        Label *btn2;
        Label *btn3;
        Label *btn4;
        QRect mainWindowSize;

    private slots:
        void on_exitButton_clicked();
        void test_km();

    private:
        Ui::MainWindow *ui;
    };


#endif // MAINWINDOW_H
