#ifndef GAME_3_H
#define GAME_3_H

#include <QWidget>
#include"database.h"
namespace Ui {
class game_3;
}

class game_3 : public QWidget
{
    Q_OBJECT

public:
    explicit game_3(QWidget *parent = nullptr);
    ~game_3();
    void  closeEvent(QCloseEvent *);
    void show_current();
    void receive_name(QString a);
signals:
    void exit();
private:
    Ui::game_3 *ui;
    DataBase my_data;
    QString player_name;
};

#endif // GAME_3_H
