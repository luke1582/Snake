#include "setting.h"
#include "ui_setting.h"
#include"QDebug"
#include<QPushButton>
#include<QPixmap>
#include<QPalette>
#include<QIcon>
setting::setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);
    pic_num=1;
    skin_num=1;
    //设置背景展示橱窗
    setBtnQss(ui->pushButton, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    ui->groupBox->setStyleSheet("font: 16pt '楷体';border:2px;border-radius:"
                                "10px;padding:2px 4px;background-color:rgb(255,255,255,100)");
    ui->groupBox_2->setStyleSheet("font: 16pt '楷体';border:2px;border-radius:"
                                "10px;padding:2px 4px;background-color:rgb(255,255,255,100)");
    ui->groupBox_3->setStyleSheet("font: 16pt '楷体';border:2px;border-radius:"
                                "10px;padding:2px 4px;background-color:rgb(255,255,255,100)");
    setSliderQss(ui->horizontalSlider, "#E8EDF2", "#4E6D8C", "#34495E");
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(100);
    ui->horizontalSlider->setSingleStep(1);
    QPixmap *pixmap = new QPixmap(":/new/image/11.jpeg");
    pixmap->scaled(ui->label_2->size(), Qt::KeepAspectRatio);
    ui->label_2->setScaledContents(true);
    ui->label_2->setPixmap(*pixmap);
    QPixmap *pixmap1 = new QPixmap(":/new/image/22.png");
    pixmap1->scaled(ui->label_4->size(), Qt::KeepAspectRatio);
    ui->label_4->setScaledContents(true);
    ui->label_4->setPixmap(*pixmap1);
    QPixmap *pixmap2 = new QPixmap(":/new/image/33.png");
    pixmap2->scaled(ui->label_3->size(), Qt::KeepAspectRatio);
    ui->label_3->setScaledContents(true);
    ui->label_3->setPixmap(*pixmap2);
    QPixmap *pixmap3 = new QPixmap(":/new/image/skin_1.png");
    pixmap->scaled(ui->label_5->size(), Qt::KeepAspectRatio);
    ui->label_5->setScaledContents(true);
    ui->label_5->setPixmap(*pixmap3);
    QPixmap *pixmap4 = new QPixmap(":/new/image/skin_2.png");
    pixmap1->scaled(ui->label_6->size(), Qt::KeepAspectRatio);
    ui->label_6->setScaledContents(true);
    ui->label_6->setPixmap(*pixmap4);
    QPixmap *pixmap5 = new QPixmap(":/new/image/skin_3.png");
    pixmap2->scaled(ui->label_7->size(), Qt::KeepAspectRatio);
    ui->label_7->setScaledContents(true);
    ui->label_7->setPixmap(*pixmap5);
    connect(ui->pushButton,&QPushButton::clicked,[=]{
        this->close();
        emit update_quick();
    });


}

setting::~setting()
{
    delete ui;
}

int setting::show_pic_num()
{
    return pic_num;
}

void setting::setBtnQss(QPushButton *btn, QString normalColor, QString normalTextColor, QString hoverColor, QString hoverTextColor, QString pressedColor, QString pressedTextColor)
{
    QStringList qss;

             qss.append(QString("QPushButton{border-style:none;padding:10px;border-radius:5px;color:%1;background:%2;}").arg(normalTextColor).arg(normalColor));

             qss.append(QString("QPushButton:hover{color:%1;background:%2;}").arg(hoverTextColor).arg(hoverColor));

             qss.append(QString("QPushButton:pressed{color:%1;background:%2;}").arg(pressedTextColor).arg(pressedColor));

             btn->setStyleSheet(qss.join(""));
}

void setting::closeEvent(QCloseEvent *event)
{
    emit update_quick();
}

void setting::paintEvent(QPaintEvent *event)
{
    QPainter *m_painter=new QPainter(this);
    m_painter->drawPixmap(0,0,width(),height(),QPixmap(":/new/image/duoyongde.jpeg"));
    delete m_painter;
}

void setting::on_radioButton_clicked(bool checked)
{

    if(checked == true)
    {
        pic_num=1;
        qDebug()<<"图片是1";
    }
}

void setting::on_radioButton_2_clicked(bool checked)
{
    if(checked == true)
    {
        pic_num=2;
        qDebug()<<"图片是2";
    }
}

void setting::on_radioButton_3_clicked(bool checked)
{
    if(checked == true)
    {
        pic_num=3;
        qDebug()<<"图片是3";
    }
}



void setting::on_radioButton_4_clicked(bool checked)
{
    if(checked == true)
    {
        skin_num=1;
        qDebug()<<"皮肤是1";
    }
}

void setting::on_radioButton_5_clicked(bool checked)
{
    if(checked == true)
    {
        skin_num=2;
        qDebug()<<"皮肤是2";
    }
}

void setting::on_radioButton_6_clicked(bool checked)
{
    if(checked == true)
    {
        skin_num=3;
        qDebug()<<"皮肤是3";
    }
}


void setting::setSliderQss(QSlider *slider, QString normalColor, QString grooveColor, QString handleColor)

{

         int sliderHeight = 8;

         int sliderRadius = 4;

         int handleWidth = 13;

         int handleRadius = 6;

         int handleOffset = 3;



         QStringList qss;

         qss.append(QString("QSlider::groove:horizontal,QSlider::add-page:horizontal{height:%2px;border-radius:%3px;background:%1;}").arg(normalColor).arg(sliderHeight).arg(sliderRadius));

         qss.append(QString("QSlider::sub-page:horizontal{height:%2px;border-radius:%3px;background:%1;}").arg(grooveColor).arg(sliderHeight).arg(sliderRadius));

         qss.append(QString("QSlider::handle:horizontal{width:%2px;margin-top:-%3px;margin-bottom:-%3px;border-radius:%4px;"

                            "background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0.6 #FFFFFF,stop:0.8 %1);}")

                    .arg(handleColor).arg(handleWidth).arg(handleOffset).arg(handleRadius));

    slider->setStyleSheet(qss.join(""));

}




void setting::on_horizontalSlider_valueChanged(int value)
{
    n=ui->horizontalSlider->value();
    qDebug()<<n;
}
