/********************************************************************************
** Form generated from reading UI file 'frame_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRAME_DIALOG_H
#define UI_FRAME_DIALOG_H

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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "halcon_widget.h"

QT_BEGIN_NAMESPACE

class Ui_Frame_Dialog
{
public:
    QHBoxLayout *horizontalLayout_3;
    HalconWidget *image_window;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton_capture;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButton_select_image;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_3;
    QSpinBox *spinBox_x;
    QLabel *label_5;
    QSpinBox *spinBox_y;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_4;
    QSpinBox *spinBox_w;
    QLabel *label_6;
    QSpinBox *spinBox_h;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_disk_magic_x;
    QSpinBox *spinBox_disk_magic_width;
    QLabel *label_11;
    QSpinBox *spinBox_disk_magic_height;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_15;
    QHBoxLayout *horizontalLayout_14;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_15;
    QSpinBox *spinBox_lx;
    QLabel *label_18;
    QSpinBox *spinBox_ly;
    QWidget *widget_13;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label_10;
    QSpinBox *spinBox_lw;
    QLabel *label_12;
    QSpinBox *spinBox_lh;
    QWidget *widget_11;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_16;
    QSpinBox *spinBox_side_hand_magic_x;
    QWidget *widget_9;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_6;
    QWidget *widget_10;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_8;
    QSpinBox *spinBox_rx;
    QLabel *label_9;
    QSpinBox *spinBox_ry;
    QWidget *widget_14;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_12;
    QLabel *label_13;
    QSpinBox *spinBox_rw;
    QLabel *label_14;
    QSpinBox *spinBox_rh;
    QWidget *widget_12;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_13;
    QLabel *label_17;
    QSpinBox *spinBox_side_hand_magic_y;
    QLabel *label_result;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_detect;
    QPushButton *pushButton_save_config;
    QPushButton *pushButton;

    void setupUi(QDialog *Frame_Dialog)
    {
        if (Frame_Dialog->objectName().isEmpty())
            Frame_Dialog->setObjectName(QStringLiteral("Frame_Dialog"));
        Frame_Dialog->resize(1024, 700);
        Frame_Dialog->setMinimumSize(QSize(0, 0));
        horizontalLayout_3 = new QHBoxLayout(Frame_Dialog);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        image_window = new HalconWidget(Frame_Dialog);
        image_window->setObjectName(QStringLiteral("image_window"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(image_window->sizePolicy().hasHeightForWidth());
        image_window->setSizePolicy(sizePolicy);
        image_window->setMinimumSize(QSize(350, 0));

        horizontalLayout_3->addWidget(image_window);

        frame_2 = new QFrame(Frame_Dialog);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setMaximumSize(QSize(260, 16777215));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Plain);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget_3 = new QWidget(frame_2);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        toolButton_capture = new QToolButton(widget_3);
        toolButton_capture->setObjectName(QStringLiteral("toolButton_capture"));
        toolButton_capture->setMinimumSize(QSize(67, 0));

        horizontalLayout->addWidget(toolButton_capture);

        horizontalSpacer = new QSpacerItem(75, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        toolButton_select_image = new QToolButton(widget_3);
        toolButton_select_image->setObjectName(QStringLiteral("toolButton_select_image"));
        toolButton_select_image->setMinimumSize(QSize(67, 0));

        horizontalLayout->addWidget(toolButton_select_image);


        verticalLayout_2->addWidget(widget_3);

        widget_2 = new QWidget(frame_2);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        verticalLayout_3 = new QVBoxLayout(widget_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(widget_2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(0, 136));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(groupBox_2);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(0, 30));
        widget->setMaximumSize(QSize(16777215, 48));
        horizontalLayout_5 = new QHBoxLayout(widget);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(42, 0));
        label_3->setMaximumSize(QSize(50, 16777215));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_3);

        spinBox_x = new QSpinBox(widget);
        spinBox_x->setObjectName(QStringLiteral("spinBox_x"));
        spinBox_x->setMinimumSize(QSize(60, 0));
        spinBox_x->setMaximumSize(QSize(60, 16777215));
        spinBox_x->setMinimum(100);
        spinBox_x->setMaximum(10000);
        spinBox_x->setValue(810);

        horizontalLayout_5->addWidget(spinBox_x);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(52, 0));
        label_5->setMaximumSize(QSize(50, 16777215));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_5);

        spinBox_y = new QSpinBox(widget);
        spinBox_y->setObjectName(QStringLiteral("spinBox_y"));
        spinBox_y->setMinimumSize(QSize(60, 0));
        spinBox_y->setMaximumSize(QSize(60, 16777215));
        spinBox_y->setMinimum(100);
        spinBox_y->setMaximum(10000);
        spinBox_y->setValue(800);

        horizontalLayout_5->addWidget(spinBox_y);


        verticalLayout->addWidget(widget);

        widget_6 = new QWidget(groupBox_2);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        widget_6->setMaximumSize(QSize(16777215, 48));
        horizontalLayout_6 = new QHBoxLayout(widget_6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        label_4 = new QLabel(widget_6);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(42, 0));
        label_4->setMaximumSize(QSize(50, 16777215));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_4);

        spinBox_w = new QSpinBox(widget_6);
        spinBox_w->setObjectName(QStringLiteral("spinBox_w"));
        spinBox_w->setMinimumSize(QSize(60, 0));
        spinBox_w->setMaximumSize(QSize(60, 16777215));
        spinBox_w->setMinimum(20);
        spinBox_w->setMaximum(10000);
        spinBox_w->setValue(950);

        horizontalLayout_6->addWidget(spinBox_w);

        label_6 = new QLabel(widget_6);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(52, 0));
        label_6->setMaximumSize(QSize(50, 16777215));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_6);

        spinBox_h = new QSpinBox(widget_6);
        spinBox_h->setObjectName(QStringLiteral("spinBox_h"));
        spinBox_h->setMinimumSize(QSize(60, 0));
        spinBox_h->setMaximumSize(QSize(60, 16777215));
        spinBox_h->setMinimum(20);
        spinBox_h->setMaximum(10000);
        spinBox_h->setValue(800);

        horizontalLayout_6->addWidget(spinBox_h);


        verticalLayout->addWidget(widget_6);

        widget_7 = new QWidget(groupBox_2);
        widget_7->setObjectName(QStringLiteral("widget_7"));
        widget_7->setMinimumSize(QSize(0, 30));
        widget_7->setMaximumSize(QSize(16777215, 48));
        horizontalLayout_7 = new QHBoxLayout(widget_7);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_10);

        label_disk_magic_x = new QLabel(widget_7);
        label_disk_magic_x->setObjectName(QStringLiteral("label_disk_magic_x"));
        label_disk_magic_x->setMinimumSize(QSize(42, 0));
        label_disk_magic_x->setMaximumSize(QSize(50, 16777215));
        label_disk_magic_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(label_disk_magic_x);

        spinBox_disk_magic_width = new QSpinBox(widget_7);
        spinBox_disk_magic_width->setObjectName(QStringLiteral("spinBox_disk_magic_width"));
        spinBox_disk_magic_width->setMinimumSize(QSize(60, 0));
        spinBox_disk_magic_width->setMaximumSize(QSize(60, 16777215));
        spinBox_disk_magic_width->setMinimum(20);
        spinBox_disk_magic_width->setMaximum(10000);
        spinBox_disk_magic_width->setValue(112);

        horizontalLayout_7->addWidget(spinBox_disk_magic_width);

        label_11 = new QLabel(widget_7);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setMinimumSize(QSize(52, 0));
        label_11->setMaximumSize(QSize(50, 16777215));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(label_11);

        spinBox_disk_magic_height = new QSpinBox(widget_7);
        spinBox_disk_magic_height->setObjectName(QStringLiteral("spinBox_disk_magic_height"));
        spinBox_disk_magic_height->setMinimumSize(QSize(60, 0));
        spinBox_disk_magic_height->setMaximumSize(QSize(60, 16777215));
        spinBox_disk_magic_height->setMinimum(20);
        spinBox_disk_magic_height->setMaximum(10000);
        spinBox_disk_magic_height->setValue(96);

        horizontalLayout_7->addWidget(spinBox_disk_magic_height);


        verticalLayout->addWidget(widget_7);


        verticalLayout_3->addWidget(groupBox_2);


        verticalLayout_2->addWidget(widget_2);

        widget_4 = new QWidget(frame_2);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        horizontalLayout_2 = new QHBoxLayout(widget_4);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(widget_4);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(0, 0));
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        widget_15 = new QWidget(groupBox);
        widget_15->setObjectName(QStringLiteral("widget_15"));
        widget_15->setMinimumSize(QSize(0, 30));
        widget_15->setMaximumSize(QSize(16777215, 48));
        horizontalLayout_14 = new QHBoxLayout(widget_15);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_6);

        label_15 = new QLabel(widget_15);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setMinimumSize(QSize(42, 0));
        label_15->setMaximumSize(QSize(50, 16777215));
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_14->addWidget(label_15);

        spinBox_lx = new QSpinBox(widget_15);
        spinBox_lx->setObjectName(QStringLiteral("spinBox_lx"));
        spinBox_lx->setMinimumSize(QSize(60, 0));
        spinBox_lx->setMaximumSize(QSize(60, 16777215));
        spinBox_lx->setMinimum(100);
        spinBox_lx->setMaximum(10000);
        spinBox_lx->setValue(810);

        horizontalLayout_14->addWidget(spinBox_lx);

        label_18 = new QLabel(widget_15);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setMinimumSize(QSize(52, 0));
        label_18->setMaximumSize(QSize(50, 16777215));
        label_18->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_14->addWidget(label_18);

        spinBox_ly = new QSpinBox(widget_15);
        spinBox_ly->setObjectName(QStringLiteral("spinBox_ly"));
        spinBox_ly->setMinimumSize(QSize(60, 0));
        spinBox_ly->setMaximumSize(QSize(60, 16777215));
        spinBox_ly->setMinimum(100);
        spinBox_ly->setMaximum(10000);
        spinBox_ly->setValue(800);

        horizontalLayout_14->addWidget(spinBox_ly);


        verticalLayout_4->addWidget(widget_15);

        widget_13 = new QWidget(groupBox);
        widget_13->setObjectName(QStringLiteral("widget_13"));
        widget_13->setMaximumSize(QSize(16777215, 48));
        horizontalLayout_12 = new QHBoxLayout(widget_13);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_11);

        label_10 = new QLabel(widget_13);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setMinimumSize(QSize(42, 0));
        label_10->setMaximumSize(QSize(50, 16777215));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_12->addWidget(label_10);

        spinBox_lw = new QSpinBox(widget_13);
        spinBox_lw->setObjectName(QStringLiteral("spinBox_lw"));
        spinBox_lw->setMinimumSize(QSize(60, 0));
        spinBox_lw->setMaximumSize(QSize(60, 16777215));
        spinBox_lw->setMinimum(20);
        spinBox_lw->setMaximum(10000);
        spinBox_lw->setValue(950);

        horizontalLayout_12->addWidget(spinBox_lw);

        label_12 = new QLabel(widget_13);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setMinimumSize(QSize(52, 0));
        label_12->setMaximumSize(QSize(50, 16777215));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_12->addWidget(label_12);

        spinBox_lh = new QSpinBox(widget_13);
        spinBox_lh->setObjectName(QStringLiteral("spinBox_lh"));
        spinBox_lh->setMinimumSize(QSize(60, 0));
        spinBox_lh->setMaximumSize(QSize(60, 16777215));
        spinBox_lh->setMinimum(20);
        spinBox_lh->setMaximum(10000);
        spinBox_lh->setValue(800);

        horizontalLayout_12->addWidget(spinBox_lh);


        verticalLayout_4->addWidget(widget_13);

        widget_11 = new QWidget(groupBox);
        widget_11->setObjectName(QStringLiteral("widget_11"));
        widget_11->setMinimumSize(QSize(0, 30));
        widget_11->setMaximumSize(QSize(16777215, 48));
        horizontalLayout_10 = new QHBoxLayout(widget_11);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 11, 0);
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_9);

        label_16 = new QLabel(widget_11);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setMinimumSize(QSize(38, 0));
        label_16->setMaximumSize(QSize(50, 16777215));
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_10->addWidget(label_16);

        spinBox_side_hand_magic_x = new QSpinBox(widget_11);
        spinBox_side_hand_magic_x->setObjectName(QStringLiteral("spinBox_side_hand_magic_x"));
        spinBox_side_hand_magic_x->setMinimumSize(QSize(60, 0));
        spinBox_side_hand_magic_x->setMaximumSize(QSize(60, 16777215));
        spinBox_side_hand_magic_x->setMinimum(100);
        spinBox_side_hand_magic_x->setMaximum(160000);
        spinBox_side_hand_magic_x->setValue(160);

        horizontalLayout_10->addWidget(spinBox_side_hand_magic_x);


        verticalLayout_4->addWidget(widget_11);


        horizontalLayout_2->addWidget(groupBox);


        verticalLayout_2->addWidget(widget_4);

        widget_9 = new QWidget(frame_2);
        widget_9->setObjectName(QStringLiteral("widget_9"));
        verticalLayout_5 = new QVBoxLayout(widget_9);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);

        verticalLayout_2->addWidget(widget_9);

        groupBox_3 = new QGroupBox(frame_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(0, 0));
        verticalLayout_6 = new QVBoxLayout(groupBox_3);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        widget_10 = new QWidget(groupBox_3);
        widget_10->setObjectName(QStringLiteral("widget_10"));
        widget_10->setMinimumSize(QSize(0, 30));
        widget_10->setMaximumSize(QSize(16777215, 48));
        horizontalLayout_9 = new QHBoxLayout(widget_10);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_5);

        label_8 = new QLabel(widget_10);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(42, 0));
        label_8->setMaximumSize(QSize(50, 16777215));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(label_8);

        spinBox_rx = new QSpinBox(widget_10);
        spinBox_rx->setObjectName(QStringLiteral("spinBox_rx"));
        spinBox_rx->setMinimumSize(QSize(60, 0));
        spinBox_rx->setMaximumSize(QSize(60, 16777215));
        spinBox_rx->setMinimum(100);
        spinBox_rx->setMaximum(10000);
        spinBox_rx->setValue(810);

        horizontalLayout_9->addWidget(spinBox_rx);

        label_9 = new QLabel(widget_10);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMinimumSize(QSize(52, 0));
        label_9->setMaximumSize(QSize(50, 16777215));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(label_9);

        spinBox_ry = new QSpinBox(widget_10);
        spinBox_ry->setObjectName(QStringLiteral("spinBox_ry"));
        spinBox_ry->setMinimumSize(QSize(60, 0));
        spinBox_ry->setMaximumSize(QSize(60, 16777215));
        spinBox_ry->setMinimum(100);
        spinBox_ry->setMaximum(10000);
        spinBox_ry->setValue(800);

        horizontalLayout_9->addWidget(spinBox_ry);


        verticalLayout_6->addWidget(widget_10);

        widget_14 = new QWidget(groupBox_3);
        widget_14->setObjectName(QStringLiteral("widget_14"));
        widget_14->setMaximumSize(QSize(16777215, 48));
        horizontalLayout_13 = new QHBoxLayout(widget_14);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_12);

        label_13 = new QLabel(widget_14);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setMinimumSize(QSize(42, 0));
        label_13->setMaximumSize(QSize(50, 16777215));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_13->addWidget(label_13);

        spinBox_rw = new QSpinBox(widget_14);
        spinBox_rw->setObjectName(QStringLiteral("spinBox_rw"));
        spinBox_rw->setMinimumSize(QSize(60, 0));
        spinBox_rw->setMaximumSize(QSize(60, 16777215));
        spinBox_rw->setMinimum(20);
        spinBox_rw->setMaximum(10000);
        spinBox_rw->setValue(950);

        horizontalLayout_13->addWidget(spinBox_rw);

        label_14 = new QLabel(widget_14);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setMinimumSize(QSize(52, 0));
        label_14->setMaximumSize(QSize(50, 16777215));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_13->addWidget(label_14);

        spinBox_rh = new QSpinBox(widget_14);
        spinBox_rh->setObjectName(QStringLiteral("spinBox_rh"));
        spinBox_rh->setMinimumSize(QSize(60, 0));
        spinBox_rh->setMaximumSize(QSize(60, 16777215));
        spinBox_rh->setMinimum(20);
        spinBox_rh->setMaximum(10000);
        spinBox_rh->setValue(800);

        horizontalLayout_13->addWidget(spinBox_rh);


        verticalLayout_6->addWidget(widget_14);

        widget_12 = new QWidget(groupBox_3);
        widget_12->setObjectName(QStringLiteral("widget_12"));
        widget_12->setMinimumSize(QSize(0, 30));
        widget_12->setMaximumSize(QSize(16777215, 48));
        horizontalLayout_11 = new QHBoxLayout(widget_12);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 11, 0);
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_13);

        label_17 = new QLabel(widget_12);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setMinimumSize(QSize(38, 0));
        label_17->setMaximumSize(QSize(50, 16777215));
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_17);

        spinBox_side_hand_magic_y = new QSpinBox(widget_12);
        spinBox_side_hand_magic_y->setObjectName(QStringLiteral("spinBox_side_hand_magic_y"));
        spinBox_side_hand_magic_y->setMinimumSize(QSize(60, 0));
        spinBox_side_hand_magic_y->setMaximumSize(QSize(60, 16777215));
        spinBox_side_hand_magic_y->setMinimum(100);
        spinBox_side_hand_magic_y->setMaximum(160000);
        spinBox_side_hand_magic_y->setValue(176);

        horizontalLayout_11->addWidget(spinBox_side_hand_magic_y);


        verticalLayout_6->addWidget(widget_12);


        verticalLayout_2->addWidget(groupBox_3);

        label_result = new QLabel(frame_2);
        label_result->setObjectName(QStringLiteral("label_result"));
        label_result->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_result);

        widget_8 = new QWidget(frame_2);
        widget_8->setObjectName(QStringLiteral("widget_8"));
        widget_8->setMinimumSize(QSize(0, 40));
        horizontalLayout_8 = new QHBoxLayout(widget_8);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer_2 = new QSpacerItem(59, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);

        pushButton_2 = new QPushButton(widget_8);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_8->addWidget(pushButton_2);

        horizontalSpacer_7 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_7);


        verticalLayout_2->addWidget(widget_8);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        widget_5 = new QWidget(frame_2);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        horizontalLayout_4 = new QHBoxLayout(widget_5);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pushButton_detect = new QPushButton(widget_5);
        pushButton_detect->setObjectName(QStringLiteral("pushButton_detect"));

        horizontalLayout_4->addWidget(pushButton_detect);

        pushButton_save_config = new QPushButton(widget_5);
        pushButton_save_config->setObjectName(QStringLiteral("pushButton_save_config"));

        horizontalLayout_4->addWidget(pushButton_save_config);

        pushButton = new QPushButton(widget_5);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_4->addWidget(pushButton);


        verticalLayout_2->addWidget(widget_5);


        horizontalLayout_3->addWidget(frame_2);


        retranslateUi(Frame_Dialog);

        QMetaObject::connectSlotsByName(Frame_Dialog);
    } // setupUi

    void retranslateUi(QDialog *Frame_Dialog)
    {
        Frame_Dialog->setWindowTitle(QApplication::translate("Frame_Dialog", "Dialog", Q_NULLPTR));
        toolButton_capture->setText(QApplication::translate("Frame_Dialog", "\345\233\276\345\203\217\351\207\207\351\233\206", Q_NULLPTR));
        toolButton_select_image->setText(QApplication::translate("Frame_Dialog", "\347\246\273\347\272\277\345\233\276\345\203\217", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("Frame_Dialog", "\344\270\255\351\227\264\346\224\257\346\236\266\357\274\210\350\257\267\350\201\224\347\263\273\345\274\200\345\217\221\344\272\272\345\221\230\344\277\256\346\224\271\357\274\211", Q_NULLPTR));
        label_3->setText(QApplication::translate("Frame_Dialog", "x", Q_NULLPTR));
        label_5->setText(QApplication::translate("Frame_Dialog", "y", Q_NULLPTR));
        label_4->setText(QApplication::translate("Frame_Dialog", "width", Q_NULLPTR));
        label_6->setText(QApplication::translate("Frame_Dialog", "height", Q_NULLPTR));
        label_disk_magic_x->setText(QApplication::translate("Frame_Dialog", "mx", Q_NULLPTR));
        label_11->setText(QApplication::translate("Frame_Dialog", "my", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Frame_Dialog", "\345\267\246\344\276\247\346\241\243\346\235\206\357\274\210\350\257\267\350\201\224\347\263\273\345\274\200\345\217\221\344\272\272\345\221\230\344\277\256\346\224\271\357\274\211", Q_NULLPTR));
        label_15->setText(QApplication::translate("Frame_Dialog", "x", Q_NULLPTR));
        label_18->setText(QApplication::translate("Frame_Dialog", "y", Q_NULLPTR));
        label_10->setText(QApplication::translate("Frame_Dialog", "w/2", Q_NULLPTR));
        label_12->setText(QApplication::translate("Frame_Dialog", "h/2", Q_NULLPTR));
        label_16->setText(QApplication::translate("Frame_Dialog", "mx2", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("Frame_Dialog", "\345\217\263\344\276\247\346\214\241\346\235\206\357\274\210\350\257\267\350\201\224\347\263\273\345\274\200\345\217\221\344\272\272\345\221\230\344\277\256\346\224\271\357\274\211", Q_NULLPTR));
        label_8->setText(QApplication::translate("Frame_Dialog", "x", Q_NULLPTR));
        label_9->setText(QApplication::translate("Frame_Dialog", "y", Q_NULLPTR));
        label_13->setText(QApplication::translate("Frame_Dialog", "w/2", Q_NULLPTR));
        label_14->setText(QApplication::translate("Frame_Dialog", "h/2", Q_NULLPTR));
        label_17->setText(QApplication::translate("Frame_Dialog", "my2", Q_NULLPTR));
        label_result->setText(QApplication::translate("Frame_Dialog", "OK/NG", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Frame_Dialog", "\344\277\235\345\255\230\347\273\223\346\236\234\345\233\276\345\203\217", Q_NULLPTR));
        pushButton_detect->setText(QApplication::translate("Frame_Dialog", "\346\243\200\346\265\213", Q_NULLPTR));
        pushButton_save_config->setText(QApplication::translate("Frame_Dialog", "\344\277\235\345\255\230\350\256\276\347\275\256", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Frame_Dialog", "\344\277\235\345\255\230\345\233\276\345\203\217", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Frame_Dialog: public Ui_Frame_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRAME_DIALOG_H
