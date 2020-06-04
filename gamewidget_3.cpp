#include "gamewidget_3.h"
#include "ui_gamewidget_3.h"
#include <QKeyEvent>
#include <QTime>
#include <QtDebug>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QMediaPlaylist>

static int sec = 0;
gamewidget_3::gamewidget_3(QWidget *parent) : QWidget(parent),
  ui(new Ui::gamewidget_3)
{
  ui->setupUi(this);
  pic_num=1;
  skin_num1=1;
  skin_num2=2;
  connect(&w,&endgame1::close_end_win,[=]{
      emit game_exit();
  });
}
void gamewidget_3::timebegin()
{
    timerid = this->startTimer(1000);
}


void gamewidget_3::play()
{
    gameSound= new QMediaPlayer(this);
    gameList= new QMediaPlaylist(this);
    gameList->addMedia(QUrl("qrc:/new/image/music.wav"));//添加音乐
    gameList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);//循环播放
    gameSound->setMedia(gameList);
    gameSound->setVolume(n);
    gameSound->play();

    qDebug()<<"w"<<skin_num1<<' '<<skin_num2;
    my_data.createConnection();
    flag_timeout=false;
    sec=0;

  this->setFixedSize(800, 450);
  this->setWindowTitle("您瞧，这不是双人模式嘛？");

    qDebug() << this->width();
    //随机数种子
    qsrand(uint(QTime(0, 0, 0).secsTo(QTime::currentTime())));

    isKey = true;
    //初始化蛇
    direction[0] = 4;
    direction[1] = 4;

    headX1[0] =(qrand() % 24)*25;    //随机生成向右的蛇
    while(headX1[0]<125||headX1[0]>500)
       {headX1[0] =(qrand() % 24)*25;}
    headY1[0] =6*25;
    headX2[0] =(qrand() % 24)*25;    //随机生成向右的蛇
    while(headX2[0]<125||headX2[0]>500)
       {headX2[0] =(qrand() % 24)*25;}
    headY2[0] =12*25;

    headState1[0] = 4;
    headState2[0] = 4;

    bodyLen1 = 4;
    bodyLen2 = 4;

    score1=0;
    score2=0;
    for (int i = 1; i < bodyLen1; i++)
    {
        headX1[i] = headX1[i - 1] - 25;
        headY1[i] = headY1[i - 1];
        headState1[i] = headState1[i - 1];
    }
    for (int i = 1; i < bodyLen2; i++)
    {
        headX2[i] = headX2[i - 1] - 25;
        headY2[i] = headY2[i - 1];
        headState2[i] = headState2[i - 1];
    }

    //初始化食物的位置，不能与蛇同在,防止食物生成在边界墙上
    while(1)
    {
        int flag = 1,flag1 =1;
        foodX = (qrand() % 24) *25;    //
        foodY = (qrand() % 18) *25;
        for (int i = 0; i < bodyLen1||i <bodyLen2; i++)
        {
            if((headX1[i] == foodX && headY1[i] == foodY)||(headX2[i] == foodX && headY2[i] == foodY))
            {
                flag = 0;
                break;
            }
        }
        if(foodX==0||foodX==575||foodY==0||foodY==425)
            flag1=0;

        if(flag == 1 && flag1 == 1)
         {
             break;
         }

    }
    //this->setWindowTitle("您瞧，这不是限时模式嘛?");


    //移动（300毫秒一帧）
    timerGame = new QTimer(this);
    connect(timerGame, &QTimer::timeout, [=](){     //每当计时器重新启动，即为一帧
        //移动
        snakeMove();
        isKey = true;
    });
    timerGame->start(300);    //计时器每300毫秒重新启动一次

    //动作（蛇嘴嘴的动作75毫秒一帧）
    timerAction = new QTimer(this);
    connect(timerAction, &QTimer::timeout, [=](){
        //动作
        snakeAction();
        QFont font("Microsoft YaHei",10,75);
        ui->label_2->setFont(font);

        ui->label_2->setText(
                    QString("的昵称为:%1").arg(player_1)
                    );
        QFont font_1("Microsoft YaHei",10,75);
        ui->label_3->setFont(font_1);

        ui->label_3->setText(
                    QString("<center>该玩家成绩为:%1</center>").arg(score1)
                    );
        ui->label_4->setFont(font_1);
        //int*p=my_data.sort(2);
        ui->label_4->setText(
                    QString("的昵称为:%1").arg(player_2)
                    );
        ui->label_5->setFont(font_1);

        ui->label_5->setText(
                    QString("<center>该玩家成绩为:%1</center>").arg(score2)
                    );
    });
    timerAction->start(75);

    /*connect(&w,&endgame::close_end_win,[=]{
        emit game_exit();
       });
     */
}

void gamewidget_3::get_player_name(QString in_name)
{
    player_name=in_name;
}

void gamewidget_3::get_players_names(QString p1, QString p2)
{
    player_1=p1;
    player_2=p2;
    qDebug()<<"唔晓得了"<<player_1<<" "<<player_2;
}

void gamewidget_3::get_pic_num(int cin_pic_num)
{
    pic_num=cin_pic_num;
}

void gamewidget_3::set_skin_num(int player_skin_1, int player_skin_2)
{
    skin_num1=player_skin_1;
    skin_num2=player_skin_2;
}

void gamewidget_3::setBtnQss(QPushButton *btn, QString normalColor, QString normalTextColor, QString hoverColor, QString hoverTextColor, QString pressedColor, QString pressedTextColor)
{

}

