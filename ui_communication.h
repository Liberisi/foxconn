/********************************************************************************
** Form generated from reading UI file 'communication.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMUNICATION_H
#define UI_COMMUNICATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Communication
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label;
    QComboBox *comboBox_ip;
    QSpacerItem *horizontalSpacer_4;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLabel *label_robotic_port;
    QLabel *label_4;
    QLabel *label_advance_device_port;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *textEdit;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *lineEdit_CMC_ip;
    QLabel *label_5;
    QLineEdit *lineEdit_CMC_port;
    QPushButton *pushButton_CMC_connect;
    QLabel *label_cmc_socket_connect_status;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *Communication)
    {
        if (Communication->objectName().isEmpty())
            Communication->setObjectName(QStringLiteral("Communication"));
        Communication->resize(800, 600);
        verticalLayout = new QVBoxLayout(Communication);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new QWidget(Communication);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(13, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        comboBox_ip = new QComboBox(widget);
        comboBox_ip->setObjectName(QStringLiteral("comboBox_ip"));
        comboBox_ip->setMinimumSize(QSize(180, 0));

        horizontalLayout->addWidget(comboBox_ip);

        horizontalSpacer_4 = new QSpacerItem(15, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout->addWidget(widget);

        widget_5 = new QWidget(Communication);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        widget_5->setMinimumSize(QSize(0, 30));
        horizontalLayout_3 = new QHBoxLayout(widget_5);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(widget_5);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        label_robotic_port = new QLabel(widget_5);
        label_robotic_port->setObjectName(QStringLiteral("label_robotic_port"));

        horizontalLayout_3->addWidget(label_robotic_port);

        label_4 = new QLabel(widget_5);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        label_advance_device_port = new QLabel(widget_5);
        label_advance_device_port->setObjectName(QStringLiteral("label_advance_device_port"));

        horizontalLayout_3->addWidget(label_advance_device_port);


        verticalLayout->addWidget(widget_5);

        widget_2 = new QWidget(Communication);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        verticalLayout_3 = new QVBoxLayout(widget_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        textEdit = new QTextEdit(widget_3);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        verticalLayout_3->addWidget(textEdit);


        verticalLayout_2->addWidget(widget_3);

        widget_6 = new QWidget(widget_2);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        widget_6->setMinimumSize(QSize(0, 60));
        horizontalLayout_4 = new QHBoxLayout(widget_6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(widget_6);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        lineEdit_CMC_ip = new QLineEdit(widget_6);
        lineEdit_CMC_ip->setObjectName(QStringLiteral("lineEdit_CMC_ip"));

        horizontalLayout_4->addWidget(lineEdit_CMC_ip);

        label_5 = new QLabel(widget_6);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_4->addWidget(label_5);

        lineEdit_CMC_port = new QLineEdit(widget_6);
        lineEdit_CMC_port->setObjectName(QStringLiteral("lineEdit_CMC_port"));
        lineEdit_CMC_port->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_4->addWidget(lineEdit_CMC_port);

        pushButton_CMC_connect = new QPushButton(widget_6);
        pushButton_CMC_connect->setObjectName(QStringLiteral("pushButton_CMC_connect"));

        horizontalLayout_4->addWidget(pushButton_CMC_connect);

        label_cmc_socket_connect_status = new QLabel(widget_6);
        label_cmc_socket_connect_status->setObjectName(QStringLiteral("label_cmc_socket_connect_status"));

        horizontalLayout_4->addWidget(label_cmc_socket_connect_status);

        horizontalSpacer_2 = new QSpacerItem(166, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_2->addWidget(widget_6);

        widget_4 = new QWidget(widget_2);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        horizontalLayout_2 = new QHBoxLayout(widget_4);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(294, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_2->addWidget(widget_4);


        verticalLayout->addWidget(widget_2);


        retranslateUi(Communication);

        QMetaObject::connectSlotsByName(Communication);
    } // setupUi

    void retranslateUi(QDialog *Communication)
    {
        Communication->setWindowTitle(QApplication::translate("Communication", "\351\200\232\344\277\241\350\256\276\347\275\256", Q_NULLPTR));
        label->setText(QApplication::translate("Communication", "\346\234\254\346\234\272IP\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("Communication", "\346\234\272\346\242\260\350\207\202\350\277\236\346\216\245\346\234\254\346\234\272\347\253\257\345\217\243", Q_NULLPTR));
        label_robotic_port->setText(QApplication::translate("Communication", "0", Q_NULLPTR));
        label_4->setText(QApplication::translate("Communication", "\345\211\215\346\256\265\350\256\276\345\244\207\350\277\236\346\216\245\346\234\254\346\234\272\347\253\257\345\217\243", Q_NULLPTR));
        label_advance_device_port->setText(QApplication::translate("Communication", "0", Q_NULLPTR));
        label_3->setText(QApplication::translate("Communication", "CMC Server IP", Q_NULLPTR));
        lineEdit_CMC_ip->setText(QApplication::translate("Communication", "192.168.5.11", Q_NULLPTR));
        label_5->setText(QApplication::translate("Communication", "\347\253\257\345\217\243", Q_NULLPTR));
        lineEdit_CMC_port->setText(QApplication::translate("Communication", "55962", Q_NULLPTR));
        pushButton_CMC_connect->setText(QApplication::translate("Communication", "\344\277\235\345\255\230\345\271\266\351\207\215\350\277\236", Q_NULLPTR));
        label_cmc_socket_connect_status->setText(QApplication::translate("Communication", "\346\234\252\350\277\236\346\216\245", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Communication: public Ui_Communication {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMUNICATION_H
