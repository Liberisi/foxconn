#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <string>
#include <QtSerialPort/QSerialPort>
#include <QLabel>
#include <QTimer>
#include <QLineEdit>
#include <QStandardItemModel>
#include <ssvision/ssvision>
#include "reading_code_config.h"
#include "product.h"
#include "halcon_widget.h"
#include "baojitai.h"
#include "ActUtlType.h"



using namespace  std;
using namespace ssvision;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public HalconWidgetDelegate
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static void resetUI(QWidget* pWidget);

//    static float getScale();


protected :
    void closeEvent(QCloseEvent *event);
    virtual void on_paint(HalconWidget * halconwidget, HWindow& halcon_widow);

private slots:
    void on_toolButton_3_windowIconTextChanged(const QString &iconText);

    void on_help_btn_clicked();

    void on_sty_btn_clicked();

    void on_main_btn_clicked();

    void on_Pc_btn_clicked();

    void on_cam_btn_clicked();

    void on_qr_btn_clicked();

    void on_sav_btn_clicked();

    void on_label_2_linkActivated(const QString &link);

    void timeUpdate();

    void on_pro_btn_clicked();

    void on_toolButton_change_product_clicked();

    void on_toolButton_change_clicked();


    void on_toolButton_create_clicked();

    void on_toolButton_del_clicked();

    void on_toolButton_start_clicked();

    void on_toolButton_stop_clicked();

    void on_toolButton_reset_clicked();

    void on_commun_btn_clicked();

    void on_plc_btn_clicked();

    void on_Imparam_btn_clicked();

    void on_frame_btn_clicked();

    void on_toolButton_9_clicked();

    void on_toolButton_send_undo_0_clicked();

    void on_checkBox_close_location_toggled(bool checked);

    void on_checkBox_close_tid_toggled(bool checked);

    void on_checkBox_close_sn_toggled(bool checked);

    void on_checkBox_close_fid_toggled(bool checked);

    void on_pushButton_send_AAAAAA_clicked();

    void on_checkBox_offline_toggled(bool checked);

    void on_checkBox_toggled(bool checked);

    void on_pushButton_save_line_station_info_clicked();

    void on_pushButton_clear_ng_table_clicked();

    void on_pushButton_export_ng_table_clicked();

    void on_pushButton_select_scan_dir_clicked();

    void on_lineEdit_scan_tid_returnPressed();

    void on_timer_scan_dir();

    void on_toolButton_information_xlsx_clicked();
    
    void on_pushButton_refresh_advance_ng_list_clicked();

    void on_toolButton_romove_advance_product_ng_clicked();

public slots:
    void on_serial_sinal(const string& device_name);
    void on_serial_port_status_signal(SerialPort* serial_port);
    void on_robotic_status_change_signal(RoboticTCPServer* robotic_tcp_server);
	void on_plc_status_change_signal();
    void on_camera_status_change_signal(Camera* camera);
    void on_camera_buffer_changed(Camera* camera);
    void on_running_status_change();
    void on_signal_plc_repair_mode_change();
    void on_signal_plc_reset();
    void on_advanced_device_count_change();
    void on_fid_cmc_socket_status_change();
    void on_location_finish();
    void on_reading_code_finish();
    void on_check_frame_finish();
    void on_prodoct_change_signal(Product* product);
    void on_signal_product_arrive();
    void on_signal_product_info(QString info);
    // on ng signal
    void on_signal_location_ng();
    void on_signal_tid_ng(QString tid, QString reason);
    void on_signal_sn_ng(QString sn, QString reason, QString tid);
    void on_signal_fid_ng(QString fid, QString reason);

private:
    void on_camera_reading_code_buffer_changed();
    void on_camera_location_buffer_changed();
    void on_camera_check_frame_buffer_changed();
    void draw_camera_reading_code(HWindow& window);
    void draw_camera_location(HWindow& window);
    void draw_camera_check_frame(HWindow& window);
    void reload_advanced_device_ng_table();


    Ui::MainWindow *ui;
    QTimer timer_;
    QLabel *currentTimeLabel ;
    // reading_code_serial_port_status__;
    QLineEdit *reading_code_serial_port_status_lineedit;
    QLineEdit *reading_code_serial_port_status_lineedit2;
    QLineEdit *reading_code_serial_port_status_lineedit3;
    QLineEdit *fid_cmc_socket_status_lineedit;

    QLineEdit *qr_camera_status_lineedit;
    QLineEdit *pos_camera_status_lineedit;
    QLineEdit *frame_camera_status_lineedit;
	QLineEdit *robotic_status_lineEdit;
	QLineEdit *plc_status_lineedit;
    QLineEdit *running_status_lineEdit;
    QLabel* advanced_device_count_label;

    HImage image_location_;
    HImage image_reading_code_;
    HImage image_check_frame_;

    bool location_result_updated_;
    BaojitaiLocationResult location_result_;

    bool reading_code_result_updated_;
    bool reading_code_success_;
	string tid_;
	string sn_;
	HRegion board_bar_code_region_;
	HRegion product_bar_code_region_;
	HXLD product_mat_code_xld_;

    bool check_frame_result_updated_;
    BaojitaiCheckFrameResult check_frame_result_;

    ActUtlTypeLib::ActUtlType plc_utltype_;

	ActUtlTypeLib::ActUtlType* plc_utl_;

    QStandardItemModel info_list_item_model_;
    QStandardItemModel ng_list_item_model_;
    QStandardItemModel advanced_device_ng_item_model_;

};

#endif // MAINWINDOW_H
