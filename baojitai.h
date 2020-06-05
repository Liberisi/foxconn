#ifndef BAOJITAI_H
#define BAOJITAI_H

#include <QObject>
#include <string>
#include <halconcpp\HalconCpp.h>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/ml.hpp>
#include "ActUtlType.h"
#include <ssvision/ssvision>
#include <product.h>
#include "fid_cmc_socket.h"
#include "datetime_filesystem.h"
#include "item_information_center.h"
#include "material_product_map.h"
#include "fidparser.h"
#include "frameparam.h"
#include "msleepsetting.h"

using namespace std;
using namespace ssvision;
using namespace HalconCpp;

typedef struct BaojitaiLocationResult
{
    bool find_rect;
    bool success;
    double x;
    double y;
    double phi;
    double l1;
    double l2;
    double width_mm;
    double height_mm;
} BaojitaiLocationResult;

typedef struct BaojitaiCheckFrameResult
{
    bool is_disk_ok;
    bool is_found_left;
    bool is_found_right;
} BaojitaiCheckFrameResult;

/**
 * @brief The Baojitai class
 * Baojitai 会管理 set_xxx 对应的类指针
 */
class Baojitai : public QObject, SerialPortDelegate, RoboticTCPServerDelegate, CameraDelegate, ItemInformationCenterDelegate, FidCMCSocketDelegate
{
public:
    Q_OBJECT
public:
    static Baojitai* instance();

private:
    Baojitai();

public:
    bool material_exists(string material, string& product);
    void insert_material_product(string material, string product);
    string scan_dir() {return scan_dir_;}
    string line_name() { return line_name_;}
    string station_name() { return station_name_;}
    string station_id() { return station_id_;}
    string frame_hog_file_path();
    string frame_side_hand_hog_file_path();
    string date_file_path(QDateTime date_time, string file_name);
    void save_line_station_info(string scan_dir, string line_name, string station_name, string station_id);
    void read_line_station_info();
    void save_fid_cmc_ip_port(string ip, int port);
    void read_fid_cmc_ip_port(string& ip, int& port);
    void remove_data_files(QDate date);

    void setup();
    void shutdown();
	
	void start();
    // 强制恢复从tid开始轮流发码
    void reset();
    // 返修模式 从sn开始轮流发码
    void repair_mode_reset();
	bool is_running() { return is_running_; }
	void stop();
    void on_user_send_undo();
    void on_user_send_AAAAAA();

    bool is_close_location();
    bool is_close_tid();
    bool is_close_sn();
    bool is_close_fid();
    void set_close_location(bool close);
    void set_close_tid(bool close);
    void set_close_sn(bool close);
    void set_close_fid(bool close);

    int robotic_x_offset(){return robotic_x_offset_;}
    int robotic_y_offset(){return robotic_y_offset_;}
    int robotic_rz_offset(){return robotic_rz_offset_;}
    void set_robotic_x_offset(int x_offset);
    void set_robotic_y_offset(int y_offset);
    void set_robotic_rz_offset(int rz_offset);

    // 设备运行时不能改变返修模式
    bool set_repair_mode(bool repair_mode);
    bool is_repair_mode(){return repair_mode_;}
    //void set_receive_send_fid(bool receive_send_fid) {receive_send_fid_ = receive_send_fid;}

    void set_offline_mode(bool offline_mode) {offline_mode_ = offline_mode;}
    bool is_offline_mode(){return offline_mode_;}

