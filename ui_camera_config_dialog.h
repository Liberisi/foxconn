/********************************************************************************
** Form generated from reading UI file 'camera_config_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERA_CONFIG_DIALOG_H
#define UI_CAMERA_CONFIG_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "halcon_widget.h"

QT_BEGIN_NAMESPACE

class Ui_CameraConfigDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    HalconWidget *image_window;
    QWidget *botton_menu;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QComboBox *comboBox;
    QToolButton *toolButton_2;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpinBox *spinBox;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QSpinBox *spinBox_2;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *toolButton_3;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButton_4;

    void setupUi(QDialog *CameraConfigDialog)
    {
        if (CameraConfigDialog->objectName().isEmpty())
            CameraConfigDialog->setObjectName(QStringLiteral("CameraConfigDialog"));
        CameraConfigDialog->resize(682, 635);
        CameraConfigDialog->setStyleSheet(QStringLiteral("background-color: rgb(181, 181, 181);"));
        verticalLayout_2 = new QVBoxLayout(CameraConfigDialog);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        image_window = new HalconWidget(CameraConfigDialog);
        image_window->setObjectName(QStringLiteral("image_window"));
        image_window->setMouseTracking(true);
        image_window->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(image_window);

        botton_menu = new QWidget(CameraConfigDialog);
        botton_menu->setObjectName(QStringLiteral("botton_menu"));
        botton_menu->setEnabled(true);
        botton_menu->setMaximumSize(QSize(16777215, 100));
        botton_menu->setStyleSheet(QStringLiteral("background-color: rgb(131, 131, 131);"));
        horizontalLayout = new QHBoxLayout(botton_menu);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget = new QWidget(botton_menu);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_3->addWidget(label);

        comboBox = new QComboBox(widget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        verticalLayout_3->addWidget(comboBox);

        toolButton_2 = new QToolButton(widget);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));
        toolButton_2->setAutoRaise(false);

        verticalLayout_3->addWidget(toolButton_2);


        horizontalLayout->addWidget(widget);

        widget_2 = new QWidget(botton_menu);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMinimumSize(QSize(180, 0));
        verticalLayout_4 = new QVBoxLayout(widget_2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        widget_4 = new QWidget(widget_2);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setMinimumSize(QSize(0, 42));
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(widget_4);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_3->addWidget(label_3);

        spinBox = new QSpinBox(widget_4);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMinimumSize(QSize(60, 0));
        spinBox->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        spinBox->setMaximum(120);

        horizontalLayout_3->addWidget(spinBox);


        verticalLayout_4->addWidget(widget_4);

        widget_5 = new QWidget(widget_2);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        widget_5->setMinimumSize(QSize(0, 42));
        horizontalLayout_4 = new QHBoxLayout(widget_5);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(widget_5);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(60, 16777215));
        label_2->setMidLineWidth(0);

        horizontalLayout_4->addWidget(label_2);

        spinBox_2 = new QSpinBox(widget_5);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setMinimumSize(QSize(60, 0));
        spinBox_2->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        spinBox_2->setMaximum(120);
        spinBox_2->setSingleStep(1);

        horizontalLayout_4->addWidget(spinBox_2);


        verticalLayout_4->addWidget(widget_5);


        horizontalLayout->addWidget(widget_2);

        widget_3 = new QWidget(botton_menu);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        toolButton_3 = new QToolButton(widget_3);
        toolButton_3->setObjectName(QStringLiteral("toolButton_3"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221 Light"));
        font.setPointSize(14);
        toolButton_3->setFont(font);
        toolButton_3->setIconSize(QSize(30, 30));
        toolButton_3->setAutoRaise(false);

        horizontalLayout_2->addWidget(toolButton_3);

        horizontalSpacer = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        toolButton_4 = new QToolButton(widget_3);
        toolButton_4->setObjectName(QStringLiteral("toolButton_4"));
        toolButton_4->setFont(font);
        toolButton_4->setIconSize(QSize(35, 35));
        toolButton_4->setAutoRaise(false);

        horizontalLayout_2->addWidget(toolButton_4);


        horizontalLayout->addWidget(widget_3);


        verticalLayout->addWidget(botton_menu);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(CameraConfigDialog);

        QMetaObject::connectSlotsByName(CameraConfigDialog);
    } // setupUi

    void retranslateUi(QDialog *CameraConfigDialog)
    {
        CameraConfigDialog->setWindowTitle(QApplication::translate("CameraConfigDialog", "\347\233\270\346\234\272\345\217\202\346\225\260", Q_NULLPTR));
        label->setText(QApplication::translate("CameraConfigDialog", "   \347\233\270\346\234\272\345\217\267", Q_NULLPTR));
        toolButton_2->setText(QApplication::translate("CameraConfigDialog", "\350\216\267\345\217\226\347\233\270\346\234\272", Q_NULLPTR));
        label_3->setText(QApplication::translate("CameraConfigDialog", "   \346\233\235\345\205\211", Q_NULLPTR));
        label_2->setText(QApplication::translate("CameraConfigDialog", "   \345\242\236\347\233\212", Q_NULLPTR));
        toolButton_3->setText(QApplication::translate("CameraConfigDialog", "\350\256\276\347\275\256", Q_NULLPTR));
        toolButton_4->setText(QApplication::translate("CameraConfigDialog", "\344\277\235\345\255\230", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CameraConfigDialog: public Ui_CameraConfigDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERA_CONFIG_DIALOG_H
