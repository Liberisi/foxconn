#ifndef IMAGE_PARAMETER_H
#define IMAGE_PARAMETER_H

#include <QDialog>
#include <halconcpp/HalconCpp.h>
#include "halcon_widget.h"
#include <ssvision/ssvision>

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

public slots:
    void on_camera_buffer_changed(Camera* camera);
    void on_robotic_command(RoboticTCPServer* robotic_tcp_server, QString command);

private slots:
    void on_toolButton_choose_image_clicked();

    void on_toolButton_extract_clicked();

    void on_pushButton_save_image_clicked();

    void on_toolButton_save_product_param_clicked();

    void on_toolButton_clicked();

    void on_pushButton_save_result_image_clicked();

private:
    Ui::Imageparameter *ui;
    HalconCpp::HImage  halcon_image_;
    bool editing_;

	int x_, y_, l1_, l2_;
	double phi_;
	bool found_;

    //float x1_, y1_, x2_, y2_, x3_, y3_;
};

#endif // IMAGE_PARAMETER_H
