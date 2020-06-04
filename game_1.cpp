#include "game_1.h"
#include "ui_game_1.h"
#include <QKeyEvent>
#include <QDateTime>
#include <QtDebug>
#include <QMessageBox>
#include <QPainter>


game_1::game_1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::game_1)
{
    ui->setupUi(this);
    this->setWindowTitle("您瞧，这不是限时模式嘛");
}

game_1::~game_1()
{
    delete ui;
}
void game_1::closeEvent(QCloseEvent *)
{
    emit exit();
}

void game_1::playsnake(){
    this->setFixedSize(1000, 600);
    qDebug() << this->width();
    //随机数种子
    qsrand(uint(QTime(0, 0, 0).secsTo(QTime::currentTime())));
    create_snake();
    create_food();

    timerGame = new QTimer(this);
    connect(timerGame, &QTimer::timeout, [=](){
        //移动
        snakeMove();
    });
    timerGame->start(300);

    //动作
}
void game_1::paintEvent(QPaintEvent *)//输出游戏背景
{
    //背景
    QPainter p(this);
    p.drawPixmap(0, 0,g_weight,600,QPixmap("../Image/默认背景.png"));
    //蛇头和蛇身
    gamePainter = new QPainter(this);
    int k = 0;
    SNAKE* temp = head;
    while (temp != nullptr)//查找蛇的每一节
    {
        if (k == 0)  //显示蛇头图片
            gamePainter->drawPixmap(temp->x_snake, temp->y_snake,QPixmap("../Image/默认蛇身.png"));
        else    //显示蛇身
            gamePainter->drawPixmap(temp->x_snake, temp->y_snake,QPixmap("../Image/默认蛇身.png"));
        k++;
        temp = temp->next;
    }
    //食物
   gamePainter->drawPixmap(foodx, foody,QPixmap("../Image/默认食物.png"));
}

void game_1::create_snake()//随机创建一个初始长度为5的蛇,开头死的问题在这里
{
    head = new SNAKE;
    //创建头节点；head是全局变量，是一个SNAKE的指针，这里分配了一个动态空间给了蛇头
    head->x_snake = bit * (qrand() % weight + 1);
    //随机出蛇头的坐标,因为画布宽是1500，bit是15，所以一共有100个格子，所以是rand()%100
    head->y_snake = bit * (qrand() % 30 + 5);
    //因为画布高是900，就是60个格子，所以我随机蛇头在5到54之间，防止蛇尾越底和开头死
    SNAKE* pnew, * ptail = head;
    for (int i = 1; i < length_first; i++)//创建新节点，并使其相连
    {
        pnew = new SNAKE;//创建一个新蛇身结点
        ptail->next = pnew;//将新结点和前一个结点相连
        pnew->x_snake = ptail->x_snake;//这两步将新结点对应的位置设置为前一个结点的下面
        pnew->y_snake = ptail->y_snake + bit;//y值多一位
        ptail = pnew;//定位蛇尾在新结点
    }
    ptail->next = nullptr;
}

//删除了设置皮肤和食物和游戏背景的代码
void game_1::snakeMove(){
    updatewithout(flag2);
    eat_food();
    check1();

}

void game_1::check1()//模式一规则,检测蛇的状态，是否撞墙或者咬到自己等等
{
    if (head->x_snake <= 0 || head->y_snake <= 0)
    {
        timerGame->stop();
        timerAction->stop();
        return ;
    }
    if (head->y_snake >= g_height){
        timerGame->stop();
        timerAction->stop();
        return ;
    }
    if (head->x_snake >= g_weight)
    {
        timerGame->stop();
        timerAction->stop();
        return ;
    }
    SNAKE* temp = head;
    while (temp->next != nullptr)//判断是否咬到自己，若咬到则返回0，游戏失败
    {
        temp = temp->next;
        if (head->x_snake == temp->x_snake && head->y_snake == temp->y_snake)
            timerGame->stop();
            timerAction->stop();
            return ;
    }
   update();
}


void game_1::create_food()//为食物赋予初值；这样函数嵌套会不会不太好？？
{
    SNAKE* temp = head;    //将蛇的头结点所指赋值给temp
    foodx= bit * (qrand() % weight + 1);
    foody = bit * (qrand()% height + 1);
    while (temp->next != nullptr) //条件测试 ：如果生成的食物位置在蛇身上，则重新生成食物
    {
        if (temp->x_snake == foodx&& temp->y_snake == foody)
        {
            create_food();
            break;
        }
        else
            temp = temp->next;
    }
}

void game_1::create_bit()//增加新头节点
{
    SNAKE* temp;
    temp = (SNAKE*)malloc(sizeof(SNAKE));
    temp->next = head;
    head = temp;
}

void game_1::delete_bit()//删除最后一个节点
{
    SNAKE* temp = head;
    while (temp->next->next != nullptr)
    {
        temp = temp->next;
    }
    delete(temp->next);
    temp->next =nullptr;
}

