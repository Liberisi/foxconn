/********************************************************************************
** Form generated from reading UI file 'position_calibrate.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POSITION_CALIBRATE_H
#define UI_POSITION_CALIBRATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "halcon_widget.h"

QT_BEGIN_NAMESPACE

class Ui_PositionCalibrate
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *mid_str;
    QHBoxLayout *horizontalLayout;
    HalconWidget *image_window;
    QWidget *Console;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *im_operat;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *toolButton_capture;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *toolButton_select_image;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_4;
    QWidget *pos_form;
    QHBoxLayout *horizontalLayout_7;
    QTableView *tableView;
    QTableView *tableView_2;
    QWidget *cailbrate_operat;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget_13;
    QVBoxLayout *verticalLayout_5;
    QToolButton *toolButton_add_mark;
    QToolButton *toolButton_remove_selected_rows;
    QToolButton *toolButton_remove_all_rows;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QSpinBox *spinBox_x_offset;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_4;
    QSpinBox *spinBox_y_offset;
    QWidget *widget_4;
    QWidget *widget_11;
    QVBoxLayout *verticalLayout_6;
    QSpacerItem *verticalSpacer;
    QToolButton *toolButton_calibrate;
    QSpacerItem *verticalSpacer_2;
    QToolButton *toolButton_save;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pushButton_save_image;
    QSpacerItem *verticalSpacer_4;
    QWidget *bot_str;
    QHBoxLayout *horizontalLayout_14;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QSpacerItem *horizontalSpacer_8;

    void setupUi(QDialog *PositionCalibrate)
    {
        if (PositionCalibrate->objectName().isEmpty())
            PositionCalibrate->setObjectName(QStringLiteral("PositionCalibrate"));
        PositionCalibrate->resize(1024, 700);
        PositionCalibrate->setMinimumSize(QSize(1024, 0));
        PositionCalibrate->setMaximumSize(QSize(1110, 700));
        PositionCalibrate->setStyleSheet(QStringLiteral("background-color: rgb(191, 191, 191);"));
        verticalLayout = new QVBoxLayout(PositionCalibrate);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        mid_str = new QWidget(PositionCalibrate);
        mid_str->setObjectName(QStringLiteral("mid_str"));
        horizontalLayout = new QHBoxLayout(mid_str);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        image_window = new HalconWidget(mid_str);
        image_window->setObjectName(QStringLiteral("image_window"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(image_window->sizePolicy().hasHeightForWidth());
        image_window->setSizePolicy(sizePolicy);
        image_window->setMinimumSize(QSize(300, 0));
        image_window->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout->addWidget(image_window);

        Console = new QWidget(mid_str);
        Console->setObjectName(QStringLiteral("Console"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Console->sizePolicy().hasHeightForWidth());
        Console->setSizePolicy(sizePolicy1);
        Console->setMinimumSize(QSize(300, 0));
        Console->setMaximumSize(QSize(360, 16777215));
        Console->setStyleSheet(QStringLiteral("background-color: rgb(171, 171, 171);"));
        verticalLayout_2 = new QVBoxLayout(Console);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        im_operat = new QGroupBox(Console);
        im_operat->setObjectName(QStringLiteral("im_operat"));
        im_operat->setMaximumSize(QSize(16777215, 110));
        horizontalLayout_3 = new QHBoxLayout(im_operat);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        widget_7 = new QWidget(im_operat);
        widget_7->setObjectName(QStringLiteral("widget_7"));
        horizontalLayout_4 = new QHBoxLayout(widget_7);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        toolButton_capture = new QToolButton(widget_7);
        toolButton_capture->setObjectName(QStringLiteral("toolButton_capture"));

        horizontalLayout_4->addWidget(toolButton_capture);

        horizontalSpacer_2 = new QSpacerItem(139, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        toolButton_select_image = new QToolButton(widget_7);
        toolButton_select_image->setObjectName(QStringLiteral("toolButton_select_image"));

        horizontalLayout_4->addWidget(toolButton_select_image);


        horizontalLayout_3->addWidget(widget_7);


        verticalLayout_2->addWidget(im_operat);

        widget_5 = new QWidget(Console);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        widget_5->setMaximumSize(QSize(16777215, 40));
        horizontalLayout_6 = new QHBoxLayout(widget_5);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_5 = new QSpacerItem(75, 16, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        label_2 = new QLabel(widget_5);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        label_2->setFont(font);

        horizontalLayout_6->addWidget(label_2);

        horizontalSpacer_3 = new QSpacerItem(78, 16, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        label_3 = new QLabel(widget_5);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        horizontalLayout_6->addWidget(label_3);

        horizontalSpacer_4 = new QSpacerItem(75, 16, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);


        verticalLayout_2->addWidget(widget_5);

        pos_form = new QWidget(Console);
        pos_form->setObjectName(QStringLiteral("pos_form"));
        pos_form->setMinimumSize(QSize(0, 220));
        horizontalLayout_7 = new QHBoxLayout(pos_form);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        tableView = new QTableView(pos_form);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_7->addWidget(tableView);

        tableView_2 = new QTableView(pos_form);
        tableView_2->setObjectName(QStringLiteral("tableView_2"));

        horizontalLayout_7->addWidget(tableView_2);


        verticalLayout_2->addWidget(pos_form);

        cailbrate_operat = new QWidget(Console);
        cailbrate_operat->setObjectName(QStringLiteral("cailbrate_operat"));
        cailbrate_operat->setMinimumSize(QSize(0, 160));
        horizontalLayout_2 = new QHBoxLayout(cailbrate_operat);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        widget_13 = new QWidget(cailbrate_operat);
        widget_13->setObjectName(QStringLiteral("widget_13"));
        verticalLayout_5 = new QVBoxLayout(widget_13);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        toolButton_add_mark = new QToolButton(widget_13);
        toolButton_add_mark->setObjectName(QStringLiteral("toolButton_add_mark"));
        toolButton_add_mark->setMinimumSize(QSize(79, 0));

        verticalLayout_5->addWidget(toolButton_add_mark);

        toolButton_remove_selected_rows = new QToolButton(widget_13);
        toolButton_remove_selected_rows->setObjectName(QStringLiteral("toolButton_remove_selected_rows"));

        verticalLayout_5->addWidget(toolButton_remove_selected_rows);

        toolButton_remove_all_rows = new QToolButton(widget_13);
        toolButton_remove_all_rows->setObjectName(QStringLiteral("toolButton_remove_all_rows"));
        toolButton_remove_all_rows->setMinimumSize(QSize(79, 0));

        verticalLayout_5->addWidget(toolButton_remove_all_rows);


        horizontalLayout_2->addWidget(widget_13);

        widget = new QWidget(cailbrate_operat);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        horizontalLayout_5 = new QHBoxLayout(widget_2);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label = new QLabel(widget_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_5->addWidget(label);

        spinBox_x_offset = new QSpinBox(widget_2);
        spinBox_x_offset->setObjectName(QStringLiteral("spinBox_x_offset"));
        spinBox_x_offset->setMinimum(-100);
        spinBox_x_offset->setMaximum(100);

        horizontalLayout_5->addWidget(spinBox_x_offset);


        verticalLayout_3->addWidget(widget_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        horizontalLayout_8 = new QHBoxLayout(widget_3);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_4 = new QLabel(widget_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_8->addWidget(label_4);

        spinBox_y_offset = new QSpinBox(widget_3);
        spinBox_y_offset->setObjectName(QStringLiteral("spinBox_y_offset"));
        spinBox_y_offset->setMinimum(-100);
        spinBox_y_offset->setMaximum(100);

        horizontalLayout_8->addWidget(spinBox_y_offset);


        verticalLayout_3->addWidget(widget_3);

        widget_4 = new QWidget(widget);
        widget_4->setObjectName(QStringLiteral("widget_4"));

        verticalLayout_3->addWidget(widget_4);


        horizontalLayout_2->addWidget(widget);

        widget_11 = new QWidget(cailbrate_operat);
        widget_11->setObjectName(QStringLiteral("widget_11"));
        widget_11->setMaximumSize(QSize(60, 16777215));
        verticalLayout_6 = new QVBoxLayout(widget_11);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 3, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);

        toolButton_calibrate = new QToolButton(widget_11);
        toolButton_calibrate->setObjectName(QStringLiteral("toolButton_calibrate"));
        QIcon icon;
        icon.addFile(QStringLiteral("images/edit_image_202px_1210732_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_calibrate->setIcon(icon);
        toolButton_calibrate->setIconSize(QSize(50, 50));
        toolButton_calibrate->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_calibrate->setAutoRaise(true);

        verticalLayout_6->addWidget(toolButton_calibrate);

        verticalSpacer_2 = new QSpacerItem(20, 4, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_2);

        toolButton_save = new QToolButton(widget_11);
        toolButton_save->setObjectName(QStringLiteral("toolButton_save"));
        toolButton_save->setMinimumSize(QSize(67, 0));
        QIcon icon1;
        icon1.addFile(QStringLiteral("images/file_save_473px_1173836_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_save->setIcon(icon1);
        toolButton_save->setIconSize(QSize(50, 50));
        toolButton_save->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_save->setAutoRaise(true);

        verticalLayout_6->addWidget(toolButton_save);

        verticalSpacer_3 = new QSpacerItem(20, 3, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_3);

        pushButton_save_image = new QPushButton(widget_11);
        pushButton_save_image->setObjectName(QStringLiteral("pushButton_save_image"));
        pushButton_save_image->setIconSize(QSize(50, 50));

        verticalLayout_6->addWidget(pushButton_save_image);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_4);


        horizontalLayout_2->addWidget(widget_11);


        verticalLayout_2->addWidget(cailbrate_operat);


        horizontalLayout->addWidget(Console);


        verticalLayout->addWidget(mid_str);

        bot_str = new QWidget(PositionCalibrate);
        bot_str->setObjectName(QStringLiteral("bot_str"));
        bot_str->setMinimumSize(QSize(0, 20));
        bot_str->setMaximumSize(QSize(16777215, 35));
        horizontalLayout_14 = new QHBoxLayout(bot_str);
        horizontalLayout_14->setSpacing(0);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(0, 0, 0, 0);
        lineEdit_2 = new QLineEdit(bot_str);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        horizontalLayout_14->addWidget(lineEdit_2);

        lineEdit_3 = new QLineEdit(bot_str);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setMaximumSize(QSize(64, 16777215));

        horizontalLayout_14->addWidget(lineEdit_3);

        lineEdit_4 = new QLineEdit(bot_str);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setMaximumSize(QSize(64, 16777215));

        horizontalLayout_14->addWidget(lineEdit_4);

        horizontalSpacer_8 = new QSpacerItem(750, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_8);


        verticalLayout->addWidget(bot_str);


        retranslateUi(PositionCalibrate);

        QMetaObject::connectSlotsByName(PositionCalibrate);
    } // setupUi

    void retranslateUi(QDialog *PositionCalibrate)
    {
        PositionCalibrate->setWindowTitle(QApplication::translate("PositionCalibrate", "\346\240\207\345\256\232\345\256\232\344\275\215", Q_NULLPTR));
        im_operat->setTitle(QApplication::translate("PositionCalibrate", "\345\233\276\345\203\217\346\223\215\344\275\234", Q_NULLPTR));
        toolButton_capture->setText(QApplication::translate("PositionCalibrate", "\345\233\276\345\203\217\351\207\207\351\233\206", Q_NULLPTR));
        toolButton_select_image->setText(QApplication::translate("PositionCalibrate", "\347\246\273\347\272\277\345\233\276\345\203\217", Q_NULLPTR));
        label_2->setText(QApplication::translate("PositionCalibrate", "\345\233\276\345\203\217\345\235\220\346\240\207", Q_NULLPTR));
        label_3->setText(QApplication::translate("PositionCalibrate", "\346\234\272\346\242\260\345\235\220\346\240\207", Q_NULLPTR));
        toolButton_add_mark->setText(QApplication::translate("PositionCalibrate", "\347\273\230\345\210\266ROI", Q_NULLPTR));
        toolButton_remove_selected_rows->setText(QApplication::translate("PositionCalibrate", "\345\210\240\351\231\244\351\200\211\344\270\255\350\241\214", Q_NULLPTR));
        toolButton_remove_all_rows->setText(QApplication::translate("PositionCalibrate", "\346\270\205\347\251\272\345\210\227\350\241\250", Q_NULLPTR));
        label->setText(QApplication::translate("PositionCalibrate", "x offset", Q_NULLPTR));
        label_4->setText(QApplication::translate("PositionCalibrate", "y offset", Q_NULLPTR));
        toolButton_calibrate->setText(QApplication::translate("PositionCalibrate", "\346\211\213\347\234\274\346\240\207\345\256\232", Q_NULLPTR));
        toolButton_save->setText(QApplication::translate("PositionCalibrate", "\344\277\235\345\255\230\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_save_image->setText(QApplication::translate("PositionCalibrate", "\344\277\235\345\255\230\345\233\276\345\203\217", Q_NULLPTR));
        lineEdit_3->setText(QApplication::translate("PositionCalibrate", "\345\233\276\345\203\217\347\255\233\351\200\211", Q_NULLPTR));
        lineEdit_4->setText(QApplication::translate("PositionCalibrate", "\346\240\207\345\256\232\347\212\266\346\200\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PositionCalibrate: public Ui_PositionCalibrate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSITION_CALIBRATE_H
