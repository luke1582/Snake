#ifndef GAME_1_H
#define GAME_1_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include"database.h"
namespace Ui {
class game_1;
}

class game_1 : public QWidget
{
    Q_OBJECT

public:
    explicit game_1(QWidget *parent = nullptr);
    ~game_1();
    const int g_weight = 810, g_height = 600;//游戏框的宽和高
    const int  bit = 15;//基本长度单位，取决于节点大小
    const int length_first = 5;
    const int weight = g_weight / bit;//横着数有几个格子
    const int height = g_height / bit;//数着数有几个格子
    int foodx;  //食物横坐标
    int foody;  //食物纵坐标
    int flag2;//判断运动方向
    typedef struct snake
    {
        int x_snake, y_snake;
        struct snake* next = NULL;
    } SNAKE;
    SNAKE* head = NULL; //头指针
    int k = 0;//标记程序是否第一次运行
    int hour = 200;//用于控制系统暂停时间
    int basic[3] = { 1,1,1 };//记录是否更改默认设置，012分别对应背景，皮肤图标
    void creat_tool_down();//用于产生加速道具
    void creat_tool_up();//用于产生减速道具
    void create_snake();//随机创建一个初始长度为5的蛇
    void select_form();         //选择模式下同皮肤，食物和背景
    void select_pifu();
    void select_food();
    void select_background();
    void print_snake();//用于输出蛇
    void print_food(); //用于输出食物
    void print_first();//输出开始界面
    //int check1();//模式一规则,检测蛇的状态，是否撞墙或者咬到自己等等
    int check2(int* score);//模式二规则
    void create_food();//为食物赋予初值
    void create_bit();//增加头节点
    void delete_bit();//删除最后一个节点
    int FLAG1();//控制节点生成方向,并返回判断值
    int FLAG2();//控制运动方向
    void defeated();//用来输出失败后的图像
    void show();//输出
    void updatewith(int flag2);//按键更新
    void updatewithout(int flag2);//持续更新
    void eat_food();//吃到食物之后的变化
    void free_neicun();//释放链表和图像等占据的内存
    void form1();//模式一,无限模式
    void form2();//模式二,限时模式
    void print_sign(int x, int y);//显示菜单栏的小箭头
    int move_sign(int x, int y); //返回标志的纵坐标来判断回车位置
    void menu_introduction();    //输出游戏说明
    void menu();//用于输出菜单
    void menu_shezhi();          //输出设置菜单
    int break_wall();//穿墙术
    void eat_tool_up();//吃到道具之后的变化
    void eat_tool_down();//吃到减速道具后的变化
    void print_tool_up();//输出道具包
    void print_tool_down();
    void print_cebian();//侧栏显示
    void form3();//模式三，无敌模式
    void get_highscore(int* highscore);//从文件中读取最高分
    void store_highscore(int highscore);//写入新的游戏最高分
    void firstimage();//创建图片类型

    void  closeEvent(QCloseEvent *);
    void show_current();
    void receive_name(QString name);
    void keyPressEvent(QKeyEvent *event);
    void snakeMove();//蛇移动
    void playsnake();

signals:
    void exit();
private:
    Ui::game_1 *ui;
    QPainter *gamePainter;//游戏贴图
    QTimer *timerGame;//持续移动
    QTimer *timerAction;//持续动作
    DataBase my_data;
    QString player_name;
    int current_score;
    void check1();
protected:
    void paintEvent(QPaintEvent *);
};

#endif // GAME_1_H
