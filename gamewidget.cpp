#include "gamewidget.h"
#include "ui_gamewidget.h"
#include <QKeyEvent>
#include <QTime>
#include <QtDebug>
#include <QMessageBox>
#include<QPainter>
#include<QPixmap>
#include <QMediaPlayer>
#include <QMediaPlaylist>


static int sec = 0;
int time1,time2,time3=0;
GameWidget::GameWidget(QWidget *parent) : QWidget(parent),
  ui(new Ui::gamewidget)
{
  ui->setupUi(this);
  pic_num=3;
  skin_num=3;
}
void GameWidget::timebegin()
{
    timerid = this->startTimer(1000);
}

void GameWidget::play()
{
    gameSound= new QMediaPlayer(this);
    gameList= new QMediaPlaylist(this);
    gameList->addMedia(QUrl("qrc:/new/image/music.wav"));//添加音乐
    gameList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);//循环播放
    gameSound->setMedia(gameList);

    gameSound->setVolume(n);
    gameSound->play();
    c1=1;
    c2=1;
    c3=1;
    my_data.createConnection();
    flag_timeout=false;
    sec=0;

  this->setFixedSize(800, 450);
  this->setWindowTitle("您瞧，这不是限时模式嘛？");

    qDebug() << this->width();
    //随机数种子
    qsrand(uint(QTime(0, 0, 0).secsTo(QTime::currentTime())));

    isKey = true;
    //初始化蛇
    direction = 4;
    headX[0] =(qrand() % 24)*25;    //随机生成向右的蛇
    while(headX[0]<100||headX[0]>500)
       {headX[0] =(qrand() % 24)*25;}
    headY[0] =(qrand() % 18) *25;
    headState[0] = 4;
    bodyLen = 4;
    score=0;
    for (int i = 1; i < bodyLen; i++)
    {
        headX[i] = headX[i - 1] - 25;
        headY[i] = headY[i - 1];
        headState[i] = headState[i - 1];
    }

    //初始化食物的位置，不能与蛇同在
    while(1)
    {
        int flag = 1;
        foodX = (qrand() % 24) *25;    ////
        foodY = (qrand() % 18) *25;
        for (int i = 0; i < bodyLen; i++)
        {
            if(headX[i] == foodX && headY[i] == foodY)
            {
                flag = 0;
                break;
            }
        }
        if(flag == 1)
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
                    QString("<center>当前成绩为:%1</center>").arg(score)
                    );
        QFont font_1("Microsoft YaHei",10,75);
        ui->label_3->setFont(font_1);

        ui->label_3->setText(
                    QString("<center>您最好成绩是:%1</center>").arg(my_data.score(1,player_name))
                    );
        ui->label_4->setFont(font_1);
        int*p=my_data.sort(1);
        ui->label_4->setText(
                    QString("<center>历史最高:%1</center>").arg(p[0])
                    );
    });
    timerAction->start(75);
    connect(&w,&endgame::close_end_win,[=]{
        emit game_exit();
    });
    //建道具
    tool=new QTimer(this);
    tool->start(5000);
    connect(tool,&QTimer::timeout,[=]{
        creattool();
    });

}

