/********************************************************************************
** Form generated from reading UI file 'setting.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTING_H
#define UI_SETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_setting
{
public:
    QLabel *label;
    QGroupBox *groupBox;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QGroupBox *groupBox_2;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_3;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QPushButton *pushButton;

    void setupUi(QWidget *setting)
    {
        if (setting->objectName().isEmpty())
            setting->setObjectName(QString::fromUtf8("setting"));
        setting->resize(800, 450);
        label = new QLabel(setting);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(600, 30, 151, 81));
        label->setStyleSheet(QString::fromUtf8("font: 45pt \"\345\215\216\346\226\207\346\245\267\344\275\223\";"));
        groupBox = new QGroupBox(setting);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(40, 20, 431, 131));
        groupBox->setStyleSheet(QString::fromUtf8("font: 16pt \"\346\245\267\344\275\223\";"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(40, 30, 80, 80));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(190, 20, 80, 80));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(340, 30, 80, 80));
        radioButton_4 = new QRadioButton(groupBox);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));
        radioButton_4->setGeometry(QRect(40, 110, 81, 16));
        radioButton_5 = new QRadioButton(groupBox);
        radioButton_5->setObjectName(QString::fromUtf8("radioButton_5"));
        radioButton_5->setGeometry(QRect(190, 110, 81, 16));
        radioButton_6 = new QRadioButton(groupBox);
        radioButton_6->setObjectName(QString::fromUtf8("radioButton_6"));
        radioButton_6->setGeometry(QRect(340, 110, 81, 16));
        groupBox_2 = new QGroupBox(setting);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(40, 160, 731, 241));
        groupBox_2->setStyleSheet(QString::fromUtf8("font: 16pt \"\346\245\267\344\275\223\";"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 50, 220, 150));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(260, 50, 220, 150));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(500, 50, 220, 150));
        radioButton = new QRadioButton(groupBox_2);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(90, 200, 81, 21));
        radioButton_2 = new QRadioButton(groupBox_2);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(330, 200, 81, 16));
        radioButton_3 = new QRadioButton(groupBox_2);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));
        radioButton_3->setGeometry(QRect(580, 200, 81, 16));
        label_2->raise();
        label_4->raise();
        label_3->raise();
        radioButton->raise();
        radioButton_3->raise();
        radioButton_2->raise();
        pushButton = new QPushButton(setting);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(660, 400, 85, 40));

        retranslateUi(setting);

        QMetaObject::connectSlotsByName(setting);
    } // setupUi

    void retranslateUi(QWidget *setting)
    {
        setting->setWindowTitle(QCoreApplication::translate("setting", "Form", nullptr));
        label->setText(QCoreApplication::translate("setting", "\350\256\276\347\275\256", nullptr));
        groupBox->setTitle(QCoreApplication::translate("setting", "\350\264\252\345\220\203\350\233\207\347\232\256\350\202\244\350\256\276\347\275\256", nullptr));
        label_5->setText(QString());
        label_6->setText(QString());
        label_7->setText(QString());
        radioButton_4->setText(QCoreApplication::translate("setting", "\347\232\256\350\202\2441", nullptr));
        radioButton_5->setText(QCoreApplication::translate("setting", "\347\232\256\350\202\2442", nullptr));
        radioButton_6->setText(QCoreApplication::translate("setting", "\347\232\256\350\202\2443", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("setting", "\350\203\214\346\231\257", nullptr));
        label_2->setText(QCoreApplication::translate("setting", "1111111111111111111111111111111111111111111", nullptr));
        label_4->setText(QCoreApplication::translate("setting", "11111111111111111111111111111111", nullptr));
        label_3->setText(QCoreApplication::translate("setting", "111111111111111111111111111111111", nullptr));
        radioButton->setText(QCoreApplication::translate("setting", "\350\203\214\346\231\2571", nullptr));
        radioButton_2->setText(QCoreApplication::translate("setting", "\350\203\214\346\231\2572", nullptr));
        radioButton_3->setText(QCoreApplication::translate("setting", "\350\203\214\346\231\2573", nullptr));
        pushButton->setText(QCoreApplication::translate("setting", "\350\277\224\345\233\236\344\270\273\347\225\214\351\235\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class setting: public Ui_setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
