#ifndef IMAGE_PARAMETER_H
#define IMAGE_PARAMETER_H

#include <QDialog>
#include <halconcpp/HalconCpp.h>
#include "halcon_widget.h"
#include <ssvision/ssvision>
#include <QCloseEvent>

using namespace ssvision;

namespace Ui {
class Imageparameter;
}

class LocationConfigDialog : public QDialog,public HalconWidgetDelegate
{
    Q_OBJECT

public:
    explicit LocationConfigDialog(QWidget *parent = 0);
    ~LocationConfigDialog();

    virtual void on_paint(HalconWidget* , HWindow& halcon_widow);
    virtual void on_paint2(HalconWidget* , HWindow& halcon_widow);

protected:

//    void closeEvent(QCloseEvent *event);

public slots:
    void on_camera_buffer_changed(Camera* camera);
    void on_robotic_command(RoboticTCPServer* robotic_tcp_server, QString command);

public:
    typedef struct Material
    {
        float x;
        float y;
        float phi;
        float r1;
        float r2;
    } Material ;


private slots:
    void on_toolButton_choose_image_clicked();

    void on_toolButton_extract_clicked();

    void on_pushButton_save_image_clicked();


    void on_toolButton_clicked();

    void on_pushButton_save_result_image_clicked();

	void on_toolButton_save_product_param_clicked();

//    void on_spinBox_x_offset_valueChanged(int arg1);

//    void on_spinBox_y_offset_valueChanged(int arg1);

//    void on_spinBox_z_offset_valueChanged(int arg1);

//    void on_toolButton_save_product_param_clicked(bool checked);

    void on_toolButton_2_clicked();

    void on_spinBox_x_valueChanged(int arg1);

    void on_spinBox_y_valueChanged(int arg1);

    void on_spinBox_width_valueChanged(int arg1);

    void on_spinBox_height_valueChanged(int arg1);

    void on_doubleSpinBox_phi_valueChanged(double arg1);

private:
    Ui::Imageparameter *ui;
    HalconCpp::HImage  halcon_image_;
    bool editing_;

    bool mark_moving_;
    bool mark_scaling_;
    bool mark_can_moving_;
    bool mark_can_scaling_;
    int mark_x_;
    int mark_y_;
    float mark_phi_;
    int mark_l1_;
    int mark_l2_;
    int mark_cross_r_;
    int mark_mouse_dist_;
    vector<Material> Material_;

    bool support_location_;

	int x_, y_, l1_, l2_;
	double phi_;
	bool found_;

    //float x1_, y1_, x2_, y2_, x3_, y3_;
};

#endif // IMAGE_PARAMETER_H
