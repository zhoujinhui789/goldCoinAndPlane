
#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H


#include <QPushButton>


class myPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit myPushButton(QWidget *parent = nullptr);

    //构造函数     参数一 默认状态下的图标路径     参数二  按下后显示的图标路径
    myPushButton(QString normalImg, QString pressImg="");

    //弹跳特效
    void zoom1();//向下跳
    void zoom2();//向上跳

    //成员属性 保存用户传入的默认显示路径 以及按下后显示的路径
    QString normalImgPath;
    QString pressImgPath;

    //重写鼠标按下 和释放事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);


signals:

};

#endif // MYPUSHBUTTON_H
