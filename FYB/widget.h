#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mypushbutton.h"
#include <QLabel>
#include "gameplay.h"
#include "mymoneybutton.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent *);//背景绘图

private:
    Ui::Widget *ui;
    MyPushButton *buttonStart;//开始游戏按钮
    MyPushButton *buttonClose;//退出游戏按钮
    GamePlay *myPlays;//关卡
};

#endif // WIDGET_H
