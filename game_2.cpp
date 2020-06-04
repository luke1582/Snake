#include "game_2.h"
#include "ui_game_2.h"

game_2::game_2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::game_2)
{
    ui->setupUi(this);
}

game_2::~game_2()
{
    delete ui;
}
void game_2::closeEvent(QCloseEvent *)
{
    emit exit();
}
void game_2::show_current()
{
    my_data.createConnection();
    ui->current_score->setText(QString("%1,您好！ \n限时模式您历史最高分是%2").arg(player_name).arg(my_data.score(2,player_name)));
}

void game_2::receive_name(QString a)
{
    player_name=a;
}
