#include "endgame1.h"
#include <QLabel>
#include <QFont>
#include<QDebug>

endgame1::endgame1(QWidget *parent) : QWidget(parent)
{
    //my_data.createConnection();
    this->setFixedSize(800, 450);
    my_rect.setRect(300,100,200,200);
    temp.setParent(this);
    temp.setFixedSize(100,35);
   // temp.setText("返回主界面");
    temp.setStyleSheet("QPushButton{border-image:url(:/new/image/button.png)}");
    temp.move(350,285);
    connect(&temp,&QPushButton::clicked,[=]{
        this->close();
        emit close_end_win();
    });

}

void endgame1::closeEvent(QCloseEvent *event)
{
    emit close_end_win();
    delete a;
    delete c;
    //delete d;
}

/*void endgame1::set_current_score(int cin_score)
{
    temp_score=cin_score;
     qDebug() <<"成绩传进来啦";
}*/

void endgame1::set_current_score(int cin_score,int cin_score1)
{
    temp_score=cin_score;
    temp_score1=cin_score1;
    qDebug() <<"成绩传进来啦";
}

void endgame1::see(){

    a=new QLabel(this);
    c=new QLabel(this);
    d=new QLabel(this);
    //int *s=my_data.sort(mode);
    QFont font("Microsoft YaHei", 20, 75);
    a->setFont(font);
    a->move(300,185);
    c->setFont(font);
    c->move(300,215);
    if(ss==0){
    a->setText(
                QString("<center> <font color='#696969'>恭喜%1赢得比赛</font></center>").arg(player_name)
                );
    c->setText(
                QString("<center><font color='#696969'>您的成绩是:%1</font></center>").arg(temp_score)
                );
    }
    if(ss==1){
    a->setText(
                QString("<center><font color='#696969'>恭喜%1赢得比赛</font></center>").arg(player_name)
                );
    c->setText(
                QString("<center><font color='#696969'>您的成绩是:%1</font></center>").arg(temp_score1)
                );
    }
    if(ss==2){
    a->setText(
                QString("<center><font color='#696969'>很不巧二位打成平手</font></center>")
                );
    /*c->setText(
                QString("<center>您的成绩是:%1</center>").arg(temp_score)
                );*/
    }
    /*d->setFont(font);
    d->move(50,115);
    if(temp_score>s[0]){
        s[0]=temp_score;
    }
    d->setText(
                QString("<center>游戏历史最高:%1</center>").arg(s[0])
                );
    delete s;*/

}

/*void endgame1::get_mode(int cin_mode)
{
    mode=cin_mode;
}*/
void endgame1::set_player_name(QString cin_name)
{
    player_name=cin_name;
    qDebug() <<"名字传进来啦";

}
void endgame1::set_player_name(QString cin_name1,QString cin_name2)
{
    player_name=cin_name1;
    player_name2=cin_name2;
    qDebug() <<"两个名字传进来啦";

}

void endgame1::setBtnQss(QPushButton *btn, QString normalColor, QString normalTextColor, QString hoverColor, QString hoverTextColor, QString pressedColor, QString pressedTextColor)
{
    QStringList qss;

             qss.append(QString("QPushButton{border-style:none;padding:10px;border-radius:5px;color:%1;background:%2;}").arg(normalTextColor).arg(normalColor));

             qss.append(QString("QPushButton:hover{color:%1;background:%2;}").arg(hoverTextColor).arg(hoverColor));

             qss.append(QString("QPushButton:pressed{color:%1;background:%2;}").arg(pressedTextColor).arg(pressedColor));

             btn->setStyleSheet(qss.join(""));
}


void endgame1::paintEvent(QPaintEvent *){
    b=new QPainter(this);
    b->drawPixmap(0,0,width(),height(),QPixmap(":/new/image/end_test.png"));
}
