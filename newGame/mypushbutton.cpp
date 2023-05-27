
#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>

//myPushButton::myPushButton(QWidget *parent)
//    : QPushButton{parent}
//{

//}

myPushButton::myPushButton(QString normalImg, QString pressImg){
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    QPixmap pix;
    bool ret = pix.load(normalImg);
    if(!ret){
        qDebug()<<"图片加载失败！";
        return;
    }
    //设置图片固定大小
    this->setFixedSize(pix.width(),pix.height());

    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));


}

//向下跳
void myPushButton:: zoom1(){
    //创建动态对象
    QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");
    //设置时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //结束位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();


}

//向上跳
void myPushButton:: zoom2(){
    //创建动态对象
    QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");
    //设置时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //结束位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();

}

//重写鼠标按下 和释放事件
void myPushButton:: mousePressEvent(QMouseEvent *e){
    if(pressImgPath != ""){//传入的图片不为空 重新渲染为新传入的图片
        QPixmap pix;
        bool ret = pix.load(pressImgPath);
        if(!ret){
            qDebug()<<"图片加载失败！";
            return;
        }
        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //让父类执行其他内容
    return QPushButton::mousePressEvent(e);
}

void myPushButton:: mouseReleaseEvent(QMouseEvent *e){
    if(pressImgPath != ""){//传入的图片不为空 重新渲染为原来的图片
        QPixmap pix;
        bool ret = pix.load(normalImgPath);
        if(!ret){
            qDebug()<<"图片加载失败！";
            return;
        }
        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //让父类执行其他内容
    return QPushButton::mouseReleaseEvent(e);
}