void gamewidget_3::getn(int m)
{
    n=m;
}

void gamewidget_3::timerEvent(QTimerEvent *)
{

    //static int sec = 0;
    QFont font("Microsoft YaHei",10,75);
    ui->label->setFont(font);

    ui->label->setText(
                QString("<center>游戏剩余时间:%1秒</center>").arg(180-sec)
                );
    sec=sec+1;
    if(sec==180)
    {
        timerGame->stop();
        timerAction->stop();
        this->killTimer(this->timerid);//根据计时器的id关闭计时器（id起到区分多个定时器的作用，将开始与结束连起来

        QFont font("Adobe Caslon Pro Bold",15,75);
        ui->label->setFont(font);
        ui->label->setText("<center>Game Begin！！</center>");
        flag_timeout=true;
      /*if(score>my_data.score(2,player_name)){
            my_data.modify(2,player_name,score);
        }
      */
        if(score1>score2){
        w.set_current_score(score1,score2);//传成绩
        w.set_player_name(player_1);//传姓名
        }
        else if(score1<score2)
        {
            w.ss=1;
            w.set_current_score(score1,score2);//传成绩
            w.set_player_name(player_2);//传姓名
        }
        else{
            w.ss=2;
            w.set_player_name(player_1,player_2);
            w.set_current_score(score1,score2);
        }
        //w.get_mode(3);
        w.see();
        w.show();
        timerGame->stop();
        timerAction->stop();
        this->close();
        gameSound->stop();
        this->killTimer(this->timerid);

    }
}

