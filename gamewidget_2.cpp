#include "gamewidget_2.h"
#include "ui_gamewidget_2.h"
#include <QKeyEvent>
#include <QTime>
#include <QtDebug>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QMediaPlaylist>

//static int sec = 0;
gamewidget_2::gamewidget_2(QWidget *parent) : QWidget(parent),
  ui(new Ui::gamewidget_2)
{
  ui->setupUi(this);
  pic_num=1;
  skin_num=3;
}
/*
void gamewidget_2::timebegin()
{
    timerid = this->startTimer(1000);
}
*/
void gamewidget_2::play()
{
    gameSound= new QMediaPlayer(this);
    gameList= new QMediaPlaylist(this);
    gameList->addMedia(QUrl("qrc:/new/image/music.wav"));//添加音乐
    gameList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);//循环播放
    gameSound->setMedia(gameList);
    gameSound->setVolume(n);
    gameSound->play();


    if_die=false;
    my_data.createConnection();
    flag_timeout=false;
   // sec=0;

  this->setFixedSize(800, 450);
  this->setWindowTitle("您瞧，这不是无限模式嘛？");

    qDebug() << this->width();
    //随机数种子
    qsrand(uint(QTime(0, 0, 0).secsTo(QTime::currentTime())));

    isKey = true;
    //初始化蛇
    direction = 4;
    headX[0] =(qrand() % 24)*25;    //随机生成向右的蛇
    while(headX[0]<125||headX[0]>500)//防止生成即撞墙
       {headX[0] =(qrand() % 24)*25;}
    headY[0] =(qrand() % 18) *25;
    while(headY[0]<50||headY[0]>400)//防止生成即撞墙
       {headY[0] =(qrand() % 24)*25;}
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
        int flag = 1,flag1=1;
        foodX = (qrand() % 24) *25;    //
        foodY = (qrand() % 18) *25;
        for (int i = 0; i < bodyLen; i++)
        {
            //防止食物生成到蛇上
            if(headX[i] == foodX && headY[i] == foodY)
            {
                flag = 0;
                break;
            }

        }
        //防止食物生成在边界墙上
        for(int j=0;j<18;j++){
            if(foodX==0&& foodY == j*25)
          {
            flag1= 0;
            break;
          }
       }
        for(int j=0;j<18;j++){
            if(foodX ==575&& foodY == j*25)
          {
            flag1 = 0;
            break;
          }
       }
        for(int j=0;j<24;j++){
            if(foodX==j*25&& foodY == 0)
          {
            flag1 = 0;
            break;
          }
       }
        for(int j=0;j<24;j++){
            if(foodX ==j*25&& foodY == 425)
          {
            flag1 = 0;
            break;
          }
       }
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
                    QString("<center>当前成绩为:%1</center>").arg(score)
                    );
        QFont font_1("Microsoft YaHei",10,75);
        ui->label_3->setFont(font_1);

        ui->label_3->setText(
                    QString("<center>您最好成绩是:%1</center>").arg(my_data.score(3,player_name))
                    );
        ui->label_4->setFont(font_1);
        int*p=my_data.sort(3);
        ui->label_4->setText(
                    QString("<center>历史最高:%1</center>").arg(p[0])
                    );
    });
    //建墙
    creatwall();
    wall=new QTimer(this);
    wall->start(10000);
    connect(wall,&QTimer::timeout,[=]{
        creatwall();
    });
    //
    timerAction->start(75);
    connect(&w,&endgame::close_end_win,[=]{
        emit game_exit();
    });

}

//生成墙
void gamewidget_2::creatwall(){
    while(1)
    {
        int flag1 = 1,flag2=1,flag3=1;
        int x=qrand() % 2;
        //随机生成横着或者竖着的墙
        if(x==1){
        wallX[0] =(qrand() % 24)*25;    //随机生成向右的蛇
        while(wallX[0]<200||wallX[0]>400)
           {wallX[0] =(qrand() % 24)*25;}
        wallY[0] =(qrand() % 18) *25;
        for (int i = 1; i < 8; i++)
        {
            wallX[i] = wallX[i - 1] - 25;
            wallY[i] = wallY[i - 1];

        }
        }
        if(x==0){
            wallY[0] =(qrand() % 18) *25;
            while (wallY[0]<200||wallY[0]>250) {
                wallY[0] =(qrand() % 18) *25;
            }
            wallX[0] =(qrand() % 24)*25;
            for (int i = 1; i < 8; i++)
            {
                wallY[i] = wallY[i - 1] - 25;
                wallX[i] = wallX[i - 1];

            }
        }


        //防止墙和边界重叠
        for(int i=0;i<8;i++){
            for(int j=0;j<18;j++){
                if(wallX[i] ==0&& wallY[i] == j*25)
              {
                flag2 = 0;
                break;
              }
           }
            for(int j=0;j<18;j++){
                if(wallX[i] ==575&& wallY[i] == j*25)
              {
                flag2 = 0;
                break;
              }
           }
            for(int j=0;j<24;j++){
                if(wallX[i] ==j*25&& wallY[i] == 0)
              {
                flag2 = 0;
                break;
              }
           }
            for(int j=0;j<24;j++){
                if(wallX[i] ==j*25&& wallY[i] == 425)
              {
                flag2 = 0;
                break;
              }
           }
        }
        //防止食物重叠
        for (int i = 0; i < 8; i++)
        {
            if(wallX[i] == foodX && wallY[i] == foodY)
            {
                flag1 = 0;
                break;
            }

        }
        //防止蛇身重叠
        for (int i = 0; i < 8; i++){
            for(int j=0;j<bodyLen;j++){
                if(wallX[i] ==headX[j]&& wallY[i] == headY[j])
              {
                flag2 = 0;
                break;
              }
           }
        }
        if(flag1 == 1&&flag2==1&&flag3==1)
        {
            break;
        }
    }
}

