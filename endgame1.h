#ifndef ENDGAME1_H
#define ENDGAME1_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include<QPushButton>
#include<QRect>
//#include"database.h"
class endgame1 : public QWidget
{
    Q_OBJECT
public:
    explicit endgame1(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event);
     QPushButton temp;
     QRect my_rect;
    // void set_current_score(int cin_score);
     void set_current_score(int cin_score,int cin_score1);
     void set_player_name(QString cin_name);
     void set_player_name(QString cin_name1,QString cin_name2);
     void setBtnQss(QPushButton *btn,

                    QString normalColor, QString normalTextColor,

                    QString hoverColor, QString hoverTextColor,

                    QString pressedColor, QString pressedTextColor);
     void see();
     //DataBase my_data;//数据库对象

     QString player_name;//这局玩家的名字
     QString player_name2;

     int ss=0;


     int mode;
    // void get_mode(int cin_mode);

protected:
    void paintEvent(QPaintEvent *);


private:
    QPainter *b=new QPainter(this);
    int temp_score,temp_score1;//玩家这局的成绩
    QLabel *a,*c,*d;

signals:
    void close_end_win();

public slots:
};
#endif // ENDGAME1_H