    Camera* camera_check_frame() { return camera_check_frame_;}
    Camera* camera_location() { return camera_location_;}
    Camera* camera_reading_code() { return camera_reading_code_;}
    void set_camera_reading_code(Camera* camera);
    void set_camera_location(Camera* camera);
    void set_camera_check_frame(Camera* camera);
    void camera_reading_code_buffer(const unsigned char** p_buffer, int *width, int* height);
    void camera_location_buffer(const unsigned char** p_buffer, int *width, int* height);
    void camera_check_frame_buffer(const unsigned char** p_buffer, int *width, int* height);
    void location_result(BaojitaiLocationResult& result) { result = location_result_;}
	void reading_code_result(bool &success, string& tid, string& sn, HRegion &board_bar_code_region, HRegion &product_bar_code_region, HXLD& product_mat_code_xld);
    void check_frame_result(BaojitaiCheckFrameResult& result) { result = check_frame_result_;}
    int location_duration() { return location_duration_;}
    int reading_code_duration() { return reading_code_duration_;}
    int check_frame_duration() { return check_frame_duration_;}
    QDateTime capture_time_location() { return location_time_;}
    QDateTime capture_time_reading_code() { return reading_code_time_;}
    QDateTime capture_time_check_frame() { return check_frame_time_;}

    HHomMat2D image_to_robotic_matrix(){return image_to_robotic_coordinates_matrix_;}
	void set_image_to_robotic_matrix(HHomMat2D hommat);

//    HMetrologyModel image_to_MetrologyHandle(){return MetrologyHandle;}
//    void set_image_to_MetrologyHandle(HMetrologyModel HMetrologyHandle);

	SerialPort* serial_port_sending_code() { return sp_sending_code_; }
    SerialPort* serial_port_repair_mode() { return serial_port_repair_mode_;}
    SerialPort* serial_port_read_fid() { return sp_read_fid_;}
    void set_serial_port_sending_code(SerialPort* serial_port);
    void set_serial_port_repair_mode(SerialPort* serial_port);
    void set_serial_port_reading_fid(SerialPort* serial_port);
    void save_serial_port_sending_code_config();
    void save_serial_port_repair_mode_config();
    void save_serial_port_check_frame_config();

    void connect_fid_cmc_tcp_server(string ip, int port);

//#ifdef DEBUG
    void on_read_fid_data(const char* data, int length);
//#endif

public:
    Product *current_product()  {return current_product_;}
    void set_current_product(Product* product);

    RoboticTCPServer* robotic_tcp_server() {return robotic_tcp_server_;}
    void send_product_information_to_robotic(float x, float y, float delta_z, float rotation, float vertical_length);

	ActUtlTypeLib::ActUtlType* plc_act_utl() { return plc_act_utl_; }
	void set_plc_act_utl(ActUtlTypeLib::ActUtlType* plc_act_utl);
	void open_plc_act_utl();
	void send_location_result_to_plc();
    //void send_reading_code_result_to_plc();
	void send_check_frame_result_to_plc();

    vector<string> advanced_device_ip_list();
    ItemInformationCenter* item_center() { return item_center_;}

    bool is_fid_cmc_socket_connected() { return fid_cmc_socket_.is_connected();}
    void test_emit_tid_ng(QString tid, QString reason);
    void test_emit_sn_ng(QString sn, QString reason, QString tid);

private:
    void try_sending_tid();
    void try_sending_fid();
    void try_sending_undo();
    void send_sn(SerialPort* sp);
    void send_fid(SerialPort* sp);
    void on_read_fid(string fid);
    void log_tid_sn_fid();

signals:
    void signal_send_tid(SerialPort* sp);
    void signal_send_fid(SerialPort* sp);
    void signal_repair_mode_send_sn();
    void signal_check_fid_board_leaving();
    void signal_check_plc_camera_control();
    void signal_post_process_location_image();
    void signal_post_process_reading_code_image();
    void signal_post_process_check_frame_image();
    void signal_reset();

private slots:
    void on_signal_check_fid_board_leaving();
    void on_signal_check_plc_camera_control();
    void on_signal_send_tid(SerialPort* sp);
    void on_signal_send_fid(SerialPort* sp);
    void on_signal_repair_mode_send_sn();
    void on_signal_post_process_location_image();
    void on_signal_post_process_reading_code_image();
    void on_signal_post_process_check_frame_image();
    void on_signal_reset();

private slots:
    void on_timer_check_fid_board_leaving();
    void on_timer_check_plc_camera_control();
    void on_timer_try_sending_sn();
    void on_timer_send_undo_postfix();
    void on_timer_check_tid_result();
    void on_timer_check_sn_result();
    void on_waiting_fid_timeout();
    void on_timer_check_fid_result();
    void on_receive_fid_ok_or_ng();

signals:

