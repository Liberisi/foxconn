/********************************************************************************
** Form generated from reading UI file 'location_config.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCATION_CONFIG_H
#define UI_LOCATION_CONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "halcon_widget.h"

QT_BEGIN_NAMESPACE

class Ui_Imageparameter
{
public:
    QHBoxLayout *horizontalLayout;
    HalconWidget *image_widget;
    QHBoxLayout *horizontalLayout_4;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *toolButton;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButton_choose_image;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_5;
    QSpinBox *spinBox_black_region_threshold;
    QSpacerItem *verticalSpacer;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_size;
    QSpacerItem *horizontalSpacer_5;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_3;
    QLineEdit *lineEdit_grap_z;
    QLabel *label_2;
    QLineEdit *lineEdit_drop_z;
    QLabel *label;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *lineEdit_l1;
    QLineEdit *lineEdit_l2;
    QLineEdit *lineEdit_3;
    QLabel *label_4;
    QLineEdit *lineEdit_size_var;
    QFrame *line;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout;
    QToolButton *toolButton_extract;
    QToolButton *toolButton_save_product_param;
    QPushButton *pushButton_save_image;
    QPushButton *pushButton_save_result_image;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *Imageparameter)
    {
        if (Imageparameter->objectName().isEmpty())
            Imageparameter->setObjectName(QStringLiteral("Imageparameter"));
        Imageparameter->resize(900, 535);
        Imageparameter->setMaximumSize(QSize(1024, 768));
        horizontalLayout = new QHBoxLayout(Imageparameter);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        image_widget = new HalconWidget(Imageparameter);
        image_widget->setObjectName(QStringLiteral("image_widget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(image_widget->sizePolicy().hasHeightForWidth());
        image_widget->setSizePolicy(sizePolicy);
        image_widget->setMinimumSize(QSize(300, 0));
        horizontalLayout_4 = new QHBoxLayout(image_widget);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));

        horizontalLayout->addWidget(image_widget);

        widget_2 = new QWidget(Imageparameter);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy1);
        widget_2->setMaximumSize(QSize(385, 16777215));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy2);
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        toolButton = new QToolButton(widget_3);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(toolButton->sizePolicy().hasHeightForWidth());
        toolButton->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(toolButton);

        horizontalSpacer = new QSpacerItem(99, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        toolButton_choose_image = new QToolButton(widget_3);
        toolButton_choose_image->setObjectName(QStringLiteral("toolButton_choose_image"));
        sizePolicy3.setHeightForWidth(toolButton_choose_image->sizePolicy().hasHeightForWidth());
        toolButton_choose_image->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(toolButton_choose_image);


        verticalLayout_2->addWidget(widget_3);

        widget = new QWidget(widget_2);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(0, 60));
        horizontalLayout_7 = new QHBoxLayout(widget);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_7->addWidget(label_5);

        spinBox_black_region_threshold = new QSpinBox(widget);
        spinBox_black_region_threshold->setObjectName(QStringLiteral("spinBox_black_region_threshold"));
        spinBox_black_region_threshold->setMinimum(30);
        spinBox_black_region_threshold->setMaximum(230);

        horizontalLayout_7->addWidget(spinBox_black_region_threshold);


        verticalLayout_2->addWidget(widget);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_2->addItem(verticalSpacer);

        widget_6 = new QWidget(widget_2);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(widget_6->sizePolicy().hasHeightForWidth());
        widget_6->setSizePolicy(sizePolicy4);
        horizontalLayout_5 = new QHBoxLayout(widget_6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        groupBox = new QGroupBox(widget_6);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_size = new QLabel(groupBox);
        label_size->setObjectName(QStringLiteral("label_size"));

        verticalLayout_3->addWidget(label_size);

        horizontalSpacer_5 = new QSpacerItem(220, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_3->addItem(horizontalSpacer_5);


        horizontalLayout_5->addWidget(groupBox);


        verticalLayout_2->addWidget(widget_6);

        widget_4 = new QWidget(widget_2);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        sizePolicy4.setHeightForWidth(widget_4->sizePolicy().hasHeightForWidth());
        widget_4->setSizePolicy(sizePolicy4);
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        groupBox_2 = new QGroupBox(widget_4);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_4->addWidget(label_3);

        lineEdit_grap_z = new QLineEdit(groupBox_2);
        lineEdit_grap_z->setObjectName(QStringLiteral("lineEdit_grap_z"));

        verticalLayout_4->addWidget(lineEdit_grap_z);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_4->addWidget(label_2);

        lineEdit_drop_z = new QLineEdit(groupBox_2);
        lineEdit_drop_z->setObjectName(QStringLiteral("lineEdit_drop_z"));

        verticalLayout_4->addWidget(lineEdit_drop_z);

        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_4->addWidget(label);

        widget_7 = new QWidget(groupBox_2);
        widget_7->setObjectName(QStringLiteral("widget_7"));
        widget_7->setMinimumSize(QSize(0, 40));
        horizontalLayout_6 = new QHBoxLayout(widget_7);
        horizontalLayout_6->setSpacing(10);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        lineEdit_l1 = new QLineEdit(widget_7);
        lineEdit_l1->setObjectName(QStringLiteral("lineEdit_l1"));

        horizontalLayout_6->addWidget(lineEdit_l1);

        lineEdit_l2 = new QLineEdit(widget_7);
        lineEdit_l2->setObjectName(QStringLiteral("lineEdit_l2"));

        horizontalLayout_6->addWidget(lineEdit_l2);

        lineEdit_3 = new QLineEdit(widget_7);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        horizontalLayout_6->addWidget(lineEdit_3);


        verticalLayout_4->addWidget(widget_7);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_4->addWidget(label_4);

        lineEdit_size_var = new QLineEdit(groupBox_2);
        lineEdit_size_var->setObjectName(QStringLiteral("lineEdit_size_var"));

        verticalLayout_4->addWidget(lineEdit_size_var);


        horizontalLayout_3->addWidget(groupBox_2);

        line = new QFrame(widget_4);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line);

        widget_5 = new QWidget(widget_4);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        verticalLayout = new QVBoxLayout(widget_5);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        toolButton_extract = new QToolButton(widget_5);
        toolButton_extract->setObjectName(QStringLiteral("toolButton_extract"));

        verticalLayout->addWidget(toolButton_extract);

        toolButton_save_product_param = new QToolButton(widget_5);
        toolButton_save_product_param->setObjectName(QStringLiteral("toolButton_save_product_param"));

        verticalLayout->addWidget(toolButton_save_product_param);

        pushButton_save_image = new QPushButton(widget_5);
        pushButton_save_image->setObjectName(QStringLiteral("pushButton_save_image"));

        verticalLayout->addWidget(pushButton_save_image);

        pushButton_save_result_image = new QPushButton(widget_5);
        pushButton_save_result_image->setObjectName(QStringLiteral("pushButton_save_result_image"));

        verticalLayout->addWidget(pushButton_save_result_image);


        horizontalLayout_3->addWidget(widget_5);


        verticalLayout_2->addWidget(widget_4);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout->addWidget(widget_2);


        retranslateUi(Imageparameter);

        QMetaObject::connectSlotsByName(Imageparameter);
    } // setupUi

    void retranslateUi(QDialog *Imageparameter)
    {
        Imageparameter->setWindowTitle(QApplication::translate("Imageparameter", "Dialog", Q_NULLPTR));
        toolButton->setText(QApplication::translate("Imageparameter", "\351\207\207\351\233\206\345\233\276\345\203\217", Q_NULLPTR));
        toolButton_choose_image->setText(QApplication::translate("Imageparameter", "\347\246\273\347\272\277\345\233\276\345\203\217", Q_NULLPTR));
        label_5->setText(QApplication::translate("Imageparameter", "\346\255\244\345\217\202\346\225\260\344\270\215\344\274\232\350\242\253\344\277\235\345\255\230", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Imageparameter", "\345\260\272\345\257\270", Q_NULLPTR));
        label_size->setText(QApplication::translate("Imageparameter", "[0,0]", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("Imageparameter", "\346\234\272\346\242\260\350\207\202\346\230\276\347\244\272\345\231\250\345\217\226\346\224\276\345\217\202\346\225\260", Q_NULLPTR));
        label_3->setText(QApplication::translate("Imageparameter", "\345\217\226\346\230\276\347\244\272\345\231\250\351\253\230\345\272\246", Q_NULLPTR));
        label_2->setText(QApplication::translate("Imageparameter", "\346\224\276\346\230\276\347\244\272\345\231\250\351\253\230\345\272\246", Q_NULLPTR));
        label->setText(QApplication::translate("Imageparameter", "\346\230\276\347\244\272\345\231\250\345\256\275\351\253\230\345\216\232 mm", Q_NULLPTR));
        label_4->setText(QApplication::translate("Imageparameter", "\345\256\275\351\253\230\350\257\257\345\267\256\350\214\203\345\233\264 mm", Q_NULLPTR));
        toolButton_extract->setText(QApplication::translate("Imageparameter", "\346\243\200\346\265\213\346\230\276\347\244\272\345\231\250\350\275\256\345\273\223", Q_NULLPTR));
        toolButton_save_product_param->setText(QApplication::translate("Imageparameter", "\344\277\235\345\255\230\345\217\226\346\224\276\345\217\202\346\225\260", Q_NULLPTR));
        pushButton_save_image->setText(QApplication::translate("Imageparameter", "\344\277\235\345\255\230\345\233\276\345\203\217", Q_NULLPTR));
        pushButton_save_result_image->setText(QApplication::translate("Imageparameter", "\344\277\235\345\255\230\347\273\223\346\236\234\345\233\276", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Imageparameter: public Ui_Imageparameter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCATION_CONFIG_H
