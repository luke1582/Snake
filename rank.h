#ifndef RANK_H
#define RANK_H

#include <QWidget>
#include"database.h"
#include<QPainter>
namespace Ui {
class rank;
}

class rank : public QWidget
{
    Q_OBJECT
signals:
    void main_win_show();
public:
    explicit rank(QWidget *parent = nullptr);
    ~rank();
    void closeEvent(QCloseEvent *event);
    void show_rank();
    QString* get_info(int mode);
    void get_name(QString cin_name);
    void paintEvent(QPaintEvent *event);
    QString kongge(QString a);
private:
    Ui::rank *ui;
    DataBase my_data;
    QString my_name;
};

#endif // RANK_H
