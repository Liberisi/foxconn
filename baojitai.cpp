
#include "baojitai.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <QApplication>
#include <QCoreApplication>
#include <QThread>
#include <QTimer>
#include <QDir>
#include <QStorageInfo>
#include <halconcpp/HalconCpp.h>
#include <ssvision/ssvision>
#include <product.h>
#include "halcon_tools.h"
#include "serial_port_manager.h"


using namespace ssvision;
using namespace HalconCpp;

// 定义相对路径
// 文件夹命名
static const char* const kConfigDirName = "config";
static const char* const kLogDirName = "log";
static const char* const kDataDirName = "data";

// 相机序列号文件
static const char* const kCameraSerialNumberFileName = "camera_serial_numbers";

static const char* const kLineStationInfoFileName = "line_station_info";

// 配置文件名称
// 注意，产品文件由用户命名，且占用 xml 扩展名
// 其他配置文件不能使用 xml 做扩展名
static const char* const kImageToRoboticCoordsTransformMatrixFileName = "image2robotic_matrix";
static const char* const kSerialPortSendingCodeConfigFileName = "send_code_sp_config";
static const char* const kSerialPortRepairModeConfigFileName = "repair_mode_sp_config";
static const char* const kSerialPortReadingFidConfigFileName = "read_fid_sp_config";
static const char* const kFidCMCTcpServerConfigFileName = "fid_tcp_server_config";
static const char* const kCurrentProductModelNameFileName = "current_product_model";
static const char* const kFrameParamFileName = "frame_param";
static const char* const kFrameDiskSVMFileName = "frame_detect_svm";
static const char* const kFrameSideHandSVMFileName = "frame_side_hand_svm";
static const char* const kCurrentProductNGDataBaseFileName = "item.db";
static const char* const kMaterialProductDataBaseFileName = "material_product.db";

string config_dir_path();
string log_dir_path();
string data_dir_path();
string yyyyMMdd_hhmmss_xxx_location_bmp(QDateTime& datetime);
string yyyyMMdd_hhmmss_xxx_location_NG_bmp(QDateTime& datetime);
string yyyyMMdd_hhmmss_xxx_reading_code_bmp(QDateTime& datetime);
string yyyyMMdd_hhmmss_xxx_reading_code_NG_bmp(QDateTime& datetime);
string yyyyMMdd_hhmmss_xxx_check_frame_bmp(QDateTime& datetime);
string yyyyMMdd_hhmmss_xxx_check_frame_NG_bmp(QDateTime& datetime);

Baojitai* Baojitai::instance()
{
    static Baojitai* baojitai = NULL;
    if (!baojitai)
        baojitai = new Baojitai();
    return baojitai;
}

Baojitai::Baojitai():
    camera_reading_code_(NULL), camera_location_(NULL), camera_check_frame_(NULL),
	sp_sending_code_(NULL), serial_port_repair_mode_(NULL), sp_read_fid_(NULL), baojitai_logger_(NULL), tid_sn_fid_logger_(NULL),
    current_product_(NULL), robotic_tcp_server_(NULL), plc_act_utl_(NULL),data_filesystem_(data_dir_path()),item_center_(NULL)
{
	image_to_robotic_coordinates_matrix_.HomMat2dIdentity();
    image_reading_code_buffer_ = NULL;
    image_location_buffer_ = NULL;
    image_check_frame_buffer_ = NULL;
    is_running_ = false;
	repair_mode_ = false;
    offline_mode_ = false;
    is_waiting_fid_ = false;
    wait_fid_send_ = false;
    //receive_send_fid_ = false;

    robotic_x_offset_ = 0;
    robotic_y_offset_ = 0;
    robotic_rz_offset_ = 0;

    fid_cmc_socket_.set_delegate(this);

    connect(this, SIGNAL(signal_send_tid(SerialPort*)),
            this, SLOT(on_signal_send_tid(SerialPort*)), Qt::QueuedConnection);
    connect(this, SIGNAL(signal_send_fid(SerialPort*)),
            this, SLOT(on_signal_send_fid(SerialPort*)), Qt::QueuedConnection);
    connect(this, SIGNAL(signal_repair_mode_send_sn()),
            this, SLOT(on_signal_repair_mode_send_sn()), Qt::QueuedConnection);
    connect(this, SIGNAL(signal_check_fid_board_leaving()),
            this, SLOT(on_signal_check_fid_board_leaving()), Qt::QueuedConnection);
    connect(this, SIGNAL(signal_check_plc_camera_control()),
            this, SLOT(on_signal_check_plc_camera_control()), Qt::QueuedConnection);
    connect(this, SIGNAL(signal_post_process_location_image()),
            this, SLOT(on_signal_post_process_location_image()), Qt::QueuedConnection);
    connect(this, SIGNAL(signal_post_process_reading_code_image()),
            this, SLOT(on_signal_post_process_reading_code_image()), Qt::QueuedConnection);
    connect(this, SIGNAL(signal_post_process_check_frame_image()),
            this, SLOT(on_signal_post_process_check_frame_image()), Qt::QueuedConnection);
    connect(this, SIGNAL(signal_reset()),
            this, SLOT(on_signal_reset()), Qt::QueuedConnection);
    //emit signal_check_plc_camera_control();
}

string Baojitai::frame_hog_file_path()
{
    string config_dir = config_dir_path();
    QString frame_hog_svm_path = QDir::cleanPath(QString(config_dir.c_str()) + QDir::separator() + kFrameDiskSVMFileName);
    return frame_hog_svm_path.toStdString();
}

string Baojitai::frame_side_hand_hog_file_path()
{
    string config_dir = config_dir_path();
    QString frame_hog_svm_path = QDir::cleanPath(QString(config_dir.c_str()) + QDir::separator() + kFrameSideHandSVMFileName);
    return frame_hog_svm_path.toStdString();
}

string Baojitai::date_file_path(QDateTime date_time, string file_name)
{
    string file_path = data_filesystem_.file_path(date_time, file_name);
    return file_path;
}

void Baojitai::start()
{
    if (is_running_)
        return;
    is_running_ = true;
    if (camera_reading_code_ && camera_reading_code_->close())
        camera_reading_code_->open();
    if (camera_location_ && camera_location_->close())
        camera_location_->open();
    if (camera_check_frame_ && camera_check_frame_->close())
        camera_check_frame_->open();
    emit signal_running_status_change();

    if (baojitai_logger_)
    {
        baojitai_logger_->log(Logger::kLogLevelInfo,
                              "启动",
                              repair_mode_ ? "返修模式" : "正常模式");
    }

    try_sending_undo();

    static bool start_once = false;
    if (!start_once)
    {
        start_once = true;
        emit signal_check_fid_board_leaving();
    }
}

void Baojitai::stop()
{
    if (!is_running_)
        return;
	if (camera_reading_code_ && camera_reading_code_->is_open())
        camera_reading_code_->close();
	if (camera_location_ && camera_location_->is_open())
        camera_location_->close();
	if (camera_check_frame_ && camera_check_frame_->is_open())
        camera_check_frame_->close();
    is_running_ = false;
    emit signal_running_status_change();
    if (baojitai_logger_)
    {
        baojitai_logger_->log(Logger::kLogLevelInfo,
                              "停止",
                              repair_mode_ ? "返修模式" : "正常模式");
    }
}

bool Baojitai::is_close_location()
{
    if (plc_act_utl_)
    {
        int close = false;
        plc_act_utl_->GetDevice("M70", close);
        return close;
    }
    else
    return false;
}
bool Baojitai::is_close_tid()
{
    if (plc_act_utl_)
    {
        int close = false;
        plc_act_utl_->GetDevice("M71", close);
        return close;
    }
    else
    return false;
}
bool Baojitai::is_close_sn()
{
    if (plc_act_utl_)
    {
        int close = false;
        plc_act_utl_->GetDevice("M72", close);
        return close;
    }
    else
    return false;
}
bool Baojitai::is_close_fid()
{
    if (plc_act_utl_)
    {
        int close = false;
        plc_act_utl_->GetDevice("M73", close);
        return close;
    }
    else
    return false;
}
void Baojitai::set_close_location(bool close)
{
    set_plc("M70", close ? 1 : 0);
    if (baojitai_logger_)
        baojitai_logger_->log(Logger::kLogLevelInfo, "定位", close ? "关闭" : "打开");
}
void Baojitai::set_close_tid(bool close)
{
    set_plc("M71", close ? 1 : 0);
    if (baojitai_logger_)
        baojitai_logger_->log(Logger::kLogLevelInfo, "tid", close ? "关闭" : "打开");
}
void Baojitai::set_close_sn(bool close)
{
    set_plc("M72", close ? 1 : 0);
    if (baojitai_logger_)
        baojitai_logger_->log(Logger::kLogLevelInfo, "sn", close ? "关闭" : "打开");
}
void Baojitai::set_close_fid(bool close)
{
    set_plc("M73", close ? 1 : 0);
    if (baojitai_logger_)
        baojitai_logger_->log(Logger::kLogLevelInfo, "fid", close ? "关闭" : "打开");
}

void Baojitai::on_user_send_undo()
{
    try_sending_undo();
}

void Baojitai::on_user_send_AAAAAA()
{
    string fid = "AAAAAA";
    SerialPort* sp = NULL;
    if (repair_mode_)
    {
        sp = serial_port_repair_mode();
    }
    else
    {
        sp = serial_port_sending_code();
    }
    if (!offline_mode_)
    {
        sp->writeline(fid.c_str(), fid.length());
        emit signal_product_info((string("-> ") + fid).c_str());
    }
}

void Baojitai::set_robotic_x_offset(int x_offset)
{
    x_offset = x_offset < -100 ? -100 : x_offset;
    x_offset = x_offset > 100 ? 100 : x_offset;
    robotic_x_offset_ = x_offset;
}
void Baojitai::set_robotic_y_offset(int y_offset)
{
    y_offset = y_offset < -200 ? -200 : y_offset;
    y_offset = y_offset > 200 ? 200 : y_offset;
    robotic_y_offset_ = y_offset;
}

void  Baojitai::set_robotic_rz_offset(int rz_offset)
{
    rz_offset = rz_offset < -30 ? -30 : rz_offset;
    rz_offset = rz_offset > 30 ? 30 : rz_offset;
    robotic_rz_offset_ = rz_offset;
}

bool Baojitai::set_repair_mode(bool repair_mode)
{
    if (baojitai_logger_)
        baojitai_logger_->log(Logger::kLogLevelInfo, repair_mode ? "返修模式" : "正常模式");
    emit signal_product_info( repair_mode ? "返修模式" : "正常模式");
    repair_mode_ = repair_mode;
    emit signal_plc_repair_mode_change();
    return true;
}

