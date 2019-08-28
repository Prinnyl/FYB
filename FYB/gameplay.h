#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QWidget>
#include <QLabel>
#include "mymoneybutton.h"
#include "mypushbutton.h"

class GamePlay : public QWidget
{
    Q_OBJECT
public:
    //explicit GamePlay(QWidget *parent = nullptr);
    GamePlay(int level);
public:
    void paintEvent(QPaintEvent *);//背景绘图


signals:

public slots:
private:
    int myLevel;//当前关卡
    QLabel *lableGame;//硬币背景
    GamePlay *myPlays;
    MyPushButton *buttonLast;//上一关
    MyPushButton *buttonNext;//下一关
    MyPushButton *buttonClose;//退出按钮
    QLabel *lableTitle;//标题
    int gameArray[4][4];//保存用数组
    MyMoneyButton *moneyArray[4][4];//修改判断用数组
    bool isWin = false;//是否胜利
    QLabel *lableWin;//胜利显示
};

#endif // GAMEPLAY_H