    // 设备状态信号
    void signal_camera_status_change(Camera* camera);
    void signal_camera_buffer_updated(Camera* camera);
    void signal_location_finish();
    void signal_reading_code_finish();
    void signal_check_frame_finish();
    void signal_serial_port_status_change(SerialPort* serial_port);
    void signal_serial_port_read(SerialPort* serial_port, QString message);
    void signal_product_change(Product* product);
    void signal_robotic_status_change(RoboticTCPServer* robotic_tcp_server);
    void signal_robotic_command(RoboticTCPServer* robotic_tcp_server, QString command);
	void signal_plc_status_change();
    void signal_plc_repair_mode_change();
    void signal_plc_reset();
    void signal_running_status_change();
    void signal_advanced_device_count_change();
    void signal_fid_cmc_socket_status_change();
    void signal_product_arrive();
    void signal_product_info(QString info);

    // ng 信号
    void signal_location_ng();
    void signal_tid_ng(QString tid, QString reason);
    void signal_sn_ng(QString sn, QString reason, QString tid);
    void signal_fid_ng(QString fid, QString reason);

private:
    // 相机
    void setup_cameras();
    void shutdown_cameras();

    // 串口
    void setup_serial_port_devices();
    void shutdown_serial_port_devices();

    // 日志文件
    void setup_loggers();
    void shutdown_loggers();

    // 机械臂
    void setup_robotic_tcp_server();
    void shutdown_robotic_tcp_server();

public:

    // CameraDelegate
    virtual void on_camera_open(Camera* camera);
    virtual void on_camera_close(Camera* camera);
    virtual void on_camera_capture(Camera* camera, int width, int height, void* data, PixelFormat pixel_format);
    // SerialPortDelegate
    virtual void on_serial_port_open(SerialPort* serial_port);
    virtual void on_serial_port_close(SerialPort* serial_port);
    virtual void on_serial_port_read(SerialPort* serial_port, const char* data, int size);
    // RoboticTCPServerDelegate
    virtual void on_robotic_connected(RoboticTCPServer* robotic_server);
    virtual void on_robotic_disconnected(RoboticTCPServer* robotic_server);
    virtual void on_robotic_command(RoboticTCPServer* robotic_server, void* data, int size);
    // ItemInformationCenterDelegate
    virtual void on_advanced_device_connect(ItemInformationCenter* info_center, const string& ip_str);
    virtual void on_advanced_device_disconnect(ItemInformationCenter* info_center, const string& ip_str);
	virtual void on_advanced_device_item_information(const string& name, bool is_ng, const string& ng_reason, const string &station, const string &datatime); ///
    // Fid CMC Socket Delegate
    virtual void on_fid_cmc_socket_connected(FidCMCSocket* fid_cmc_socket);
    virtual void on_fid_cmc_socket_disconnected(FidCMCSocket* cmc_client);
    virtual void on_fid_cmc_socket_read_bytes(const QByteArray& bytes);
    virtual void on_fid_cmc_socket_read_fid(const string fid);

private:
    Camera* camera_reading_code_;        // 读码相机
    Camera* camera_location_;            // 定位相机
    Camera* camera_check_frame_;         // 支架检测相机
    SerialPort* sp_sending_code_;    // 读码串口
    SerialPort* serial_port_repair_mode_;     // 返修串口
    SerialPort* sp_read_fid_;     // 支架检测串口
    // RFid CMC Client
    FidCMCSocket fid_cmc_socket_;
    // PLC
	ActUtlTypeLib::ActUtlType* plc_act_utl_;
    // 机械臂
    RoboticTCPServer* robotic_tcp_server_;
    // 日志
    Logger* baojitai_logger_;
	Logger* tid_sn_fid_logger_;
    Product* current_product_; //产品

private:
	void log_camera_status(Camera* camera, const string& camera_name);

