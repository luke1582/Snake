#ifndef GAME_BEGIN_H
#define GAME_BEGIN_H
#include"database.h"
#include <QWidget>
#include"game_select.h"
#include<QDialog>
#include<QMessageBox>
#include"rank.h"
#include"setting.h"
#include<QPainter>
#include<QPixmap>
namespace Ui {
class game_begin;
}

class game_begin : public QWidget
{
    Q_OBJECT

public:
    friend class GameWidget;
    void setBtnQss(QPushButton *btn,

                   QString normalColor, QString normalTextColor,

                   QString hoverColor, QString hoverTextColor,

                   QString pressedColor, QString pressedTextColor);
    void show_name();
    void receive_name(QString a);
    void send_name();
    DataBase my_data;
    explicit game_begin(QWidget *parent = nullptr);
    ~game_begin();
    void paintEvent(QPaintEvent *event);
    int n;
private slots:
    void on_pushButton_4_clicked();

private:
    Ui::game_begin *ui;
    game_select my_select;
    QString player_name;
    rank my_rank;
    int background;
    setting my_set;
    int pic_num;
    int skin_num;

};

#endif // GAME_BEGIN_H
