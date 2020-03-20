#include "material_product_dialog.h"
#include "ui_material_product_dialog.h"
#include <string>
#include <product.h>

using namespace std;

MaterialProductDialog::MaterialProductDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MaterialProductDialog)
{
    ui->setupUi(this);

    ProductManager* product_manager = ProductManager::instance();
    vector<string> product_name_list = product_manager->product_name_list();
    foreach(string product_name, product_name_list)
    {
        ui->comboBox_product ->addItem(product_name.c_str());
        //ui->switch_model->addItem(product_name.c_str());
    }

}

MaterialProductDialog::~MaterialProductDialog()
{
    delete ui;
}


void MaterialProductDialog::set_material(string material)
{
    ui->label_material->setText(material.c_str());
}

std::string MaterialProductDialog::get_product()
{
    QString product = ui->comboBox_product->currentText();
    return product.toStdString();
}