int game_1::FLAG1()//控制节点生成方向
{
    int flag1;
    SNAKE* temp = head;
    while ((temp->next)->next != nullptr)    //将temp指向倒数第二个结点，来判断从那个方向加一个尾接点
        temp = temp->next;
    if (temp->y_snake == temp->next->y_snake + bit)
        flag1 = 1; //向上加节点
    else if (temp->y_snake == temp->next->y_snake - bit)
        flag1 = 2;//向下加节点
    else if (temp->x_snake == temp->next->x_snake + bit)
        flag1 = 3;//向左加节点
    else if (temp->x_snake == temp->next->x_snake - bit)
        flag1 = 4;//向右加节点
    return flag1;
}

int game_1::FLAG2()//判断当前运动方向
{
    SNAKE *temp = head;
    if (temp->y_snake == temp->next->y_snake - bit)
        flag2 = 1; //向上
    else if (temp->y_snake == temp->next->y_snake + bit)
        flag2 = 2;//向下
    else if (temp->x_snake == temp->next->x_snake - bit)
        flag2 = 3;//向左
    else if (temp->x_snake == temp->next->x_snake + bit)
        flag2 = 4;//向右
    return flag2;
}


void game_1::keyPressEvent(QKeyEvent *event)//按键更新
{
        char stir;
        stir = event->key();
        if (stir == 'w' && flag2 == 2)     //一下四条判断语句是为了防止按键方向和当前运动方向反向
            return;
        else if (stir == 'w' && flag2 == 1)   //防止因为多次按键造成的加速问题
            return;
        else if (stir == 's' && flag2 == 1)
            return;
        else if (stir == 's' && flag2 == 2)
            return;
        else if (stir == 'a' && flag2 == 4)
            return;
        else if (stir == 'a' && flag2 == 3)
            return;
        else if (stir == 'd' && flag2 == 3)
            return;
        else if (stir == 'd' && flag2 == 4)
            return;
        if (stir == 'w')//根据按键为新生成节点赋值
        {
            create_bit();
            delete_bit();
            head->x_snake = head->next->x_snake;
            head->y_snake = head->next->y_snake - bit;
        }
        else if (stir == 'a')
        {
            create_bit();
            delete_bit();
            head->x_snake = head->next->x_snake - bit;
            head->y_snake = head->next->y_snake;
        }
        else if (stir == 's')
        {
            create_bit();
            delete_bit();
            head->x_snake = head->next->x_snake;
            head->y_snake = head->next->y_snake + bit;
        }
        else if (stir == 'd')
        {
            create_bit();
            delete_bit();
            head->x_snake = head->next->x_snake + bit;
            head->y_snake = head->next->y_snake;
        }
        else return;
    update();
    return;
}

void game_1::updatewithout(int flag2)//持续更新
{
    create_bit();
    delete_bit();
    //为新生成节点赋值
    if (flag2 == 1) //上
    {
        head->x_snake = head->next->x_snake;
        head->y_snake = head->next->y_snake - bit;
    }
    else if (flag2 == 2) //下
    {
        head->y_snake = head->next->y_snake + bit;
        head->x_snake = head->next->x_snake;
    }
    else if (flag2 == 3) //左
    {
        head->x_snake = head->next->x_snake - bit;
        head->y_snake = head->next->y_snake;
    }
    else if (flag2 == 4) //右
    {
        head->y_snake = (head->next)->y_snake;
        head->x_snake = (head->next)->x_snake + bit;
    }
}

void game_1::eat_food()//吃到食物之后的变化
{
    int flag1;
    flag1 = FLAG1();
    SNAKE* pnew, * temp;
    temp = head;
    pnew = (SNAKE*)malloc(sizeof(SNAKE));//生成新节点并使其连接在末尾
    while (temp->next !=nullptr)
    {
        temp = temp->next;
    }
    temp->next = pnew;
    pnew->next = nullptr;//使新节点成为尾节点
    //为新节点赋值
    if (flag1 == 3) //上
    {
        pnew->x_snake = temp->x_snake - bit;
        pnew->y_snake = temp->y_snake;
    }
    if (flag1 == 4) //下
    {
        pnew->x_snake = temp->x_snake + bit;
        pnew->y_snake = temp->y_snake;
    }
    if (flag1 == 2) //右
    {
        pnew->x_snake = temp->x_snake;
        pnew->y_snake = temp->y_snake + bit;
    }
    if (flag1 == 1) //左
    {
        pnew->x_snake = temp->x_snake;
        pnew->y_snake = temp->y_snake - bit;
    }
    create_food();
    return ;
}

void game_1::free_neicun()//释放链表和图像等占据的内存
{
    SNAKE* temp = head;
    while (head != nullptr)
    {
        temp = head;
        head = head->next;
        delete(temp);
        temp = nullptr;
    }//从链表首到链表尾依次释放动态数据结构所占据的内存
    return;
}
void game_1::show_current()
{
    my_data.createConnection();
    ui->current_score->setText(QString("%1,您好！ \n限时模式您历史最高分是%2").arg(player_name).arg(my_data.score(1,player_name)));
}

void game_1::receive_name(QString a)
{
    player_name=a;
}




//删除form2&3

//删除加减速道具


//删除玩家对界面的操作



//删除菜单和模式




//删除穿墙术

//删除加减速

//删除固定位置输出侧边栏


