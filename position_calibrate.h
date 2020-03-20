#ifndef POS_CALIBRATE_H
#define POS_CALIBRATE_H

#include <QDialog>
#include <vector>
#include <QTableView>
#include <QItemDelegate>
#include <QStandardItemModel>
#include <halconcpp/HalconCpp.h>
#include "halcon_widget.h"
#include "baojitai.h"

using namespace std;

namespace Ui {
class PositionCalibrate;
}

class PositionCalibrate : public QDialog, public HalconWidgetDelegate

{
    Q_OBJECT

public:
	typedef struct Ellipse
	{
		float x;
		float y;
		float r1;
		float r2;
		float phi;
	} Ellipse;

public:
    explicit PositionCalibrate(QWidget *parent = 0);
    ~PositionCalibrate();

    virtual void on_paint(HalconWidget*, HWindow& halcon_widow);
	virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    bool extract_current_marker();

public slots:
    void on_tableview_selection_changed(QItemSelection selected, QItemSelection deselected);
    void on_camera_buffer_changed(Camera* camera);
    void on_robotic_command(RoboticTCPServer* robotic_tcp_server, QString command);

private slots:

    void on_toolButton_select_image_clicked();

    void on_toolButton_add_mark_clicked();

    void on_toolButton_remove_selected_rows_clicked();

    void on_toolButton_remove_all_rows_clicked();

    void on_toolButton_calibrate_clicked();

    void on_toolButton_save_clicked();

    void on_toolButton_capture_clicked();

    void on_pushButton_save_image_clicked();

    void on_spinBox_x_offset_valueChanged(int arg1);

    void on_spinBox_y_offset_valueChanged(int arg1);

private:
    Ui::PositionCalibrate *ui;
    QStandardItemModel item_model_markers_;
    QStandardItemModel item_model_editable_markers_;

    HalconCpp::HImage  halcon_image_;
    HHomMat2D          hommat2d_;
    bool editing_;
    bool mark_moving_;
    bool mark_scaling_;
    bool mark_can_moving_;
    bool mark_can_scaling_;
    int mark_x_;
    int mark_y_;
    int mark_r_;
	int mark_cross_r_;
	int mark_mouse_dist_; 
	vector<Ellipse> ellipses_;

    bool calibrate_finish_;
};

#endif // POS_CALIBRATE_H