void Baojitai::set_camera_reading_code(Camera* camera)
{
    if (camera_reading_code_ == camera)
        return;
    if (camera_reading_code_)
    {
        delete camera_reading_code_;
        camera_reading_code_ = NULL;
    }
    camera_reading_code_ = camera;
}
void Baojitai::set_camera_location(Camera* camera)
{
    if (camera_location_ == camera)
        return;
    if (camera_location_)
    {
        delete camera_location_;
        camera_location_ = NULL;
    }
    camera_location_ = camera;
}
void Baojitai::set_camera_check_frame(Camera* camera)
{
    if (camera_check_frame_ == camera)
        return;
    if (camera_check_frame_)
    {
        delete camera_check_frame_;
        camera_check_frame_ = NULL;
    }
    camera_check_frame_ = camera;
}
void Baojitai::set_serial_port_sending_code(SerialPort*serial_port)
{
	if (sp_sending_code_ == serial_port)
        return;
	if (sp_sending_code_)
    {
		delete sp_sending_code_;
		sp_sending_code_ = NULL;
    }
	sp_sending_code_ = serial_port;
	if (serial_port)
	{
		serial_port->set_delegate(this);
		if (!serial_port->is_open())
			serial_port->open();
	}
}
void Baojitai::set_serial_port_repair_mode(SerialPort*serial_port)
{
    if (serial_port_repair_mode_ == serial_port)
        return;
    if (serial_port_repair_mode_)
    {
        delete serial_port_repair_mode_;
        serial_port_repair_mode_ = NULL;
    }
    serial_port_repair_mode_ = serial_port;
	if (serial_port)
	{
		serial_port->set_delegate(this);
		if (!serial_port->is_open())
			serial_port->open();
	}
}
void Baojitai::set_serial_port_reading_fid(SerialPort*serial_port)
{
	if (sp_read_fid_ == serial_port)
        return;
	if (sp_read_fid_)
    {
		delete sp_read_fid_;
		sp_read_fid_ = NULL;
    }
	sp_read_fid_ = serial_port;
	if (serial_port)
	{
		serial_port->set_delegate(this);
		if (!serial_port->is_open())
			serial_port->open();
	}
}

void Baojitai::save_serial_port_sending_code_config()
{
    SerialPort* sp = serial_port_sending_code();
	SerialPortManager::instance()->save_serial_port_config(sp, kSerialPortSendingCodeConfigFileName);
}
void Baojitai::save_serial_port_repair_mode_config()
{
    SerialPort* sp = serial_port_repair_mode();
    SerialPortManager::instance()->save_serial_port_config(sp, kSerialPortRepairModeConfigFileName);
}
void Baojitai::save_serial_port_check_frame_config()
{
    SerialPort* sp = serial_port_read_fid();
    SerialPortManager::instance()->save_serial_port_config(sp, kSerialPortReadingFidConfigFileName);
}

void Baojitai::set_current_product(Product* product)
{
    if (product)
    {
        string config_dir = config_dir_path();
        QString current_product_config_path = QDir::cleanPath(QString(config_dir.c_str()) + QDir::separator() + kCurrentProductModelNameFileName);
        ofstream config_file(current_product_config_path.toStdString());
        config_file << product->name() << endl;
    }
    if (current_product_ == product)
        return;
    if (current_product_)
    {
        delete current_product_;
        current_product_ = NULL;
    }
    current_product_ = product;
    emit signal_product_change(product);
}

void Baojitai::remove_data_files(QDate date)
{
    string path = data_filesystem_.directory_path(date);
    QDir dir(path.c_str());
    dir.removeRecursively();
    if (baojitai_logger_)
        baojitai_logger_->log(Logger::kLogLevelInfo, "remove files in ", path);
}

bool Baojitai::material_exists(string material, string& product)
{
    return material_product_map_.exist(material, product);
}

void Baojitai::insert_material_product(string material, string product)
{
    material_product_map_.insert(material, product);
}

void Baojitai::setup()
{
    setup_loggers();

    QStorageInfo storage_info("D:");
    int bytes_available_GB = storage_info.bytesAvailable() / (1024*1024*1024);
    if (baojitai_logger_)
        baojitai_logger_->log(Logger::kLogLevelInfo, "D: ", to_string(bytes_available_GB) + " GB");

    QDate today = QDate::currentDate();
    QDate date(2019, 10, 10);
    while (bytes_available_GB < 200)
    {
        date = date.addDays(1);
        if (date == today)
            break;
        remove_data_files(date);
        bytes_available_GB = storage_info.bytesAvailable() / (1024*1024*1024);
        if (baojitai_logger_)
            baojitai_logger_->log(Logger::kLogLevelInfo, "D: ", to_string(bytes_available_GB) + " GB");
    }

    string config_dir = config_dir_path();

    setup_cameras();
    setup_serial_port_devices();
    setup_robotic_tcp_server();

    read_line_station_info();
    string fid_cmc_ip;
    int fid_cmc_port = 0;
    read_fid_cmc_ip_port(fid_cmc_ip, fid_cmc_port);
    connect_fid_cmc_tcp_server(fid_cmc_ip, fid_cmc_port);

    item_center_ = ItemInformationCenter::instance();
    QString current_item_db_path = QDir::cleanPath(QString(config_dir.c_str()) + QDir::separator() + kCurrentProductNGDataBaseFileName);
    item_center_->open(current_item_db_path.toStdString());
    item_center_->set_delegate(this);
    item_center_->listening(6668);

    QString material_product_db_path = QDir::cleanPath(QString(config_dir.c_str()) + QDir::separator() + kMaterialProductDataBaseFileName);
    material_product_map_.open(material_product_db_path.toStdString());

    ProductManager* product_manager = ProductManager::instance();
    product_manager->set_product_dir_path(config_dir);

    string current_product_model;
    QString current_product_config_path = QDir::cleanPath(QString(config_dir.c_str()) + QDir::separator() + kCurrentProductModelNameFileName);
    QFileInfo current_product_file_info(current_product_config_path);
    if (current_product_file_info.exists())
    {
        ifstream config_file(current_product_config_path.toStdString());
        string line;
        if (getline(config_file, line))
            current_product_model = line;
    }

    if (current_product_model.length() > 0)
    {
        vector<string> product_name_list = product_manager->product_name_list();
        foreach (string product_name, product_name_list)
        {
            if (product_name.compare(current_product_model) == 0)
            {
                Product* product = product_manager->create_product(product_name);
                set_current_product(product);
                break;
            }
        }
    }

    QString config_matrix_path = QDir::cleanPath(QString(config_dir.c_str()) + QDir::separator() + kImageToRoboticCoordsTransformMatrixFileName);
	QFileInfo file_info(config_matrix_path);
	if (file_info.exists())
	{
		HFile hfile(config_matrix_path.toStdString().c_str(), "input_binary");
		if (hfile.IsHandleValid())
		{
			HSerializedItem serilized_item;
			serilized_item.FreadSerializedItem(hfile);
			image_to_robotic_coordinates_matrix_.DeserializeHomMat2d(serilized_item);
		}
	}

    QString frame_param_path = QDir::cleanPath(QString(config_dir.c_str()) + QDir::separator() + kFrameParamFileName);
    frame_param_.read_param(frame_param_path.toStdString());

    QString frame_hog_svm_path = QDir::cleanPath(QString(config_dir.c_str()) + QDir::separator() + kFrameDiskSVMFileName);
    frame_disk_hog_.load(frame_hog_svm_path.toStdString());

    QString frame_hog_side_hand_svm_path = QDir::cleanPath(QString(config_dir.c_str()) + QDir::separator() + kFrameSideHandSVMFileName);
    frame_side_hand_hog_.load(frame_hog_side_hand_svm_path.toStdString());

    if (baojitai_logger_)
    {
        baojitai_logger_->log(Logger::kLogLevelInfo, "抱机台", "程序打开");
    }
}

void Baojitai::save_frame_param()
{
    string config_dir = config_dir_path();
    QString frame_param_path = QDir::cleanPath(QString(config_dir.c_str()) + QDir::separator() + kFrameParamFileName);
    frame_param_.write_param(frame_param_path.toStdString());
}

void Baojitai::shutdown()
{
    shutdown_cameras();
    shutdown_serial_port_devices();
    shutdown_robotic_tcp_server();
    if (baojitai_logger_)
    {
        baojitai_logger_->log(Logger::kLogLevelInfo, "抱机台", "程序关闭");
    }
    shutdown_loggers();
}

void Baojitai::set_image_to_robotic_matrix(HHomMat2D hommat)
{
	image_to_robotic_coordinates_matrix_ = hommat;
	string config_dir = config_dir_path();
    QString config_matrix_path = QDir::cleanPath(QString(config_dir.c_str()) + QDir::separator() + kImageToRoboticCoordsTransformMatrixFileName);
	HSerializedItem serilized_item = image_to_robotic_coordinates_matrix_.SerializeHomMat2d();
	HFile file(config_matrix_path.toStdString().c_str(), "output_binary");
	serilized_item.FwriteSerializedItem(file);
}

void Baojitai:: save_line_station_info(string scan_dir, string line_name, string station_name, string station_id)
{
    scan_dir_ = scan_dir;
    line_name_ = line_name;
    station_name_ = station_name;
    station_id_ = station_id;
    string config_dir = config_dir_path();
    QString line_station_info_path = QDir::cleanPath(QString(config_dir.c_str()) + QDir::separator() + kLineStationInfoFileName);
    ofstream line_station_file(line_station_info_path.toStdString());
    line_station_file << scan_dir << endl
                      << line_name << endl
                      << station_name << endl
                      << station_id << endl;
}

void Baojitai::read_line_station_info()
{
    string config_dir = config_dir_path();
    QString line_station_info_path = QDir::cleanPath(QString(config_dir.c_str()) + QDir::separator() + kLineStationInfoFileName);
    ifstream line_station_file(line_station_info_path.toStdString());
    string line;
    if (getline(line_station_file, line))
        scan_dir_ = line;
    if (getline(line_station_file, line))
        line_name_ = line;
    if (getline(line_station_file, line))
        station_name_ = line;
    if (getline(line_station_file, line))
        station_id_ = line;
}

void Baojitai::save_fid_cmc_ip_port(string ip, int port)
{
    string config_dir = config_dir_path();
    QString ip_port_config_path = QDir::cleanPath(QString(config_dir.c_str()) + QDir::separator() + kFidCMCTcpServerConfigFileName);
    ofstream ip_port_config_file(ip_port_config_path.toStdString());
    ip_port_config_file << ip << endl
                      << port << endl;
}

