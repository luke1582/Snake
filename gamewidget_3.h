#ifndef GAMEWIDGET_3_H
#define GAMEWIDGET_3_H

#include <QWidget>

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include "endgame1.h"
#include"database.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
class gamewidget_3;
}
class gamewidget_3 : public QWidget
{
    Q_OBJECT
public:
    DataBase my_data;
    explicit gamewidget_3(QWidget *parent = nullptr);
    ~gamewidget_3();
    void paintEvent(QPaintEvent *);//绘图事件
    void keyPressEvent(QKeyEvent *event);
    void snakeMove();//蛇移动
    void  closeEvent(QCloseEvent *);
    void snakeAction();//蛇动作
    void timebegin();
    //void timeclose();
    void play();
    void get_player_name(QString in_name);
    void get_players_names(QString p1,QString p2);
    void get_pic_num(int cin_pic_num);
    void set_skin_num(int player_skin_1,int player_skin_2);
    void setBtnQss(QPushButton *btn,

                   QString normalColor, QString normalTextColor,

                   QString hoverColor, QString hoverTextColor,

                   QString pressedColor, QString pressedTextColor);
    int n;
    void getn(int m);
signals:
    void gameClose();
    void game_exit();//关闭窗口的信号




public slots:


protected:
     void timerEvent(QTimerEvent *)override;

private:
        QString player_name ,player_1,player_2;

    int pic_num;
    int skin_num1;  //玩家一
    int skin_num2;   //玩家二

    int direction[2];//方向 1上  2下  3左  4右

    int preDirection[2];//前一个的方向  1上  2下  3左  4右


    int headX1[500];//蛇X轴保存数组
    int headY1[500];//蛇Y轴保存数组
    int headX2[500];//蛇X轴保存数组
    int headY2[500];//蛇Y轴保存数组

    int headState1[500];//蛇状态 1上，2下，3左，4右，5上左，6上右，7左上，8右上，9左下，10右下，11下左，12下右
    int headState2[500];//蛇状态 1上，2下，3左，4右，5上左，6上右，7左上，8右上，9左下，10右下，11下左，12下右

    int bodyLen1;//蛇长
    int bodyLen2;//蛇长

    int foodX;//食物X
    int foodY;//食物Y
    QPainter *gamePainter;//游戏贴图
    QTimer *timerGame;//持续移动
    bool isKey;//是否能按按键
    int minUp[2] ={1,1};
    int minDown[2] = {1,1};
    int minLeft[2] = {1,1};
    int minRight[2] ={1,1};
    QTimer *timerAction;//持续动作
    int score1; //成绩
    int score2;
    int timerid;
    Ui::gamewidget_3 *ui;
    bool flag_timeout;
    QTimer *timerall;
    endgame1 w;
    QMediaPlayer *gameSound;
    QMediaPlaylist *gameList;


};


#endif // GAMEWIDGET_3_H
