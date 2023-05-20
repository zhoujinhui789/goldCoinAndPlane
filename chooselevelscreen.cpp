
#include "chooselevelscreen.h"
#include <QMenuBar>
#include <QDebug>
#include <QPainter>
#include <mypushbutton.h>
#include <QTimer>
#include <QLabel>
#include <QSoundEffect>

ChooseLevelScreen::ChooseLevelScreen(QWidget *parent)
    : QMainWindow{parent}
{
    //配置选择关卡信息
    this->setFixedSize(320,588);

    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

     setWindowTitle("关卡选择页面");

     //代码实现菜单栏界面
     QMenuBar* bar = menuBar();
     setMenuBar(bar);

    //创建开始菜单
     QMenu* startMenu =  bar->addMenu("开始");
    //创建出退出菜单项
    QAction* quitAction =  startMenu->addAction("退出");
    //点击退出
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //选择关卡音效
    QSoundEffect* chooseSound = new QSoundEffect(this);
    chooseSound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));

    //返回按钮音效
    QSoundEffect* backSound = new QSoundEffect(this);
    backSound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));


    //返回按钮
    myPushButton* backBtn = new myPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(),this->height() - backBtn->height());

    //点击返回主场景
    connect(backBtn,&myPushButton::clicked,[=](){
//        qDebug()<<"点击了back";
        //告诉主场景 我要返回  主场景监听ChooseLevelScreen的返回按钮

        backSound->play();

        //一个延迟返回
        QTimer::singleShot(300,this,[=](){
            emit this->chooseScreenBack();
        });

    });

    //显示关卡选择
    for(int i =0;i<20;i++){
        myPushButton* menuBtn = new myPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+i%4*70,130+i/4*70);

        //监听每个按钮的点击事件
        connect(menuBtn,&myPushButton::clicked,[=](){
            //播放点击音频
            chooseSound->play();




            QString str = QString("你选择的是第%1关").arg(i+1);
            qDebug()<<str;



            //进入到游戏页面

            play = new playScreen(i+1);//创建游戏界面
              //设置游戏场景的初始位置
            play->setGeometry(this->geometry());

            play->show();
            this->hide();//关闭选关页面

            connect(play,&playScreen::chooseScreenBack,[=](){

                this->setGeometry(play->geometry());

                this->show();
                delete play;
                play = NULL;
            });

        });

        QLabel* label = new QLabel;
        label->setParent(this);
        //label默认没有大小 需要设置大小
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(25+i%4*70,130+i/4*70);

        //设置label上的文字对齐方式
        label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        //设置label的鼠标穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);



    }

}

void ChooseLevelScreen:: paintEvent(QPaintEvent *event){
    QPainter* painter = new QPainter(this);
    QPixmap pix;
    //加载背景
    pix.load(":/res/OtherSceneBg.png");
    painter->drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    painter->drawPixmap(this->width()*0.5 - pix.width()*0.5,30,pix);

}
