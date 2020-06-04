#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"game_begin.h"
#include"database.h"
#include<QDebug>
#include<QPushButton>
#include<QPainter>
#include<QPixmap>
#include<QLineEdit>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    game_begin my_begin;
    void info_insert(QString a,QString b,QString c);
    QString a,b,c;
    DataBase my_database;
    void  closeEvent(QCloseEvent *);
    void paintEvent(QPaintEvent *);
    void setBtnQss(QPushButton *btn,

                   QString normalColor, QString normalTextColor,

                   QString hoverColor, QString hoverTextColor,

                   QString pressedColor, QString pressedTextColor);
    void setTxtQss(QLineEdit *txt, QString normalColor, QString focusColor);
signals:
    void login_show();
private:
    Ui::MainWindow *ui;
    QString name;
    bool if_register,flag_register;
public:


};
#endif // MAINWINDOW_H
