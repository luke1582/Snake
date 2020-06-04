/********************************************************************************
** Form generated from reading UI file 'gamewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWIDGET_H
#define UI_GAMEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gamewidget
{
public:
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *gamewidget)
    {
        if (gamewidget->objectName().isEmpty())
            gamewidget->setObjectName(QString::fromUtf8("gamewidget"));
        gamewidget->resize(800, 454);
        label = new QLabel(gamewidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(600, 30, 201, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("Adobe Caslon Pro Bold"));
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label_2 = new QLabel(gamewidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(600, 120, 201, 41));

        retranslateUi(gamewidget);

        QMetaObject::connectSlotsByName(gamewidget);
    } // setupUi

    void retranslateUi(QWidget *gamewidget)
    {
        gamewidget->setWindowTitle(QCoreApplication::translate("gamewidget", "Form", nullptr));
        label->setText(QCoreApplication::translate("gamewidget", "  Game Begin!!", nullptr));
        label_2->setText(QCoreApplication::translate("gamewidget", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gamewidget: public Ui_gamewidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWIDGET_H
