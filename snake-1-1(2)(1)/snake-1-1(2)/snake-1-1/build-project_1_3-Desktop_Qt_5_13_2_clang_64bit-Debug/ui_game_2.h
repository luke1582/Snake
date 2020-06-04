/********************************************************************************
** Form generated from reading UI file 'game_2.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_2_H
#define UI_GAME_2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_game_2
{
public:
    QLabel *top_score;
    QLabel *current_score;

    void setupUi(QWidget *game_2)
    {
        if (game_2->objectName().isEmpty())
            game_2->setObjectName(QString::fromUtf8("game_2"));
        game_2->resize(900, 600);
        top_score = new QLabel(game_2);
        top_score->setObjectName(QString::fromUtf8("top_score"));
        top_score->setGeometry(QRect(730, 400, 161, 161));
        current_score = new QLabel(game_2);
        current_score->setObjectName(QString::fromUtf8("current_score"));
        current_score->setGeometry(QRect(710, 220, 190, 71));

        retranslateUi(game_2);

        QMetaObject::connectSlotsByName(game_2);
    } // setupUi

    void retranslateUi(QWidget *game_2)
    {
        game_2->setWindowTitle(QCoreApplication::translate("game_2", "Form", nullptr));
        top_score->setText(QCoreApplication::translate("game_2", "TextLabel", nullptr));
        current_score->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class game_2: public Ui_game_2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_2_H
