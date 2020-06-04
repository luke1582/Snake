/********************************************************************************
** Form generated from reading UI file 'game_begin.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_BEGIN_H
#define UI_GAME_BEGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_game_begin
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *begin_game;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;

    void setupUi(QWidget *game_begin)
    {
        if (game_begin->objectName().isEmpty())
            game_begin->setObjectName(QString::fromUtf8("game_begin"));
        game_begin->resize(900, 600);
        verticalLayoutWidget = new QWidget(game_begin);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(400, 280, 77, 191));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        begin_game = new QPushButton(verticalLayoutWidget);
        begin_game->setObjectName(QString::fromUtf8("begin_game"));

        verticalLayout->addWidget(begin_game);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        label = new QLabel(game_begin);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(300, 140, 161, 91));

        retranslateUi(game_begin);

        QMetaObject::connectSlotsByName(game_begin);
    } // setupUi

    void retranslateUi(QWidget *game_begin)
    {
        game_begin->setWindowTitle(QCoreApplication::translate("game_begin", "Form", nullptr));
        begin_game->setText(QCoreApplication::translate("game_begin", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        pushButton->setText(QCoreApplication::translate("game_begin", "\346\216\222\350\241\214\346\246\234", nullptr));
        pushButton_2->setText(QCoreApplication::translate("game_begin", "\347\210\267\344\270\215\347\216\251\344\272\206", nullptr));
        label->setText(QCoreApplication::translate("game_begin", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class game_begin: public Ui_game_begin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_BEGIN_H
