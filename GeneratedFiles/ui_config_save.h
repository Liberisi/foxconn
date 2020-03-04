/********************************************************************************
** Form generated from reading UI file 'config_save.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIG_SAVE_H
#define UI_CONFIG_SAVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Configsave
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_14;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_15;
    QLabel *label;
    QSpacerItem *horizontalSpacer_16;
    QWidget *widget_2;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *checkBox_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_9;
    QCheckBox *checkBox_5;
    QSpacerItem *horizontalSpacer_10;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_12;
    QToolButton *toolButton;
    QSpacerItem *horizontalSpacer_11;
    QToolButton *toolButton_2;
    QSpacerItem *horizontalSpacer_13;

    void setupUi(QDialog *Configsave)
    {
        if (Configsave->objectName().isEmpty())
            Configsave->setObjectName(QStringLiteral("Configsave"));
        Configsave->resize(295, 487);
        Configsave->setStyleSheet(QStringLiteral("background-color: rgb(181, 181, 181);"));
        verticalLayout = new QVBoxLayout(Configsave);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new QWidget(Configsave);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_14 = new QSpacerItem(213, 9, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_14);


        verticalLayout->addWidget(widget);

        widget_4 = new QWidget(Configsave);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setMaximumSize(QSize(16777215, 60));
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_15 = new QSpacerItem(71, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_15);

        label = new QLabel(widget_4);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        horizontalLayout_3->addWidget(label);

        horizontalSpacer_16 = new QSpacerItem(70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_16);


        verticalLayout->addWidget(widget_4);

        widget_2 = new QWidget(Configsave);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        gridLayout = new QGridLayout(widget_2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer_2 = new QSpacerItem(57, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(57, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 3, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(57, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 0, 1, 1);

        checkBox_2 = new QCheckBox(widget_2);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221 Light"));
        font1.setPointSize(12);
        checkBox_2->setFont(font1);

        gridLayout->addWidget(checkBox_2, 1, 1, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(57, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 3, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(57, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 2, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(57, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 2, 3, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(57, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 3, 0, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(57, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 3, 3, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(57, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_9, 4, 0, 1, 1);

        checkBox_5 = new QCheckBox(widget_2);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));
        checkBox_5->setFont(font1);

        gridLayout->addWidget(checkBox_5, 4, 1, 1, 2);

        horizontalSpacer_10 = new QSpacerItem(57, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_10, 4, 3, 1, 1);

        checkBox_3 = new QCheckBox(widget_2);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        checkBox_3->setFont(font1);

        gridLayout->addWidget(checkBox_3, 2, 1, 1, 2);

        checkBox_4 = new QCheckBox(widget_2);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));
        checkBox_4->setFont(font1);

        gridLayout->addWidget(checkBox_4, 3, 1, 1, 2);

        checkBox = new QCheckBox(widget_2);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setFont(font1);

        gridLayout->addWidget(checkBox, 0, 1, 1, 2);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(Configsave);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setMaximumSize(QSize(16777215, 80));
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_12 = new QSpacerItem(37, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_12);

        toolButton = new QToolButton(widget_3);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        QIcon icon;
        icon.addFile(QStringLiteral("images/close_536px_1199468_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon);
        toolButton->setIconSize(QSize(50, 50));
        toolButton->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton);

        horizontalSpacer_11 = new QSpacerItem(38, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_11);

        toolButton_2 = new QToolButton(widget_3);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("images/approve_536px_1199463_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_2->setIcon(icon1);
        toolButton_2->setIconSize(QSize(50, 50));
        toolButton_2->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton_2);

        horizontalSpacer_13 = new QSpacerItem(37, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_13);


        verticalLayout->addWidget(widget_3);


        retranslateUi(Configsave);

        QMetaObject::connectSlotsByName(Configsave);
    } // setupUi

    void retranslateUi(QDialog *Configsave)
    {
        Configsave->setWindowTitle(QApplication::translate("Configsave", "\344\277\235\345\255\230\350\256\276\347\275\256", Q_NULLPTR));
        label->setText(QApplication::translate("Configsave", "\345\255\230\345\202\250\350\256\276\347\275\256", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("Configsave", "\344\277\235\345\255\230NG\347\274\251\347\225\245\345\233\276", Q_NULLPTR));
        checkBox_5->setText(QApplication::translate("Configsave", "\345\261\217\350\224\275\351\225\277\345\256\275\351\231\220\345\210\266", Q_NULLPTR));
        checkBox_3->setText(QApplication::translate("Configsave", "\344\277\235\345\255\230OK\345\216\237\345\233\276", Q_NULLPTR));
        checkBox_4->setText(QApplication::translate("Configsave", "\344\277\235\345\255\230OK\347\274\251\347\225\245\345\233\276", Q_NULLPTR));
        checkBox->setText(QApplication::translate("Configsave", "\344\277\235\345\255\230NG\345\216\237\345\233\276", Q_NULLPTR));
        toolButton->setText(QApplication::translate("Configsave", "...", Q_NULLPTR));
        toolButton_2->setText(QApplication::translate("Configsave", "...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Configsave: public Ui_Configsave {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIG_SAVE_H
