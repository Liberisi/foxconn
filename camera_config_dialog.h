#ifndef CAMERACONFIGDIALOG_H
#define CAMERACONFIGDIALOG_H

#include <QDialog>
#include <halconcpp/HalconCpp.h>
#include "halcon_widget.h"

namespace Ui {
class CameraConfigDialog;
}

class CameraConfigDialog : public QDialog,public HalconWidgetDelegate

{
    Q_OBJECT

public:
    explicit CameraConfigDialog(QWidget *parent = 0);
    ~CameraConfigDialog();

    virtual void on_paint(HalconWidget* , HWindow& halcon_widow);

private:
    Ui::CameraConfigDialog *ui;
    HalconCpp::HImage  halcon_image_;
};

#endif // CAMERACONFIGDIALOG_H