void GameWidget::creattool(){
   int aa=qrand() % 6;
   if(aa==0){
       while(1)
       {
           s1=1;
           int flag = 1,flag1=1;
           fastx = (qrand() % 24) *25;
           fasty = (qrand() % 18) *25;
           for (int i = 0; i < bodyLen; i++)
           {
               if(headX[i] == fastx && headY[i] == fasty)
               {
                   flag = 0;
                   break;
               }
           }
           if(fastx==foodX&&fasty==foodY){
               flag1=0;
           }
           if(fastx==slowx&&fasty==slowy){
               flag1=0;
           }
           if(fastx==mashx&&fasty==mashy){
               flag1=0;
           }
           if(giftx==fastx&&gifty==fasty){
               flag1=0;
           }
           if(flag == 1&&flag1==1)
           {
               break;
           }
       }
   }
   if(aa==1){
       while(1)
       {
           s2=1;
           int flag = 1,flag1=1;
           slowx = (qrand() % 24) *25;
           slowy = (qrand() % 18) *25;
           for (int i = 0; i < bodyLen; i++)
           {
               if(headX[i] == slowx && headY[i] == slowy)
               {
                   flag = 0;
                   break;
               }
           }
           if(slowx==foodX&&slowy==foodY){
               flag1=0;
           }
           if(slowx==mashx&&slowy==mashy){
               flag1=0;
           }
           if(slowx==fastx&&slowy==fasty){
               flag1=0;
           }
           if(giftx==slowx&&gifty==slowy){
               flag1=0;
           }
           if(flag == 1&&flag1==1)
           {
               break;
           }
       }
   }
   if(aa==2){
       while(1)
       {
           s3=1;
           int flag = 1,flag1=1;
           mashx = (qrand() % 24) *25;
           mashy = (qrand() % 18) *25;
           for (int i = 0; i < bodyLen; i++)
           {
               if(headX[i] == mashx && headY[i] == mashy)
               {
                   flag = 0;
                   break;
               }
           }
           if(mashx==foodX&&mashy==foodY){
               flag1=0;
           }
           if(mashx==slowx&&mashy==slowy){
               flag1=0;
           }
           if(mashx==fastx&&mashy==fasty){
               flag1=0;
           }
           if(giftx==mashx&&gifty==mashy){
               flag1=0;
           }
           if(flag == 1&&flag1==1)
           {
               break;
           }
       }
   }

   if(aa==3){
       while(1)
       {
           s4=1;
           int flag = 1,flag1=1;
           giftx = (qrand() % 24) *25;
           gifty = (qrand() % 18) *25;
           for (int i = 0; i < bodyLen; i++)
           {
               if(headX[i] == giftx && headY[i] == gifty)
               {
                   flag = 0;
                   break;
               }
           }
           if(giftx==foodX&&gifty==foodY){
               flag1=0;
           }
           if(giftx==slowx&&gifty==slowy){
               flag1=0;
           }
           if(giftx==fastx&&gifty==fasty){
               flag1=0;
           }
           if(giftx==mashx&&gifty==mashy){
               flag1=0;
           }
           if(flag == 1&&flag1==1)
           {
               break;
           }
       }
   }
}

void GameWidget::get_skin_num(int cin_skin_num)
{
    skin_num=cin_skin_num;
}

void GameWidget::getn(int m)
{
    n=m;
}

void GameWidget::get_player_name(QString in_name)
{
    player_name=in_name;
}

void GameWidget::get_pic_num(int cin_pic_num)
{
    pic_num=cin_pic_num;
}

void GameWidget::timerEvent(QTimerEvent *e)
{
    if(e->timerId()==timerid)
    //static int sec = 0;
    {
    QFont font("Microsoft YaHei",10,75);
    ui->label->setFont(font);

    ui->label->setText(
                QString("<center>游戏剩余时间:%1秒</center>").arg(60-sec)
                );

    sec=sec+1;
    if(sec==60)
    {
        cc=0;
        timerGame->stop();
        timerAction->stop();
        this->killTimer(this->timerid);//根据计时器的id关闭计时器（id起到区分多个定时器的作用，将开始与结束连起来

        QFont font("Adobe Caslon Pro Bold",15,75);
        ui->label->setFont(font);
        ui->label->setText("<center>Game Begin！！</center>");
        ui->label_5->setText("<center> </center>");
        flag_timeout=true;
        if(score>my_data.score(1,player_name)){
            my_data.modify(1,player_name,score);
        }
        this->close();
        gameSound->stop();
        w.set_current_score(score);//传成绩
        w.set_player_name(player_name);//传姓名
        w.get_mode(1);
        w.see();
        w.show();
        timerGame->stop();
        timerAction->stop();
        tool->stop();
        this->killTimer(this->timerid);
        this->killTimer(this->timerid2);
    }
    }

    if(e->timerId()==timerid2)
    {
        time1++;
        if(time1==10)
        {
            this->killTimer(this->timerid2);
            timerGame->stop();
            timerAction->stop();
            ui->label_5->setText("<center> </center>");

            timerGame->start(300);
            timerAction->start(75);
            c1=1;
            time1++;
        }
    }
    if(e->timerId()==timerid3)
    {
        time2++;
        if(time2==10)
          {
            this->killTimer(this->timerid3);
            timerGame->stop();
            timerAction->stop();
            ui->label_5->setText("<center> </center>");

            timerGame->start(300);
            timerAction->start(75);
            time2++;
            c2=1;
           }
    }
    if(e->timerId()==timerid4)
    {
        time3++;
        if(time3==10)
         {
            this->killTimer(this->timerid4);
            ui->label_5->setText("<center> </center>");
            cc=0;
            time3++;
            c3=1;
         }

    }
}