void gamewidget_3::paintEvent(QPaintEvent *)
{
    //背景
    QPainter groundPainter(this);
    groundPainter.fillRect(0, 0, 600, 450, QBrush(QColor(0, 0, 255, 100)));
    if(pic_num==1){
        groundPainter.drawPixmap(0,0,600,450,QString(":/new/image/11.jpeg"));
        groundPainter.drawPixmap(600,0,200,450,QString(":/new/image/1.jpeg"));
    }
    if(pic_num==2){
        groundPainter.drawPixmap(0,0,600,450,QString(":/new/image/22.png"));
        groundPainter.drawPixmap(600,0,200,450,QString(":/new/image/2.png"));
    }
    if(pic_num==3){
        groundPainter.drawPixmap(0,0,600,450,QString(":/new/image/33.png"));
        groundPainter.drawPixmap(600,0,200,450,QString(":/new/image/3.png"));
    }
    QPainter wallpainter(this);
    for(int i=0;i<24;i++){
    wallpainter.drawPixmap(25*i, 0, 25, 25, QPixmap(":/new/image/wall.jpg"));
    }
    for(int i=0;i<24;i++){
    wallpainter.drawPixmap(25*i, 425, 25, 25, QPixmap(":/new/image/wall.jpg"));
    }
    for(int i=0;i<17;i++){
    wallpainter.drawPixmap(0, 25*i, 25, 25, QPixmap(":/new/image/wall.jpg"));
    }
    for(int i=0;i<17;i++){
    wallpainter.drawPixmap(575, 25*i, 25, 25, QPixmap(":/new/image/wall.jpg"));
    }

    gamePainter = new QPainter(this);
    if(skin_num1==1)     //红色
    {
        qDebug()<<"皮肤11";
    QString snakeUp = QString(":/new/image/headup%1.png").arg(this->minUp[0]++);
    QString snakeDown = QString(":/new/image/headdown%1.png").arg(this->minDown[0]++);
    QString snakeLeft = QString(":/new/image/headleft%1.png").arg(this->minLeft[0]++);
    QString snakeRight = QString(":/new/image/headright%1.png").arg(this->minRight[0]++);
    //蛇头
    if(headState1[0] == 1)
    {
        gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(snakeUp));
    }
    if(headState1[0] == 2)
    {
        gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(snakeDown));
    }
    if(headState1[0] == 3)
    {
        gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(snakeLeft));
    }
    if(headState1[0] == 4)
    {
        gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(snakeRight));
    }
    if(headState1[0] == 5)
    {
        gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(":/new/image/headupleft.png"));
    }
    if(headState1[0] == 6)
    {
        gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(":/new/image/headupright.png"));
    }
    if(headState1[0] == 7)
    {
        gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(":/new/image/headleftup.png"));
    }
    if(headState1[0] == 8)
    {
        gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(":/new/image/headrightup.png"));
    }
    if(headState1[0] == 9)
    {
        gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(":/new/image/headleftdown.png"));
    }
    if(headState1[0] == 10)
    {
        gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(":/new/image/headrightdown.png"));
    }
    if(headState1[0] == 11)
    {
        gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(":/new/image/headdownleft.png"));
    }
    if(headState1[0] == 12)
    {
        gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(":/new/image/headdownright.png"));
    }
    //蛇身
    for (int i = 1; i < bodyLen1; i++)
    {
        if(headState1[i] == 1 || headState1[i] == 2)
        {
            gamePainter->drawPixmap(headX1[i], headY1[i], 25, 25, QPixmap(":/new/image/bodyup.png"));
        }
        if(headState1[i] == 3 || headState1[i] == 4)
        {
            gamePainter->drawPixmap(headX1[i], headY1[i], 25, 25, QPixmap(":/new/image/bodyleft.png"));
        }
        if(headState1[i] == 5 || headState1[i] == 10)
        {
            gamePainter->drawPixmap(headX1[i], headY1[i], 25, 25, QPixmap(":/new/image/upleft.png"));
        }
        if(headState1[i] == 6 || headState1[i] == 9)
        {
            gamePainter->drawPixmap(headX1[i], headY1[i], 25, 25, QPixmap(":/new/image/upright.png"));
        }
        if(headState1[i] == 7 || headState1[i] == 12)
        {
            gamePainter->drawPixmap(headX1[i], headY1[i], 25, 25, QPixmap(":/new/image/downright.png"));
        }
        if(headState1[i] == 8 || headState1[i] == 11)
        {
            gamePainter->drawPixmap(headX1[i], headY1[i], 25, 25, QPixmap(":/new/image/downleft.png"));
        }
    }
    }


    if(skin_num1==2)     //米虫
    {
         qDebug()<<"皮肤12";
        if(headState1[0] == 1||headState1[0] == 7||headState1[0] == 8)
        {
            gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(":/new/image/headup.png"));
        }
        if(headState1[0] == 2||headState1[0] == 9||headState1[0] == 10)
        {
            gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(":/new/image/headdown.png"));
        }
        if(headState1[0] == 3||headState1[0] == 5||headState1[0] == 11)
        {
            gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(":/new/image/headleft.png"));
        }
        if(headState1[0] == 4||headState1[0] == 6||headState1[0] == 12)
        {
            gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(":/new/image/headright.png"));
        }

        //蛇身
        for (int i = 1; i < bodyLen1-1; i++)
        {

            if(headState1[i] == 1 || headState1[i] == 2||headState1[i] == 3 || headState1[i] == 4)
            {
                gamePainter->drawPixmap(headX1[i], headY1[i], 25, 25, QPixmap(":/new/image/body.png"));
            }
            /*if(headState[i] == 3 || headState[i] == 4)
            {
                gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/bodyleft.png"));
            }
            */
            if(headState1[i] == 5 || headState1[i] == 10)
            {
                gamePainter->drawPixmap(headX1[i], headY1[i], 25, 25, QPixmap(":/new/image/change1.png"));
            }
            if(headState1[i] == 6 || headState1[i] == 9)
            {
                gamePainter->drawPixmap(headX1[i], headY1[i], 25, 25, QPixmap(":/new/image/change3.png"));
            }
            if(headState1[i] == 7 || headState1[i] == 12)
            {
                gamePainter->drawPixmap(headX1[i], headY1[i], 25, 25, QPixmap(":/new/image/change2.png"));
            }
            if(headState1[i] == 8 || headState1[i] == 11)
            {
                gamePainter->drawPixmap(headX1[i], headY1[i], 25, 25, QPixmap(":/new/image/change4.png"));
            }
        }
           int i=bodyLen1-1;
           if(headState1[i] == 1||headState1[i] == 7||headState1[i] == 8)
                 gamePainter->drawPixmap(headX1[i], headY1[i], 25, 25, QPixmap(":/new/image/tail1.png"));
           if(headState1[i] == 2||headState1[i] == 9||headState1[i] == 10)
                 gamePainter->drawPixmap(headX1[i], headY1[i], 25, 25, QPixmap(":/new/image/tail3.png"));
           if(headState1[i] == 3||headState1[i] == 5||headState1[i] == 11)
                 gamePainter->drawPixmap(headX1[i], headY1[i], 25, 25, QPixmap(":/new/image/tail2.png"));
           if(headState1[i] == 4||headState1[i] == 6||headState1[i] == 12)
                 gamePainter->drawPixmap(headX1[i], headY1[i], 25, 25, QPixmap(":/new/image/tail4.png"));


    }


    if(skin_num1==3)    //绿色
    { qDebug()<<"皮肤13";
        QString snakeUp = QString(":/new/image/headup2%1.png").arg(this->minUp[0]++);
        QString snakeDown = QString(":/new/image/headdown2%1.png").arg(this->minDown[0]++);
        QString snakeLeft = QString(":/new/image/headleft2%1.png").arg(this->minLeft[0]++);
        QString snakeRight = QString(":/new/image/headright2%1.png").arg(this->minRight[0]++);

        //蛇头
        if(headState1[0] == 1)
        {
            gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(snakeUp));
        }
        if(headState1[0] == 2)
        {
            gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(snakeDown));
        }
        if(headState1[0] == 3)
        {
            gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(snakeLeft));
        }
        if(headState1[0] == 4)
        {
            gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(snakeRight));
        }
        if(headState1[0] == 5)
        {
            gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(":/new/image/headupleft2.png"));
        }
        if(headState1[0] == 6)
        {
            gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(":/new/image/headupright2.png"));
        }
        if(headState1[0] == 7)
        {
            gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(":/new/image/headleftup2.png"));
        }
        if(headState1[0] == 8)
        {
            gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(":/new/image/headrightup2.png"));
        }
        if(headState1[0] == 9)
        {
            gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(":/new/image/headleftdown2.png"));
        }
        if(headState1[0] == 10)
        {
            gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(":/new/image/headrightdown2.png"));
        }
        if(headState1[0] == 11)
        {
            gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(":/new/image/headdownleft2.png"));
        }
        if(headState1[0] == 12)
        {
            gamePainter->drawPixmap(headX1[0], headY1[0], 25, 25, QPixmap(":/new/image/headdownright2.png"));
        }
        //蛇身
        for (int i = 1; i < bodyLen1; i++)
        {
            if(headState1[i] == 1 || headState1[i] == 2)
            {
                gamePainter->drawPixmap(headX1[i], headY1[i], 25, 25, QPixmap(":/new/image/bodyup2.png"));
            }
            if(headState1[i] == 3 || headState1[i] == 4)
            {
                gamePainter->drawPixmap(headX1[i], headY1[i], 25, 25, QPixmap(":/new/image/bodyleft2.png"));
            }
            if(headState1[i] == 5 || headState1[i] == 10)
            {
                gamePainter->drawPixmap(headX1[i], headY1[i], 25, 25, QPixmap(":/new/image/upleft2.png"));
            }
            if(headState1[i] == 6 || headState1[i] == 9)
            {
                gamePainter->drawPixmap(headX1[i], headY1[i], 25, 25, QPixmap(":/new/image/upright2.png"));
            }
            if(headState1[i] == 7 || headState1[i] == 12)
            {
                gamePainter->drawPixmap(headX1[i], headY1[i], 25, 25, QPixmap(":/new/image/downright2.png"));
            }
            if(headState1[i] == 8 || headState1[i] == 11)
            {
                gamePainter->drawPixmap(headX1[i], headY1[i], 25, 25, QPixmap(":/new/image/downleft2.png"));
            }
        }

    }

    if(skin_num2==1)     //红色
    { qDebug()<<"皮肤21";
    QString snakeUp2 = QString(":/new/image/headup%1.png").arg(this->minUp[1]++);
    QString snakeDown2 = QString(":/new/image/headdown%1.png").arg(this->minDown[1]++);
    QString snakeLeft2 = QString(":/new/image/headleft%1.png").arg(this->minLeft[1]++);
    QString snakeRight2 = QString(":/new/image/headright%1.png").arg(this->minRight[1]++);
    //蛇头
    if(headState2[0] == 1)
    {
        gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(snakeUp2));
    }
    if(headState2[0] == 2)
    {
        gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(snakeDown2));
    }
    if(headState2[0] == 3)
    {
        gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(snakeLeft2));
    }
    if(headState2[0] == 4)
    {
        gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(snakeRight2));
    }
    if(headState2[0] == 5)
    {
        gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(":/new/image/headupleft.png"));
    }
    if(headState2[0] == 6)
    {
        gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(":/new/image/headupright.png"));
    }
    if(headState2[0] == 7)
    {
        gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(":/new/image/headleftup.png"));
    }
    if(headState2[0] == 8)
    {
        gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(":/new/image/headrightup.png"));
    }
    if(headState2[0] == 9)
    {
        gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(":/new/image/headleftdown.png"));
    }
    if(headState2[0] == 10)
    {
        gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(":/new/image/headrightdown.png"));
    }
    if(headState2[0] == 11)
    {
        gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(":/new/image/headdownleft.png"));
    }
    if(headState2[0] == 12)
    {
        gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(":/new/image/headdownright.png"));
    }
    //蛇身
    for (int i = 1; i < bodyLen2; i++)
    {
        if(headState2[i] == 1 || headState2[i] == 2)
        {
            gamePainter->drawPixmap(headX2[i], headY2[i], 25, 25, QPixmap(":/new/image/bodyup.png"));
        }
        if(headState2[i] == 3 || headState2[i] == 4)
        {
            gamePainter->drawPixmap(headX2[i], headY2[i], 25, 25, QPixmap(":/new/image/bodyleft.png"));
        }
        if(headState2[i] == 5 || headState2[i] == 10)
        {
            gamePainter->drawPixmap(headX2[i], headY2[i], 25, 25, QPixmap(":/new/image/upleft.png"));
        }
        if(headState2[i] == 6 || headState2[i] == 9)
        {
            gamePainter->drawPixmap(headX2[i], headY2[i], 25, 25, QPixmap(":/new/image/upright.png"));
        }
        if(headState2[i] == 7 || headState2[i] == 12)
        {
            gamePainter->drawPixmap(headX2[i], headY2[i], 25, 25, QPixmap(":/new/image/downright.png"));
        }
        if(headState2[i] == 8 || headState2[i] == 11)
        {
            gamePainter->drawPixmap(headX2[i], headY2[i], 25, 25, QPixmap(":/new/image/downleft.png"));
        }
    }
    }


    if(skin_num2==2)     //米虫
    { qDebug()<<"皮肤22";

        if(headState2[0] == 1||headState2[0] == 7||headState2[0] == 8)
        {
            gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(":/new/image/headup.png"));
        }
        if(headState2[0] == 2||headState2[0] == 9||headState2[0] == 10)
        {
            gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(":/new/image/headdown.png"));
        }
        if(headState2[0] == 3||headState2[0] == 5||headState2[0] == 11)
        {
            gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(":/new/image/headleft.png"));
        }
        if(headState2[0] == 4||headState2[0] == 6||headState2[0] == 12)
        {
            gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(":/new/image/headright.png"));
        }

        //蛇身
        for (int i = 1; i < bodyLen2-1; i++)
        {

            if(headState2[i] == 1 || headState2[i] == 2||headState2[i] == 3 || headState2[i] == 4)
            {
                gamePainter->drawPixmap(headX2[i], headY2[i], 25, 25, QPixmap(":/new/image/body.png"));
            }
            /*if(headState[i] == 3 || headState[i] == 4)
            {
                gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/bodyleft.png"));
            }
            */
            if(headState2[i] == 5 || headState2[i] == 10)
            {
                gamePainter->drawPixmap(headX2[i], headY2[i], 25, 25, QPixmap(":/new/image/change1.png"));
            }
            if(headState2[i] == 6 || headState2[i] == 9)
            {
                gamePainter->drawPixmap(headX2[i], headY2[i], 25, 25, QPixmap(":/new/image/change3.png"));
            }
            if(headState2[i] == 7 || headState2[i] == 12)
            {
                gamePainter->drawPixmap(headX2[i], headY2[i], 25, 25, QPixmap(":/new/image/change2.png"));
            }
            if(headState2[i] == 8 || headState2[i] == 11)
            {
                gamePainter->drawPixmap(headX2[i], headY2[i], 25, 25, QPixmap(":/new/image/change4.png"));
            }
        }
           int i=bodyLen2-1;
           if(headState2[i] == 1||headState2[i] == 7||headState2[i] == 8)
                 gamePainter->drawPixmap(headX2[i], headY2[i], 25, 25, QPixmap(":/new/image/tail1.png"));
           if(headState2[i] == 2||headState2[i] == 9||headState2[i] == 10)
                 gamePainter->drawPixmap(headX2[i], headY2[i], 25, 25, QPixmap(":/new/image/tail3.png"));
           if(headState2[i] == 3||headState2[i] == 5||headState2[i] == 11)
                 gamePainter->drawPixmap(headX2[i], headY2[i], 25, 25, QPixmap(":/new/image/tail2.png"));
           if(headState2[i] == 4||headState2[i] == 6||headState2[i] == 12)
                 gamePainter->drawPixmap(headX2[i], headY2[i], 25, 25, QPixmap(":/new/image/tail4.png"));


    }


    if(skin_num2==3)    //绿色
    {
 qDebug()<<"皮肤23";
        QString snakeUp2 = QString(":/new/image/headup2%1.png").arg(this->minUp[1]++);
        QString snakeDown2 = QString(":/new/image/headdown2%1.png").arg(this->minDown[1]++);
        QString snakeLeft2 = QString(":/new/image/headleft2%1.png").arg(this->minLeft[1]++);
        QString snakeRight2 = QString(":/new/image/headright2%1.png").arg(this->minRight[1]++);
        //蛇头
        if(headState2[0] == 1)
        {
            gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(snakeUp2));
        }
        if(headState2[0] == 2)
        {
            gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(snakeDown2));
        }
        if(headState2[0] == 3)
        {
            gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(snakeLeft2));
        }
        if(headState2[0] == 4)
        {
            gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(snakeRight2));
        }
        if(headState2[0] == 5)
        {
            gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(":/new/image/headupleft2.png"));
        }
        if(headState2[0] == 6)
        {
            gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(":/new/image/headupright2.png"));
        }
        if(headState2[0] == 7)
        {
            gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(":/new/image/headleftup2.png"));
        }
        if(headState2[0] == 8)
        {
            gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(":/new/image/headrightup2.png"));
        }
        if(headState2[0] == 9)
        {
            gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(":/new/image/headleftdown2.png"));
        }
        if(headState2[0] == 10)
        {
            gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(":/new/image/headrightdown2.png"));
        }
        if(headState2[0] == 11)
        {
            gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(":/new/image/headdownleft2.png"));
        }
        if(headState2[0] == 12)
        {
            gamePainter->drawPixmap(headX2[0], headY2[0], 25, 25, QPixmap(":/new/image/headdownright2.png"));
        }
        //蛇身
        for (int i = 1; i < bodyLen2; i++)
        {
            if(headState2[i] == 1 || headState2[i] == 2)
            {
                gamePainter->drawPixmap(headX2[i], headY2[i], 25, 25, QPixmap(":/new/image/bodyup2.png"));
            }
            if(headState2[i] == 3 || headState2[i] == 4)
            {
                gamePainter->drawPixmap(headX2[i], headY2[i], 25, 25, QPixmap(":/new/image/bodyleft2.png"));
            }
            if(headState2[i] == 5 || headState2[i] == 10)
            {
                gamePainter->drawPixmap(headX2[i], headY2[i], 25, 25, QPixmap(":/new/image/upleft2.png"));
            }
            if(headState2[i] == 6 || headState2[i] == 9)
            {
                gamePainter->drawPixmap(headX2[i], headY2[i], 25, 25, QPixmap(":/new/image/upright2.png"));
            }
            if(headState2[i] == 7 || headState2[i] == 12)
            {
                gamePainter->drawPixmap(headX2[i], headY2[i], 25, 25, QPixmap(":/new/image/downright2.png"));
            }
            if(headState2[i] == 8 || headState2[i] == 11)
            {
                gamePainter->drawPixmap(headX2[i], headY2[i], 25, 25, QPixmap(":/new/image/downleft2.png"));
            }
        }


    }
    //食物
    gamePainter->drawPixmap(foodX, foodY, 25, 25, QPixmap(":/new/image/food.png"));

    delete gamePainter;
}

