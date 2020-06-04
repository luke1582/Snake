#ifndef DATABASE_H
#define DATABASE_H

#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>
#include<QSqlQueryModel>

class DataBase
{
public:
    DataBase();
public:
    bool createConnection();  //创建一个连接
    bool createTable();
    bool insert(QString a,QString b);//登录时创建
    bool queryAll();//show
    int score(int a,QString b);//返回成绩（a是模式 b是玩家名字）
    bool find(QString a);//判断库里面有没有这个人
    bool modify(int a,QString b,int c);//（修改成绩 a是模式 b是玩家名字 c是被重新赋予的值）
    int* sort(int a);
    QString* name_sort(int a);
    bool check(QString a,QString b);
    QString log(QString a,QString b);
    int num();
};

#endif // DATABASE_H
