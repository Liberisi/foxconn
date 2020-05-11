#include "product.h"
#include <QDir>
#include <opencv2\opencv.hpp>
#include <ssvision/ssvision>
#include "baojitai.h"

static Product* current_product;

ProductManager* ProductManager::instance()
{
    static ProductManager* manager = nullptr;
    if (!manager)
    {
        manager = new ProductManager();
    }
    return manager;
}

ProductManager::ProductManager()
{

}

vector<string> ProductManager::product_name_list()
{
    vector<string> xml_name_list;
    QDir dir(product_dir_path_.c_str());
	dir.mkpath(".");
    QStringList images = dir.entryList(QStringList() << "*.xml" << "*.XML", QDir::Files);
    foreach(QString filename, images)
    {
		filename.truncate(filename.lastIndexOf("."));
        xml_name_list.push_back(filename.toStdString());
    }
    return xml_name_list;
}

string ProductManager::product_config_path(const string& product_name)
{
    QString product_dir(product_dir_path_.c_str());
    QChar sep = QDir::separator();
    QString file_name = QString((product_name + ".xml").c_str());
    QString filepath = product_dir + sep + file_name;
    return filepath.toStdString();
}

Product* ProductManager::create_product(const string& product_name)
{
    string product_file_path = product_config_path(product_name);
    QFileInfo file_info(product_file_path.c_str());
    if (file_info.exists())
    {
        Product* product = new Product(product_name);
        if (product)
            product->load_config(product_file_path);
        return product;
    }
    return NULL;
}

void ProductManager::remove_product(const string& product_name)
{
    string product_file_path = product_config_path(product_name);
    QFile product_file(product_file_path.c_str());
    if (product_file.exists())
        product_file.remove();
}

void ProductManager::set_product_dir_path(string dir_path)
{
	product_dir_path_ = dir_path;
}


static const char* const kProductKeyMetricParam = "metric";
static const char* const kProductKeyVisionParam = "vision";
static const char* const kProductKeyCodeParam = "code";

static void ProductReadFileStorage(Product* product, cv::FileStorage& fs);
static void ProductWriteFileStorage(Product* product, cv::FileStorage& fs);

void Product::load_config(const string& config_path)
{
    cv::FileStorage fs(config_path, cv::FileStorage::READ | cv::FileStorage::FORMAT_XML);
    ProductReadFileStorage(this, fs);
	saved_ = true;
}

void Product::save_config(const string& config_path)
{
    cv::FileStorage fs(config_path, cv::FileStorage::WRITE | cv::FileStorage::FORMAT_XML);
    ProductWriteFileStorage(this, fs);
	saved_ = true;
}

void Product::set_metric_param(MetricParam metric_param)
{
	metric_param_ = metric_param;
	saved_ = false;
}

void Product::set_vision_param(VisionParam vision_param)
{
	vision_param_ = vision_param;
	saved_ = false;
}

void Product::set_code_param(DataCodeParam code_param)
{
	code_param_ = code_param;
	saved_ = false;
}

void ProductWriteFileStorage(Product* product, cv::FileStorage& fs)
{
    fs << kProductKeyMetricParam << product->metric_param();
    fs << kProductKeyVisionParam << product->vision_param();
    fs << kProductKeyCodeParam << product->data_code_param();
}

void ProductReadFileStorage(Product* product, cv::FileStorage& fs)
{
	Product::MetricParam metrix_param;
	fs[kProductKeyMetricParam] >> metrix_param;
	product->set_metric_param(metrix_param);

	Product::VisionParam vision_param;
	fs[kProductKeyVisionParam] >> vision_param;
	product->set_vision_param(vision_param);

	Product::DataCodeParam code_param;
	fs[kProductKeyCodeParam] >> code_param;
	product->set_code_param(code_param);
}

