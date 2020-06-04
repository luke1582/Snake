#include "endgame.h"
#include <QLabel>
#include <QFont>
#include<QDebug>

#include <QVBoxLayout>
#include<QPushButton>
endgame::endgame(QWidget *parent) : QWidget(parent)
{
    my_data.createConnection();
    this->setFixedSize(800, 450);
    my_rect.setRect(0,0,width(),height());
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

void endgame::closeEvent(QCloseEvent *event)
{
    emit close_end_win();
    delete a;
    delete c;
    delete d;
}

void endgame::set_current_score(int cin_score)
{
    temp_score=cin_score;
     qDebug() <<"成绩传进来啦";
}

void endgame::see(){

    a=new QLabel(this);
    c=new QLabel(this);
    d=new QLabel(this);
    int *s=my_data.sort(mode);
    QFont font("Microsoft YaHei", 15, 75);
    a->setFont(font);
    a->move(330,185);
    a->setText(
                QString("<center> <font color='#696969'>当前成绩为:%1</font></center>").arg(temp_score)
                );
    c->setFont(font);
    c->move(330,210);
    c->setText(
                QString("<center><font color='#696969'>您最好成绩是:%1</font></center>").arg(my_data.score(mode,player_name))
                );
    d->setFont(font);
    d->move(330,235);
    if(temp_score>s[0]){
        s[0]=temp_score;
    }
    d->setText(
                QString("<center><font color='#696969'>游戏历史最高:%1</font></center>").arg(s[0])
                );
    delete s;

}

void endgame::get_mode(int cin_mode)
{
    mode=cin_mode;
}

void endgame::setBtnQss(QPushButton *btn, QString normalColor, QString normalTextColor, QString hoverColor, QString hoverTextColor, QString pressedColor, QString pressedTextColor)
{
    QStringList qss;

             qss.append(QString("QPushButton{border-style:none;padding:10px;border-radius:5px;color:%1;background:%2;}").arg(normalTextColor).arg(normalColor));

             qss.append(QString("QPushButton:hover{color:%1;background:%2;}").arg(hoverTextColor).arg(hoverColor));

             qss.append(QString("QPushButton:pressed{color:%1;background:%2;}").arg(pressedTextColor).arg(pressedColor));

             btn->setStyleSheet(qss.join(""));
}
void endgame::set_player_name(QString cin_name)
{
    player_name=cin_name;
    qDebug() <<"名字传进来啦";
}
void endgame::paintEvent(QPaintEvent *){
    b=new QPainter(this);
    b->drawPixmap(0,0,width(),height(),QPixmap(":/new/image/end_test.png"));
   // delete b;
}
