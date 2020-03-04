#include "plc_config_dialog.h"
#include "ui_plc_config_dialog.h"
#include "baojitai.h"

PLCConfigDialog::PLCConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PLCConfigDialog), plc_utltype_(NULL)
{
    ui->setupUi(this);
    ui->label_open_return_value->setText(QString::fromUtf8(""));
}

PLCConfigDialog::~PLCConfigDialog()
{
    delete ui;
}

void PLCConfigDialog::set_plc_act_utl_type(ActUtlTypeLib::ActUtlType *plc_utltype)
{
    plc_utltype_ = plc_utltype;
}

void PLCConfigDialog::on_pushButton_open_clicked()
{
    if (plc_utltype_)
    {

    }
//    long value;
//	PlcOle* plc = Baojitai::instance()->plc();
//    if (plc && plc->open(&value))
//    {
//        string value_str = to_string(value);
//        ui->label_open_return_value->setText(value_str.c_str());
//    }
//    else
//    {
//        ui->label_open_return_value->setText(QString::fromUtf8("打开失败"));
//    }
}

void PLCConfigDialog::on_pushButton_cpu_type_clicked()
{
    if (plc_utltype_)
    {
    QString szCpuName;
    int lCpuType;
    int iRet=plc_utltype_->GetCpuType(szCpuName,lCpuType);
    qDebug("return:%x szCpuName:%s lCpuType:%d",iRet,qPrintable(szCpuName),lCpuType);

    //显示CPU型号
    ui->label_cpu_type->setText(szCpuName);
    }
}

void PLCConfigDialog::on_pushButton_read_device_clicked()
{
    if (plc_utltype_)
    {
        int value;
        QString device_name = ui->lineEdit_device_read->text();
        int iRet= plc_utltype_->GetDevice(device_name, value);
        string device_value = ::to_string(value);
        ui->label_read_value_1->setText(device_value.c_str());
    }
}

void PLCConfigDialog::on_pushButton_write_device_clicked()
{
    if (plc_utltype_)
    {
        int device_value = ui->lineEdit_device_write_value->text().toInt();
        QString device_name = ui->lineEdit_device_read->text();
        int iRet = plc_utltype_->SetDevice(device_name, device_value);
    }
}
