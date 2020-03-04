#include "save_config_dialog.h"
#include "ui_config_save.h"

SaveConfigDialog::SaveConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Configsave)
{
    ui->setupUi(this);
}

SaveConfigDialog::~SaveConfigDialog()
{
    delete ui;
}
