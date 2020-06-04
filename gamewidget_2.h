#ifndef GAMEWIDGET_2_H
#define GAMEWIDGET_2_H

#include <QWidget>

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include "endgame.h"
#include"database.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
class gamewidget_2;
}
class gamewidget_2 : public QWidget
{
    Q_OBJECT
public:
    DataBase my_data;
    explicit gamewidget_2(QWidget *parent = nullptr);
    ~gamewidget_2();
    void paintEvent(QPaintEvent *);//绘图事件
    void keyPressEvent(QKeyEvent *event);
    void snakeMove();//蛇移动
    void  closeEvent(QCloseEvent *);
    void snakeAction();//蛇动作
    //void timebegin();
    //void timeclose();
    void play();

    void get_player_name(QString in_name);
    void creatwall();
    void get_pic_num(int cin_pic_num);
    void get_skin_num(int cin_skin_num);
    int n;
    void getn(int m);
private:
    bool if_die;
    int pic_num;
    int skin_num;
    signals:
    void gameClose();
    void game_exit();//关闭窗口的信号




public slots:


private:
        QString player_name;

    int direction;//方向 1上  2下  3左  4右
    int preDirection;//前一个的方向  1上  2下  3左  4右
    int headX[500];//蛇X轴保存数组
    int headY[500];//蛇Y轴保存数组

    int wallX[50];//墙保持数组
    int wallY[50];

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
    QTimer *wall;
    int score; //成绩
    int timerid;
    Ui::gamewidget_2 *ui;
    bool flag_timeout;
    QTimer *timerall;
    endgame w;
    QMediaPlayer *gameSound;
    QMediaPlaylist *gameList;


};


#endif // GAMEWIDGET_2_H