void Baojitai::read_fid_cmc_ip_port(string& ip, int& port)
{
    string config_dir = config_dir_path();
    QString ip_port_config_path = QDir::cleanPath(QString(config_dir.c_str()) + QDir::separator() + kFidCMCTcpServerConfigFileName);
    ifstream ip_port_config_file(ip_port_config_path.toStdString());
    string ip_str;
    if (getline(ip_port_config_file, ip_str))
        ip = ip_str;
    string port_str;
    if (getline(ip_port_config_file, port_str))
        port = QString(port_str.c_str()).toInt();
}

void Baojitai::setup_cameras()
{
    BaslerCamera::start_basler_camera();

    string camera_reading_code_sn = "23220388";
    string camera_location_sn =  "23034793";
    string camera_check_frame_sn = "23200934";

    vector<string> camera_list = BaslerCamera::camera_list();
    foreach (string sn, camera_list)
    {
        BaslerCamera* basler_camera = new BaslerCamera(sn);
        if (camera_reading_code_sn.length() > 0 && sn.compare(camera_reading_code_sn) == 0)
        {
            set_camera_reading_code(basler_camera);
        }
        else if(camera_location_sn.length() > 0 && sn.compare(camera_location_sn) == 0)
        {
            set_camera_location(basler_camera);
        }
        else if(camera_check_frame_sn.length() > 0 && sn.compare(camera_check_frame_sn) == 0)
        {
            set_camera_check_frame(basler_camera);
        }
        else
        {
            delete basler_camera;
            basler_camera = NULL;
        }
        if (basler_camera)
        {
            basler_camera->set_delegate(this);
            basler_camera->open();
        }
    }
}

void Baojitai::shutdown_cameras()
{
    set_camera_reading_code(NULL);
    set_camera_location(NULL);
    set_camera_check_frame(NULL);
    BaslerCamera::stop_basler_camera();
}

void Baojitai::setup_serial_port_devices()
{
    SerialPortManager* manager = SerialPortManager::instance();
    manager->set_config_dir_path(config_dir_path());
	set_serial_port_sending_code(manager->create_serial_port(kSerialPortSendingCodeConfigFileName));
    set_serial_port_repair_mode(manager->create_serial_port(kSerialPortRepairModeConfigFileName));
	set_serial_port_reading_fid(manager->create_serial_port(kSerialPortReadingFidConfigFileName));
}

void Baojitai::shutdown_serial_port_devices()
{
	if (sp_sending_code_)
    {
		if (sp_sending_code_->is_open())
			sp_sending_code_->close();
		delete sp_sending_code_;
		sp_sending_code_ = NULL;
    }
    if (serial_port_repair_mode_)
    {
        if (serial_port_repair_mode_->is_open())
            serial_port_repair_mode_->close();
        delete serial_port_repair_mode_;
        serial_port_repair_mode_ = NULL;
    }
	if (sp_read_fid_)
    {
		if (sp_read_fid_->is_open())
			sp_read_fid_->close();
		delete sp_read_fid_;
		sp_read_fid_ = NULL;
    }
}

void Baojitai::setup_loggers()
{
    Logger* system_logger = new DateFileLogger(log_dir_path(), "system.log");
    if (system_logger)
        baojitai_logger_ = system_logger;
	Logger* tid_sn_fid_logger = new DateFileLogger(log_dir_path(), "tid_sn_fid.csv");
	if (tid_sn_fid_logger)
		tid_sn_fid_logger_ = tid_sn_fid_logger;
}

void Baojitai::shutdown_loggers()
{
    if (baojitai_logger_)
    {
        baojitai_logger_->close();
        delete baojitai_logger_;
        baojitai_logger_ = NULL;
    }
}

//void Baojitai::setup_plcole()
//{
//    if (PlcOle::initialize_ole())
//    {
//        plc_ = PlcOleProg::instance();
//        if (plc_)
//            plc_->create();
//    }
//}
//void Baojitai::shutdown_plcole()
//{
//    if (plc_)
//        plc_->destroy();
//    PlcOle::uninitialize_ole();
//}

void Baojitai::setup_robotic_tcp_server()
{
    RoboticTCPServer* robotic_tcp_server = new RoboticTCPServer();
    if (robotic_tcp_server)
    {
        robotic_tcp_server->set_delegate(this);
        robotic_tcp_server_ = robotic_tcp_server;
        robotic_tcp_server->listening(8886);
    }
}

void Baojitai::shutdown_robotic_tcp_server()
{
    if (robotic_tcp_server_)
    {
        delete robotic_tcp_server_;
        robotic_tcp_server_ = NULL;
    }
}

// CameraDelegate
void Baojitai::on_camera_open(Camera* camera)
{
    if (camera == camera_reading_code())
    {
        if (baojitai_logger_)
            baojitai_logger_->log(Logger::kLogLevelInfo, "读码相机", "open");
    }
    else if (camera == camera_location())
    {
        if (baojitai_logger_)
            baojitai_logger_->log(Logger::kLogLevelInfo, "定位相机", "open");
    }
    else if (camera == camera_check_frame())
    {
        if (baojitai_logger_)
            baojitai_logger_->log(Logger::kLogLevelInfo, "支架相机", "open");
    }
    emit signal_camera_status_change(camera);
}

void Baojitai::on_camera_close(Camera* camera)
{

}

void Baojitai::camera_reading_code_buffer(const unsigned char** p_buffer, int *width, int* height)
{
	if (p_buffer)
		*p_buffer = image_reading_code_buffer_;
	if (width)
		*width = image_reading_code_buffer_width_;
	if (height)
		*height = image_reading_code_buffer_height_;
}

void Baojitai::camera_location_buffer(const unsigned char** p_buffer, int *width, int* height)
{
    if (p_buffer)
        *p_buffer = image_location_buffer_;
    if (width)
        *width = image_location_buffer_width_;
    if (height)
        *height = image_location_buffer_height_;
}

void Baojitai::camera_check_frame_buffer(const unsigned char** p_buffer, int *width, int* height)
{
    if (p_buffer)
        *p_buffer = image_check_frame_buffer_;
    if (width)
        *width = image_check_frame_buffer_width_;
    if (height)
        *height = image_check_frame_buffer_height_;
}

void Baojitai::update_camera_location_buffer(void* data, int width, int height)
{
    if (image_location_buffer_ == NULL)
    {
        if (width > 0 && height > 0)
        {
            image_location_buffer_ = new unsigned char[width * height];
        }
    }
    else
    {
        if ((width > 0 && height > 0) && (width != image_location_buffer_width_ || height != image_location_buffer_height_))
        {
            delete[] image_location_buffer_;
            image_location_buffer_ = new unsigned char[width * height];
        }
    }

    if (image_location_buffer_)
    {
        image_location_buffer_width_ = width;
        image_location_buffer_height_ = height;
        memcpy((void*)image_location_buffer_, data, width * height);
        emit signal_camera_buffer_updated(camera_location());
    }
}

void Baojitai::update_camera_check_frame_buffer(void* data, int width, int height)
{
    if (image_check_frame_buffer_ == NULL)
    {
        if (width > 0 && height > 0)
        {
            image_check_frame_buffer_ = new unsigned char[width * height];
        }
    }
    else
    {
        if ((width > 0 && height > 0) && (width != image_check_frame_buffer_width_ || height != image_check_frame_buffer_height_))
        {
            delete[] image_check_frame_buffer_;
            image_check_frame_buffer_ = new unsigned char[width * height];
        }
    }

    if (image_check_frame_buffer_)
    {
        image_check_frame_buffer_width_ = width;
        image_check_frame_buffer_height_ = height;
        memcpy((void*)image_check_frame_buffer_, data, width * height);
        emit signal_camera_buffer_updated(camera_check_frame());
    }
}

void Baojitai::update_camera_reading_code_buffer(void* data, int width, int height)
{
    if (image_reading_code_buffer_ == NULL)
    {
        if (width > 0 && height > 0)
        {
            image_reading_code_buffer_ = new unsigned char[width * height];
        }
    }
    else
    {
        if ((width > 0 && height > 0) && (width != image_reading_code_buffer_width_ || height != image_reading_code_buffer_height_))
        {
            delete[] image_reading_code_buffer_;
            image_reading_code_buffer_ = new unsigned char[width * height];
        }
    }

    if (image_reading_code_buffer_)
    {
        image_reading_code_buffer_width_ = width;
        image_reading_code_buffer_height_ = height;
        memcpy((void*)image_reading_code_buffer_, data, width * height);
        emit signal_camera_buffer_updated(camera_reading_code());
    }
}

void Baojitai::process_location_image(void* data, int width, int height)
{
    location_result_.success = false;
    location_result_.find_rect = false;
    Product* product = current_product();
    if (!product)
        return;

    int width_config = product->vision_param().l1;
    int height_config = product->vision_param().l2;
    int var = product->vision_param().xl1;

    string width_config_str = to_string(width_config);
    string height_config_str = to_string(height_config);
    string var_str = to_string(var);
    baojitai_logger_->log(Logger::kLogLevelInfo,
                          "config size",
                          string("[") + width_config_str + ", " + height_config_str + "] var " + var_str);

    // 图像处理， 定位
    int black_region_threshold[4] = {98, 128, 118, 108};
    bool find_sucess = false;
    for (int i = 0; i < sizeof(black_region_threshold) / sizeof(black_region_threshold[0]); ++i)
    {
        int x, y, length1, length2;
        double phi;
        bool find = false;
        halcontools::extract_rect(data, width, height, &x, &y, &phi, &length1, &length2, &find, black_region_threshold[i]);

        if (find
                &&
                length1 * 2 > width * 0.2 &&
                length1 * 2 < width * 0.9 &&
                length2 * 2 > height * 0.2 &&
                length2 * 2 < height * 0.9 &&
                x > width * 0.1 &&
                x < width * 0.9 &&
                y > height * 0.1 &&
                y < height * 0.9
                )
        {
            location_result_.find_rect = true;
            location_result_.x = x;
            location_result_.y = y;
            location_result_.phi = phi;
            location_result_.l1 = length1;
            location_result_.l2 = length2;
            find_sucess = halcontools::check_rect_size(x, y, phi, length1, length2, image_to_robotic_coordinates_matrix_, width_config, height_config, var);
            if (find_sucess)
            {
                float x1 = x + length1 * cos(phi);
                float y1 = y - length1 * sin(phi);
                float x2 = x - length1 * cos(phi);
                float y2 = y + length1 * sin(phi);
                halcontools::transform_point(image_to_robotic_coordinates_matrix_, x1, y1, x1, y1);
                halcontools::transform_point(image_to_robotic_coordinates_matrix_, x2, y2, x2, y2);
                float pi_2 = 3.14159f * 0.5;
                float x3 = x + length2 * cos(pi_2 + phi);
                float y3 = y - length2 * sin(pi_2 + phi);
                float x4 = x - length2 * cos(pi_2 + phi);
                float y4 = y + length2 * sin(pi_2 + phi);
                halcontools::transform_point(image_to_robotic_coordinates_matrix_, x3, y3, x3, y3);
                halcontools::transform_point(image_to_robotic_coordinates_matrix_, x4, y4, x4, y4);
                float dx = x1 - x2;
                float dy = y1 - y2;
                float width_mm = sqrt(dx * dx + dy * dy);
                dx = x3 - x4;
                dy = y3 - y4;
                float height_mm = sqrt(dx * dx + dy * dy);

                location_result_.width_mm = width_mm;
                location_result_.height_mm = height_mm;
                location_result_.success = true;

                stringstream ss;
                ss << "[" << x << " " << y << " " << length1 << " " << length2 << " " << (int)phi*180/3.14 << "]";
                emit signal_product_info(ss.str().c_str());
                emit signal_product_info("location success");

                stringstream ss2;
                ss2 << "size " << "[" << width_mm << ", " << height_mm << "]";
                emit signal_product_info(ss2.str().c_str());

                break;
            }
            else
            {
                location_result_.success = false;
            }
        }
    }

    if (baojitai_logger_)
    {
        baojitai_logger_->log(Logger::kLogLevelInfo,
                              location_result_.success ? "location success" : "location fail");
    }
}

