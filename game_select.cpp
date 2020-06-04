#include "game_select.h"
#include "ui_game_select.h"
#include <QFileInfo>
#include <QString>
#include <QtMultimedia/QSound>



game_select::game_select(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::game_select)
{

    //初始化
    ui->setupUi(this);
    this->setWindowTitle("选择模式");
    this->setFixedSize(800,450);
    setBtnQss(ui->ultimate_mode, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    setBtnQss(ui->limited_time_mode, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    setBtnQss(ui->no_die_mode, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    //如果按下了限时模式怎么办
    connect(ui->limited_time_mode,&QPushButton::clicked,[=](){
        emit my_slot();
        this->hide();
        my_game.getn(n);
        my_game.get_pic_num(pic_num);
        my_game.get_skin_num(skin_num);
        my_game.get_player_name(player_name);
        my_game.play();
        my_game.show();
        my_game.timebegin();
        //my_game.timeclose();
    });
    //如果按下了障碍模式怎么办
    connect(ui->ultimate_mode,&QPushButton::clicked,[=](){
        emit my_slot();
        this->hide();
        my_two_login.begin_this_win();
        my_two_login.show();


    });
    connect(&my_two_login,&two_sankes::begin_battle,[=]{
        qDebug()<<"信号已收到";
        player_1=my_two_login.player_1;
        player_2=my_two_login.player_2;
        my_game_3.set_skin_num(my_two_login.show_skin_1(),my_two_login.show_skin_2());
        my_two_login.close();
        my_game_3.getn(n);
        my_game_3.timebegin();
        my_game_3.get_players_names(player_1,player_2);
        my_game_3.show();
        my_game_3.get_pic_num(pic_num);
        my_game_3.repaint();
        my_game_3.play();
    });
    connect(&my_two_login,&two_sankes::back_1,[=]{
        emit main_win_show();
        this->close();
    });
    //如果按下了无限模式怎么办
    connect(ui->no_die_mode,&QPushButton::clicked,[=](){
        emit my_slot();
        this->hide();

       my_game_2.getn(n);
       my_game_2.get_player_name(player_name);
       my_game_2.get_skin_num(skin_num);
       my_game_2.get_pic_num(pic_num);
       my_game_2.play();
       my_game_2.show();
       //my_game_2.timebegin();
    });
    //关闭窗口区
    connect(&my_game,&GameWidget::game_exit,[=]{
        emit main_win_show();
        this->close();
    });
    connect(&my_game_2,&gamewidget_2::game_exit,[=]{
        emit main_win_show();
        this->close();
    });
    connect(&my_game_3,&gamewidget_3::game_exit,[=]{
        emit main_win_show();
        this->close();
    });
}


game_select::~game_select()
{
    delete ui;
}

void game_select::paintEvent(QPaintEvent *event)
{
    QPainter background(this);
    background.drawPixmap(0,0,width(),height(),QPixmap(":/new/image/duoyongde.jpeg"));

}

void game_select::receive_name(QString a)
{
    player_name=a;
}

void game_select::send_name()
{

}

void game_select::get_pic_num(int cin_pic_num)
{
    pic_num=cin_pic_num;
}

void game_select::get_skin_num(int cin_skin_num)
{
    skin_num=cin_skin_num;
}

void game_select::closeEvent(QCloseEvent *event)
{
    emit main_win_show();
}

void game_select::setBtnQss(QPushButton *btn, QString normalColor, QString normalTextColor, QString hoverColor, QString hoverTextColor, QString pressedColor, QString pressedTextColor)
{
    QStringList qss;

             qss.append(QString("QPushButton{font: 18pt '华文楷体';border-style:none;padding:10px;border-radius:5px;color:%1;background:%2;}").arg(normalTextColor).arg(normalColor));

             qss.append(QString("QPushButton:hover{color:%1;background:%2;}").arg(hoverTextColor).arg(hoverColor));

             qss.append(QString("QPushButton:pressed{color:%1;background:%2;}").arg(pressedTextColor).arg(pressedColor));

             btn->setStyleSheet(qss.join(""));
}

void game_select::getn(int m)
{
    n=m;
}

