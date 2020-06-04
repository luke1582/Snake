#include "mainwindow.h"
#include"login.h"
#include <QApplication>
#include"database.h"
#include<QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString name;

    login my_login;
    my_login.show();
    return a.exec();
}
