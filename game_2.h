#ifndef GAME_2_H
#define GAME_2_H

#include <QWidget>
#include"database.h"
namespace Ui {
class game_2;
}

class game_2 : public QWidget
{
    Q_OBJECT

public:
    explicit game_2(QWidget *parent = nullptr);
    ~game_2();
    void  closeEvent(QCloseEvent *);
    void show_current();
    void receive_name(QString a);
signals:
    void exit();
private:
    Ui::game_2 *ui;
    DataBase my_data;
    QString player_name;
};

#endif // GAME_2_H
