#ifndef MATERIAL_PRODUCT_DIALOG_H
#define MATERIAL_PRODUCT_DIALOG_H

#include <QDialog>
#include <vector>
#include <string>

namespace Ui {
class MaterialProductDialog;
}

class MaterialProductDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MaterialProductDialog(QWidget *parent = 0);
    ~MaterialProductDialog();

    void set_material(std::string material);
    std::string get_product();

private:
    Ui::MaterialProductDialog *ui;
};

#endif // MATERIAL_PRODUCT_DIALOG_H