void Baojitai::process_reading_code_image(void* data, int width, int height)
{
	Product* product = current_product();
	if (!product)
		return;

	Product::DataCodeParam param = product->data_code_param();
    emit signal_product_info(param.use_board_code ? "use tid" : "not use tid");

	tid_ = "";
	board_bar_code_region_ = HRegion();
	vector<HRegion> bar_code_regions;
	vector<string> bar_codes;
	int board_code_duration = 0;
	if (param.board_bar_code_type)
		halcontools::read_bar_code(data, width, height, param.board_bar_code_type, bar_codes, bar_code_regions, board_code_duration);
	bool find_board_code = false;
	if (param.use_board_code && bar_codes.size() > 0)
	{
		for (int i = 0; i < bar_codes.size(); ++i)
		{
			string code = bar_codes[i];
            if (code.length() <= 2 )
                continue;
            code = code.substr(1, code.length() - 2);
			qDebug() << "board bar code: " << code.c_str() << endl;
            qDebug() << "check length: " << code.length() << " vs " << param.board_code_length << endl;
			if (code.length() == param.board_code_length)
			{
				string prefix = param.board_code_prefix();
                qDebug() << "check length: " << param.board_code_length << endl;
                qDebug() << "check prefix: " << prefix.c_str() << endl;
				if (prefix.length() > 0 && prefix.length() <= code.length())
				{
					bool prefix_equal = true;
					for (int i = 0; i < prefix.length(); ++i)
					{
						if (prefix[i] != code[i])
						{
							prefix_equal = false;
							break;
						}
					}
					if (prefix_equal)
					{
						find_board_code = true;
						tid_ = code;
						board_bar_code_region_ = bar_code_regions[i];
						break;
					}
				}
				else
				{
                    qDebug() << "not check prefix and find board code " << endl;
					find_board_code = true;
					tid_ = code;
					board_bar_code_region_ = bar_code_regions[i];
					break;
				}
			}
            else
            {
                qDebug() << "board code length error" << endl;
            }
		}
	}
	if (!param.use_board_code || find_board_code)
		board_code_success_ = true;
	else
		board_code_success_ = false;

    if (param.use_board_code)
    {
        emit signal_product_info((string("tid ") + tid_).c_str());
    }

    emit signal_product_info(param.use_product_code ? "use sn" : "not use sn");

	sn_ = "";
	bool find_product_code = false;
	int product_mat_code_duration = 0;
	if (param.product_mat_code_type)
    {
        emit signal_product_info("sn - mat code");
		vector<HXLD> mat_code_xlds;
		vector<string> mat_codes;
		halcontools::read_2d_code_complex(data, width, height, param.product_mat_code_type, mat_codes, mat_code_xlds, product_mat_code_duration);
		for (int i = 0; i < mat_codes.size(); ++i)
		{
			string code = mat_codes[i];
            if (code.length() <= 2 )
                continue;
            code = code.substr(1, code.length() - 2);
			qDebug() << "product mat code: " << code.c_str() << endl;
            qDebug() << "check mat code length: " << code.length() << " vs " << param.product_code_length << endl;
			if (code.length() == param.product_code_length)
			{
				find_product_code = true;
				sn_ = code;
				product_mat_code_xld_ = mat_code_xlds[i];
				break;
			}
		}

		if (!find_product_code)
		{
			mat_code_xlds.clear();
			mat_codes.clear();
			halcontools::read_2d_code(data, width, height, param.product_mat_code_type, mat_codes, mat_code_xlds, product_mat_code_duration);
			for (int i = 0; i < mat_codes.size(); ++i)
			{
				string code = mat_codes[i];
				if (code.length() <= 2)
					continue;
				code = code.substr(1, code.length() - 2);
				qDebug() << "product mat code: " << code.c_str() << endl;
				qDebug() << "check mat code length: " << code.length() << " vs " << param.product_code_length << endl;
				if (code.length() == param.product_code_length)
				{
					find_product_code = true;
					sn_ = code;
					product_mat_code_xld_ = mat_code_xlds[i];
					break;
				}
			}
		}
	}
	else if (param.product_bar_code_type)
	{
        emit signal_product_info("sn - bar code");
		vector<HRegion> bar_code_regions;
		vector<string> bar_codes;
		halcontools::read_bar_code(data, width, height, param.board_bar_code_type, bar_codes, bar_code_regions, product_mat_code_duration);
		for (int i = 0; i < bar_codes.size(); ++i)
		{
			string code = bar_codes[i];
            if (code.length() <= 2 )
                continue;
            code = code.substr(1, code.length() - 2);
			qDebug() << "product bar code " << code.c_str() << endl;
            qDebug() << "check bar code length: " << code.length() << " vs " << param.product_code_length << endl;
			if (code.length() == param.product_code_length)
			{
				find_product_code = true;
				sn_ = code;
				product_bar_code_region_ = bar_code_regions[i];
				break;
			}
		}
	}
	if (!param.use_product_code || find_product_code)
		product_code_success_ = true;
	else
		product_code_success_ = false;
	reading_code_duration_ = board_code_duration + product_mat_code_duration;

    if (param.use_board_code)
        emit signal_product_info((string("sn ") + sn_).c_str());

	if (baojitai_logger_)
	{
		if (param.use_board_code)
		{
			if (find_board_code)
				baojitai_logger_->log(Logger::kLogLevelInfo, "tid", tid_);
			else
				baojitai_logger_->log(Logger::kLogLevelInfo, "tid", "[]");
		}
		else
		{
			baojitai_logger_->log(Logger::kLogLevelInfo, "not use board code");
		}

		if (param.use_product_code)
		{
			if (find_product_code)
				baojitai_logger_->log(Logger::kLogLevelInfo, "sn", sn_);
			else
				baojitai_logger_->log(Logger::kLogLevelInfo, "sn", "[]");
		}
		else
		{
			baojitai_logger_->log(Logger::kLogLevelInfo, "not use product code");
		}
	}

    // remove me
//    this->board_code_success_ = true;
//    this->product_code_success_ = true;
//    tid_ = "test_tid";
//    sn_ = "test_sn";
}

void Baojitai::process_check_frame_image(void* data, int width, int height)
{
	if (baojitai_logger_)
		baojitai_logger_->log(Logger::kLogLevelInfo, "check frame", check_frame_success_ ? "ok" : "ng");

    int x = frame_param_.x();
    int y = frame_param_.y();
    int w = frame_param_.w();
    int h = frame_param_.h();
    int mw = frame_param_.magic_w();
    int mh = frame_param_.magic_h();

    bool disk_ok = false;
    halcontools::detect_frame_disk(data, width, height, frame_disk_hog_, x, y, w, h, mw, mh, disk_ok);
    check_frame_result_.is_disk_ok = disk_ok;

    int side_hand_magic_width = frame_param_.side_hand_magic_w();
    int side_hand_magic_height = frame_param_.side_hand_magic_h();

    int lx = frame_param_.lx();
    int ly = frame_param_.ly();
    int lw = frame_param_.lw();
    int lh = frame_param_.lh();

    int left_rect_x = lx - lw;
    int left_rect_y = ly - lh;
    int left_rect_w = lw * 2;
    int left_rect_h = lh * 2;

    bool left_hand_found = false;
    halcontools::detect_frame_side_hand(data, width, height,
                                        frame_side_hand_hog_,
                                        left_rect_x, left_rect_y, left_rect_w, left_rect_h,
                                        side_hand_magic_width, side_hand_magic_height,
                                        left_hand_found);
    check_frame_result_.is_found_left = left_hand_found;

    int rx = frame_param_.rx();
    int ry = frame_param_.ry();
    int rw = frame_param_.rw();
    int rh = frame_param_.rh();
    int right_rect_x = rx - rw;
    int right_rect_y = ry - rh;
    int right_rect_w = rw * 2;
    int right_rect_h = rh * 2;

    bool right_hand_found = false;
    halcontools::detect_frame_side_hand(data, width, height,
                                        frame_side_hand_hog_,
                                        right_rect_x, right_rect_y, right_rect_w, right_rect_h,
                                        side_hand_magic_width, side_hand_magic_height,
                                        right_hand_found);
    check_frame_result_.is_found_right = right_hand_found;

    if (check_frame_result_.is_disk_ok &&
            !check_frame_result_.is_found_left &&
            !check_frame_result_.is_found_right)
    {
        check_frame_success_ = true;
    }
    else
    {
        check_frame_success_ = false;
    }
}

void Baojitai::post_process_location_image()
{
    if (baojitai_logger_)
        baojitai_logger_->log(Logger::kLogLevelInfo, "location finish");
    emit signal_location_finish();
    if (!location_result_.success)
        emit signal_location_ng();
    send_location_result_to_plc();
    string file_name = location_result_.success ? yyyyMMdd_hhmmss_xxx_location_bmp(location_time_) : yyyyMMdd_hhmmss_xxx_location_NG_bmp(location_time_);
    string file_path = data_filesystem_.file_path(location_time_, file_name);
    halcontools::write_image((void*)image_location_buffer_, image_location_buffer_width_, image_location_buffer_height_, file_path);
    if (!location_result_.success)
    {
        string file_path_ng = data_filesystem_.file_path_ng(location_time_, file_name);
        halcontools::write_location_image_ng((void*)image_location_buffer_, image_location_buffer_width_, image_location_buffer_height_,
                                             location_result_.find_rect,
                                             location_result_.x,
                                             location_result_.y,
                                             location_result_.phi,
                                             location_result_.l1,
                                             location_result_.l2,
                                             location_result_.success ? "OK" : "NG",
                                             file_path_ng);
    }
}

