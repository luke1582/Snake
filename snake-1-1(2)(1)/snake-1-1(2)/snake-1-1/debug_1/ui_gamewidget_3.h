/********************************************************************************
** Form generated from reading UI file 'gamewidget_3.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWIDGET_3_H
#define UI_GAMEWIDGET_3_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gamewidget_3
{
public:
    QLabel *label;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *gamewidget_3)
    {
        if (gamewidget_3->objectName().isEmpty())
            gamewidget_3->setObjectName(QString::fromUtf8("gamewidget_3"));
        gamewidget_3->resize(800, 454);
        label = new QLabel(gamewidget_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(590, 0, 211, 71));
        label_6 = new QLabel(gamewidget_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(610, 320, 51, 51));
        label_7 = new QLabel(gamewidget_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(610, 130, 51, 51));
        label_4 = new QLabel(gamewidget_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(660, 320, 141, 51));
        label_5 = new QLabel(gamewidget_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(610, 390, 191, 51));
        label_2 = new QLabel(gamewidget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(660, 130, 141, 51));
        label_3 = new QLabel(gamewidget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(610, 200, 191, 51));

        retranslateUi(gamewidget_3);

        QMetaObject::connectSlotsByName(gamewidget_3);
    } // setupUi

    void retranslateUi(QWidget *gamewidget_3)
    {
        gamewidget_3->setWindowTitle(QCoreApplication::translate("gamewidget_3", "Form", nullptr));
        label->setText(QCoreApplication::translate("gamewidget_3", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:600;\">Game Begin!!</span></p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("gamewidget_3", "<html><head/><body><p align=\"center\"><img src=\":/new/image/headright24.png\"/></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("gamewidget_3", "<html><head/><body><p align=\"center\"><img src=\":/new/image/headright4.png\"/></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("gamewidget_3", "<html><head/><body><p>TextLabel</p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("gamewidget_3", "<html><head/><body><p align=\"center\">TextLabel</p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("gamewidget_3", "<html><head/><body><p>TextLabel</p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("gamewidget_3", "<html><head/><body><p align=\"center\">TextLabel</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gamewidget_3: public Ui_gamewidget_3 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWIDGET_3_H
