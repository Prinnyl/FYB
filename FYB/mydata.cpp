#include "mydata.h"

MyData::MyData(QObject *parent) : QObject(parent)
{
    //关卡
    int array1[4][4] = {{1, 1, 1, 1},
                        {1, 1, 0, 1},
                        {1, 0, 0, 0},
                        {1, 1, 0, 1}};
    int array2[4][4] = {{1, 0, 1, 1},
                        {0, 0, 1, 1},
                        {1, 1, 0, 0},
                        {1, 1, 0, 1}};
    int array3[4][4] = {{0, 0, 0, 0},
                        {0, 1, 1, 0},
                        {0, 1, 1, 0},
                        {0, 0, 0, 0}};
    int array4[4][4] = {{0, 1, 0, 0},
                        {1, 0, 0, 0},
                        {0, 0, 1, 0},
                        {0, 0, 0, 0}};
    int array5[4][4] = {{0, 1, 0, 0},
                        {1, 0, 1, 0},
                        {0, 1, 0, 1},
                        {0, 0, 1, 0}};
    int array6[4][4] = {{0, 1, 0, 0},
                        {0, 0, 1, 0},
                        {1, 0, 0, 1},
                        {1, 0, 1, 0}};
    int array7[4][4] = {{0, 1, 0, 1},
                        {0, 0, 0, 1},
                        {1, 0, 0, 0},
                        {1, 0, 1, 0}};
    int array8[4][4] = {{0, 1, 1, 0},
                        {0, 0, 0, 0},
                        {0, 0, 0, 0},
                        {0, 1, 1, 0}};
    int array9[4][4] = {{0, 0, 0, 0},
                        {0, 0, 0, 0},
                        {0, 0, 0, 0},
                        {0, 0, 0, 0}};
    //放入容器
    forData(dataSelect, 1, array1);
    forData(dataSelect, 2, array2);
    forData(dataSelect, 3, array3);
    forData(dataSelect, 4, array4);
    forData(dataSelect, 5, array5);
    forData(dataSelect, 6, array6);
    forData(dataSelect, 7, array7);
    forData(dataSelect, 8, array8);
    forData(dataSelect, 9, array9);
}

void MyData::forData(QMap<int, QVector<QVector<int>>> &myDataSelect, int include, int (*array)[4])
{
    QVector<QVector<int>> v;
    for(int i = 0; i <4; i++)
    {
        QVector<int> v1;
        for(int j = 0; j < 4; j++)
        {
            v1.push_back(array[i][j]);
        }
        v.push_back(v1);
    }
    myDataSelect.insert(include, v);
    //v.clear();
}
