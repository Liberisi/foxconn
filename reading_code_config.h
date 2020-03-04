#ifndef QR_CONFIG_H
#define QR_CONFIG_H

#include <QDialog>
#include <string>
#include <halconcpp/HalconCpp.h>
#include <halcon_widget.h>
#include "baojitai.h"

using namespace std;
using namespace HalconCpp;

namespace Ui {
class ReadingCodeConfigDialog;
}

class ReadingCodeConfigDialog : public QDialog, public HalconWidgetDelegate
{
    Q_OBJECT

public:
    explicit ReadingCodeConfigDialog(QWidget *parent = 0);
    ~ReadingCodeConfigDialog();

    virtual void on_paint(HalconWidget* widget, HWindow &halcon_window);

private slots:

    void on_connect_btn_clicked();

    void on_senddata_btn_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_reading_code_clicked();

    void on_product_change_signal(Product* product);

    void on_toolButton_capture_clicked();

    void on_toolButton_save_serial_config_clicked();

    void on_toolButton_save_clicked();

    void on_pushButton_save_image_clicked();

    void on_radioButton_product_mat_code_toggled(bool checked);

    void on_radioButton_product_bar_code_toggled(bool checked);

    void on_pushButton_save_result_image_clicked();

public slots:
    void on_camera_buffer_changed(Camera* camera);
    void on_serial_port_read_signal(SerialPort* serial_port, QString message);

private:
    Ui::ReadingCodeConfigDialog *ui;
    HImage halcon_image_;
    int reading_code_duration_;
    vector<string> bar_codes_;
    vector<HRegion> bar_code_regions_;
    vector<string> mat_codes_;
    vector<HXLD> mat_code_xlds_;

signals:
    void SignalSerialPort(const string& device_name);
};

#endif // QR_CONFIG_H
