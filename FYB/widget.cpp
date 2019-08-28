#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QTimer>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(800, 450);

    //开始按钮
    buttonStart = new MyPushButton(":/Pixmap/image/start.png");
    buttonStart->setParent(this);
    buttonStart->move(this->width() * 0.5 - buttonStart->width() * 0.5, 120);
    connect(buttonStart, &MyPushButton::clicked, [=](){
        buttonStart->zoom1();
        buttonStart->zoom2();
        QTimer::singleShot(200, this, [=](){
            this->hide();
            myPlays = new GamePlay(1);
            myPlays->setGeometry(this->geometry());
            myPlays->show();
        });
    });

    //离开游戏
    buttonClose = new MyPushButton(":/Pixmap/image/close.png");
    buttonClose->setParent(this);
    buttonClose->move(this->width() * 0.5 - buttonStart->width() * 0.5, 250);
    connect(buttonClose, &MyPushButton::clicked, [=](){
        buttonClose->zoom1();
        buttonClose->zoom2();
        QTimer::singleShot(200, this, [=](){
            this->close();
        });
    });

}

Widget::~Widget()
{
    delete ui;
}

//背景
void Widget::paintEvent(QPaintEvent *)
{
    QPainter painterBackground(this);
    QPixmap pixmapBackground;
    pixmapBackground.load(":/Pixmap/image/75354898_p9.png");
    painterBackground.drawPixmap(0, 0, this->width(), this->height(), pixmapBackground);
}


