#include "two_sankes.h"
#include "ui_two_sankes.h"
#include<QDebug>
#include<QPixmap>
two_sankes::two_sankes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::two_sankes)
{
    ui->setupUi(this);
    if_fill=false;
    this->setWindowTitle("创建角色");
    setTxtQss(ui->lineEdit, "#DCE4EC", "#34495E");
    setTxtQss(ui->lineEdit_2, "#DCE4EC", "#34495E");
     setBtnQss(ui->pushButton, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
     setBtnQss(ui->pushButton_3, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
     setBtnQss(ui->pushButton_2, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    who_is_turn="player1";
    painter_active=true;
    QPixmap pix;
    QImage image(":/new/image/skin_1.png");//filename，图片的路径名字
    ui->label_9->setPixmap(pix.fromImage(image));// ui->pix就是label的控件名字
    ui->label_9->setScaledContents(true);
    QPixmap pix1;
    QImage image1(":/new/image/skin_2.png");//filename，图片的路径名字
    ui->label_10->setPixmap(pix1.fromImage(image1));// ui->pix就是label的控件名字
    ui->label_10->setScaledContents(true);
    QPixmap pix2;
    QImage image2(":/new/image/skin_3.png");//filename，图片的路径名字
    ui->label_11->setPixmap(pix2.fromImage(image2));// ui->pix就是label的控件名字
    ui->label_11->setScaledContents(true);
    ui->label_12->setText("<center>请玩家1设置花名并选择皮肤</center>");

}

two_sankes::~two_sankes()
{
    delete ui;
}

void two_sankes::closeEvent(QCloseEvent *event)
{
    if(if_fill){
        ui->lineEdit->setText("");
        ui->lineEdit_2->setText("");
    }
    else{
        emit back_1();
    }
}

void two_sankes::paintEvent(QPaintEvent *event)
{
    if(painter_active=true){
        QPainter *m_p=new QPainter(this);
        m_p->drawPixmap(ui->label_7->x(),ui->label_7->y(),ui->label_7->width()
                        ,ui->label_7->height(),QPixmap(QString( ":/new/image/skin_%1.png").arg(skin_1)));
        m_p->drawPixmap(ui->label_8->x(),ui->label_8->y(),ui->label_8->width()
                        ,ui->label_8->height(),QPixmap(QString( ":/new/image/skin_%1.png").arg(skin_2)));
        delete m_p;
    }
    QPainter *m_painter=new QPainter(this);
    m_painter->drawPixmap(0,0,width(),height(),QPixmap(":/new/image/duoyongde.jpeg"));
    delete m_painter;
}

int two_sankes::show_skin_1()
{
    return skin_1;
}

int two_sankes::show_skin_2()
{
    return skin_2;
}

void two_sankes::begin_this_win()
{
    who_is_turn="player1";
    painter_active=true;
    QPixmap pix;
    QImage image(":/new/image/skin_1.png");//filename，图片的路径名字
    ui->label_9->setPixmap(pix.fromImage(image));// ui->pix就是label的控件名字
    ui->label_9->setScaledContents(true);
    ui->lineEdit_2->setFocusPolicy(Qt::ClickFocus);
    QPixmap pix1;
    QImage image1(":/new/image/skin_2.png");//filename，图片的路径名字
    ui->label_10->setPixmap(pix1.fromImage(image1));// ui->pix就是label的控件名字
    ui->label_10->setScaledContents(true);
    QPixmap pix2;
    QImage image2(":/new/image/skin_3.png");//filename，图片的路径名字
    ui->label_11->setPixmap(pix2.fromImage(image2));// ui->pix就是label的控件名字
    ui->label_11->setScaledContents(true);
    ui->lineEdit->setEnabled(false);
    ui->label_12->setText("<center>请玩家1设置花名并选择皮肤</center>");
}

void two_sankes::setBtnQss(QPushButton *btn, QString normalColor, QString normalTextColor, QString hoverColor, QString hoverTextColor, QString pressedColor, QString pressedTextColor)
{
    QStringList qss;

             qss.append(QString("QPushButton{border-style:none;padding:10px;border-radius:5px;color:%1;background:%2;}").arg(normalTextColor).arg(normalColor));

             qss.append(QString("QPushButton:hover{color:%1;background:%2;}").arg(hoverTextColor).arg(hoverColor));

             qss.append(QString("QPushButton:pressed{color:%1;background:%2;}").arg(pressedTextColor).arg(pressedColor));

             btn->setStyleSheet(qss.join(""));
}

void two_sankes::up_pic()
{
    QPixmap pix3;
    QImage image3(QString( ":/new/image/skin_%1.png").arg(skin_1));//filename，图片的路径名字
    ui->label_7->setPixmap(pix3.fromImage(image3));// ui->pix就是label的控件名字
    ui->label_7->setScaledContents(true);
    QPixmap pix4;
    QImage image4(QString( ":/new/image/skin_%1.png").arg(skin_2));//filename，图片的路径名字
    ui->label_8->setPixmap(pix4.fromImage(image4));// ui->pix就是label的控件名字
    ui->label_8->setScaledContents(true);
    ui->lineEdit_2->setEnabled(true);
    //ui->lineEdit->setEnabled(false);
    //ui->label_12->setText("<center>请玩家1设置花名并选择皮肤</center>");
}

void two_sankes::setTxtQss(QLineEdit *txt, QString normalColor, QString focusColor)
{
    QStringList qss;

    qss.append(QString("QLineEdit{border-style:none;padding:6px;border-radius:5px;border:2px solid %1;}").arg(normalColor));

    qss.append(QString("QLineEdit:focus{border:2px solid %1;}").arg(focusColor));

    txt->setStyleSheet(qss.join(""));
}

void two_sankes::on_radioButton_clicked(bool checked)
{
    if(checked == true)
    {
        if(painter_active){
            if(who_is_turn=="player1"){
                skin_1=1;
                up_pic();
            }
            if(who_is_turn=="player2"){
                skin_2=1;
                up_pic();
            }
        }

    }

}

void two_sankes::on_radioButton_2_clicked(bool checked)
{
    if(checked == true)
    {
        if(painter_active){
            if(who_is_turn=="player1"){
                skin_1=2;
                up_pic();
            }
            if(who_is_turn=="player2"){
                skin_2=2;
                up_pic();
            }
        }
    }
}


void two_sankes::on_radioButton_3_clicked(bool checked)
{
    if(checked == true)
    {
        if(painter_active){
            if(who_is_turn=="player1"){
                skin_1=3;
                up_pic();
            }
            if(who_is_turn=="player2"){
                skin_2=3;
                up_pic();
            }
        }
    }
}

void two_sankes::on_pushButton_2_clicked()
{
    player_1=ui->lineEdit_2->text();
    who_is_turn="player2";
    ui->lineEdit_2->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit->setEnabled(true);
    ui->label_12->setText("<center>请玩家2设置花名并选择皮肤</center>");
    ui->lineEdit->setFocusPolicy(Qt::ClickFocus);
}

void two_sankes::on_pushButton_3_clicked()
{
    player_2=ui->lineEdit->text();
    ui->lineEdit->setFocusPolicy(Qt::NoFocus);
    painter_active=false;
    ui->label_12->setText("<center>要开始喽！摁下按钮 开始battle</center>");
    up_pic();
}

void two_sankes::on_pushButton_clicked(bool checked)
{
    if_fill=true;
    emit begin_battle();
}
