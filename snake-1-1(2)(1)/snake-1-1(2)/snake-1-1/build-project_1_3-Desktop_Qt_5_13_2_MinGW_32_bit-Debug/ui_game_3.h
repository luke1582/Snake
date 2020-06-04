/********************************************************************************
** Form generated from reading UI file 'game_3.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_3_H
#define UI_GAME_3_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_game_3
{
public:
    QLabel *current_score;
    QLabel *top_score;

    void setupUi(QWidget *game_3)
    {
        if (game_3->objectName().isEmpty())
            game_3->setObjectName(QString::fromUtf8("game_3"));
        game_3->resize(900, 600);
        current_score = new QLabel(game_3);
        current_score->setObjectName(QString::fromUtf8("current_score"));
        current_score->setGeometry(QRect(640, 110, 190, 71));
        top_score = new QLabel(game_3);
        top_score->setObjectName(QString::fromUtf8("top_score"));
        top_score->setGeometry(QRect(670, 260, 161, 161));

        retranslateUi(game_3);

        QMetaObject::connectSlotsByName(game_3);
    } // setupUi

    void retranslateUi(QWidget *game_3)
    {
        game_3->setWindowTitle(QCoreApplication::translate("game_3", "Form", nullptr));
        current_score->setText(QString());
        top_score->setText(QCoreApplication::translate("game_3", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class game_3: public Ui_game_3 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_3_H