void Baojitai::repair_mode_post_process_reading_code_image()
{
    if (baojitai_logger_)
        baojitai_logger_->log(Logger::kLogLevelInfo, "repair mode read code finish");
    emit signal_reading_code_finish();
    if (product_code_success_ && sn_.length() > 0)
    {
        if (baojitai_logger_)
            baojitai_logger_->log(Logger::kLogLevelInfo, "success and sn length > 0");
        emit signal_repair_mode_send_sn();
    }
    else
    {
        set_plc("M41", 1);
        emit signal_sn_ng("unknown", "image", tid_.c_str());
    }
}

void Baojitai::post_process_reading_code_image()
{
    if (baojitai_logger_)
        baojitai_logger_->log(Logger::kLogLevelInfo, "read code finish");
    emit signal_reading_code_finish();
    bool close_tid = is_close_tid();
    bool close_sn = is_close_sn();
    if (board_code_success_ && product_code_success_)
	{
        if (tid_.length() > 0)
        {
            if (baojitai_logger_)
                baojitai_logger_->log(Logger::kLogLevelInfo, "success and tid.length > 0");
            try_sending_tid();
        }
        else
        {
            if (baojitai_logger_)
                baojitai_logger_->log(Logger::kLogLevelInfo, "success bud tid.length == 0");
            set_plc("M31", 1);
        }
	}
	else if (!board_code_success_)
	{
        if (!close_tid)
        {
            set_plc("M31", 1);
            emit signal_tid_ng("unknown", "image");
        }
	}
	else if (!product_code_success_)
	{
        if (!close_sn)
        {
            set_plc("M41", 1);
            emit signal_sn_ng("unknown", "image", tid_.c_str());
        }
	}
	string file_name = (board_code_success_ && product_code_success_) ? yyyyMMdd_hhmmss_xxx_reading_code_bmp(reading_code_time_) : yyyyMMdd_hhmmss_xxx_reading_code_NG_bmp(reading_code_time_);
    string file_path = data_filesystem_.file_path(reading_code_time_, file_name);
    halcontools::write_image((void*)image_reading_code_buffer_, image_reading_code_buffer_width_, image_reading_code_buffer_height_, file_path);
    if (!board_code_success_ || !product_code_success_)
    {
        Product* product = current_product();
        if (!product)
            return;

        bool draw_region_1 = false;
        bool draw_region_2 = false;
        bool draw_xld = false;
        HRegion region_1, region_2;
        HXLD xld;
        string tid, sn;
        if (board_code_success_)
        {
            draw_region_1 = true;
            region_1 = board_bar_code_region_;
            tid = tid_;
        }

        Product::DataCodeParam param = product->data_code_param();
        if (param.product_mat_code_type && product_code_success_)
        {
            draw_xld = true;
            xld = product_mat_code_xld_;
            sn = sn_;
        }

        if (param.product_bar_code_type && product_code_success_)
        {
            draw_region_2 = true;
            region_2 = product_bar_code_region_;
            sn = sn_;
        }

        string file_path_ng = data_filesystem_.file_path_ng(reading_code_time_, file_name);
        halcontools::write_reading_code_image_ng(
                    (void*)image_reading_code_buffer_, image_reading_code_buffer_width_, image_reading_code_buffer_height_,
                    draw_region_1, region_1,
                    draw_region_2, region_2,
                    draw_xld, xld,
                    tid, sn,
                    file_path_ng);
    }
}

void Baojitai::on_signal_post_process_location_image()
{
    this->post_process_location_image();
}

void Baojitai::on_signal_post_process_reading_code_image()
{
    this->post_process_reading_code_image();
}

void Baojitai::on_signal_post_process_check_frame_image()
{
    this->post_process_check_frame_image();
}

void Baojitai::post_process_check_frame_image()
{
    emit signal_check_frame_finish();
    send_check_frame_result_to_plc();
    string file_name = check_frame_success_ ? yyyyMMdd_hhmmss_xxx_check_frame_bmp(check_frame_time_) : yyyyMMdd_hhmmss_xxx_check_frame_NG_bmp(check_frame_time_);
    string file_path = data_filesystem_.file_path(check_frame_time_, file_name);
    halcontools::write_image((void*)image_check_frame_buffer_, image_check_frame_buffer_width_, image_check_frame_buffer_height_, file_path);
    if (!check_frame_result_.is_disk_ok || check_frame_result_.is_found_left || check_frame_result_.is_found_right)
    {
        int x = frame_param_.x();
        int y = frame_param_.y();
        int w = frame_param_.w();
        int h = frame_param_.h();
        int left_x = frame_param_.lx();
        int left_y = frame_param_.ly();
        int left_w = frame_param_.lw();
        int left_h = frame_param_.lh();
        int right_x = frame_param_.rx();
        int right_y = frame_param_.ry();
        int right_w = frame_param_.rw();
        int right_h = frame_param_.rh();
        string file_path_ng = data_filesystem_.file_path_ng(check_frame_time_, file_name);
        halcontools::write_frame_image_ng((void*)image_check_frame_buffer_, image_check_frame_buffer_width_, image_check_frame_buffer_height_,
                                          check_frame_result_.is_disk_ok, x, y, w, h,
                                          check_frame_result_.is_found_left, left_x, left_y, left_w, left_h,
                                          check_frame_result_.is_found_right, right_x, right_y, right_w, right_h,
                                          file_path_ng);
    }
}

void Baojitai::set_plc(const string& device, int value)
{
    QThread* main_thread = QApplication::instance()->thread();
    QThread* current_thread = QThread::currentThread();
    if (baojitai_logger_ && main_thread != current_thread)
        baojitai_logger_->log(Logger::kLogLevelInfo, "set plc not in main thread");

    if (plc_act_utl_ && device.length() > 0)
    {
        emit signal_product_info((string("set plc ") + device).c_str());
        int ret = plc_act_utl_->SetDevice(device.c_str(), value);
        while (ret != 0)
        {
            QThread::msleep(100);
            ret = plc_act_utl_->SetDevice(device.c_str(), value);
        }
        if (baojitai_logger_)
            baojitai_logger_->log(Logger::kLogLevelInfo, string("set plc success "),  device + " " + to_string(value));
    }
}

void Baojitai::get_plc(const string& device, int& value)
{
    QThread* main_thread = QApplication::instance()->thread();
    QThread* current_thread = QThread::currentThread();
    if (baojitai_logger_ && main_thread != current_thread)
        baojitai_logger_->log(Logger::kLogLevelInfo, "get plc not in main thread");

    if (plc_act_utl_ && device.length() > 0)
    {
        int ret = plc_act_utl_->GetDevice(device.c_str(), value);
        while (ret != 0)
        {
            QThread::msleep(100);
            ret = plc_act_utl_->GetDevice(device.c_str(), value);
        }
        if (baojitai_logger_)
            baojitai_logger_->log(Logger::kLogLevelInfo, string("get plc success "), device + " " + to_string(value));
    }
}

void Baojitai::reading_code_result(bool &success, string& tid, string& sn, HRegion &board_bar_code_region, HRegion &product_bar_code_region, HXLD& product_mat_code_xld)
{
	success = board_code_success_ && product_code_success_;
	tid = tid_;
	sn = sn_;
	board_bar_code_region = board_bar_code_region_;
	product_bar_code_region = product_bar_code_region_;
	product_mat_code_xld = product_mat_code_xld_;
}

void Baojitai::on_camera_capture(Camera *camera, int width, int height, void *data, PixelFormat pixel_format)
{
    if (!camera)
        return;

    if (camera == camera_reading_code())
    {
//        if (plc_act_utl_)
//        {
//            int flag;
//            plc_act_utl_->GetDevice("M80", flag);
//            if (flag == 0)
//            {
//                if (baojitai_logger_)
//                    baojitai_logger_->log(Logger::kLogLevelInfo, "读码相机", "M80 == 0 误触发 不处理 不保存");
//                return;
//            }
//            else if (flag == 1)
//            {
//                if (baojitai_logger_)
//                    baojitai_logger_->log(Logger::kLogLevelInfo, "读码相机", "M80 == 1 主动触发");
//                do {
//                    QThread::msleep(10);
//                    set_plc("M80", 0);
//                    QThread::msleep(10);
//                    plc_act_utl_->GetDevice("M80", flag);
//                } while (flag == 1);
//                if (baojitai_logger_)
//                    baojitai_logger_->log(Logger::kLogLevelInfo, "读码相机", "M80 == 0 已拉低");
//            }
//        }

        reading_code_time_ = QDateTime::currentDateTime();
        if (baojitai_logger_)
            baojitai_logger_->log(Logger::kLogLevelInfo, "读码相机", "capture");
		switch (pixel_format)
		{
		case kPixelFormatGray8:
		{
            update_camera_reading_code_buffer(data, width, height);
            if (is_running()){
                process_reading_code_image(data, width, height);
                if (repair_mode_)
                    repair_mode_post_process_reading_code_image();
                else
                    emit signal_post_process_reading_code_image();
            }
        }
			break;
		default:
			break;
		}
    }
    else if (camera == camera_location())
    {
//        if (plc_act_utl_)
//        {
//            int flag;
//            plc_act_utl_->GetDevice("M79", flag);
//            if (flag == 0)
//            {
//                if (baojitai_logger_)
//                    baojitai_logger_->log(Logger::kLogLevelInfo, "定位相机", "M79 == 0 误触发 不处理 不保存");
//                return;
//            }
//            else if (flag == 1)
//            {
//                if (baojitai_logger_)
//                    baojitai_logger_->log(Logger::kLogLevelInfo, "定位相机", "M79 == 1 主动触发");
//                do {
//                    QThread::msleep(10);
//                    set_plc("M79", 0);
//                    QThread::msleep(10);
//                    plc_act_utl_->GetDevice("M79", flag);
//                } while (flag == 1);
//                if (baojitai_logger_)
//                    baojitai_logger_->log(Logger::kLogLevelInfo, "定位相机", "M79 == 0 已拉低");
//            }
//        }

        location_time_ = QDateTime::currentDateTime();
        if (baojitai_logger_)
            baojitai_logger_->log(Logger::kLogLevelInfo, "定位相机", "capture");
    switch (pixel_format)
        {
        case kPixelFormatGray8:
        {
            emit signal_product_arrive();
            update_camera_location_buffer(data, width, height);

//            unsigned char* img_data = (unsigned char*)data;

            // 152, 745
            //    444, 1362
//            for (int row = 152; row < 500; row++)
//            {
//                for (int col = 765; col < 1662; ++col)
//                {
//                    unsigned char* byte = img_data + row * width + col;
//                    *byte = 255;
//                }
//            }

//            for (int row = 1354; row < 1652; row++)
//            {
//                for (int col = 569; col < 1357; col++)
//                {
//                    unsigned char* byte = img_data + row * width + col;
//                    *byte = 255;
//                }
//            }

            if (is_running()){
                process_location_image(data, width, height);
                emit signal_post_process_location_image();
            }
        }
        }
     }
    else if (camera == camera_check_frame())
    {
//        if (plc_act_utl_)
//        {
//            int flag;
//            plc_act_utl_->GetDevice("M81", flag);
//            if (flag == 0)
//            {
//                if (baojitai_logger_)
//                    baojitai_logger_->log(Logger::kLogLevelInfo, "支架相机", "M81 == 0 误触发 不处理 不保存");
//                return;
//            }
//            else if (flag == 1)
//            {
//                if (baojitai_logger_)
//                    baojitai_logger_->log(Logger::kLogLevelInfo, "支架相机", "M81 == 1 主动触发");
//                do {
//                    QThread::msleep(10);
//                    set_plc("M81", 0);
//                    QThread::msleep(10);
//                    plc_act_utl_->GetDevice("M81", flag);
//                } while (flag == 1);
//                if (baojitai_logger_)
//                    baojitai_logger_->log(Logger::kLogLevelInfo, "支架相机", "M81 == 0 已拉低");
//            }
//        }

        check_frame_time_ = QDateTime::currentDateTime();
        if (baojitai_logger_)
            baojitai_logger_->log(Logger::kLogLevelInfo, "支架相机", "capture");
        switch (pixel_format)
        {
        case kPixelFormatGray8:
        {
            update_camera_check_frame_buffer(data, width, height);
            if (is_running()){
                process_check_frame_image(data, width, height);
                emit signal_post_process_check_frame_image();
            }
        }
        }
     }
}

