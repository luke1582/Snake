#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include"mainwindow.h"
#include<QPushButton>
#include<QDebug>
#include<QLineEdit>
#include"rank.h"
namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    void paintEvent(QPaintEvent *event);
    void setBtnQss(QPushButton *btn,

                   QString normalColor, QString normalTextColor,

                   QString hoverColor, QString hoverTextColor,

                   QString pressedColor, QString pressedTextColor);
    void setTxtQss(QLineEdit *txt, QString normalColor, QString focusColor);
private:
    Ui::login *ui;
    MainWindow my_main;
    game_begin my_begin;
    QString a,b;
    endgame test;//debug用
    rank my_rank;
};

#endif // LOGIN_H
