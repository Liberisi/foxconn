/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName(QStringLiteral("About"));
        About->resize(508, 257);
        About->setStyleSheet(QString::fromUtf8("background-color: rgb(101, 101, 101);\n"
"font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(8, 22, 141);\n"
""));
        label = new QLabel(About);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(120, 60, 361, 121));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(101, 101, 101);\n"
"font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(8, 22, 141);\n"
""));
        label_2 = new QLabel(About);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 80, 81, 81));
        label_2->setStyleSheet(QStringLiteral("background-color: rgb(101, 101, 101);"));
        label_2->setMidLineWidth(0);
        label_2->setPixmap(QPixmap(QString::fromUtf8("images/logo6.png")));
        label_2->setScaledContents(true);

        retranslateUi(About);

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QDialog *About)
    {
        About->setWindowTitle(QApplication::translate("About", "\345\205\263\344\272\216", Q_NULLPTR));
        label->setText(QApplication::translate("About", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">\347\211\210\346\234\254\357\274\232v1.0.0</span></p><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">\345\205\254\345\217\270\344\277\241\346\201\257\357\274\232\346\210\220\351\203\275\344\270\211\346\230\257\347\247\221\346\212\200\346\234\211\351\231\220\345\205\254\345\217\270</span></p><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">\350\201\224\347\263\273\347\224\265\350\257\235\357\274\232+86 028 84206180</span></p><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">\347\275\221\345\235\200\357\274\232www.sanshi-tech.com</span></p></body></html>", Q_NULLPTR));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
