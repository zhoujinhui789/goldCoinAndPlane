
#include "mycoin.h"
#include <QTimer>
//MyCoin::MyCoin(QPushButton *parent)
//    : QWidget{parent}
//{


//}
//参数代表传入的是金币路径 还是银币
MyCoin ::MyCoin(QString btnImg){
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(!ret){
        QString str = QString("图片路径 %1 错误").arg(btnImg);
        qDebug()<<str;
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始化定时器对象
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听正面翻翻面的信号 并且反转金币
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //判断如果翻完了 重置min 并且关掉定时器
        if(this->min > this->max){
            this->min = 1;
            this->isAnimation = false;
            timer1->stop();
        }
    });

    //监听反面翻正面的信号 并且反转银币
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //判断如果翻完了 重置max 并且关掉定时器
        if(this->max < this->min){
            this->max = 8;
              this->isAnimation = false;
            timer2->stop();
        }
    });

}
//改变标志的方法
void MyCoin :: changeFlag(){
    //如果是正面 翻成反面
    if(flag){
        //开启定时器1
        timer1->start(30);
        this->isAnimation =  true;

        this->flag = false;
    }else{
        //开启定时器2
        timer2->start(30);
        this->isAnimation = true;
        this->flag = true;
    }

}

//重写按下事件
void MyCoin:: mousePressEvent(QMouseEvent *e){
    if(this->isAnimation || this->isWin){
        return;
    }else{
        QPushButton::mousePressEvent(e);
    }
}

