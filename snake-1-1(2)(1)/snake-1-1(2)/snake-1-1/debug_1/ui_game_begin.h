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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_game_begin
{
public:
    QLabel *label;
    QLabel *label_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *begin_game;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QLabel *label_3;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;

    void setupUi(QWidget *game_begin)
    {
        if (game_begin->objectName().isEmpty())
            game_begin->setObjectName(QString::fromUtf8("game_begin"));
        game_begin->resize(800, 450);
        label = new QLabel(game_begin);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 20, 211, 61));
        label->setStyleSheet(QString::fromUtf8(""));
        label_2 = new QLabel(game_begin);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(320, 140, 141, 211));
        verticalLayoutWidget = new QWidget(game_begin);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(340, 130, 101, 231));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        begin_game = new QPushButton(verticalLayoutWidget);
        begin_game->setObjectName(QString::fromUtf8("begin_game"));

        verticalLayout->addWidget(begin_game);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_3 = new QPushButton(verticalLayoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        label_3 = new QLabel(game_begin);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(260, 150, 121, 191));
        horizontalLayoutWidget = new QWidget(game_begin);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(40, 370, 731, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_4 = new QPushButton(horizontalLayoutWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        horizontalLayout->addWidget(pushButton_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(horizontalLayoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        label_3->raise();
        label_2->raise();
        label->raise();
        verticalLayoutWidget->raise();
        horizontalLayoutWidget->raise();

        retranslateUi(game_begin);

        QMetaObject::connectSlotsByName(game_begin);
    } // setupUi

    void retranslateUi(QWidget *game_begin)
    {
        game_begin->setWindowTitle(QCoreApplication::translate("game_begin", "Form", nullptr));
        label->setText(QCoreApplication::translate("game_begin", "TextLabel", nullptr));
        label_2->setText(QString());
        begin_game->setText(QCoreApplication::translate("game_begin", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        pushButton->setText(QCoreApplication::translate("game_begin", "\346\216\222\350\241\214\346\246\234", nullptr));
        pushButton_3->setText(QCoreApplication::translate("game_begin", "\350\256\276\347\275\256", nullptr));
        label_3->setText(QString());
        pushButton_4->setText(QCoreApplication::translate("game_begin", "\346\270\270\346\210\217\350\247\204\345\210\231", nullptr));
        pushButton_2->setText(QCoreApplication::translate("game_begin", "\347\210\267\344\270\215\347\216\251\344\272\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class game_begin: public Ui_game_begin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_BEGIN_H
