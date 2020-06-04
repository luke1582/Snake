/********************************************************************************
** Form generated from reading UI file 'game_1.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_1_H
#define UI_GAME_1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_game_1
{
public:
    QLabel *current_score;
    QLabel *top_score;

    void setupUi(QWidget *game_1)
    {
        if (game_1->objectName().isEmpty())
            game_1->setObjectName(QString::fromUtf8("game_1"));
        game_1->resize(900, 600);
        current_score = new QLabel(game_1);
        current_score->setObjectName(QString::fromUtf8("current_score"));
        current_score->setGeometry(QRect(710, 50, 190, 71));
        top_score = new QLabel(game_1);
        top_score->setObjectName(QString::fromUtf8("top_score"));
        top_score->setGeometry(QRect(660, 350, 161, 161));

        retranslateUi(game_1);

        QMetaObject::connectSlotsByName(game_1);
    } // setupUi

    void retranslateUi(QWidget *game_1)
    {
        game_1->setWindowTitle(QCoreApplication::translate("game_1", "Form", nullptr));
        current_score->setText(QString());
        top_score->setText(QCoreApplication::translate("game_1", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class game_1: public Ui_game_1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_1_H
