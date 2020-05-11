#ifndef PRODUCT_H
#define PRODUCT_H

/**
<?xml version="1.0" encoding="UTF-8"?>

-<参数设置>
-<参数设置>
<TH_MIN>0</TH_MIN>
<TH_MAX>110</TH_MAX>
<AREA_MIN>259999</AREA_MIN>
<AREA_MAX>699999</AREA_MAX>
<SIGA>5</SIGA>
<L1>100</L1>
<L2>100</L2>
<X_L1>150</X_L1>
<X_L2>100</X_L2>
<z向补偿>5.00</z向补偿>
<角R1>495.222319859402</角R1>
<角C1>58.3126094570928</角C1>
<角R2>1841.00439367311</角R2>
<角C2>2232.88704028021</角C2>
<z向补偿放>-5</z向补偿放>
</参数设置>
</参数设置>

-<数据端口>
-<数据端口>
<端口号>COM2</端口号>
<波特率>9600</波特率>
<数据位>8</数据位>
<端口号2>COM1</端口号2>
<波特率2>9600</波特率2>
<数据位2>8</数据位2>
</数据端口>
</数据端口>

-<读码参数>
-<读码参数>
<QR>Data Matrix ECC 200</QR>
<DM>Code 128</DM>
<数据位1>6</数据位1>
<数据位2>10</数据位2>
<解码个数>2</解码个数>
<启用二维码>F</启用二维码>
</读码参数>
</读码参数>

-<比例尺>
-<比例尺>
<BL>0.338</BL>
<公差带>5</公差带>
<长边>441</长边>
<宽边>277</宽边>
</比例尺>
</比例尺>

*/

#include <string>
#include <vector>
#include <ssvision/ssvision>

using namespace std;

/**
  * ProductManager 类并不读写Product配置文件
  * ProductMnaager 不会 delete current product， 如有需要，先 get current product 再 set current product null
  *
*/
class Product;
class ProductManager
{
public:
    static ProductManager* instance();

private:
    ProductManager();

public:
    void set_product_dir_path(string dir_path);
    vector<string> product_name_list();
    string product_config_path(const string& product_name);
    Product* create_product(const string& product_name);
    void remove_product(const string& product_name);

private:
    string product_dir_path_;
};

class Product
{
public:
	typedef struct MetricParam
	{
		float scale;            // 缩放比例
		float tolerance_band;   // 公差带
		float long_side;        // 长边
		float short_side;       // 宽边
		MetricParam()
		{
			scale = 1;
			tolerance_band = 10;
			long_side = 400;
			long_side = 300;
		};
	} MetricParam;              // 尺寸参数

	typedef struct DataCodeParam
	{
        const char* product_mat_code_type;
        const char* product_bar_code_type;
        const char* board_bar_code_type;
        int product_code_length;
		int board_code_length;
        bool use_product_code;
		bool use_board_code;
        char bar_code_prefix[10];
		DataCodeParam()
		{
            use_product_code = true;
            product_code_length = 10;
            product_mat_code_type = ssvision::k2DCodeDataMatrixECC200;
            product_bar_code_type = NULL;

            use_board_code = true;
			board_bar_code_type = ssvision::kBarCodeCode128;
            board_code_length = 6;

            memset(bar_code_prefix, 0, sizeof(bar_code_prefix));
		}
        int board_code_prefix_length_max()
        {
            return sizeof(bar_code_prefix)/sizeof(bar_code_prefix[0]);
        }
        string board_code_prefix()
        {
            int length_max = board_code_prefix_length_max();
            return string(bar_code_prefix, length_max);
        }
        void set_board_code_prefix(string prefix)
        {
            int length_max = board_code_prefix_length_max();
            int prefix_length = prefix.length();
            prefix_length = prefix_length > length_max ? length_max : prefix_length;
            for (int i = 0; i < prefix_length; ++i)
            {
                bar_code_prefix[i] = prefix[i];
            }
			for (int i = prefix_length; i < length_max; i++)
			{
				bar_code_prefix[i] = 0;
			}
        }
	} DataCodeParam;            // 读码参数

	typedef struct VisionParam
	{
		int th_min;             //<TH_MIN>0</TH_MIN>
		int th_max;             //<TH_MAX>110</TH_MAX>
		int area_min;           //<AREA_MIN>259999</AREA_MIN>
		int area_max;           //<AREA_MAX>699999</AREA_MAX>
		int siga;               //<SIGA>5</SIGA>
		int l1;                 //<L1>100</L1>
		int l2;                 //<L2>100</L2>
		int xl1;                //<X_L1>150</X_L1>
		int xl2;                //<X_L2>100</X_L2>
		int delta_z;            //<z向补偿>5.00</z向补偿>
		int angle_r1;           //    <角R1>495.222319859402</角R1>
		int angle_c1;           //    <角C1>58.3126094570928</角C1>
		int angle_r2;           //        <角R2>1841.00439367311</角R2>
		int angle_c2;           //        <角C2>2232.88704028021</角C2>
		int delta_z_put;        //        <z向补偿放>-5</z向补偿放>
        int x_offset;           //  
        int y_offset;
        int z_offset;
        int location_exposure_time;  //定位曝光
        int read_code_exposure_time;  //读码曝光
        int frame_exposure_time;   //支架曝光
        int black_region_threshold;   //图像阈值分割
		VisionParam()
		{
			th_min = 0;
			th_max = 0;
			area_min = 0;
			area_max = 0;
			siga = 0;
			l1 = 0;
			l2 = 0;
			xl1 = 0;
			xl2 = 0;
			delta_z = 0;
			angle_r1 = 0;
			angle_c1 = 0;
			angle_r2 = 0;
			angle_c2 = 0;
			delta_z_put = 0;
            x_offset = 0;
            y_offset = 0;
            z_offset = 0;
            location_exposure_time = 35000;
            read_code_exposure_time = 35000;
            frame_exposure_time = 35000;
            black_region_threshold = 128;
		}
	} VisionParam;              // 视觉检测参数

public:
    Product(string name) : name_(name), saved_(false){}
	~Product(){}

	string name() { return name_; }
	bool is_saved() { return saved_; }
	void load_config(const string& config_path);
	void save_config(const string& config_path);
	MetricParam metric_param(){ return metric_param_; }
	VisionParam vision_param(){ return vision_param_; }
	DataCodeParam data_code_param() { return code_param_; }
	void set_metric_param(MetricParam metric_param);
	void set_vision_param(VisionParam vision_param);
	void set_code_param(DataCodeParam code_param);

protected:
    MetricParam metric_param_;
    VisionParam vision_param_;
    DataCodeParam code_param_;
    string name_;
	bool saved_;
};

#endif // PRODUCT_H