gamewidget_3::~gamewidget_3()
{
    delete ui;
}

void gamewidget_3::keyPressEvent(QKeyEvent *event)
{
    //1上  2下  3左  4右
    //1上，2下，3左，4右，5上左，6上右，7左上，8右上，9左下，10右下，11下左，12下右
    preDirection[0] = direction[0];
    preDirection[1] = direction[1];
    switch (event->key())
    {
    case Qt::Key_Up:
        if(isKey == false ||preDirection[0] == 2)
        {
            return;
        }
        if(preDirection[0] == 3)
        {
            headState1[0] = 7;
        }
        if(preDirection[0] == 4)
        {
            headState1[0] = 8;
        }
        direction[0] = 1;
        break;
    case Qt::Key_W:
        if(isKey == false ||preDirection[1] == 2)
        {
            return;
        }
        if(preDirection[1] == 3)
        {
            headState2[0] = 7;
        }
        if(preDirection[1] == 4)
        {
            headState2[0] = 8;
        }
        direction[1] = 1;
        break;

    case Qt::Key_Down:
        if(isKey == false || preDirection[0] == 1)
        {
            return;
        }
        if(preDirection[0] == 3)
        {
            headState1[0] = 9;
        }
        if(preDirection[0] == 4)
        {
            headState1[0] = 10;
        }
        direction[0] = 2;
        break;

    case Qt::Key_S:
        if(isKey == false || preDirection[1] == 1)
        {
            return;
        }
        if(preDirection[1] == 3)
        {
            headState2[0] = 9;
        }
        if(preDirection[1] == 4)
        {
            headState2[0] = 10;
        }
        direction[1] = 2;
        break;

    case Qt::Key_Left:
        if(isKey == false || preDirection[0] == 4)
        {
            return;
        }
        if(preDirection[0] == 1)
        {
            headState1[0] = 5;
        }
        if(preDirection[0] == 2)
        {
            headState1[0] = 11;
        }
        direction[0] = 3;
        break;
    case Qt::Key_A:
        if(isKey == false || preDirection[1] == 4)
        {
            return;
        }
        if(preDirection[1] == 1)
        {
            headState2[0] = 5;
        }
        if(preDirection[1] == 2)
        {
            headState2[0] = 11;
        }
        direction[1] = 3;
        break;

    case Qt::Key_Right:
        if(isKey == false || preDirection[0] == 3)
        {
            return;
        }
        if(preDirection[0] == 1)
        {
            headState1[0] = 6;
        }
        if(preDirection[0] == 2)
        {
            headState1[0] = 12;
        }
        direction[0] = 4;
        break;
    case Qt::Key_D:
        if(isKey == false || preDirection[1] == 3)
        {
            return;
        }
        if(preDirection[1] == 1)
        {
            headState2[0] = 6;
        }
        if(preDirection[1] == 2)
        {
            headState2[0] = 12;
        }
        direction[1] = 4;
        break;
    default:
        return;
    }
    isKey = false;
    update();
}

