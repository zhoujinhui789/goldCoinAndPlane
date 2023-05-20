
#ifndef MYCOIN_H
#define MYCOIN_H


#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString btnImg);

    //金币属性 XY的坐标 硬币的正反
    int posX;
    int posY;
    bool flag;

    //改变标志的方法
    void changeFlag();
    QTimer* timer1;//正变反的定时器
    QTimer* timer2;//反变正的定时器

    //金币银币的路径表示
    int min = 1;
    int max = 8;

    //执行动画标志
    bool isAnimation = false;

    //重写按下事件
    void mousePressEvent(QMouseEvent *);

    //是否胜利
    bool isWin = false;

signals:

};

#endif // MYCOIN_H
