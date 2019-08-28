#ifndef MYMONEYBUTTON_H
#define MYMONEYBUTTON_H

#include <QPushButton>
#include <QTimer>

class MyMoneyButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyMoneyButton(QWidget *parent = nullptr);
    MyMoneyButton(QString imageB);
    void boolChange();//如何翻面
    void mousePressEvent(QMouseEvent *e);//重写按下

public:
    int moneyX;
    int moneyY;
    bool moneyBool;
    bool isWin = false;
signals:

public slots:
private:
    QTimer *myTimer1;//定时器翻到反面
    QTimer *myTimer2;//定时器翻到正面
    int min = 1;//最小的图片
    int max = 5;//最大的图片
    bool isAnimation = false;//是否做动画
};

#endif // MYMONEYBUTTON_H