void GameWidget::paintEvent(QPaintEvent *)
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


    QPainter toolPainter(this);
    if(s1==1){
    toolPainter.drawPixmap(fastx,fasty,25,25,QString(":/new/image/secret.png"));
    }
    else{
    toolPainter.drawPixmap(-50,-50,25,25,QString(":/new/image/secret.png"));
    }

    if(s2==1){
    toolPainter.drawPixmap(slowx,slowy,25,25,QString(":/new/image/secret.png"));
    }
    else{
    toolPainter.drawPixmap(-50,-50,25,25,QString(":/new/image/secret.png"));
    }

    if(s3==1){
    toolPainter.drawPixmap(mashx,mashy,25,25,QString(":/new/image/secret.png"));
    }
    else{
    toolPainter.drawPixmap(-50,-50,25,25,QString(":/new/image/secret.png"));
    }
    if(s4==1){
    toolPainter.drawPixmap(giftx,gifty,25,25,QString(":/new/image/secret.png"));
    }
    else{
    toolPainter.drawPixmap(-50,-50,25,25,QString(":/new/image/secret.png"));
    }


    gamePainter = new QPainter(this);
    //动次打次（吃吃吃）
    if(skin_num==1)     //红色
    {
    QString snakeUp = QString(":/new/image/headup%1.png").arg(this->minUp++);
    QString snakeDown = QString(":/new/image/headdown%1.png").arg(this->minDown++);
    QString snakeLeft = QString(":/new/image/headleft%1.png").arg(this->minLeft++);
    QString snakeRight = QString(":/new/image/headright%1.png").arg(this->minRight++);
    //蛇头
    if(headState[0] == 1)
    {
        gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(snakeUp));
    }
    if(headState[0] == 2)
    {
        gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(snakeDown));
    }
    if(headState[0] == 3)
    {
        gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(snakeLeft));
    }
    if(headState[0] == 4)
    {
        gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(snakeRight));
    }
    if(headState[0] == 5)
    {
        gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headupleft.png"));
    }
    if(headState[0] == 6)
    {
        gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headupright.png"));
    }
    if(headState[0] == 7)
    {
        gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headleftup.png"));
    }
    if(headState[0] == 8)
    {
        gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headrightup.png"));
    }
    if(headState[0] == 9)
    {
        gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headleftdown.png"));
    }
    if(headState[0] == 10)
    {
        gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headrightdown.png"));
    }
    if(headState[0] == 11)
    {
        gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headdownleft.png"));
    }
    if(headState[0] == 12)
    {
        gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headdownright.png"));
    }
    //蛇身
    for (int i = 1; i < bodyLen; i++)
    {
        if(headState[i] == 1 || headState[i] == 2)
        {
            gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/bodyup.png"));
        }
        if(headState[i] == 3 || headState[i] == 4)
        {
            gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/bodyleft.png"));
        }
        if(headState[i] == 5 || headState[i] == 10)
        {
            gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/upleft.png"));
        }
        if(headState[i] == 6 || headState[i] == 9)
        {
            gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/upright.png"));
        }
        if(headState[i] == 7 || headState[i] == 12)
        {
            gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/downright.png"));
        }
        if(headState[i] == 8 || headState[i] == 11)
        {
            gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/downleft.png"));
        }
    }
    }


    if(skin_num==2)     //米虫
    {

        if(headState[0] == 1||headState[0] == 7||headState[0] == 8)
        {
            gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headup.png"));
        }
        if(headState[0] == 2||headState[0] == 9||headState[0] == 10)
        {
            gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headdown.png"));
        }
        if(headState[0] == 3||headState[0] == 5||headState[0] == 11)
        {
            gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headleft.png"));
        }
        if(headState[0] == 4||headState[0] == 6||headState[0] == 12)
        {
            gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headright.png"));
        }

        //蛇身
        for (int i = 1; i < bodyLen-1; i++)
        {

            if(headState[i] == 1 || headState[i] == 2||headState[i] == 3 || headState[i] == 4)
            {
                gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/body.png"));
            }
            /*if(headState[i] == 3 || headState[i] == 4)
            {
                gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/bodyleft.png"));
            }
            */
            if(headState[i] == 5 || headState[i] == 10)
            {
                gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/change1.png"));
            }
            if(headState[i] == 6 || headState[i] == 9)
            {
                gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/change3.png"));
            }
            if(headState[i] == 7 || headState[i] == 12)
            {
                gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/change2.png"));
            }
            if(headState[i] == 8 || headState[i] == 11)
            {
                gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/change4.png"));
            }
        }
           int i=bodyLen-1;
           if(headState[i] == 1||headState[i] == 7||headState[i] == 8)
                 gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/tail1.png"));
           if(headState[i] == 2||headState[i] == 9||headState[i] == 10)
                 gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/tail3.png"));
           if(headState[i] == 3||headState[i] == 5||headState[i] == 11)
                 gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/tail2.png"));
           if(headState[i] == 4||headState[i] == 6||headState[i] == 12)
                 gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/tail4.png"));


    }


    if(skin_num==3)    //绿色
    {
        QString snakeUp = QString(":/new/image/headup2%1.png").arg(this->minUp++);
        QString snakeDown = QString(":/new/image/headdown2%1.png").arg(this->minDown++);
        QString snakeLeft = QString(":/new/image/headleft2%1.png").arg(this->minLeft++);
        QString snakeRight = QString(":/new/image/headright2%1.png").arg(this->minRight++);

        //蛇头
        if(headState[0] == 1)
        {
            gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(snakeUp));
        }
        if(headState[0] == 2)
        {
            gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(snakeDown));
        }
        if(headState[0] == 3)
        {
            gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(snakeLeft));
        }
        if(headState[0] == 4)
        {
            gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(snakeRight));
        }
        if(headState[0] == 5)
        {
            gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headupleft2.png"));
        }
        if(headState[0] == 6)
        {
            gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headupright2.png"));
        }
        if(headState[0] == 7)
        {
            gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headleftup2.png"));
        }
        if(headState[0] == 8)
        {
            gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headrightup2.png"));
        }
        if(headState[0] == 9)
        {
            gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headleftdown2.png"));
        }
        if(headState[0] == 10)
        {
            gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headrightdown2.png"));
        }
        if(headState[0] == 11)
        {
            gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headdownleft2.png"));
        }
        if(headState[0] == 12)
        {
            gamePainter->drawPixmap(headX[0], headY[0], 25, 25, QPixmap(":/new/image/headdownright2.png"));
        }
        //蛇身
        for (int i = 1; i < bodyLen; i++)
        {
            if(headState[i] == 1 || headState[i] == 2)
            {
                gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/bodyup2.png"));
            }
            if(headState[i] == 3 || headState[i] == 4)
            {
                gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/bodyleft2.png"));
            }
            if(headState[i] == 5 || headState[i] == 10)
            {
                gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/upleft2.png"));
            }
            if(headState[i] == 6 || headState[i] == 9)
            {
                gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/upright2.png"));
            }
            if(headState[i] == 7 || headState[i] == 12)
            {
                gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/downright2.png"));
            }
            if(headState[i] == 8 || headState[i] == 11)
            {
                gamePainter->drawPixmap(headX[i], headY[i], 25, 25, QPixmap(":/new/image/downleft2.png"));
            }
        }

    }

    //食物
    gamePainter->drawPixmap(foodX, foodY, 25, 25, QPixmap(":/new/image/food.png"));

    delete gamePainter;

}

