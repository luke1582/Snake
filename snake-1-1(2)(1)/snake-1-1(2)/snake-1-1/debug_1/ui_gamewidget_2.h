/********************************************************************************
** Form generated from reading UI file 'gamewidget_2.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWIDGET_2_H
#define UI_GAMEWIDGET_2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gamewidget_2
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label;

    void setupUi(QWidget *gamewidget_2)
    {
        if (gamewidget_2->objectName().isEmpty())
            gamewidget_2->setObjectName(QString::fromUtf8("gamewidget_2"));
        gamewidget_2->resize(800, 454);
        verticalLayoutWidget = new QWidget(gamewidget_2);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(570, 70, 220, 371));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        label = new QLabel(gamewidget_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(590, 0, 218, 87));
        label->setMargin(1);

        retranslateUi(gamewidget_2);

        QMetaObject::connectSlotsByName(gamewidget_2);
    } // setupUi

    void retranslateUi(QWidget *gamewidget_2)
    {
        gamewidget_2->setWindowTitle(QCoreApplication::translate("gamewidget_2", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("gamewidget_2", "<html><head/><body><p align=\"center\">TextLabel</p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("gamewidget_2", "<html><head/><body><p align=\"center\">TextLabel</p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("gamewidget_2", "<html><head/><body><p align=\"center\">TextLabel</p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("gamewidget_2", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:600;\">Game Begin!!</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gamewidget_2: public Ui_gamewidget_2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWIDGET_2_H