void gamewidget_2::get_pic_num(int cin_pic_num)
{
    pic_num=cin_pic_num;
}

void gamewidget_2::get_skin_num(int cin_skin_num)
{
    skin_num=cin_skin_num;
}

void gamewidget_2::getn(int m)
{
    n=m;
}

void gamewidget_2::get_player_name(QString in_name)
{
    player_name=in_name;
}


void gamewidget_2::paintEvent(QPaintEvent *)
{
    //背景
    QPainter groundPainter(this);
    qDebug()<<"图片是"<<pic_num;
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
    //画墙
    QPainter wallpainter(this);
    for(int i=0;i<8;i++){
        wallpainter.drawPixmap(wallX[i], wallY[i], 25, 25, QPixmap(":/new/image/wall.jpg"));
    }
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

gamewidget_2::~gamewidget_2()
{
    delete ui;
}

void gamewidget_2::keyPressEvent(QKeyEvent *event)
{
    //1上  2下  3左  4右
    //1上，2下，3左，4右，5上左，6上右，7左上，8右上，9左下，10右下，11下左，12下右
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

void gamewidget_2::snakeMove()
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


    //吃的判定
    if(headX[0] == foodX && headY[0] == foodY)
    {
        while(1)
        {
            int flag = 1,flag1=1,flag2=1;
            foodX = (qrand() % 24) *25;      //重新生成食物
            foodY = (qrand() % 18) *25;
            //防止生成到蛇上
            for (int i = 0; i < bodyLen; i++)
            {
                if(headX[i] == foodX && headY[i] == foodY)
                {
                    flag = 0;
                    break;
                }
            }
            //防止生成在边界的墙上
            for(int j=0;j<18;j++){
                if(foodX==0&& foodY == j*25)
              {
                flag1= 0;
                break;
              }
           }
            for(int j=0;j<18;j++){
                if(foodX ==575&& foodY == j*25)
              {
                flag1 = 0;
                break;
              }
           }
            for(int j=0;j<24;j++){
                if(foodX==j*25&& foodY == 0)
              {
                flag1 = 0;
                break;
              }
           }
            for(int j=0;j<24;j++){
                if(foodX ==j*25&& foodY == 425)
              {
                flag1 = 0;
                break;
              }
           }
            for (int i = 0; i < 8; i++)
            {
                if(wallX[i] == foodX && wallY[i] == foodY)
                {
                    flag2 = 0;
                    break;
                }

            }
            if(flag == 1 && flag1==1&&flag2==1)
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


    //死亡判定
    for(int i = 1; i < bodyLen; i++)
    {
        if(headX[0] == headX[i] && headY[0] == headY[i]||(headX[0]==0||headX[0]==575||headY[0]==0||headY[0]==425))
        {

           timerGame->stop();
           timerAction->stop();
            isKey = false;
            if_die=true;
            //this->killTimer(this->timerid);//根据计时器的id关闭计时器（id起到区分多个定时器的作用，将开始与结束连起来

            QFont font("Adobe Caslon Pro Bold",15,75);
            ui->label->setFont(font);
            ui->label->setText("<center>Game Begin！！</center>");
            flag_timeout=true;
            if(score>my_data.score(3,player_name))
            {
                my_data.modify(3,player_name,score);
            }
            this->close();
            gameSound->stop();
            w.set_current_score(score);//传成绩
            w.set_player_name(player_name);//传姓名
            w.get_mode(3);
            w.see();
            w.show();
            timerGame->stop();
            timerAction->stop();
            wall->stop();
             //this->killTimer(this->timerid);
           }
     }
    for(int i = 0; i < 8; i++)
    {
        if(headX[0] == wallX[i] && headY[0] == wallY[i])
        {
            if_die=true;
           timerGame->stop();
           timerAction->stop();
            isKey = false;
            //this->killTimer(this->timerid);//根据计时器的id关闭计时器（id起到区分多个定时器的作用，将开始与结束连起来

            QFont font("Adobe Caslon Pro Bold",15,75);
            ui->label->setFont(font);
            ui->label->setText("<center>Game Begin！！</center>");
            flag_timeout=true;
            if(score>my_data.score(3,player_name))
            {
                my_data.modify(3,player_name,score);
            }
            this->close();
             gameSound->stop();
            w.set_current_score(score);//传成绩
            w.set_player_name(player_name);//传姓名
            w.get_mode(3);
            w.see();
            w.show();
            timerGame->stop();
            timerAction->stop();
            wall->stop();
             //this->killTimer(this->timerid);
           }
    }

}


void gamewidget_2::closeEvent(QCloseEvent *e)
{
    if(!if_die){
        timerGame->stop();
        timerAction->stop();
        wall->stop();
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
            wall->start();
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
void gamewidget_2::snakeAction()
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

