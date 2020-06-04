#include "rank.h"
#include "ui_rank.h"
#include<QPainter>
#include<QPixmap>
rank::rank(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rank)
{
    my_data.createConnection();

    ui->setupUi(this);
    this->setWindowTitle("排行榜");
    ui->groupBox_3->setVisible(false);

}

rank::~rank()
{
    delete ui;
}

void rank::closeEvent(QCloseEvent *event)
{
    emit main_win_show();
}

void rank::show_rank()
{
    ui->label_2->setStyleSheet("QLabel{background-color:rgb(255,255,255,50);}");
    ui->label_3->setStyleSheet("QLabel{background-color:rgb(255,255,255,50);}");
    ui->label_4->setStyleSheet("QLabel{background-color:rgb(255,255,255,50);}");
    ui->label_5->setStyleSheet("QLabel{background-color:rgb(255,255,255,50);}");
    ui->label_6->setStyleSheet("QLabel{background-color:rgb(255,255,255,50);}");
    ui->label_9->setStyleSheet("QLabel{background-color:rgb(255,255,255,50);}");
    ui->label_10->setStyleSheet("QLabel{background-color:rgb(255,255,255,50);}");
    ui->label_11->setStyleSheet("QLabel{background-color:rgb(255,255,255,50);}");
    ui->label_12->setStyleSheet("QLabel{background-color:rgb(255,255,255,50);}");
    ui->label_13->setStyleSheet("QLabel{background-color:rgb(255,255,255,50);}");
    ui->groupBox->setStyleSheet("font: 15pt '华文细黑';border:2px;border-radius:"
                                "10px;padding:2px 4px;background-color:rgb(255,255,255,50)");
    ui->groupBox_2->setStyleSheet("font: 15pt '华文细黑';border:2px;border-radius:"
                                "10px;padding:2px 4px;background-color:rgb(255,255,255,50)");
    int *temp1=my_data.sort(1);
    QString*p1= my_data.name_sort(1);
    QFont font("kaiti", 15, 85);
    ui->label_2->setFont(font);
    ui->label_3->setFont(font);
    ui->label_4->setFont(font);
    ui->label_5->setFont(font);
    ui->label_6->setFont(font);
    ui->label_7->setFont(font);

    ui->label_2->setText(QString("1    %1").arg(p1[0])+kongge(p1[0])+QString("%1").arg(temp1[0]));
    ui->label_3->setText(QString("2    %1").arg(p1[1])+kongge(p1[1])+QString("%1").arg(temp1[1]));
    ui->label_4->setText(QString("3    %1").arg(p1[2])+kongge(p1[2])+QString("%1").arg(temp1[2]));
    ui->label_5->setText(QString("4    %1").arg(p1[3])+kongge(p1[3])+QString("%1").arg(temp1[3]));
    ui->label_6->setText(QString("5    %1").arg(p1[4])+kongge(p1[4])+QString("%1").arg(temp1[4]));
    ui->label_7->setText(QString("排名 昵称    成绩"));

    int rank_1,rank_2;
    for(int i=0;i<5;i++){
        if(p1[i]==my_name){
            rank_1=i+1;
            break;
        }
    }
    qDebug()<<my_name<<rank_1;
    switch (rank_1) {
    case 1: ui->label_2->setStyleSheet("QLabel{background-color:rgb(184,198,209);}");
        break;
    case 2: ui->label_3->setStyleSheet("QLabel{background-color:rgb(184,198,209);}");
        break;
    case 3: ui->label_4->setStyleSheet("QLabel{background-color:rgb(184,198,209);}");
        break;
    case 4: ui->label_5->setStyleSheet("QLabel{background-color:rgb(184,198,209);}");
        break;
    case 5: ui->label_6->setStyleSheet("QLabel{background-color:rgb(184,198,209);}");
        break;
    }
    int *temp2=my_data.sort(3);
    QString*p2= my_data.name_sort(3);
    ui->label_8->setFont(font);
    ui->label_9->setFont(font);
    ui->label_10->setFont(font);
    ui->label_11->setFont(font);
    ui->label_12->setFont(font);
    ui->label_13->setFont(font);
    ui->label_9->setText(QString("1    %1   %2").arg(p2[0]).arg(temp2[0]));
    ui->label_10->setText(QString("2    %1   %2").arg(p2[1]).arg(temp2[1]));
    ui->label_11->setText(QString("3    %1   %2").arg(p2[2]).arg(temp2[2]));
    ui->label_12->setText(QString("4    %1   %2").arg(p2[3]).arg(temp2[3]));
    ui->label_13->setText(QString("5    %1   %2").arg(p2[4]).arg(temp2[4]));
    ui->label_8->setText(QString("排名 昵称    成绩"));
    for(int i=0;i<5;i++){
        if(p2[i]==my_name){
            rank_2=i+1;
            break;
        }
    }
    qDebug()<<my_name<<rank_2;
    switch (rank_2) {
    case 1: ui->label_9->setStyleSheet("QLabel{background-color:rgb(184,198,209);}");
        break;
    case 2: ui->label_10->setStyleSheet("QLabel{background-color:rgb(184,198,209);}");
        break;
    case 3: ui->label_11->setStyleSheet("QLabel{background-color:rgb(184,198,209);}");
        break;
    case 4: ui->label_12->setStyleSheet("QLabel{background-color:rgb(184,198,209);}");
        break;
    case 5: ui->label_13->setStyleSheet("QLabel{background-color:rgb(184,198,209);}");
        break;
    }

}

QString* rank::get_info(int mode)
{

}

void rank::get_name(QString cin_name)
{
    my_name=cin_name;

}

void rank::paintEvent(QPaintEvent *event)
{
    QPainter *m_painter=new QPainter(this);
    m_painter->drawPixmap(0,0,width(),height(),QPixmap(":/new/image/m_rank.jpeg"));
    delete m_painter;
}

QString rank::kongge(QString a)
{

    QString temp="";
    for(int i=0;i<9-a.toLocal8Bit().length()+1;i++){
        temp+=" ";
    }
    if(a.toLocal8Bit().length()==a.length())
    {
        temp+="";
    }
    return  temp;
}
