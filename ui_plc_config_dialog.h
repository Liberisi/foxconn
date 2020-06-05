/********************************************************************************
** Form generated from reading UI file 'plc_config_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLC_CONFIG_DIALOG_H
#define UI_PLC_CONFIG_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PLCConfigDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_cpu_type;
    QPushButton *pushButton_cpu_type;
    QPushButton *pushButton_open;
    QLabel *label_open_return_value;
    QPushButton *pushButton_read_device;
    QPushButton *pushButton_write_device;
    QLineEdit *lineEdit_device_read;
    QLineEdit *lineEdit_device_write;
    QLabel *label_read_value_1;
    QLabel *label_read_value_2;
    QLineEdit *lineEdit_device_write_value;

    void setupUi(QDialog *PLCConfigDialog)
    {
        if (PLCConfigDialog->objectName().isEmpty())
            PLCConfigDialog->setObjectName(QStringLiteral("PLCConfigDialog"));
        PLCConfigDialog->resize(599, 373);
        buttonBox = new QDialogButtonBox(PLCConfigDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(PLCConfigDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(180, 90, 72, 15));
        label_cpu_type = new QLabel(PLCConfigDialog);
        label_cpu_type->setObjectName(QStringLiteral("label_cpu_type"));
        label_cpu_type->setGeometry(QRect(290, 90, 72, 15));
        pushButton_cpu_type = new QPushButton(PLCConfigDialog);
        pushButton_cpu_type->setObjectName(QStringLiteral("pushButton_cpu_type"));
        pushButton_cpu_type->setGeometry(QRect(40, 80, 93, 28));
        pushButton_open = new QPushButton(PLCConfigDialog);
        pushButton_open->setObjectName(QStringLiteral("pushButton_open"));
        pushButton_open->setGeometry(QRect(40, 30, 93, 28));
        label_open_return_value = new QLabel(PLCConfigDialog);
        label_open_return_value->setObjectName(QStringLiteral("label_open_return_value"));
        label_open_return_value->setGeometry(QRect(290, 40, 121, 16));
        pushButton_read_device = new QPushButton(PLCConfigDialog);
        pushButton_read_device->setObjectName(QStringLiteral("pushButton_read_device"));
        pushButton_read_device->setGeometry(QRect(40, 130, 93, 28));
        pushButton_write_device = new QPushButton(PLCConfigDialog);
        pushButton_write_device->setObjectName(QStringLiteral("pushButton_write_device"));
        pushButton_write_device->setGeometry(QRect(40, 170, 93, 28));
        lineEdit_device_read = new QLineEdit(PLCConfigDialog);
        lineEdit_device_read->setObjectName(QStringLiteral("lineEdit_device_read"));
        lineEdit_device_read->setGeometry(QRect(170, 130, 113, 21));
        lineEdit_device_write = new QLineEdit(PLCConfigDialog);
        lineEdit_device_write->setObjectName(QStringLiteral("lineEdit_device_write"));
        lineEdit_device_write->setGeometry(QRect(170, 180, 113, 21));
        label_read_value_1 = new QLabel(PLCConfigDialog);
        label_read_value_1->setObjectName(QStringLiteral("label_read_value_1"));
        label_read_value_1->setGeometry(QRect(310, 130, 121, 16));
        label_read_value_2 = new QLabel(PLCConfigDialog);
        label_read_value_2->setObjectName(QStringLiteral("label_read_value_2"));
        label_read_value_2->setGeometry(QRect(440, 130, 121, 16));
        lineEdit_device_write_value = new QLineEdit(PLCConfigDialog);
        lineEdit_device_write_value->setObjectName(QStringLiteral("lineEdit_device_write_value"));
        lineEdit_device_write_value->setGeometry(QRect(310, 180, 113, 21));

        retranslateUi(PLCConfigDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), PLCConfigDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PLCConfigDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(PLCConfigDialog);
    } // setupUi

    void retranslateUi(QDialog *PLCConfigDialog)
    {
        PLCConfigDialog->setWindowTitle(QApplication::translate("PLCConfigDialog", "PLC", Q_NULLPTR));
        label->setText(QApplication::translate("PLCConfigDialog", "CPU\347\261\273\345\236\213", Q_NULLPTR));
        label_cpu_type->setText(QApplication::translate("PLCConfigDialog", "\346\234\252\347\237\245", Q_NULLPTR));
        pushButton_cpu_type->setText(QApplication::translate("PLCConfigDialog", "\350\216\267\345\217\226CPU", Q_NULLPTR));
        pushButton_open->setText(QApplication::translate("PLCConfigDialog", "\346\211\223\345\274\200", Q_NULLPTR));
        label_open_return_value->setText(QApplication::translate("PLCConfigDialog", "Open Return", Q_NULLPTR));
        pushButton_read_device->setText(QApplication::translate("PLCConfigDialog", "\350\257\273\350\256\276\345\244\207", Q_NULLPTR));
        pushButton_write_device->setText(QApplication::translate("PLCConfigDialog", "\345\206\231\350\256\276\345\244\207", Q_NULLPTR));
        label_read_value_1->setText(QApplication::translate("PLCConfigDialog", "Read Value 1", Q_NULLPTR));
        label_read_value_2->setText(QApplication::translate("PLCConfigDialog", "Read Value 2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PLCConfigDialog: public Ui_PLCConfigDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLC_CONFIG_DIALOG_H