GameWidget::~GameWidget()
{
    delete ui;
}

void GameWidget::keyPressEvent(QKeyEvent *event)
{
    //1上  2下  3左  4右
    //1上，2下，3左，4右，5上左，6上右，7左上，8右上，9左下，10右下，11下左，12下右
    if(cc==0){
    preDirection = direction;
    switch (event->key())
    {
    case Qt::Key_W:
    case Qt::Key_Up:
        if(isKey == false || preDirection == 2)
        {
            return;
        }
        if(preDirection == 3)
        {
            headState[0] = 7;
        }
        if(preDirection == 4)
        {
            headState[0] = 8;
        }
        direction = 1;
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        if(isKey == false || preDirection == 1)
        {
            return;
        }
        if(preDirection == 3)
        {
            headState[0] = 9;
        }
        if(preDirection == 4)
        {
            headState[0] = 10;
        }
        direction = 2;
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        if(isKey == false || preDirection == 4)
        {
            return;
        }
        if(preDirection == 1)
        {
            headState[0] = 5;
        }
        if(preDirection == 2)
        {
            headState[0] = 11;
        }
        direction = 3;
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        if(isKey == false || preDirection == 3)
        {
            return;
        }
        if(preDirection == 1)
        {
            headState[0] = 6;
        }
        if(preDirection == 2)
        {
            headState[0] = 12;
        }
        direction = 4;
        break;
    default:
        return;
    }
    isKey = false;
    update();
    }

    //反向
    if(cc==1){
        preDirection = direction;
        switch (event->key())
        {
        case Qt::Key_S:
        case Qt::Key_Down:
            if(isKey == false || preDirection == 2)
            {
                return;
            }
            if(preDirection == 3)
            {
                headState[0] = 7;
            }
            if(preDirection == 4)
            {
                headState[0] = 8;
            }
            direction = 1;
            break;
        case Qt::Key_W:
        case Qt::Key_Up:
            if(isKey == false || preDirection == 1)
            {
                return;
            }
            if(preDirection == 3)
            {
                headState[0] = 9;
            }
            if(preDirection == 4)
            {
                headState[0] = 10;
            }
            direction = 2;
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            if(isKey == false || preDirection == 4)
            {
                return;
            }
            if(preDirection == 1)
            {
                headState[0] = 5;
            }
            if(preDirection == 2)
            {
                headState[0] = 11;
            }
            direction = 3;
            break;
        case Qt::Key_A:
        case Qt::Key_Left:
            if(isKey == false || preDirection == 3)
            {
                return;
            }
            if(preDirection == 1)
            {
                headState[0] = 6;
            }
            if(preDirection == 2)
            {
                headState[0] = 12;
            }
            direction = 4;
            break;
        default:
            return;
        }
        isKey = false;
        update();

    }
}