void gamewidget_3::snakeMove()
{

    for (int i = bodyLen1 - 1; i > 0; i--)
    {
        headX1[i] = headX1[i - 1];
        headY1[i] = headY1[i - 1];
        headState1[i] = headState1[i - 1];
    }

    if(headState1[0] == 5 || headState1[0] == 11)
    {
        headState1[0] = 3;
    }
    if(headState1[0] == 6 || headState1[0] == 12)
    {
        headState1[0] = 4;
    }
    if(headState1[0] == 7 || headState1[0] == 8)
    {
        headState1[0] = 1;
    }
    if(headState1[0] == 9 || headState1[0] == 10)
    {
        headState1[0] = 2;
    }

    if(direction[0] == 1)
    {
        headY1[0] = headY1[0] - 25;
    }
    else if(direction[0] == 2)
    {
        headY1[0] = headY1[0] + 25;
    }
    else if(direction[0] == 3)
    {
        headX1[0] = headX1[0] - 25;
    }
    else if(direction[0] == 4)
    {
        headX1[0] = headX1[0] + 25;
    }


    for (int i = bodyLen2 - 1; i > 0; i--)
    {
        headX2[i] = headX2[i - 1];
        headY2[i] = headY2[i - 1];
        headState2[i] = headState2[i - 1];
    }

    if(headState2[0] == 5 || headState2[0] == 11)
    {
        headState2[0] = 3;
    }
    if(headState2[0] == 6 || headState2[0] == 12)
    {
        headState2[0] = 4;
    }
    if(headState2[0] == 7 || headState2[0] == 8)
    {
        headState2[0] = 1;
    }
    if(headState2[0] == 9 || headState2[0] == 10)
    {
        headState2[0] = 2;
    }

    if(direction[1] == 1)
    {
        headY2[0] = headY2[0] - 25;
    }
    else if(direction[1] == 2)
    {
        headY2[0] = headY2[0] + 25;
    }
    else if(direction[1] == 3)
    {
        headX2[0] = headX2[0] - 25;
    }
    else if(direction[1] == 4)
    {
        headX2[0] = headX2[0] + 25;
    }

    //穿墙
    /*if(headX1[0] < 0)
    {
        headX1[0] = 600 - 25;
        //qDebug() << this->width();
    }
    else if(headX1[0] == 600)
    {
        headX1[0] = 0;
    }
    else if(headY1[0] < 0)
    {
        headY1[0] = this->height() -25;
    }
    if(headY1[0] == this->height())
    {
        headY1[0] = 0;
    }

    if(headX2[0] < 0)
    {
        headX2[0] = 600 - 25;
        //qDebug() << this->width();
    }
    else if(headX2[0] == 600)
    {
        headX2[0] = 0;
    }
    else if(headY2[0] < 0)
    {
        headY2[0] = this->height() -25;
    }
    if(headY2[0] == this->height())
    {
        headY2[0] = 0;
    }
    */

    //吃的判定
    if(headX1[0] == foodX && headY1[0] == foodY)
    {
        while(1)
        {
            int flag = 1,flag1=1;
            foodX = (qrand() % 24) *25;      //重新生成食物
            foodY = (qrand() % 18) *25;
            for (int i = 0; i < bodyLen1||i <bodyLen2; i++)
            {
                if((headX1[i] == foodX && headY1[i] == foodY)||(headX2[i] == foodX && headY2[i] == foodY))
                {
                    flag = 0;
                    break;
                }
            }
            if(foodX==0||foodX==575||foodY==0||foodY==425)
                flag1=0;

            if(flag == 1 && flag1 == 1)
             {
                 break;
             }

        }
        bodyLen1++;
        score1++;
        headX1[bodyLen1 - 1] = headX1[bodyLen1 - 2];
        headY1[bodyLen1 - 1] = headY1[bodyLen1 - 2];
        headState1[bodyLen1 - 1] = headState1[bodyLen1 - 2];
    }

    if(headX2[0] == foodX && headY2[0] == foodY)
    {
        while(1)
        {
            int flag = 1,flag1=1;
            foodX = (qrand() % 24) *25;      //重新生成食物
            foodY = (qrand() % 18) *25;
            for (int i = 0; i < bodyLen1||i <bodyLen2; i++)
            {
                if((headX1[i] == foodX && headY1[i] == foodY)||(headX2[i] == foodX && headY2[i] == foodY))
                {
                    flag = 0;
                    break;
                }
            }
            if(foodX==0||foodX==575||foodY==0||foodY==425)
                flag1=0;

            if(flag == 1 && flag1 == 1)
             {
                 break;
             }
        }
        bodyLen2++;
        score2++;
        headX2[bodyLen2 - 1] = headX2[bodyLen2 - 2];
        headY2[bodyLen2 - 1] = headY2[bodyLen2 - 2];
        headState2[bodyLen2 - 1] = headState2[bodyLen2 - 2];
    }

    //死亡判定
   for(int i = 1; i < bodyLen1; i++)
    {
        if(headX1[0] == headX1[i] && headY1[0] == headY1[i])
        {

            w.ss=1;
            timerGame->stop();
            timerAction->stop();
            isKey = false;
             //this->killTimer(this->timerid);//根据计时器的id关闭计时器（id起到区分多个定时器的作用，将开始与结束连起来
             QFont font("Adobe Caslon Pro Bold",15,75);
             ui->label->setFont(font);
             ui->label->setText("<center>Game Begin！！</center>");
             flag_timeout=true;
             /*if(score>my_data.score(3,player_name))
             {
                 my_data.modify(3,player_name,score);
             }*/
             this->close();
             gameSound->stop();
             w.set_current_score(score1,score2);//传成绩
             w.set_player_name(player_2);//传姓名
             //w.get_mode(3);
             w.see();
             w.show();
             timerGame->stop();
             timerAction->stop();
        }
        if(headX2[0] == headX1[i] && headY2[0] == headY1[i])
        {

            timerGame->stop();
            timerAction->stop();
            isKey = false;
             //this->killTimer(this->timerid);//根据计时器的id关闭计时器（id起到区分多个定时器的作用，将开始与结束连起来
             QFont font("Adobe Caslon Pro Bold",15,75);
             ui->label->setFont(font);
             ui->label->setText("<center>Game Begin！！</center>");
             flag_timeout=true;
             /*if(score>my_data.score(3,player_name))
             {
                 my_data.modify(3,player_name,score);
             }*/
             this->close();
             gameSound->stop();
             w.set_current_score(score1,score2);//传成绩
             w.set_player_name(player_1);//传姓名
             //w.get_mode(3);
             w.see();
             w.show();
             timerGame->stop();
             timerAction->stop();
        }


     }
   for(int i = 1; i < bodyLen2; i++)
    {
        if(headX2[0] == headX2[i] && headY2[0] == headY2[i])
        {

            timerGame->stop();
            timerAction->stop();
            isKey = false;
             //this->killTimer(this->timerid);//根据计时器的id关闭计时器（id起到区分多个定时器的作用，将开始与结束连起来
             QFont font("Adobe Caslon Pro Bold",15,75);
             ui->label->setFont(font);
             ui->label->setText("<center>Game Begin！！</center>");
             flag_timeout=true;
             /*if(score>my_data.score(3,player_name))
             {
                 my_data.modify(3,player_name,score);
             }*/
             this->close();
             gameSound->stop();
             w.set_current_score(score1,score2);//传成绩
             w.set_player_name(player_1);//传姓名
             //w.get_mode(3);
             w.see();
             w.show();
             timerGame->stop();
             timerAction->stop();
        }
        if(headX1[0] == headX2[i] && headY1[0] == headY2[i])
        {

            w.ss=1;
            timerGame->stop();
            timerAction->stop();
            isKey = false;
             //this->killTimer(this->timerid);//根据计时器的id关闭计时器（id起到区分多个定时器的作用，将开始与结束连起来
             QFont font("Adobe Caslon Pro Bold",15,75);
             ui->label->setFont(font);
             ui->label->setText("<center>Game Begin！！</center>");
             flag_timeout=true;
             /*if(score>my_data.score(3,player_name))
             {
                 my_data.modify(3,player_name,score);
             }*/
             this->close();
             gameSound->stop();
             w.set_current_score(score1,score2);//传成绩
             w.set_player_name(player_2);//传姓名
             //w.get_mode(3);
             w.see();
             w.show();
             timerGame->stop();
             timerAction->stop();
        }

     }
   if(headX1[0] == headX2[0] && headY1[0] == headY2[0])
   {

       timerGame->stop();
       timerAction->stop();
       isKey = false;
        //this->killTimer(this->timerid);//根据计时器的id关闭计时器（id起到区分多个定时器的作用，将开始与结束连起来
        QFont font("Adobe Caslon Pro Bold",15,75);
        ui->label->setFont(font);
        ui->label->setText("<center>Game Begin！！</center>");
        flag_timeout=true;
        /*if(score>my_data.score(3,player_name))
        {
            my_data.modify(3,player_name,score);
        }*/
        this->close();
        gameSound->stop();
        if(score1>score2){
        w.set_current_score(score1,score2);//传成绩
        w.set_player_name(player_1);//传姓名
        }
        else if(score1<score2)
        {
            w.ss=1;
            w.set_current_score(score1,score2);//传成绩
            w.set_player_name(player_2);//传姓名
        }
        else{
            w.ss=2;
            w.set_player_name(player_1,player_2);
            w.set_current_score(score1,score2);
        }
        //w.get_mode(3);
        w.see();
        w.show();
        timerGame->stop();
        timerAction->stop();
   }
   if((headX1[0]==0||headX1[0]==575||headY1[0]==0||headY1[0]==425)){
       w.ss=1;
       timerGame->stop();
       timerAction->stop();
       isKey = false;
        //this->killTimer(this->timerid);//根据计时器的id关闭计时器（id起到区分多个定时器的作用，将开始与结束连起来
        QFont font("Adobe Caslon Pro Bold",15,75);
        ui->label->setFont(font);
        ui->label->setText("<center>Game Begin！！</center>");
        flag_timeout=true;
        /*if(score>my_data.score(3,player_name))
        {
            my_data.modify(3,player_name,score);
        }*/
        this->close();
        gameSound->stop();
        w.set_current_score(score1,score2);//传成绩
        w.set_player_name(player_2);//传姓名
        //w.get_mode(3);
        w.see();
        w.show();
        timerGame->stop();
        timerAction->stop();
   }
   if((headX2[0]==0||headX2[0]==575||headY2[0]==0||headY2[0]==425)){
       timerGame->stop();
       timerAction->stop();
       isKey = false;
        //this->killTimer(this->timerid);//根据计时器的id关闭计时器（id起到区分多个定时器的作用，将开始与结束连起来
        QFont font("Adobe Caslon Pro Bold",15,75);
        ui->label->setFont(font);
        ui->label->setText("<center>Game Begin！！</center>");
        flag_timeout=true;
        /*if(score>my_data.score(3,player_name))
        {
            my_data.modify(3,player_name,score);
        }*/
        this->close();
        gameSound->stop();
        w.set_current_score(score1,score2);//传成绩
        w.set_player_name(player_1);//传姓名
        //w.get_mode(3);
        w.see();
        w.show();
        timerGame->stop();
        timerAction->stop();
   }

    update();

}