static inline void write(cv::FileStorage& fs, const std::string&, const Product::MetricParam& metric_param)
{
    fs << "{";
    fs << "scale" << metric_param.scale;
    fs << "tolerance_band" << metric_param.tolerance_band;
    fs << "long_side" << metric_param.long_side;
    fs << "short_side" << metric_param.short_side;
    fs << "}";
}
static inline void read(const cv::FileNode& node, Product::MetricParam& metric_param, const Product::MetricParam& default_value = Product::MetricParam())
{
    if (node.empty())
        metric_param = default_value;
    else
    {
        node["scale"] >> metric_param.scale;
        node["tolerance_band"] >> metric_param.tolerance_band;
        node["long_side"] >> metric_param.long_side;
        node["short_side"] >> metric_param.short_side;
    }
}
static inline void write(cv::FileStorage& fs, const std::string&, const Product::VisionParam& vision_param)
{
    fs << "{";
    fs << "th_min" << vision_param.th_min;
    fs << "th_max" << vision_param.th_max;
    fs << "area_min" << vision_param.area_min;
    fs << "area_max" << vision_param.area_max;
    fs << "siga" << vision_param.siga;
    fs << "l1" << vision_param.l1;
    fs << "l2" << vision_param.l2;
    fs << "xl1" << vision_param.xl1;
    fs << "xl2" << vision_param.xl2;
    fs << "delta_z" << vision_param.delta_z;
    fs << "angle_r1" << vision_param.angle_r1;
    fs << "angle_c1" << vision_param.angle_c1;
    fs << "angle_r2" << vision_param.angle_r2;
    fs << "angle_c2" << vision_param.angle_c2;
    fs << "delta_z_put" << vision_param.delta_z_put;
    fs << "x_offset" << vision_param.x_offset;
    fs << "y_offset" << vision_param.y_offset;
    fs << "z_offset" << vision_param.z_offset;
    fs << "location_exposure_time" << vision_param.location_exposure_time;
    fs << "read_code_exposure_time" << vision_param.read_code_exposure_time;
    fs << "frame_exposure_time" << vision_param.frame_exposure_time;
    fs << "black_region_threshold" << vision_param.black_region_threshold;
    fs << "}";
}
static inline void read(const cv::FileNode& node, Product::VisionParam& vision_param, const Product::VisionParam& default_value = Product::VisionParam())
{
    if (node.empty())
        vision_param = default_value;
    else
    {
        node["th_min"] >> vision_param.th_min;
        node["th_max"] >> vision_param.th_max;
        node["area_min"] >> vision_param.area_min;
        node["area_max"] >> vision_param.area_max;
        node["siga"] >> vision_param.siga;
        int l1;
        node["l1"] >> l1;
        vision_param.l1 = l1;
        node["l2"] >> vision_param.l2;
        node["xl1"] >> vision_param.xl1;
        node["xl2"] >> vision_param.xl2;
        node["delta_z"] >> vision_param.delta_z;
        node["angle_r1"] >> vision_param.angle_r1;
        node["angle_c1"] >> vision_param.angle_c1;
        node["angle_r2"] >> vision_param.angle_r2;
        node["angle_c2"] >> vision_param.angle_c2;
        node["delta_z_put"] >> vision_param.delta_z_put;
        node["x_offset"] >> vision_param.x_offset;
        node["y_offset"] >> vision_param.y_offset;
        node["z_offset"] >> vision_param.z_offset;
        node["location_exposure_time"] >> vision_param.location_exposure_time;
        node["read_code_exposure_time"] >> vision_param.read_code_exposure_time;
        node["frame_exposure_time"] >> vision_param.frame_exposure_time;
        node["black_region_threshold"] >> vision_param.black_region_threshold;
    }
}
static inline void write(cv::FileStorage& fs, const std::string&, const Product::DataCodeParam& code_param)
{
    fs << "{";
	
	string product_mat_code_type = "";
	if (code_param.product_mat_code_type)
		product_mat_code_type = string(code_param.product_mat_code_type);
	fs << "product_mat_code_type" << product_mat_code_type;
	
	string product_bar_code_type = "";
	if (code_param.product_bar_code_type)
		product_bar_code_type = string(code_param.product_bar_code_type);
	fs << "product_bar_code_type" << product_bar_code_type;
    
	fs << "board_bar_code_type" << string(code_param.board_bar_code_type);
    fs << "product_code_length" << code_param.product_code_length;
	fs << "board_code_length" << code_param.board_code_length;
	Product::DataCodeParam param = code_param;
	fs << "board_code_prefix" << param.board_code_prefix();
    fs << "use_product_code" << code_param.use_product_code;
	fs << "use_board_code" << code_param.use_board_code;
    fs << "}";
}
static inline void read(const cv::FileNode& node, Product::DataCodeParam& code_param, const Product::DataCodeParam& default_value = Product::DataCodeParam())
{
    if (node.empty())
        code_param = default_value;
    else
    {
        code_param.product_mat_code_type = NULL;
        string product_mat_code_type;
        node["product_mat_code_type"] >> product_mat_code_type;
        if (product_mat_code_type.length() > 0)
        {
            if (product_mat_code_type.compare(string(ssvision::k2DCodeDataMatrixECC200)) == 0)
                code_param.product_mat_code_type = ssvision::k2DCodeDataMatrixECC200;
        }

        code_param.product_bar_code_type = NULL;
        string product_bar_code_type;
        node["product_bar_code_type"] >> product_bar_code_type;
        if (product_bar_code_type.length() > 0)
        {
            if (product_bar_code_type.compare(string(ssvision::kBarCodeCode128)) == 0)
                code_param.product_bar_code_type = ssvision::kBarCodeCode128;
        }

        string DM_name;
        node["board_bar_code_type"] >> DM_name;
        if (DM_name.compare(string(ssvision::kBarCodeCode128)) == 0)
			code_param.board_bar_code_type = ssvision::kBarCodeCode128;
        node["product_code_length"] >> code_param.product_code_length;
		node["board_code_length"] >> code_param.board_code_length;
        string board_code_prefix;
        node["board_code_prefix"] >> board_code_prefix;
		code_param.set_board_code_prefix(board_code_prefix);
        node["use_product_code"] >> code_param.use_product_code;
		node["use_board_code"] >> code_param.use_board_code;
    }
}