void Baojitai::on_serial_port_open(SerialPort* serial_port)
{
    if (baojitai_logger_)
        baojitai_logger_->log(Logger::kLogLevelInfo, serial_port->port_name(), "open");
    emit signal_serial_port_status_change(serial_port);
}

void Baojitai::on_read_fid_data(const char* data, int size)
{
    int left_size = size;
    do
    {
        int buffer_size = fid_parser_.empty_buffer_size();
        if (buffer_size == 0)
            break;
        int push_size = left_size < buffer_size ? left_size : buffer_size;
        fid_parser_.push_data(data, push_size);
        left_size -= push_size;
        string fid = fid_parser_.shift_fid();
        while (fid.length() > 0)
        {
            on_read_fid(fid);
            fid = fid_parser_.shift_fid();
        }
    } while (left_size > 0);
}

void Baojitai::on_serial_port_read(SerialPort* serial_port, const char* data, int size)
{
    string s(data, size);
    if (baojitai_logger_)
        baojitai_logger_->log(Logger::kLogLevelInfo, "fid sp read bytes count", to_string(size));
    QByteArray byte_array(data, size);
    QString hex_str(byte_array.toHex().toUpper());
    int len = byte_array.length()/2;
    for(int i=1;i<len;i++)
    {
        hex_str.insert(2*i+i-1," ");
    }
    if (baojitai_logger_)
        baojitai_logger_->log(Logger::kLogLevelInfo, "fid sp read bytes", hex_str.toStdString());

    //emit signal_product_info((string("fid data ") + s).c_str());
    QString message(s.c_str());
    emit signal_serial_port_read(serial_port, message);

    if (serial_port == serial_port_read_fid())
    {
        on_read_fid_data(data, size);
    }
}

void Baojitai::try_sending_tid()
{
    if (!is_running())
        return;

    QThread::msleep(10);

    if (wait_fid_send_)
    {
        emit signal_product_info("wait sending last fid");
        new_tid_ = tid_;
        return;
    }

	SerialPort* sp = NULL;
	if (repair_mode_)
	{
		sp = serial_port_repair_mode();
	}
	else
	{
		sp = serial_port_sending_code();
	}
    qDebug() << "emit signal_send_tid(sp)" << endl;
    emit signal_send_tid(sp);
}

void Baojitai::on_timer_check_plc_camera_control()
{
    int last_flag = 0;
    if (plc_act_utl_)
    {
        int flag;
        plc_act_utl_->GetDevice("M900", flag);
        if (flag == 1)
        {
            emit signal_product_info("M900 1");
        }
        else
        {
            emit signal_product_info("M900 0");
        }
        if (flag == 1 && last_flag == 0)
        {
            emit signal_product_info("M900 camera capture");
            set_plc("M902", 1);
        }
        last_flag = flag;
    }
    QTimer::singleShot(100, this, SLOT(on_timer_check_plc_camera_control()));
}

void Baojitai::on_timer_check_fid_board_leaving()
{
    static int last_flag = 1;
    static int last_plc_repair_mode = 1;
    static int last_plc_reset = 1;
    if (plc_act_utl_)
    {
        int start_read_fid;
        get_plc("M18", start_read_fid);
        if (start_read_fid == 1)
        {
            //emit signal_product_info("M18 1");
        }
        else
        {
            //emit signal_product_info("M18 0");
        }
        if (start_read_fid == 1 && last_flag == 0)
        {
            is_waiting_fid_ = true;
            emit signal_product_info("M18 wait fid");
            QTimer::singleShot(5000, this, SLOT(on_waiting_fid_timeout()));
            //set_plc("M18", 0);
            if (baojitai_logger_)
                baojitai_logger_->log(Logger::kLogLevelInfo, "M18",  to_string(0) + "->" + to_string(1));
        }
        last_flag = start_read_fid;

        int plc_repair_mode;
        get_plc("M374", plc_repair_mode);
        if (plc_repair_mode == 1)
        {
            if (last_plc_repair_mode == 0)
            {
                if (baojitai_logger_)
                    baojitai_logger_->log(Logger::kLogLevelInfo, "M374",  to_string(0) + "->" + to_string(1));
                set_repair_mode(true);
            }
        }
        else
        {
            if (last_plc_repair_mode == 1)
            {
                if (baojitai_logger_)
                    baojitai_logger_->log(Logger::kLogLevelInfo, "M374",  to_string(1) + "->" + to_string(0));
                set_repair_mode(false);
            }
        }
        last_plc_repair_mode = plc_repair_mode;

        // 初始化/复位
        // M239
        int plc_reset;
        get_plc("M239", plc_reset);
        if (plc_reset == 1 && last_plc_reset == 0)
        {
            emit signal_reset();
        }
        last_plc_reset = plc_reset;
    }

    QTimer::singleShot(250, this, SLOT(on_timer_check_fid_board_leaving()));
}

void Baojitai::reset()
{
    wait_fid_send_ = false;
    //is_waiting_fid_ = false;
    tid_ = "";
    new_tid_ = "";
    sn_ = "";
    new_sn_ = "";
    fid_ = "";
    try_sending_undo();
    if (robotic_tcp_server_)
        robotic_tcp_server_->kick_robotic();
    emit signal_plc_reset();
}

void Baojitai::repair_mode_reset()
{
    wait_fid_send_ = false;
    //is_waiting_fid_ = false;
    tid_ = "";
    new_tid_ = "";
    sn_ = "";
    new_sn_ = "";
    fid_ = "";
    try_sending_undo();
    if (robotic_tcp_server_)
        robotic_tcp_server_->kick_robotic();
    emit signal_plc_reset();
}

void Baojitai::on_signal_reset()
{
    if (repair_mode_)
    {
        reset();
    }
    else
    {
        repair_mode_reset();;
    }
}

void Baojitai::on_signal_check_fid_board_leaving()
{
    QTimer::singleShot(200, this, SLOT(on_timer_check_fid_board_leaving()));
}

void Baojitai::on_signal_check_plc_camera_control()
{
    QTimer::singleShot(100, this, SLOT(on_timer_check_plc_camera_control()));
}

void Baojitai::on_signal_repair_mode_send_sn()
{
    if (baojitai_logger_)
        baojitai_logger_->log(Logger::kLogLevelInfo, "repair mode on signal send sn");

    if (wait_fid_send_)
    {
        emit signal_product_info("sn wait fid");
        new_sn_ = sn_;
    }
    else
    {
        emit signal_product_info("wait fid send: true");
        wait_fid_send_ = true;
        QTimer::singleShot(100, this, SLOT(on_timer_try_sending_sn()));
    }
}

void Baojitai::on_signal_send_fid(SerialPort *sp)
{
    send_fid(sp);
}

void Baojitai::on_signal_send_tid(SerialPort* sp)
{
    if (baojitai_logger_)
        baojitai_logger_->log(Logger::kLogLevelInfo, "on signal send tid");
    qDebug() << "on_signal_send_tid" << endl;
	if (!sp || tid_.length() == 0)        return;

    bool close_tid = is_close_tid();
    if (!close_tid)
    {
        if (baojitai_logger_)
            baojitai_logger_->log(Logger::kLogLevelInfo, "set plc M60");
        set_plc("M60", 1);
        QThread::msleep(10);
        set_plc("D1000", 10);
        if (baojitai_logger_)
            baojitai_logger_->log(Logger::kLogLevelInfo, "after set plc M60");
        qDebug() << "set M60 1" << endl;
        QThread::msleep(30);
        int flag;
        plc_act_utl_->GetDevice("M60", flag);
        QThread::msleep(10);
        int flag_b;
        plc_act_utl_->GetDevice("D1000", flag_b);
        qDebug() << "M60 2" << to_string(flag).c_str() << endl;
        while (flag != 0 || flag_b != 0)
        {
            if (baojitai_logger_)
                baojitai_logger_->log(Logger::kLogLevelInfo, "M60 != 0 || D1000 != 0");
            plc_act_utl_->GetDevice("M60", flag);
            plc_act_utl_->GetDevice("D1000", flag_b);
        }
        sp->writeline(tid_.c_str(), tid_.length());
        QThread::msleep(400);
        if (baojitai_logger_)
            baojitai_logger_->log(Logger::kLogLevelInfo, "send tid", tid_);
        wait_fid_send_ = true;
        emit signal_product_info("wait fid send: true");
        emit signal_product_info((string("-> ") + tid_).c_str());

        is_tid_ok_ = false;
        QTimer::singleShot(100, this, SLOT(on_timer_check_tid_result()));
    }
}

