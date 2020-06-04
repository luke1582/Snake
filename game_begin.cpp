#include "game_begin.h"
#include "ui_game_begin.h"
#include<QFont>
#include<QDialog>
void game_begin::setBtnQss(QPushButton *btn, QString normalColor, QString normalTextColor, QString hoverColor, QString hoverTextColor, QString pressedColor, QString pressedTextColor)
{
    QStringList qss;

             qss.append(QString("QPushButton{border-style:none;padding:10px;border-radius:5px;color:%1;background:%2;}").arg(normalTextColor).arg(normalColor));

             qss.append(QString("QPushButton:hover{color:%1;background:%2;}").arg(hoverTextColor).arg(hoverColor));

             qss.append(QString("QPushButton:pressed{color:%1;background:%2;}").arg(pressedTextColor).arg(pressedColor));

             btn->setStyleSheet(qss.join(""));
}

void game_begin::show_name()
{

    my_data.createConnection();
    pic_num=my_set.pic_num;
    skin_num=my_set.skin_num;
    QFont font("kaiti", 18, 85);
    ui->label->setFont(font);
    ui->label->setText(QString("欢迎回来 %1").arg(player_name));
    ui->label->setStyleSheet("QLabel{border:2px;border-radius:"
                             "10px;padding:2px 4px;background-color:rgb(255,255,255,180);}");
}

void game_begin::receive_name(QString a)
{
    player_name=a;
}

void game_begin::send_name()
{
    my_select.receive_name(player_name);
}

game_begin::game_begin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::game_begin)
{
    my_select.n=this->n;
    ui->setupUi(this);
    this->setFixedSize(800,450);
    QFont font("kaiti", 13, 85);
    setBtnQss(ui->pushButton, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    setBtnQss(ui->pushButton_2, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    setBtnQss(ui->pushButton_3, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    setBtnQss(ui->begin_game, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    setBtnQss(ui->pushButton_4, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    ui->pushButton->setFont(font);
    ui->pushButton_2->setFont(font);
    ui->pushButton_3->setFont(font);
    ui->begin_game->setFont(font);
    ui->pushButton_4->setFont(font);

    ui->label_2->setStyleSheet("QLabel{border:2px;border-radius:"
                               "10px;padding:2px 4px;background-color:rgb(255,255,255,180);}");


    this->setWindowTitle("贪吃蛇");
    connect(ui->begin_game,&QPushButton::clicked,[=]{
        my_select.get_pic_num(pic_num);
        my_select.get_skin_num(skin_num);
        my_select.show();
        my_select.getn(n);
        this->send_name();
        this->hide();
    });
    connect(ui->pushButton_3,&QPushButton::clicked,[=]{
        my_set.show();
        this->hide();
    });
    connect(&my_set,&setting::update_quick,[=]{
        pic_num=my_set.pic_num;
        skin_num=my_set.skin_num;
        n=my_set.n;
        this->show();

        qDebug()<<"俺老孙知道图片是："<<pic_num;
    });
    connect(&my_select,&game_select::my_slot,[=]{
       this->hide();
    });
    connect(&my_select,&game_select::main_win_show,[=]{
       this->show();
    });
    //按钮3退出的功能实现
    connect(ui->pushButton_2,&QPushButton::clicked,[=]{
        int action=QMessageBox::question(this,"贪吃蛇","你真的走啦？");
        switch (action) {
        case QMessageBox::Yes:
            close();
            break;
        case QMessageBox::No:
            break;

        }
    });
    connect(ui->pushButton,&QPushButton::clicked,[=]{
        this->hide();
        qDebug()<<player_name;
        my_rank.show();
        my_rank.get_name(player_name);
        my_rank.show_rank();

    });
    connect(&my_rank,&rank::main_win_show,[=]{
        this->show();

    });

}

game_begin::~game_begin()
{
    delete ui;
}

void game_begin::paintEvent(QPaintEvent *event)
{
    QPainter my_painter(this);
    my_painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/new/image/test_pic.jpg"));
}
void game_begin::on_pushButton_4_clicked()
{
    QDialog my_dialog;

    QPixmap pixmap(":/new/image/rule.png");
    QPixmap pix2=pixmap.scaled(400,600);
    QPalette   palette;
    palette.setBrush(my_dialog.backgroundRole(),QBrush(pix2));
    my_dialog.setPalette(palette);
    my_dialog.setAutoFillBackground(true);
    my_dialog.setFixedSize(400,600);
    my_dialog.setWindowTitle("游戏规则");

    my_dialog.exec();
}
