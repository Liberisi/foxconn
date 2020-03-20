#ifndef FRAME_DIALOG_H
#define FRAME_DIALOG_H

#include <QDialog>
#include <halconcpp/HalconCpp.h>
#include "halcon_widget.h"
#include <ssvision/ssvision>
#include "halcon_tools.h"

using namespace HalconCpp;
using namespace ssvision;

namespace Ui {
class Frame_Dialog;
}

class Frame_Dialog : public QDialog,public HalconWidgetDelegate
{
    Q_OBJECT

public:
    explicit Frame_Dialog(QWidget *parent = 0);
    ~Frame_Dialog();

    virtual void on_paint(HalconWidget* , HWindow& halcon_widow);

public slots:
    void on_camera_buffer_changed(Camera* camera);

private slots:
    void on_toolButton_select_image_clicked();

    void on_pushButton_clicked();

    void on_toolButton_capture_clicked();

    void on_spinBox_x_valueChanged(int arg1);

    void on_spinBox_y_valueChanged(int arg1);

    void on_spinBox_w_valueChanged(int arg1);

    void on_spinBox_h_valueChanged(int arg1);

    void on_spinBox_h2_valueChanged(int arg1);

    void on_pushButton_save_config_clicked();

    void on_spinBox_threshold_area_valueChanged(int arg1);

    void on_pushButton_detect_clicked();

    void on_spinBox_w2_valueChanged(int arg1);

    void on_spinBox_lx_valueChanged(int arg1);

    void on_spinBox_ly_valueChanged(int arg1);

    void on_spinBox_lw_valueChanged(int arg1);

    void on_spinBox_lh_valueChanged(int arg1);

    void on_spinBox_rx_valueChanged(const QString &arg1);

    void on_spinBox_ry_valueChanged(int arg1);

    void on_spinBox_rw_valueChanged(int arg1);

    void on_spinBox_rh_valueChanged(int arg1);

    void on_pushButton_2_clicked();

private:
    Ui::Frame_Dialog *ui;

    HImage  halcon_image_;
    bool detect_finish_;
    bool disk_ok_;
    bool found_left_;
    HRegion left_white_area_;
    bool found_right_;
    HRegion right_white_area_;
};

#endif // FRAME_DIALOG_H