void Baojitai::on_timer_check_tid_result()
{
    bool close_sn = is_close_sn();
    static int check_count = 0;
    qDebug() << "tid ok/ng? " << to_string(check_count ++).c_str() << endl;
    emit signal_product_info("tid ok/ng?");
	if (plc_act_utl_)
	{
		int tid_ok;
        //plc_act_utl_->GetDevice("M61", tid_ok);
        get_plc("M61", tid_ok);
		if (tid_ok == 1)
		{
			is_tid_ok_ = true;
            if (!close_sn)
                QTimer::singleShot(100, this, SLOT(on_timer_try_sending_sn()));
            emit signal_product_info("M61 tid ok");
            if (baojitai_logger_)
            {
                baojitai_logger_->log(Logger::kLogLevelInfo, "M61 tid ok");
            }
			return;
		}

		int tid_ng;
        //plc_act_utl_->GetDevice("M62", tid_ng);
        get_plc("M62", tid_ng);
		if (tid_ng == 1)
		{
            qDebug() << " tid ng" << endl;
			is_tid_ok_ = false;
            wait_fid_send_ = false;
            if (baojitai_logger_)
            {
                baojitai_logger_->log(Logger::kLogLevelInfo, "M62 tid ng");
            }
            emit signal_product_info("tid ng");
            emit signal_product_info("wait fid send: false");
            emit signal_tid_ng(tid_.c_str(), "CMC");
            try_sending_undo();
			return;
		}
	}
    QTimer::singleShot(100, this, SLOT(on_timer_check_tid_result()));
}

void Baojitai::on_timer_try_sending_sn()
{
	SerialPort* sp = NULL;
	if (repair_mode_)
	{
		sp = serial_port_repair_mode();
	}
	else
	{
		sp = serial_port_sending_code();
	}
	send_sn(sp);
}

void Baojitai::send_sn(SerialPort* sp)
{
    if (!sp || sn_.length() == 0)
        return;

    bool close_sn = is_close_sn();
    if (!close_sn)
    {
        set_plc("M63", 1);
        QThread::msleep(10);
        plc_act_utl_->SetDevice("D1100", 10);

        QThread::msleep(30);
        int flag;
        //plc_act_utl_->GetDevice("M63", flag);
        get_plc("M63", flag);
        QThread::msleep(10);
        int flag_b;
        plc_act_utl_->GetDevice("D1100", flag_b);
        //qDebug() << "M63 2" << to_string(flag).c_str() << endl;
        if (baojitai_logger_)
            baojitai_logger_->log(Logger::kLogLevelInfo, "M63 ", to_string(flag));
        while (flag != 0 || flag_b != 0)
        {
            QThread::msleep(10);
            //plc_act_utl_->GetDevice("M63", flag);
            get_plc("M63", flag);
            QThread::msleep(10);
            plc_act_utl_->GetDevice("D1100", flag_b);
            //qDebug() << "M63 3" << to_string(flag).c_str() << endl;
            if (baojitai_logger_)
                baojitai_logger_->log(Logger::kLogLevelInfo, "M63 ", to_string(flag));
        }
        if (baojitai_logger_)
            baojitai_logger_->log(Logger::kLogLevelInfo, "send sn", sn_);
        sp->writeline(sn_.c_str(), sn_.length());
        QThread::msleep(400);
        fid_cmc_socket_.clear_cmc_screen();
        emit signal_product_info((string("-> ") + sn_).c_str());
    }
    is_sn_ok_ = false;
    QTimer::singleShot(100, this, SLOT(on_timer_check_sn_result()));
}

void Baojitai::on_timer_check_sn_result()
{
    emit signal_product_info("sn ok/ng?");
    if (plc_act_utl_)
    {
        int sn_ok;
        //plc_act_utl_->GetDevice("M64", sn_ok);
        get_plc("M64", sn_ok);
        if (sn_ok == 1)
        {
            is_sn_ok_ = true;
            fid_ = "";
            emit signal_product_info("M64 sn ok");
            if (baojitai_logger_)
                baojitai_logger_->log(Logger::kLogLevelInfo, "M64 sn ok");
            this->set_plc("M30", 1);
            return;
        }

        int sn_ng;
        //plc_act_utl_->GetDevice("M65", sn_ng);
        get_plc("M65", sn_ng);
        if (sn_ng == 1)
        {
            // undo 0 发送以后再消除等 fid
            is_sn_ok_ = false;
            emit signal_product_info("M65 sn ng");
            emit signal_sn_ng(sn_.c_str(), "CMC", tid_.c_str());
            try_sending_undo();
            if (baojitai_logger_)
                baojitai_logger_->log(Logger::kLogLevelInfo, "M65 sn ng");
            return;
        }
    }
    QTimer::singleShot(100, this, SLOT(on_timer_check_sn_result()));
}

void Baojitai::on_read_fid(string fid)
{
    if (baojitai_logger_)
        baojitai_logger_->log(Logger::kLogLevelInfo, "fid ", fid);

    emit signal_product_info(string("on read fid " + fid).c_str());
    if (is_waiting_fid_)
    {
        is_waiting_fid_ = false;
        fid_ = fid;
        emit signal_product_info(string("fid " + fid).c_str());
        bool close_fid = is_close_fid();
        if (!close_fid && wait_fid_send_)
            try_sending_fid();
    }
    else
    {
//        if (receive_send_fid_)
//        {
//            fid_ = fid;
//            emit signal_product_info(string("only send fid " + fid).c_str());
//            try_sending_fid();
//        }
//        else
            emit signal_product_info(string("fid not send").c_str());
    }

    if (offline_mode_)
    {
        fid_ = fid;
         emit signal_product_info(string("offline " + fid).c_str());
         try_sending_fid();
    }

}
void Baojitai::on_waiting_fid_timeout()
{
    emit signal_product_info("fid timeout");
    if (is_waiting_fid_)
    {
        is_waiting_fid_ = false;
        fid_ = "AAAAAA";
        emit signal_product_info(string("fid " + fid_).c_str());
        bool close_fid = is_close_fid();
        if (!close_fid && wait_fid_send_)
            try_sending_fid();
        else
        {
            emit signal_product_info(string("close fid").c_str());
        }
    }
}

void Baojitai::try_sending_undo()
{
    if (!is_running())
        return;

    SerialPort* sp = NULL;
    if (repair_mode_)
    {
        sp = serial_port_repair_mode();
    }
    else
    {
        sp = serial_port_sending_code();
    }
    if (sp)
    {
        string message = "UNDO";
        sp->writeline(message.c_str(), message.length());
        emit signal_product_info((string("-> ") + message).c_str());
        //QThread::msleep(500);
        //on_timer_send_undo_postfix();
        QTimer::singleShot(100, this, SLOT(on_timer_send_undo_postfix()));
    }
}

void Baojitai::on_timer_send_undo_postfix()
{
    SerialPort* sp = NULL;
    if (repair_mode_)
    {
        sp = serial_port_repair_mode();
    }
    else
    {
        sp = serial_port_sending_code();
    }
    if (sp)
    {
        string message = "0";
        emit signal_product_info((string("-> ") + message).c_str());
        sp->writeline(message.c_str(), message.length());
        wait_fid_send_ = false;
        emit signal_product_info("wait fid send: false");
    }
}

void Baojitai::try_sending_fid()
{
    if (!is_running())
    {
        return;
    }
//    else if (!receive_send_fid_)
//    {
//        return;
//    }

    SerialPort* sp = NULL;
    if (repair_mode_)
    {
        sp = serial_port_repair_mode();
    }
    else
    {
        sp = serial_port_sending_code();
    }
    emit signal_send_fid(sp);
}

void Baojitai::send_fid(SerialPort* sp)
{
    if (!sp || fid_.length() == 0)
        return;

    if (offline_mode_ && fid_.compare("AAAAAA") != 0)
    {
        sp->writeline(fid_.c_str(), fid_.length());
        if (baojitai_logger_)
            baojitai_logger_->log(Logger::kLogLevelInfo, "send fid", fid_);
        emit signal_product_info((string("offline -> ") + fid_).c_str());
    }

    if (!offline_mode_)
    {
        set_plc("M66", 1);
        QThread::msleep(100);

        int flag;
        //plc_act_utl_->GetDevice("M66", flag);
        get_plc("M66", flag);
        while (flag != 0)
        {
            QThread::msleep(30);
            if (baojitai_logger_)
                baojitai_logger_->log(Logger::kLogLevelInfo, "M66 != 0");
            //plc_act_utl_->GetDevice("M66", flag);
            get_plc("M66", flag);
        }

        if (baojitai_logger_)
            baojitai_logger_->log(Logger::kLogLevelInfo, "send fid", fid_);
        emit signal_product_info((string("-> ") + fid_).c_str());
        sp->writeline(fid_.c_str(), fid_.length());
        QThread::msleep(400);

        is_fid_ok_ = false;
        //if (!receive_send_fid_)
        QTimer::singleShot(200, this, SLOT(on_timer_check_fid_result()));
    }
}

void Baojitai::on_receive_fid_ok_or_ng()
{
    wait_fid_send_ = false;
    emit signal_product_info("wait fid send: false");
    if (repair_mode_)
    {
        if (new_sn_.length() > 0)
        {
            qDebug() << "signal repair mode send sn" << endl;
            QThread::msleep(500);
            emit signal_repair_mode_send_sn();
            new_sn_ = "";
        }
    }
    else
    {
        if (new_tid_.length() > 0)
        {
            qDebug() << "try_sending_tid()" << endl;
            QThread::msleep(400);
            try_sending_tid();
            new_tid_ = "";
        }
    }
}

void Baojitai::on_timer_check_fid_result()
{
    //emit signal_product_info("fid ok/ng?");
    if (plc_act_utl_)
    {
        int fid_ok;
        //plc_act_utl_->GetDevice("M67", fid_ok);
        get_plc("M67", fid_ok);
        if (fid_ok == 1)
        {
            is_fid_ok_ = true;
            log_tid_sn_fid();
            emit signal_product_info("M67 fid ok");
            //set_plc("M30", 1);
            if (baojitai_logger_)
            {
                baojitai_logger_->log(Logger::kLogLevelInfo, "M67 fid ok");
            }
            on_receive_fid_ok_or_ng();
            return;
        }

        int fid_ng;
        //plc_act_utl_->GetDevice("M68", fid_ng);
        get_plc("M68", fid_ng);
        if (fid_ng == 1)
        {
            is_fid_ok_ = false;
            log_tid_sn_fid();
            emit signal_product_info("M68 fid ng");
            emit signal_fid_ng(fid_.c_str(), "CMC");
            if (baojitai_logger_)
            {
                baojitai_logger_->log(Logger::kLogLevelInfo, "M68 fid ng");
            }
            on_receive_fid_ok_or_ng();
            return;
        }
    }
    QTimer::singleShot(100, this, SLOT(on_timer_check_fid_result()));
}

