#include "mymoneybutton.h"
#include <QMessageBox>

//MyMoneyButton::MyMoneyButton(QWidget *parent) : QPushButton(parent)
//{

//}
MyMoneyButton::MyMoneyButton(QString imageB)
{
    QPixmap pixmapImage;
    bool ret = pixmapImage.load(imageB);
    if(ret == false)
    {
        QMessageBox::warning(this, "错误", "加载硬币图片出错");
        return;
    }
    this->setFixedSize(pixmapImage.width(), pixmapImage.height());
    this->setStyleSheet("QPushButton{border : 0px;}");
    this->setIcon(pixmapImage);
    this->setIconSize(QSize(pixmapImage.width(), pixmapImage.height()));

    //初始化定时器
    myTimer1 = new QTimer(this);
    myTimer2 = new QTimer(this);

    connect(myTimer1, &QTimer::timeout, [=](){
        QPixmap moneyPixmap;
        QString moneyStr = QString(":/Pixmap/image/0%1.png").arg(this->min++);
        moneyPixmap.load(moneyStr);
        this->setFixedSize(moneyPixmap.width(), moneyPixmap.height());
        this->setStyleSheet("QPushButton{border : 0px;}");
        this->setIcon(moneyPixmap);
        this->setIconSize(QSize(moneyPixmap.width(), moneyPixmap.height()));
        //当大于5时重置为1
        if(this->min > this->max)
        {
            this->min = 1;
            isAnimation = false;
            myTimer1->stop();
        }
    });

    connect(myTimer2, &QTimer::timeout, [=](){
        QPixmap moneyPixmap;
        QString moneyStr = QString(":/Pixmap/image/0%1.png").arg(this->max--);
        moneyPixmap.load(moneyStr);
        this->setFixedSize(moneyPixmap.width(), moneyPixmap.height());
        this->setStyleSheet("QPushButton{border : 0px;}");
        this->setIcon(moneyPixmap);
        this->setIconSize(QSize(moneyPixmap.width(), moneyPixmap.height()));
        //当小于1时重置为5
        if(this->max < this->min)
        {
            this->max = 5;
            isAnimation = false;
            myTimer2->stop();
        }
    });
}

void MyMoneyButton::boolChange()
{
    if(this->moneyBool == true)
    {
        myTimer1->start(30);
        isAnimation = true;
        this->moneyBool = false;
    }
    else
    {
        myTimer2->start(30);
        isAnimation = true;
        this->moneyBool = true;
    }
}

void MyMoneyButton::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation || this->isWin == true)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}
