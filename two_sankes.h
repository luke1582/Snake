#ifndef TWO_SANKES_H
#define TWO_SANKES_H

#include <QWidget>
#include<QPainter>
#include<QPixmap>
#include<QPushButton>
#include<QLineEdit>
namespace Ui {
class two_sankes;
}

class two_sankes : public QWidget
{
    Q_OBJECT

public:
    explicit two_sankes(QWidget *parent = nullptr);
    ~two_sankes();
     QString player_1,player_2;
     void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *event);
    int show_skin_1();
    int show_skin_2();
    void begin_this_win();

    void setBtnQss(QPushButton *btn,

                   QString normalColor, QString normalTextColor,

                   QString hoverColor, QString hoverTextColor,

                   QString pressedColor, QString pressedTextColor);
    void up_pic();
    void setTxtQss(QLineEdit *txt, QString normalColor, QString focusColor);
signals:
    void begin_battle();
    void back_1();
private slots:
    void on_radioButton_clicked(bool checked);

    void on_radioButton_2_clicked(bool checked);

    void on_radioButton_3_clicked(bool checked);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked(bool checked);

private:
    Ui::two_sankes *ui;
    int skin_1,skin_2;
    bool painter_active;
    QString who_is_turn;
    bool if_fill;

};

#endif // TWO_SANKES_H
