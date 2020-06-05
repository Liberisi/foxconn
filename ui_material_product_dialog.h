/********************************************************************************
** Form generated from reading UI file 'material_product_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATERIAL_PRODUCT_DIALOG_H
#define UI_MATERIAL_PRODUCT_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MaterialProductDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_material;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label_4;
    QComboBox *comboBox_product;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *MaterialProductDialog)
    {
        if (MaterialProductDialog->objectName().isEmpty())
            MaterialProductDialog->setObjectName(QStringLiteral("MaterialProductDialog"));
        MaterialProductDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(MaterialProductDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(MaterialProductDialog);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        label_material = new QLabel(MaterialProductDialog);
        label_material->setObjectName(QStringLiteral("label_material"));

        verticalLayout->addWidget(label_material);

        label_5 = new QLabel(MaterialProductDialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        label_3 = new QLabel(MaterialProductDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(MaterialProductDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        comboBox_product = new QComboBox(MaterialProductDialog);
        comboBox_product->setObjectName(QStringLiteral("comboBox_product"));

        verticalLayout->addWidget(comboBox_product);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(MaterialProductDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(MaterialProductDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), MaterialProductDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), MaterialProductDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(MaterialProductDialog);
    } // setupUi

    void retranslateUi(QDialog *MaterialProductDialog)
    {
        MaterialProductDialog->setWindowTitle(QApplication::translate("MaterialProductDialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("MaterialProductDialog", "\345\275\223\345\211\215\346\226\231\345\217\267", Q_NULLPTR));
        label_material->setText(QString());
        label_5->setText(QString());
        label_3->setText(QApplication::translate("MaterialProductDialog", "\351\200\211\346\213\251\345\205\263\350\201\224\344\272\247\345\223\201", Q_NULLPTR));
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MaterialProductDialog: public Ui_MaterialProductDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATERIAL_PRODUCT_DIALOG_H
