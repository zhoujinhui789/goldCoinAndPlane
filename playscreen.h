
#ifndef PLAYSCREEN_H
#define PLAYSCREEN_H


#include <QMainWindow>
#include "mycoin.h"

class playScreen : public QMainWindow
{
    Q_OBJECT
public:
//    explicit playScreen(QWidget *parent = nullptr);
    playScreen(int num);

    int levelIndex;//内部成员属性 记录关卡

    //重写painterEventer事件
    void paintEvent(QPaintEvent *event);

    //二维数组维护每个关卡的具体数据
    int gameArray[4][4];

    MyCoin* coinBtn[4][4];
    //是否胜利
    bool isWin;


signals:
    void chooseScreenBack();

};

#endif // PLAYSCREEN_H