void GameWidget::snakeMove()
{

    for (int i = bodyLen - 1; i > 0; i--)
    {
        headX[i] = headX[i - 1];
        headY[i] = headY[i - 1];
        headState[i] = headState[i - 1];
    }

    if(headState[0] == 5 || headState[0] == 11)
    {
        headState[0] = 3;
    }
    if(headState[0] == 6 || headState[0] == 12)
    {
        headState[0] = 4;
    }
    if(headState[0] == 7 || headState[0] == 8)
    {
        headState[0] = 1;
    }
    if(headState[0] == 9 || headState[0] == 10)
    {
        headState[0] = 2;
    }

    if(direction == 1)
    {
        headY[0] = headY[0] - 25;
    }
    else if(direction == 2)
    {
        headY[0] = headY[0] + 25;
    }
    else if(direction == 3)
    {
        headX[0] = headX[0] - 25;
    }
    else if(direction == 4)
    {
        headX[0] = headX[0] + 25;
    }

    //穿墙
    if(headX[0] < 0)
    {
        headX[0] = 600 - 25;
        //qDebug() << this->width();
    }
    else if(headX[0] == 600)
    {
        headX[0] = 0;
    }
    else if(headY[0] < 0)
    {
        headY[0] = this->height() -25;
    }
    if(headY[0] == this->height())
    {
        headY[0] = 0;
    }

    //吃的判定
    if(headX[0] == foodX && headY[0] == foodY)
    {

        while(1)
        {
            int flag = 1,flag1=1;
            foodX = (qrand() % 24) *25;      //重新生成食物
            foodY = (qrand() % 18) *25;
            for (int i = 0; i < bodyLen; i++)
            {
                if(headX[i] == foodX && headY[i] == foodY)
                {
                    flag = 0;
                    break;
                }
            }
            if(fastx==foodX&&fasty==foodY){
                flag1=0;
            }
            if(foodX==slowx&&foodY==slowy){
                flag1=0;
            }
            if(foodX==mashx&&foodY==mashy){
                flag1=0;
            }
            if(giftx==foodX&&gifty==foodY){
                flag1=0;
            }
            if(flag == 1&&flag1==1)
            {
                break;
            }
        }
        bodyLen++;
        score++;
        headX[bodyLen - 1] = headX[bodyLen - 2];
        headY[bodyLen - 1] = headY[bodyLen - 2];
        headState[bodyLen - 1] = headState[bodyLen - 2];
    }

    //吃加速道具判定
    if(headX[0] == fastx && headY[0] == fasty){
        qDebug()<<"吃到加速道具啦";
        QFont font("Microsoft YaHei",10,75);
        ui->label_5->setFont(font);
        ui->label_5->setText("<center>吃到加速道具啦！</center>");
        s1=0;
        c1=0;
        timerGame->stop();
        timerAction->stop();
        timerGame->start(150);
        timerAction->start(37);
        this->killTimer(this->timerid2);
        timerid2 = this->startTimer(1000);
        time1=0;
    }
    //减速
    if(headX[0] == slowx && headY[0] == slowy){
        qDebug()<<"吃到减速道具啦";
        QFont font("Microsoft YaHei",10,75);
        ui->label_5->setFont(font);
        ui->label_5->setText("<center>吃到减速道具啦！</center>");
        s2=0;
        c2=0;
        timerGame->stop();
        timerAction->stop();
        timerGame->start(600);
        timerAction->start(150);
        this->killTimer(this->timerid3);
        timerid3 = this->startTimer(1000);
        time2=0;
    }
    //毒蘑菇
    if(headX[0] == mashx && headY[0] == mashy){
        qDebug()<<"吃到毒蘑菇啦";
        QFont font("Microsoft YaHei",10,75);
        ui->label_5->setFont(font);
        ui->label_5->setText("<center>吃到毒蘑菇啦！</center>");
        s3=0;
        c3=0;
        cc=1;
        toolmash = new QTimer(this);
        this->killTimer(this->timerid4);
        timerid4 = this->startTimer(1000);
        time3=0;

    }
    if(headX[0] == giftx && headY[0] == gifty){
        s4=0;
        qDebug()<<"吃到礼物啦啦";
        QFont font("Microsoft YaHei",10,75);
        ui->label_5->setFont(font);
        ui->label_5->setText("<center>吃到礼物啦！</center>");
        score=score+3;

    }


    //死亡判定
    for(int i = 1; i < bodyLen; i++)
    {
        if(headX[0] == headX[i] && headY[0] == headY[i])
        {
          score=score-(bodyLen-i);
          bodyLen=i;

        }

     }

    update();
}

