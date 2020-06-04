#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //初始化
    ui->setupUi(this);
    if_register=false;
    flag_register=true;
    //注册
    my_database.createConnection();

    my_database.createTable();   //之前注释掉了
    setWindowTitle("注册");
    setTxtQss(ui->lineEdit, "#DCE4EC", "#34495E");
    setTxtQss(ui->lineEdit_name, "#DCE4EC", "#34495E");
    setTxtQss(ui->lineEdit_password, "#DCE4EC", "#34495E");
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    ui->label->setStyleSheet("QLabel{border:2px;border-radius:"
        "10px;padding:2px 4px;background-color:rgb(255,255,255,150);}");
    ui->label_2->setStyleSheet("QLabel{border:2px;border-radius:"
                               "10px;padding:2px 4px;background-color:rgb(255,255,255,150);}");
    ui->label_3->setStyleSheet("QLabel{border:2px;border-radius:"
                               "10px;padding:2px 4px;background-color:rgb(255,255,255,150);}");
    ui->label_5->setStyleSheet("QLabel{background-color:rgb(255,255,255,150);}");
    ui->label_5->setFont(QFont("等线",13));
    QFont font("等线",18,65);
    ui->label->setFont(font);
    ui->label_2->setFont(font);
    ui->label_3->setFont(font);
    connect(ui->register_2,&QPushButton::clicked,[=]{
       a=ui->lineEdit_name->text();
       b=ui->lineEdit_password->text();
        c=ui->lineEdit->text();
       info_insert(a,b,c);
       });
    //my_begin.show();
    setBtnQss(ui->register_2, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::info_insert(QString a, QString b, QString c)
{
    QPalette pe;
        pe.setColor(QPalette::WindowText,Qt::red);
        ui->label_4->setPalette(pe);
    if(a!=""&&b!=""&&c!=""){
       if(b==c){
           if(my_database.find(a)){
                ui->label_4->setText("用户名重复");
               qDebug()<<"重了";
           }
           else{
               if(a.length()<4&&a.toLocal8Bit().length()<8){
                   my_database.insert(a,b);
                   my_database.queryAll();
                   this->close();
                   emit login_show();
               }
               else{
                   ui->label_4->setText("不是跟您说了 昵称不能超过4个汉字嘛！");
               }
           }
       }
        else{

            ui->label_4->setText("您了两次输得可不一样,重新来");
           qDebug()<<"您了两次输得可不一样";
       }
    }
    else{
        ui->label_4->setText("请输入完整的账号和密码");
        qDebug()<<"请输入完整的账号和密码";
    }

}

void MainWindow::closeEvent(QCloseEvent *)
{
    emit login_show();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter *m_painter=new QPainter(this);
    m_painter->drawPixmap(0,0,width(),height(),QPixmap(":/new/image/login.jpg"));
    delete m_painter;
}

void MainWindow::setBtnQss(QPushButton *btn, QString normalColor, QString normalTextColor, QString hoverColor, QString hoverTextColor, QString pressedColor, QString pressedTextColor)
{

    QStringList qss;

             qss.append(QString("QPushButton{border-style:none;padding:10px;border-radius:5px;color:%1;background:%2;}").arg(normalTextColor).arg(normalColor));

             qss.append(QString("QPushButton:hover{color:%1;background:%2;}").arg(hoverTextColor).arg(hoverColor));

             qss.append(QString("QPushButton:pressed{color:%1;background:%2;}").arg(pressedTextColor).arg(pressedColor));

             btn->setStyleSheet(qss.join(""));
}

void MainWindow::setTxtQss(QLineEdit *txt, QString normalColor, QString focusColor)
{
    QStringList qss;

    qss.append(QString("QLineEdit{border-style:none;padding:6px;border-radius:5px;border:2px solid %1;}").arg(normalColor));

    qss.append(QString("QLineEdit:focus{border:2px solid %1;}").arg(focusColor));

    txt->setStyleSheet(qss.join(""));
}

