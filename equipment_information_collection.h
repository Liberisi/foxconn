#ifndef EQUIPMENT_INFORMATION_COLLECTION_H
#define EQUIPMENT_INFORMATION_COLLECTION_H


class Equipment_Information_Collection
{
public:
    Equipment_Information_Collection();



#include <string>
#include <vector>
#include <ssvision/ssvision>

using namespace std;

/**
  * ProductManager 类并不读写Product配置文件
  * ProductMnaager 不会 delete current product， 如有需要，先 get current product 再 set current product null
  *
*/
class Equipment_Information_Collection;
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

class Equipment_Information_Collection
{
public:
    typedef struct important_parameter
    {
        float scale;            // 缩放比例
        float tolerance_band;   // 公差带
        float long_side;        // 长边
        float short_side;       // 宽边
        important_parameter()
        {
            scale = 1;
            tolerance_band = 10;
            long_side = 400;
            long_side = 300;
        }
    } important_parameter;              // 主要 参数

    typedef struct badID
    {

        badID()
        {

        }
    } badID;            // 故障代码参数

    typedef struct maintenance
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

        maintenance()
        {

        }
    } maintenance;              // 设备维护参数

    typedef struct alarm
    {
        alarm()
        {

        }
    }alarm;

    typedef struct productionSys
    {

        productionSys()
        {

        }
    }productionSys;

    typedef struct alarmtimerlist
    {
        alarmtimerlist()
        {

        }
    }alarmtimerlist;

    typedef struct badtimerlist
    {
        badtimerlist()
        {

        }
    }badtimerlist;



public:
    Product(string name) : name_(name), saved_(false){}
    ~Product(){}

    string name() { return name_; }
    bool is_saved() { return saved_; }
    void load_config(const string& config_path);
    void save_config(const string& config_path);
    Important_parameter important_parameter(){ return important_parameter_; }
    VisionParam badID(){ return badID_; }
    Maintenance maintenance() { return maintenance_; }
    void set_metric_param(MetricParam metric_param);
    void set_vision_param(VisionParam vision_param);
    void set_code_param(DataCodeParam code_param);

protected:
    Important_parameter important_parameter_;
    BadID badID_;
    Maintenance maintenance_;
    string name_;
    bool saved_;
};

};



#endif // EQUIPMENT_INFORMATION_COLLECTION_H
