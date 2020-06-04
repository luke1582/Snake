#ifndef GAME_SELECT_H
#define GAME_SELECT_H

#include <QWidget>
#include"game_1.h"
#include"game_2.h"
#include"game_3.h"
#include<QPainter>
#include"gamewidget.h"
#include"gamewidget_2.h"
#include"gamewidget_3.h"
#include"two_sankes.h"
#include<QPainter>
#include<QPixmap>

namespace Ui {
class game_select;
}

class game_select : public QWidget
{
    Q_OBJECT

public:
    explicit game_select(QWidget *parent = nullptr);
    ~game_select();
    void paintEvent(QPaintEvent *event);
    void receive_name(QString a);
    void send_name();
    void get_pic_num(int cin_pic_num);
    void get_skin_num(int cin_skin_num);
    void closeEvent(QCloseEvent *event);
    void setBtnQss(QPushButton *btn,

                   QString normalColor, QString normalTextColor,

                   QString hoverColor, QString hoverTextColor,

                   QString pressedColor, QString pressedTextColor);
    void music();
    int n;
    void getn(int m);

signals:
     void my_slot();//告诉主界面躲起来
     void main_win_show();
private:
    Ui::game_select *ui;
     game_1 limited_time_window;
     game_2 ultimate_window;
     game_3 no_die_window;
     QString player_name;
     GameWidget my_game;
    gamewidget_2 my_game_2;
    gamewidget_3 my_game_3;
    int pic_num,skin_num;
    two_sankes my_two_login;
    QString player_1,player_2;
};

#endif // GAME_SELECT_H
