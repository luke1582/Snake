/********************************************************************************
** Form generated from reading UI file 'gamewidget2.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWIDGET2_H
#define UI_GAMEWIDGET2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gamewidget2
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QWidget *gamewidget2)
    {
        if (gamewidget2->objectName().isEmpty())
            gamewidget2->setObjectName(QString::fromUtf8("gamewidget2"));
        gamewidget2->resize(400, 300);
        label = new QLabel(gamewidget2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(320, 50, 58, 16));
        label_2 = new QLabel(gamewidget2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(320, 110, 58, 16));
        label_3 = new QLabel(gamewidget2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(320, 170, 58, 16));
        label_4 = new QLabel(gamewidget2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(320, 230, 58, 16));

        retranslateUi(gamewidget2);

        QMetaObject::connectSlotsByName(gamewidget2);
    } // setupUi

    void retranslateUi(QWidget *gamewidget2)
    {
        gamewidget2->setWindowTitle(QCoreApplication::translate("gamewidget2", "Form", nullptr));
        label->setText(QCoreApplication::translate("gamewidget2", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("gamewidget2", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("gamewidget2", "TextLabel", nullptr));
        label_4->setText(QCoreApplication::translate("gamewidget2", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gamewidget2: public Ui_gamewidget2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWIDGET2_H
