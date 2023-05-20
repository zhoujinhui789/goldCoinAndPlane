
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <mypushbutton.h>
#include <QDebug>
#include <QTimer>
#include <QSoundEffect>
#include "../PlaneWar/mainscene.h"
#include "../PlaneWar/config.h"
#include <QIcon>
#include <QPainter>
#include <QMouseEvent>
#include <ctime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置主场景
    //固定屏幕大小
    setFixedSize(320,588);
    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题名称
    setWindowTitle("翻金币 & 飞机大战");

    //点击退出按钮退出
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //准备开始的音效

    QSoundEffect* startSound = new QSoundEffect(this);
    startSound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));



    //开始按钮实现
    myPushButton* startBtn = new myPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5 - startBtn->width()*0.5 , this->height()*0.7);

    //进入另一个游戏按钮
    myPushButton* startBtn2 = new myPushButton(":/res/MenuSceneStartButton.png");
    startBtn2->setParent(this);
    startBtn2->move(this->width()*0.5 - startBtn->width()*0.5 , this->height()*0.5);

    //点击btn2进入第二个游戏
    connect(startBtn2,&myPushButton::clicked,[=](){
        //        qDebug()<<"点击了开始按钮";
        //播放开始音效
        startSound->play();

        startBtn2->zoom1();
        startBtn2->zoom2();

        //需要延迟进入到关卡选择页面
        QTimer::singleShot(250,this,[=](){
            MainScene* planeWar = new MainScene;

            //自身(主页面)隐藏
            this->hide();

        });

    });



    //实例化选择关卡场景
    chooseScreen = new ChooseLevelScreen;

    //监听选择关卡的返回按钮
    connect(chooseScreen,&ChooseLevelScreen::chooseScreenBack,[=](){

        this->setGeometry(chooseScreen->geometry());
        this->show();//重新显示
        chooseScreen->hide();//关卡选择页面隐藏

    });

    connect(startBtn,&myPushButton::clicked,[=](){
//        qDebug()<<"点击了开始按钮";
        //播放开始音效
        startSound->play();

        startBtn->zoom1();
        startBtn->zoom2();

        //需要延迟进入到关卡选择页面
        QTimer::singleShot(250,this,[=](){
            //设置主界面的位置
            chooseScreen->setGeometry(this->geometry());

             //显示关卡
            chooseScreen->show();
            //自身(主页面)隐藏
            this->hide();

        });

    });



}

//画背景图
//重写paintEvent事件
void MainWindow:: paintEvent(QPaintEvent *event){
    QPainter* painter = new QPainter(this);
    QPixmap pix;
    pix.load(":/plane/img_bg_level_2.jpg");

    painter->drawPixmap(0,0,this->width(),this->height(),pix);

    //画背景图标
    pix.load(":/res/Title.png");
    //缩放图片大小
    pix = pix.scaled(pix.width()*0.6,pix.height()*0.6);

    painter->drawPixmap(10,60,pix);

    //画背景图标2
    pix.load(":/res/img-plane_1.png");
//    //缩放图片大小
//    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);

    painter->drawPixmap(200,30,pix);

    //夹中间的爆炸效果图
    pix.load(":/res/bomb-2.png");
    painter->drawPixmap(240,120,pix);

    pix.load(":/res/bomb-2.png");
    painter->drawPixmap(180,100,pix);


    //搭配子弹摆盘
     pix.load(":/res/bullet_1.png");
     painter->drawPixmap(240,95,pix);


     //从下到上的飞机
     pix.load(":/res/hero.png");
     painter->drawPixmap(180,210,pix);
     pix.load(":/res/bullet_11.png");
     painter->drawPixmap(220,170,pix);

}

MainWindow::~MainWindow()
{
    delete ui;
}


