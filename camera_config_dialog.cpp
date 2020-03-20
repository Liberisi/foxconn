#include "camera_config_dialog.h"
#include "ui_camera_config_dialog.h"
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <ssvision/ssvision>
#include "baojitai.h"

CameraConfigDialog::CameraConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CameraConfigDialog)
{
    ui->setupUi(this);

    setFixedSize(this->width(), this->height());

    ui->image_window->set_halcon_widget_delegate(this);
}

CameraConfigDialog::~CameraConfigDialog()
{
    delete ui;
}

void CameraConfigDialog::on_paint(HalconWidget *, HWindow &halcon_window)
{
    if (!halcon_window.IsHandleValid())
        return;
    if (halcon_image_.IsInitialized())
    {
        halcon_window.SetPart(0, 0, (Hlong)halcon_image_.Height(), (Hlong)halcon_image_.Width());
        halcon_window.DispImage(halcon_image_);
    }
}