void Baojitai::log_tid_sn_fid()
{
	if (tid_sn_fid_logger_)
	{
		stringstream stream;
		stream << tid_ << "," 
			<< sn_ << "," 
            << reading_code_time_.time().toString().toStdString() << ","
			<< fid_ << ","
			<< is_fid_ok_ ? "ok" : "ng";
		tid_sn_fid_logger_->logline(stream.str());
	}
}

void Baojitai::test_emit_tid_ng(QString tid, QString reason)
{
    emit signal_tid_ng(tid, reason);
}

void Baojitai::test_emit_sn_ng(QString sn, QString reason, QString tid)
{
    emit signal_sn_ng(sn, reason, tid);
}

void Baojitai::on_serial_port_close(SerialPort* serial_port)
{
    if (baojitai_logger_)
        baojitai_logger_->log(Logger::kLogLevelInfo, serial_port->port_name(), "close");
    emit signal_serial_port_status_change(serial_port);
}

void Baojitai::on_robotic_connected(RoboticTCPServer* robotic_server)
{
    if (baojitai_logger_)
        baojitai_logger_->log(Logger::kLogLevelInfo, "机械手", "连接成功");
    if (baojitai_logger_)
        baojitai_logger_->log(Logger::kLogLevelInfo, "send to 机械手", "ok");
    robotic_server->send_command("ok", 2);
    emit signal_robotic_status_change(robotic_server);
}

void Baojitai::on_robotic_disconnected(RoboticTCPServer* robotic_server)
{
    if (baojitai_logger_)
        baojitai_logger_->log(Logger::kLogLevelInfo, "机械手", "断开连接");
    emit signal_robotic_status_change(robotic_server);
}
void Baojitai::on_robotic_command(RoboticTCPServer* robotic_server, void* data, int size)
{
    if (baojitai_logger_  && data)
        baojitai_logger_->log(Logger::kLogLevelInfo, "机械手", string((char*)data, size));
    if(size == 1 && data &&( ((char*)data)[0] == 's' || ((char*)data)[0] == 'S'))
    {   
        if (baojitai_logger_)
            baojitai_logger_->log(Logger::kLogLevelInfo, "机械手", "s/S");
        if (location_result_.find_rect && current_product_)
        {
            if (baojitai_logger_)
                baojitai_logger_->log(Logger::kLogLevelInfo, "机械手", "send data");
            float x = location_result_.x;
            float y = location_result_.y;
            halcontools::transform_point(image_to_robotic_matrix(), x, y, x, y);
            float dz = current_product_->vision_param().delta_z;
            float r = location_result_.phi;
            float s = current_product_->vision_param().delta_z_put;
            send_product_information_to_robotic(x, y, dz, r, s);
        }
        string cmd((char*)data, 1);
        emit signal_robotic_command(robotic_server, cmd.c_str());
    }

    if(size == 1 && data &&( ((char*)data)[0] == 't' || ((char*)data)[0] == 'T'))
    {
        string cmd((char*)data, 1);
        emit signal_robotic_command(robotic_server, cmd.c_str());
    }
}

void Baojitai::send_product_information_to_robotic(float x, float y, float delta_z, float rotation, float vertical_length)
{
    if (robotic_tcp_server_)
    {
        char info[512];
        memset(info, 0, sizeof(info));
        sprintf(info, "%0.2f;%0.2f;%0.2f;%0.2f;%0.2f;",
                x + robotic_x_offset_ ,
                y + robotic_y_offset_ ,
                delta_z,
                -rotation * 180 / 3.14 + robotic_rz_offset_,
                vertical_length);
        emit signal_product_info(info);
        robotic_tcp_server_ ->send_command((const char*)info, strlen(info));
        if (baojitai_logger_)
        {
            baojitai_logger_->log(Logger::kLogLevelInfo, "robot", info);
        }
    }
}

void Baojitai::connect_fid_cmc_tcp_server(string ip, int port)
{
    fid_cmc_socket_.connect_host(ip.c_str(), port);
}

void Baojitai::set_plc_act_utl(ActUtlTypeLib::ActUtlType* plc_act_utl)
{
	plc_act_utl_ = plc_act_utl;
}
void Baojitai::open_plc_act_utl()
{
	if (!plc_act_utl_)
		return;
	plc_act_utl_->SetActLogicalStationNumber(1);
	plc_act_utl_->SetActPassword("");
	int ret = plc_act_utl_->Open();
	if (ret != 0)
		plc_act_utl_ = NULL;
	emit signal_plc_status_change();
}
void Baojitai::on_fid_cmc_socket_connected(FidCMCSocket* fid_cmc_socket)
{
    emit signal_product_info("fid cmc connected");
    emit signal_fid_cmc_socket_status_change();
}
void Baojitai::on_fid_cmc_socket_disconnected(FidCMCSocket* cmc_client)
{
    emit signal_product_info("fid cmc disconnected");
    emit signal_fid_cmc_socket_status_change();
    string ip;
    int port = 0;
    read_fid_cmc_ip_port(ip, port);
    connect_fid_cmc_tcp_server(ip, port);
}
void Baojitai::on_fid_cmc_socket_read_bytes(const QByteArray& bytes)
{
    int read_count = bytes.size();
    if (read_count > 3)
    {
        string message("fid cmc read ");
        message += to_string(read_count);
        message += " bytes";
        emit signal_product_info(message.c_str());
    }
}
void Baojitai::on_fid_cmc_socket_read_fid(const string fid)
{
    if (baojitai_logger_)
        baojitai_logger_->log(Logger::kLogLevelInfo, "fid cmc socket ", fid);
    on_read_fid(fid);
}
vector<string> Baojitai::advanced_device_ip_list()
{
    return item_center_->connected_device_ip_list();
}
void Baojitai::on_advanced_device_connect(ItemInformationCenter* item_info_center, const string& ip_str)
{
    emit signal_advanced_device_count_change();
}
void Baojitai::on_advanced_device_disconnect(ItemInformationCenter* item_info_center, const string& ip_str)
{
    emit signal_advanced_device_count_change();
}
void Baojitai::on_advanced_device_item_information(const string& name, bool is_ng, const string& ng_reason)
{
    // log ?
}
void Baojitai::send_location_result_to_plc()
{
    //QThread::msleep(100);
//    if (plc_act_utl_)
//    {
//        int value = -1;
//        plc_act_utl_->GetDevice("M20", value);
//        emit signal_product_info((string("M20 value ") + to_string(value)).c_str());
//    }

	QString plc_address;
    if (location_result_.success)
		plc_address = "M20";
	else
		plc_address = "M21";
    set_plc(plc_address.toStdString(), 1);
}

void Baojitai::send_check_frame_result_to_plc()
{
    QString plc_address;
    if (check_frame_result_.is_disk_ok)
    {
        plc_address = "M50";
    }
    else
    {
        plc_address = "M51";
    }
    set_plc(plc_address.toStdString(), 1);

    if (check_frame_result_.is_found_left || check_frame_result_.is_found_right)
    {
        plc_address = "M53";
    }
    else
    {
        plc_address = "M52";
    }
    set_plc(plc_address.toStdString(), 1);
}

string config_dir_path()
{
    QString app_dir = QCoreApplication::applicationDirPath();
    QString config_dir = QDir::cleanPath(app_dir + QDir::separator() + kConfigDirName);
    QDir dir;
    if (!dir.exists(config_dir))
        dir.mkdir(config_dir);
    return config_dir.toStdString();
}
string log_dir_path()
{
    QString app_dir = QCoreApplication::applicationDirPath();
    QString log_dir = QDir::cleanPath(app_dir + QDir::separator() + kLogDirName);
    QDir dir;
    if (!dir.exists(log_dir))
        dir.mkdir(log_dir);
    return log_dir.toStdString();
}
string data_dir_path()
{
    QString app_dir = QCoreApplication::applicationDirPath();
    QString data_dir = QDir::cleanPath(app_dir + QDir::separator() + kDataDirName);
    QDir dir;
    if (!dir.exists(data_dir))
        dir.mkdir(data_dir);
    return data_dir.toStdString();
}
string yyyyMMdd_hhmmss_xxx(QDateTime& datetime)
{
    QDate date = datetime.date();
    int year = date.year();
    int month = date.month();
    int day = date.day();
    // 20190931
    QString yyyyMMdd = QString().sprintf("%04d%02d%02d", year, month, day);
    QTime time = datetime.time();
    int hour = time.hour();
    int minute = time.minute();
    int second = time.second();
    QString hhmmss = QString().sprintf("%02d%02d%02d", hour, minute, second);
    int millisecond = time.msec();
    QString xxx = QString().sprintf("%03d", millisecond);
    return (yyyyMMdd + "_" + hhmmss + "_" + xxx).toStdString();
}
string yyyyMMdd_hhmmss_xxx_location_bmp(QDateTime& datetime)
{
    string yyyyMMdd_hhmmss_xxx_str = yyyyMMdd_hhmmss_xxx(datetime);
    return yyyyMMdd_hhmmss_xxx_str + "_p.bmp";
}
string yyyyMMdd_hhmmss_xxx_location_NG_bmp(QDateTime& datetime)
{
    string yyyyMMdd_hhmmss_xxx_str = yyyyMMdd_hhmmss_xxx(datetime);
    return yyyyMMdd_hhmmss_xxx_str + "_p_NG.bmp";
}
string yyyyMMdd_hhmmss_xxx_reading_code_bmp(QDateTime& datetime)
{
    string yyyyMMdd_hhmmss_xxx_str = yyyyMMdd_hhmmss_xxx(datetime);
    return yyyyMMdd_hhmmss_xxx_str + "_c.bmp";
}
string yyyyMMdd_hhmmss_xxx_reading_code_NG_bmp(QDateTime& datetime)
{
    string yyyyMMdd_hhmmss_xxx_str = yyyyMMdd_hhmmss_xxx(datetime);
    return yyyyMMdd_hhmmss_xxx_str + "_c_NG.bmp";
}
string yyyyMMdd_hhmmss_xxx_check_frame_bmp(QDateTime& datetime)
{
    string yyyyMMdd_hhmmss_xxx_str = yyyyMMdd_hhmmss_xxx(datetime);
    return yyyyMMdd_hhmmss_xxx_str + "_f.bmp";
}
string yyyyMMdd_hhmmss_xxx_check_frame_NG_bmp(QDateTime& datetime)
{
    string yyyyMMdd_hhmmss_xxx_str = yyyyMMdd_hhmmss_xxx(datetime);
    return yyyyMMdd_hhmmss_xxx_str + "_f_NG.bmp";
}
