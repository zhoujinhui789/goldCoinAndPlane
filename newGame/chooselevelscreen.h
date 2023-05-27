
#ifndef CHOOSELEVELSCREEN_H
#define CHOOSELEVELSCREEN_H


#include <QMainWindow>
#include "playscreen.h"
#include <QTimer>
class ChooseLevelScreen : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScreen(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);

    //游戏场景对象指针
    playScreen* play = NULL;


signals:
    //自定义信号 返回主场景
    void chooseScreenBack();

};

#endif // CHOOSELEVELSCREEN_H
