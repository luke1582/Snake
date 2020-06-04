#include "gamewidget2.h"
#include "ui_gamewidget2.h"
#include <QKeyEvent>
#include <QTime>
#include <QtDebug>
#include <QMessageBox>

static int sec = 0;
gamewidget2::gamewidget2(QWidget *parent) : QWidget(parent),
  ui(new Ui::gamewidget2)
{
  ui->setupUi(this);
}
void gamewidget2::timebegin()
{
    timerid = this->startTimer(1000);
}

/*void GameWidget::timeclose(){
    if(sec==60)
    {
        flag_timeout=true;
        if(score>my_data.score(1,player_name)){
            my_data.modify(1,player_name,score);
        }
        this->close();
        w.set_current_score(score);//传成绩
        w.set_player_name(player_name);//传姓名
        w.see();
        w.show();
        timerGame->stop();
        timerAction->stop();
         this->killTimer(this->timerid);

    }

}
*/
void gamewidget2::play()
{
    my_data.createConnection();
    flag_timeout=false;
    sec=0;

  this->setFixedSize(800, 450);
  this->setWindowTitle("您瞧，这不是无限模式嘛？");

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

}

void gamewidget2::get_player_name(QString in_name)
{
    player_name=in_name;
}

void gamewidget2::timerEvent(QTimerEvent *)
{

    //static int sec = 0;
    QFont font("Microsoft YaHei",10,75);
    ui->label->setFont(font);

    ui->label->setText(
                QString("<center>游戏剩余时间:%1秒</center>").arg(60-sec)
                );
    sec=sec+1;
    if(sec==60)
    {
        timerGame->stop();
        timerAction->stop();
        this->killTimer(this->timerid);//根据计时器的id关闭计时器（id起到区分多个定时器的作用，将开始与结束连起来

        QFont font("Adobe Caslon Pro Bold",15,75);
        ui->label->setFont(font);
        ui->label->setText("<center>Game Begin！！</center>");
        flag_timeout=true;
        if(score>my_data.score(1,player_name)){
            my_data.modify(1,player_name,score);
        }
        this->close();
        w.set_current_score(score);//传成绩
        w.set_player_name(player_name);//传姓名
        w.see();
        w.show();
        timerGame->stop();
        timerAction->stop();
         this->killTimer(this->timerid);
    }
}

void gamewidget2::paintEvent(QPaintEvent *)
{
    //背景
    QPainter groundPainter(this);
    groundPainter.fillRect(0, 0, 600, 450, QBrush(QColor(0, 0, 255, 100)));

    //动次打次（吃吃吃）
    QString snakeUp = QString(":/new/image/headup%1.png").arg(this->minUp++);
    QString snakeDown = QString(":/new/image/headdown%1.png").arg(this->minDown++);
    QString snakeLeft = QString(":/new/image/headleft%1.png").arg(this->minLeft++);
    QString snakeRight = QString(":/new/image/headright%1.png").arg(this->minRight++);
    //蛇头
    gamePainter = new QPainter(this);
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
    //食物
    gamePainter->drawPixmap(foodX, foodY, 25, 25, QPixmap(":/new/image/food.png"));

    delete gamePainter;
}

gamewidget2::~gamewidget2()
{
    delete ui;
}

void gamewidget2::keyPressEvent(QKeyEvent *event)
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

void gamewidget2::snakeMove()
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
            int flag = 1;
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
            if(flag == 1)
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
        if(headX[0] == headX[i] && headY[0] == headY[i])
        {
          /*
           timerGame->stop();
           timerAction->stop();
            isKey = false;
            QString gameDied = QString("啪叽!你死了,你的长度是%1").arg(bodyLen);
            //QMessageBox overGame(QMessageBox::Warning, "结束游戏", gameDied, QMessageBox::Yes | QMessageBox::No);
             int overSelect = QMessageBox::warning(this, "结束游戏", gameDied, tr("重新开始"), tr("离开游戏"));
         */
            //重新开始
          /*if (overSelect == 0) {
                isKey = true;
                //初始化蛇
                direction = 4;
                headX[0] = 75;
                headY[0] = 200;
                headState[0] = 4;
                bodyLen = 3;
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
                    foodX = (qrand() % 24) *25;
                    foodY = (qrand() % 18) *25;
                    for (int i = 1; i < bodyLen; i++)
                    {
                        if(headX[0] == foodX && headY[i] == foodY)
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
                timerGame->start();
                timerAction->start();
            }

            //结束游戏
            if (overSelect == 1)
            {
                emit gameClose();
            }
            return;
        }
        */
          score=score-(bodyLen-i);
          bodyLen=i;

        }

     }

    update();
}

void gamewidget2::closeEvent(QCloseEvent *e)
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
void gamewidget2::snakeAction()
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

