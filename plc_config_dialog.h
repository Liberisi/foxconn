#ifndef PLCCONFIGDIALOG_H
#define PLCCONFIGDIALOG_H

#include <QDialog>
#include "ActUtlType.h"

namespace Ui {
class PLCConfigDialog;
}

class PLCConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PLCConfigDialog(QWidget *parent = 0);
    ~PLCConfigDialog();

    void set_plc_act_utl_type(ActUtlTypeLib::ActUtlType* plc_utltype);

private slots:
    void on_pushButton_open_clicked();

    void on_pushButton_cpu_type_clicked();

    void on_pushButton_read_device_clicked();

    void on_pushButton_write_device_clicked();

private:
    Ui::PLCConfigDialog *ui;
   ActUtlTypeLib::ActUtlType* plc_utltype_;
   //  ActUtlTypeLib::ActUtlType myactive;
};

#endif // PLCCONFIGDIALOG_H
