#include "login.h"
#include "ui_login.h"
#include<QFile>
#include<QPainter>
#include<QPixmap>

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    setFixedSize(800,450);
QFont font("kaiti", 13, 85);
   ui->label->setFont(font);
   ui->label_2->setFont(font);
   ui->pushButton->setFont(font);
   ui->pushButton_2->setFont(font);
    setBtnQss(ui->pushButton, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    setBtnQss(ui->pushButton_2, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    setTxtQss(ui->lineEdit, "#DCE4EC", "#34495E");
    setTxtQss(ui->lineEdit_2, "#DCE4EC", "#34495E");
    //test.show();//debug
   // my_rank.show();//debug
    my_main.my_database.queryAll();
    connect(ui->pushButton,&QPushButton::clicked,[=]{
        my_main.show();
        this->hide();
    });
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    connect(ui->pushButton_2,&QPushButton::clicked,
       [=]
    {
        a=ui->lineEdit->text();
        b=ui->lineEdit_2->text();
        if(a!=""&&b!="")
        {
            if(my_main.my_database.check(a,b))
            {
                my_begin.show();
                this->hide();
                my_begin.receive_name(a);
                my_begin.show_name();

            }
            else
            {
                ui->label_4->setText("您介密码可不对 再好好想想");
                qDebug()<<"您介密码可不对 再好好想想";
            }
        }
        else{
            ui->label_4->setText("请完整输入账号密码");
            qDebug()<<"请完整输入账号密码";
        }
    });
    connect(&my_main,&MainWindow::login_show,[=]{this->show();});
    ui->label_3->setStyleSheet("QLabel{border:2px;border-radius:"
                               "10px;padding:2px 4px;background-color:rgb(255,255,255,180);}");
}

login::~login()
{
    delete ui;
}

void login::paintEvent(QPaintEvent *event)
{
    QPainter *b=new QPainter(this);
    b->drawPixmap(0,0,width(),height(),QPixmap(":/new/image/begin_2.jpg"));
    b->drawPixmap(60,70,496,53,QPixmap(":/new/image/b2.png"));
   delete b;
}

void login::setBtnQss(QPushButton *btn, QString normalColor, QString normalTextColor, QString hoverColor, QString hoverTextColor, QString pressedColor, QString pressedTextColor)
{
    QStringList qss;

             qss.append(QString("QPushButton{border-style:none;padding:10px;border-radius:5px;color:%1;background:%2;}").arg(normalTextColor).arg(normalColor));

             qss.append(QString("QPushButton:hover{color:%1;background:%2;}").arg(hoverTextColor).arg(hoverColor));

             qss.append(QString("QPushButton:pressed{color:%1;background:%2;}").arg(pressedTextColor).arg(pressedColor));

             btn->setStyleSheet(qss.join(""));
}

void login::setTxtQss(QLineEdit *txt, QString normalColor, QString focusColor)
{

    QStringList qss;

    qss.append(QString("QLineEdit{border-style:none;padding:6px;border-radius:5px;border:2px solid %1;}").arg(normalColor));

    qss.append(QString("QLineEdit:focus{border:2px solid %1;}").arg(focusColor));

    txt->setStyleSheet(qss.join(""));
}
