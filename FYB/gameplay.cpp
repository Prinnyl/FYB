#include "gameplay.h"
#include "mydata.h"
#include <QPainter>
#include <QDebug>
#include <QMessageBox>

//GamePlay::GamePlay(QWidget *parent) : QWidget(parent)
//{

//}

GamePlay::GamePlay(int level)
{
    this->myLevel = level;
    this->setFixedSize(800, 450);

    //上一关
    buttonLast = new MyPushButton(":/Pixmap/image/last.png", 2);
    buttonLast->setParent(this);
    buttonLast->move(45, 100);
    //qDebug() << level;
    if(myLevel < 2)
    {
        buttonLast->setEnabled(false);
    }
    connect(buttonLast, &MyPushButton::clicked, [=](){
        buttonLast->zoom1();
        buttonLast->zoom2();
        QTimer::singleShot(200, this, [=](){
            myPlays = new GamePlay(myLevel - 1);
            myPlays->setGeometry(this->geometry());
            myPlays->show();
            delete this;
        });
    });

    //下一关
    buttonNext = new MyPushButton(":/Pixmap/image/next.png", 2);
    buttonNext->setParent(this);
    buttonNext->move(45, 200);
    //qDebug() << level;
    buttonNext->setEnabled(false);
    connect(buttonNext, &MyPushButton::clicked, [=](){
        buttonNext->zoom1();
        buttonNext->zoom2();
        QTimer::singleShot(200, this, [=](){
            if(myLevel > 8)
            {
                QMessageBox::warning(this, "没了", "好啦，好啦，我们是来学习的呢(没有了呢，就这么几关呢ˋ( ° ▽、° ) )");
                return;
            }
            myPlays = new GamePlay(myLevel + 1);
            myPlays->setGeometry(this->geometry());
            myPlays->show();
            delete this;
        });
    });

    //退出游戏
    buttonClose = new MyPushButton(":/Pixmap/image/close.png", 2);
    buttonClose->setParent(this);
    buttonClose->move(45, 300);
    connect(buttonClose, &MyPushButton::clicked, this, [=](){
        buttonClose->zoom1();
        buttonClose->zoom2();
        QTimer::singleShot(200, this, [=](){
            this->close();
        });
    });

    //标题
    lableTitle = new QLabel(this);
    lableTitle->setText(QString("第%1关").arg(myLevel));
    lableTitle->setFixedSize(150, 38);
    lableTitle->move(450, 25);
    lableTitle->setStyleSheet("font-size : 38px;"
                              "font-family : 华文行楷;"
                              "color : rgba(234, 44, 235, 1);");
    lableTitle->setAlignment(Qt::AlignCenter);


    //初始化关卡
    MyData myGaneData;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->gameArray[i][j] = myGaneData.dataSelect[level][i][j];
        }
    }

    //金币背景和金币
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            //背景
            lableGame = new QLabel(this);
            lableGame->setFixedSize(70, 70);
            lableGame->setPixmap(QPixmap(":/Pixmap/image/background.png"));
            lableGame->move(370 + i *80, 80 + j *80);

            //金币
            QString moneyStr;
            if(this->gameArray[i][j] == 0)
            {
                moneyStr = ":/Pixmap/image/05.png";
            }
            else
            {
                moneyStr = ":/Pixmap/image/01.png";
            }
            MyMoneyButton *buttonMoney = new MyMoneyButton(moneyStr);
            buttonMoney->setParent(this);
            buttonMoney->move(375 + i *80, 85 + j *80);

            //坐标与是否为正值
            buttonMoney->moneyX = i;
            buttonMoney->moneyY = j;
            buttonMoney->moneyBool = gameArray[i][j];
            moneyArray[i][j] = buttonMoney;

            connect(buttonMoney, &MyMoneyButton::clicked, [=](){
                buttonMoney->boolChange();
                this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0;

                //延迟翻边上金币
                QTimer::singleShot(120, this, [=](){
                    if(buttonMoney->moneyX + 1 <= 3)//右
                    {
                        moneyArray[buttonMoney->moneyX + 1][buttonMoney->moneyY]->boolChange();
                        this->gameArray[buttonMoney->moneyX + 1][buttonMoney->moneyY] = this->gameArray[buttonMoney->moneyX + 1][buttonMoney->moneyY] == 0 ? 1 : 0;
                    }
                    if(buttonMoney->moneyX - 1 >= 0)//左
                    {
                        moneyArray[buttonMoney->moneyX - 1][buttonMoney->moneyY]->boolChange();
                        this->gameArray[buttonMoney->moneyX - 1][buttonMoney->moneyY] = this->gameArray[buttonMoney->moneyX - 1][buttonMoney->moneyY] == 0 ? 1 : 0;
                    }
                    if(buttonMoney->moneyY - 1 >= 0)//上
                    {
                        moneyArray[buttonMoney->moneyX][buttonMoney->moneyY - 1]->boolChange();
                        this->gameArray[buttonMoney->moneyX][buttonMoney->moneyY - 1] = this->gameArray[buttonMoney->moneyX][buttonMoney->moneyY - 1] == 0 ? 1 : 0;
                    }
                    if(buttonMoney->moneyY + 1 <= 3)//下
                    {
                        moneyArray[buttonMoney->moneyX][buttonMoney->moneyY + 1]->boolChange();
                        this->gameArray[buttonMoney->moneyX][buttonMoney->moneyY + 1] = this->gameArray[buttonMoney->moneyX][buttonMoney->moneyY + 1] == 0 ? 1 : 0;
                    }

                    //胜利
                    isWin = true;
                    for(int i = 0; i < 4; i++)
                    {
                        for(int j = 0; j < 4; j++)
                        {
                            if(gameArray[i][j] == 0)
                            {
                                this->isWin = false;
                                continue;
                            }
                        }
                    }
                    if(this->isWin == true)
                    {
                        //qDebug() << "胜利啦";
                        for(int i = 0; i < 4; i++)
                        {
                            for(int j = 0; j < 4; j++)
                            {
                                moneyArray[i][j]->isWin = true;
                                buttonNext->setEnabled(true);
                                lableWin->show();

                            }
                        }
                    }
                });
            });
        }
    }

    //胜利
    lableWin = new QLabel(this);
    lableWin->setText(QString("胜利啦！"));
    lableWin->setFixedSize(500, 200);
    lableWin->move(320, 140);
    lableWin->setStyleSheet("font-size : 128px;"
                              "font-family : 华文行楷;"
                              "color : rgba(255, 0, 0, 1);");
    lableWin->setAlignment(Qt::AlignCenter);
    lableWin->hide();
}

//背景
void GamePlay::paintEvent(QPaintEvent *)
{
    QPainter painterBackground(this);
    QPixmap pixmapBackground;
    pixmapBackground.load(":/Pixmap/image/75354898_p9.png");
    painterBackground.drawPixmap(0, 0, this->width(), this->height(), pixmapBackground);
}
