#ifndef SETTING_H
#define SETTING_H
#include<QPushButton>
#include <QWidget>
#include<QPainter>
#include<QPixmap>
#include<QSlider>
namespace Ui {
class setting;
}

class setting : public QWidget
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = nullptr);
    ~setting();
    int show_pic_num();
    void setBtnQss(QPushButton *btn,

                   QString normalColor, QString normalTextColor,

                   QString hoverColor, QString hoverTextColor,

                   QString pressedColor, QString pressedTextColor);
    void setSliderQss(QSlider *slider, QString normalColor, QString grooveColor, QString handleColor);
    int pic_num;
    int skin_num;
    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *event);
    int n;

private slots:
    void on_radioButton_clicked(bool checked);

    void on_radioButton_2_clicked(bool checked);

    void on_radioButton_3_clicked(bool checked);


    void on_radioButton_4_clicked(bool checked);

    void on_radioButton_5_clicked(bool checked);

    void on_radioButton_6_clicked(bool checked);

    void on_horizontalSlider_valueChanged(int value);

signals:
    void update_quick();
private:
    Ui::setting *ui;



};

#endif // SETTING_H