    void update_camera_location_buffer(void* data, int width, int height);
    void update_camera_check_frame_buffer(void* data, int width, int height);
    void update_camera_reading_code_buffer(void* data, int width, int height);
    void process_location_image(void* data, int width, int height);
    void process_reading_code_image(void* data, int width, int height);


    void process_check_frame_image(void* data, int width, int height);
    void post_process_location_image();
    void post_process_reading_code_image();
    void repair_mode_post_process_reading_code_image();
    void post_process_check_frame_image();

    void set_plc(const string& device, int value);
    void get_plc(const string& device, int& value);

    QDateTime location_time_;
    int location_duration_;
    BaojitaiLocationResult location_result_;

    QDateTime reading_code_time_;
    int reading_code_duration_;
    // 需通过 board_codes_, matrix_codes_ 以及当前产品配置判断是否读码成功
    bool board_code_success_;
	bool product_code_success_;
	HRegion board_bar_code_region_;
	HXLD product_mat_code_xld_;
	HRegion product_bar_code_region_;

	// 读码成功不一定有tid， sn，因为读码成功很可能是因为用户设置不需要读码
	// 在读码图像处理开始之前，把 tid sn fid 清空
	string tid_;   // 符合要求的 board_code
	int check_tid_result_count_;
	bool is_tid_ok_;
	string sn_;    // 符合要求的 product code
	int check_sn_result_count_;
	bool is_sn_ok_;
    string fid_;
    //char fid_[32];
    //unsigned int fid_length_;
    bool is_waiting_fid_;
    bool wait_fid_send_;
    string new_tid_;
    string new_sn_;
	int check_fid_result_count_;
	bool is_fid_ok_;

	QDateTime check_frame_time_;
	int check_frame_duration_;
	bool check_frame_success_;
    BaojitaiCheckFrameResult check_frame_result_;

    int image_reading_code_buffer_width_;
    int image_reading_code_buffer_height_;
    const unsigned char* image_reading_code_buffer_;  // 读码相机 拍照后会被刷新，然后发出异步信号

    int image_location_buffer_width_;
    int image_location_buffer_height_;
    const unsigned char* image_location_buffer_;  //定位相机

    int image_check_frame_buffer_width_;
    int image_check_frame_buffer_height_;
    const unsigned char* image_check_frame_buffer_;  //相机

	HHomMat2D image_to_robotic_coordinates_matrix_;

//    HMetrologyModel MetrologyHandle;

	bool is_running_;
	bool repair_mode_;
    bool offline_mode_;

    //bool receive_send_fid_;

//    bool switch_close_location_;
//    bool switch_close_tid_;
//    bool switch_close_sn_;
//    bool switch_close_fid_;

private:
    int robotic_x_offset_;
    int robotic_y_offset_;
    int robotic_rz_offset_;

public:
    FrameParam frame_param_;
    void save_frame_param();

private:
    DateTimeFileSystem data_filesystem_;
    ItemInformationCenter* item_center_;
    MaterialProductMap material_product_map_;
    FidParser fid_parser_;
    cv::HOGDescriptor frame_disk_hog_;
    cv::HOGDescriptor frame_side_hand_hog_;

private:
    string scan_dir_;
    string line_name_;
    string station_name_;
    string station_id_;

    QDateTime send_CMC_tid_start_;
    QDateTime send_CMC_sn_start_;

public:
    MsleepSetting msleep_time_;
    void save_msleep_time();

//public:
//    MsleepSetting msleep_time_;
//    void save_msleep_time();

private:
    bool seconed_trigger_;
};

#endif // BAOJITAI_H
