#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include "endgame.h"
#include"database.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>


namespace Ui {
class gamewidget;
}
class GameWidget : public QWidget
{
    Q_OBJECT
public:
    DataBase my_data;
    explicit GameWidget(QWidget *parent = nullptr);
    ~GameWidget();
    void paintEvent(QPaintEvent *);//绘图事件
    void keyPressEvent(QKeyEvent *event);
    void snakeMove();//蛇移动
    void  closeEvent(QCloseEvent *);
    void snakeAction();//蛇动作
    void timebegin();
    //void timeclose();
    void play();
    void get_player_name(QString in_name);
    void get_pic_num(int cin_pic_num);
    void creattool();
    void get_skin_num(int cin_skin_num);
    int n;
    void getn(int m);

signals:
    void gameClose();
    void game_exit();//关闭窗口的信号
public slots:
protected:
    void timerEvent(QTimerEvent *e)override;
private:
    QString player_name;
    int direction;//方向 1上  2下  3左  4右
    int preDirection;//前一个的方向  1上  2下  3左  4右
    int headX[500];//蛇X轴保存数组
    int headY[500];//蛇Y轴保存数组
    int headState[500];//蛇状态 1上，2下，3左，4右，5上左，6上右，7左上，8右上，9左下，10右下，11下左，12下右
    int bodyLen;//蛇长
    int foodX;//食物X
    int foodY;//食物Y
    QPainter *gamePainter;//游戏贴图
    QTimer *timerGame;//持续移动
    bool isKey;//是否能按按键
    int minUp = 1;
    int minDown = 1;
    int minLeft = 1;
    int minRight = 1;
    QTimer *timerAction;//持续动作
    int score; //成绩
    int timerid;
    int timerid2;
    int timerid3;
    int timerid4;
    Ui::gamewidget *ui;
    bool flag_timeout;
    QTimer *timerall;
    QTimer *tool;
    QTimer *toolfast;
    QTimer *toolslow;
    QTimer *toolmash;
    endgame w;
    int pic_num;
    int skin_num;


    QMediaPlayer *gameSound;
    QMediaPlaylist *gameList;
    //加速,减速，毒蘑菇
    int fastx=-50,fasty=-50,slowx=-50,slowy=-50,mashx=-50,mashy=-50,giftx=-50,gifty=-50;

    //判断吃到道具
    int s1,s2,s3,s4;
    //操作反向标识符
    int cc=0;
    //判断道具是否在有效时间内
    int c1,c2,c3;

};

#endif // MYWIDGET_H
