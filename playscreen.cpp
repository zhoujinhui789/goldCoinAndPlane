
#include "playscreen.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include "mycoin.h"
#include "dataconfig.h"
#include <QPropertyAnimation>
#include <QSoundEffect>

//playScreen::playScreen(QWidget *parent)
//    : QMainWindow{parent}
//{

//}

playScreen::playScreen(int num){
    QString str = QString("你进入了%1关").arg(num);
    qDebug()<<str;
    this->levelIndex = num;

    //配置关卡信息
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    setFixedSize(320,588);
    setWindowTitle("欢迎进入游戏！");


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

    //返回按钮音效
    QSoundEffect* backSound = new QSoundEffect(this);
    backSound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));

    //胜利音效
    QSoundEffect* vectorySound = new QSoundEffect(this);
    vectorySound->setSource(QUrl::fromLocalFile(":/res/LevelWinSound.wav"));
    //反金币音效
    QSoundEffect* filpSound = new QSoundEffect(this);
    filpSound->setSource(QUrl::fromLocalFile(":/res/ConFlipSound.wav"));

    //返回按钮
    //返回按钮
    myPushButton* backBtn = new myPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(),this->height() - backBtn->height());

    //点击返回主场景
    connect(backBtn,&myPushButton::clicked,[=](){
       backSound->play();


        //一个延迟返回
        QTimer::singleShot(300,this,[=](){
            emit this->chooseScreenBack();
        });

    });


    //显示关卡数
    QLabel* label = new QLabel;
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str1 = QString("Level : %1").arg(this->levelIndex);

    label->setParent(this);
    //将字体设置到label标签中
    label->setFont(font);
    label->setText(str1);

    //label标签默认没有大小 需要为其设置大小
    label->setGeometry(30 , this->height() - 50 , 120,50);


    //初始化每个关卡的二维数组
    dataConfig config;
    for(int i =0;i<4;i++){
        for(int j =0;j<4;j++){
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }

    }

    //显示胜利背景图案
    QLabel* winLabel = new QLabel;
    QPixmap winPix;
    winPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,winPix.width(),winPix.height());
    winLabel->setPixmap(winPix);
    winLabel->setParent(this);
    winLabel->move((this->width() - winPix.width())*0.5 , -winPix.height());


    //显示金币背景图案
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            QPixmap pix = QPixmap(":/res/BoardNode.png");

            QLabel* label = new QLabel;
            label->setParent(this);
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->move(57 + i * 50 , 200 + j * 50);

            //初始化金币
            QString str;
            if(gameArray[i][j] == 1){
                //显示金币
                str = ":/res/Coin0001.png";
            }else{
                //显示银币
                str = ":/res/Coin0008.png";
            }

            MyCoin* coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(59 + i * 50 , 204 + j * 50);

            //给金币属性赋值
            coin->posX = i;
            coin->posY = j;
            coin->flag = gameArray[i][j];

            //将金币放入到金币二维数组中 方便后期维护
            coinBtn[i][j] = coin;

            //点击金币 进行翻转
            connect(coin,&MyCoin::clicked,[=](){
                filpSound->play();

                //点击按钮 ， 将所有按钮先禁用

                for(int i=0;i<4;i++){
                    for(int j=0;j<4;j++){

                        this->coinBtn[i][j]->isWin = true;
                    }

                }

                coin->changeFlag();
                this->gameArray[i][j] = gameArray[i][j] == 0 ? 1 : 0;

                //反转周围金币

                //延时翻转
                QTimer::singleShot(300,this,[=](){

                    if(coin->posX+1 <=3){//右侧金币可以反转的条件
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY] = this->gameArray[coin->posX+1][coin->posY] == 0 ? 1 : 0;
                    }
                    if(coin->posX-1 >=0){//左侧金币可以反转的条件
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY] = this->gameArray[coin->posX-1][coin->posY] == 0 ? 1 : 0;
                    }
                    if(coin->posY+1 <=3){//上侧金币可以反转的条件
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1] = this->gameArray[coin->posX][coin->posY+1] == 0 ? 1 : 0;
                    }
                    if(coin->posY-1 >=0){//下侧金币可以反转的条件
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1] = this->gameArray[coin->posX][coin->posY-1] == 0 ? 1 : 0;
                    }

                    //翻完金币后，将所有金币解开禁用
                    for(int i=0;i<4;i++){
                        for(int j=0;j<4;j++){

                            this->coinBtn[i][j]->isWin = false;
                        }

                    }

                    //判断是否胜利
                    this->isWin = true;
                    for(int i=0;i<4;i++){
                        for(int j=0;j<4;j++){
                            if(coinBtn[i][j]->flag == false){
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if(this->isWin == true){
                        //确实胜利了1
                        qDebug()<<"游戏胜利！";
                        //将所有按钮的胜利标志改为胜利
                        for(int i=0;i<4;i++){
                            for(int j=0;j<4;j++){
                                coinBtn[i][j]->isWin = true;
                            }
                        }

                        vectorySound->play();

                        //将胜利的图片移动下来
                        QPropertyAnimation* animation = new QPropertyAnimation(winLabel , "geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //设置开始位置
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));

                        //设置结束位置
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y() + 114,winLabel->width(),winLabel->height()));

                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);

                        //执行动画
                        animation->start();

                    }

                });


            });


        }
    }

}

//重写painterEvent事件
void playScreen::paintEvent(QPaintEvent *event){
    QPainter* painter = new QPainter(this);
    QPixmap pix;
    pix.load(":/res/num1.png");

    painter->drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter->drawPixmap(10,30,pix.width(),pix.height(),pix);


}