void GameWidget::closeEvent(QCloseEvent *e)
{
    if(flag_timeout==false){
        timerGame->stop();
        timerAction->stop();
        tool->stop();
        this->killTimer(this->timerid);
        this->killTimer(this->timerid2);
        this->killTimer(this->timerid3);
        this->killTimer(this->timerid4);
        int ret=QMessageBox::question(this,"操作询问","游戏还没有结束，小主您确定要先溜吗");
        if(ret==QMessageBox::Yes){
                e->accept();
                emit game_exit();
                qDebug()<<"窗口关闭";
                gameSound->stop();
                cc=0;
                QFont font("Adobe Caslon Pro Bold",15,75);
                        ui->label->setFont(font);
                        ui->label->setText("<center>Game Begin！！</center>");
                        ui->label_5->setText("<center> </center>");
        }
        else{
            e->ignore();
            if(c1==0)
            {
                timerGame->start(150);    //计时器每300毫秒重新启动一次
                timerAction->start(37);
            }
            if(c2==0)
            {
                timerGame->start(600);    //计时器每300毫秒重新启动一次
                timerAction->start(150);
            }
            if(c1==1&&c2==1)
            {
                timerGame->start(300);    //计时器每300毫秒重新启动一次
                timerAction->start(75);
            }
            tool->start(5000);
            timerid = this->startTimer(1000);
            timerid2 = this->startTimer(1000);
            timerid3 =this->startTimer(1000);
            timerid4 =this->startTimer(1000);

    }
    }
    else{
        e->accept();
       // emit game_exit();
        qDebug()<<"窗口关闭";
    }
}





//蛇动作
void GameWidget::snakeAction()
{
    //当大于4时重置为1
    if(headState[0] == 1)
    {
        if(this->minUp > 4)
        {
            this->minUp = 1;
        }
    }
    if(headState[0] == 2)
    {
        if(this->minDown > 4)
        {
            this->minDown = 1;
        }
    }
    if(headState[0] == 3)
    {
        if(this->minLeft > 4)
        {
            this->minLeft = 1;
        }
    }
    if(headState[0] == 4)
    {
        if(this->minRight > 4)
        {
            this->minRight = 1;
        }
    }
    update();
}

