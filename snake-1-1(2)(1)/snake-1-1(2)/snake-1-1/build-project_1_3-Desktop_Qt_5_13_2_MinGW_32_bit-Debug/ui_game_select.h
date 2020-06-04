/********************************************************************************
** Form generated from reading UI file 'game_select.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_SELECT_H
#define UI_GAME_SELECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_game_select
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *no_die_mode;
    QPushButton *limited_time_mode;
    QPushButton *ultimate_mode;

    void setupUi(QWidget *game_select)
    {
        if (game_select->objectName().isEmpty())
            game_select->setObjectName(QString::fromUtf8("game_select"));
        game_select->resize(383, 393);
        verticalLayoutWidget = new QWidget(game_select);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(150, 100, 77, 191));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        no_die_mode = new QPushButton(verticalLayoutWidget);
        no_die_mode->setObjectName(QString::fromUtf8("no_die_mode"));

        verticalLayout->addWidget(no_die_mode);

        limited_time_mode = new QPushButton(verticalLayoutWidget);
        limited_time_mode->setObjectName(QString::fromUtf8("limited_time_mode"));

        verticalLayout->addWidget(limited_time_mode);

        ultimate_mode = new QPushButton(verticalLayoutWidget);
        ultimate_mode->setObjectName(QString::fromUtf8("ultimate_mode"));

        verticalLayout->addWidget(ultimate_mode);


        retranslateUi(game_select);

        QMetaObject::connectSlotsByName(game_select);
    } // setupUi

    void retranslateUi(QWidget *game_select)
    {
        game_select->setWindowTitle(QCoreApplication::translate("game_select", "Form", nullptr));
        no_die_mode->setText(QCoreApplication::translate("game_select", "\346\227\240\346\225\214\346\250\241\345\274\217", nullptr));
        limited_time_mode->setText(QCoreApplication::translate("game_select", "\351\231\220\346\227\266\346\250\241\345\274\217", nullptr));
        ultimate_mode->setText(QCoreApplication::translate("game_select", "\346\227\240\351\231\220\346\250\241\345\274\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class game_select: public Ui_game_select {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_SELECT_H