void gamewidget_3::closeEvent(QCloseEvent *e)
{
    if(flag_timeout==false){
        timerGame->stop();
        timerAction->stop();
        this->killTimer(this->timerid);
        int ret=QMessageBox::question(this,"操作询问","游戏还没有结束，小主您确定要先溜吗");
        if(ret==QMessageBox::Yes){
                e->accept();
                emit game_exit();
                qDebug()<<"窗口关闭";
                gameSound->stop();
                QFont font("Adobe Caslon Pro Bold",15,75);
                        ui->label->setFont(font);
                        ui->label->setText("<center>Game Begin！！</center>");
        }
        else{
            e->ignore();

            timerGame->start(300);    //计时器每300毫秒重新启动一次
            timerAction->start(75);
            timerid = this->startTimer(1000);
    }
    }
    else{
        e->accept();
       // emit game_exit();
        qDebug()<<"窗口关闭";
    }
}





//蛇动作
void gamewidget_3::snakeAction()
{
    //当大于4时重置为1
    if(headState1[0] == 1)
    {
        if(this->minUp[0] > 4)
        {
            this->minUp[0] = 1;
        }
    }
    if(headState1[0] == 2)
    {
        if(this->minDown[0] > 4)
        {
            this->minDown[0] = 1;
        }
    }
    if(headState1[0] == 3)
    {
        if(this->minLeft[0] > 4)
        {
            this->minLeft[0] = 1;
        }
    }
    if(headState1[0] == 4)
    {
        if(this->minRight[0] > 4)
        {
            this->minRight[0] = 1;
        }
    }
    if(headState2[0] == 1)
    {
        if(this->minUp[1] > 4)
        {
            this->minUp[1] = 1;
        }
    }
    if(headState2[0] == 2)
    {
        if(this->minDown[1] > 4)
        {
            this->minDown[1] = 1;
        }
    }
    if(headState2[0] == 3)
    {
        if(this->minLeft[1] > 4)
        {
            this->minLeft[1] = 1;
        }
    }
    if(headState2[0] == 4)
    {
        if(this->minRight[1] > 4)
        {
            this->minRight[1] = 1;
        }
    }
    update();
}


