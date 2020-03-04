#include "saveconfig.h"
#include <opencv2/opencv.hpp>
#include <ssvision/ssvision>


static const char* const kSaveConfigSetting = "setting";

static void SaveConfigReadFileStorage(SaveConfig* setting, cv::FileStorage& fs);
static void SaveConfigWriteFileStorage(SaveConfig* setting, cv::FileStorage& fs);



void SaveConfig::load_config(const string& config_path)
{
    cv::FileStorage fs(config_path, cv::FileStorage::READ | cv::FileStorage::FORMAT_XML);
    SaveConfigReadFileStorage(this, fs);
}

void SaveConfig::save_config(const string& config_path)
{
    cv::FileStorage fs(config_path, cv::FileStorage::WRITE | cv::FileStorage::FORMAT_XML);
    SaveConfigWriteFileStorage(this, fs);
}

void SaveConfigWriteFileStorage(SaveConfig* setting, cv::FileStorage& fs)
{
    fs << kSaveConfigSetting << setting->setting_config;
}

void SaveConfigReadFileStorage(SaveConfig* setting, cv::FileStorage& fs)
{
    fs[kSaveConfigSetting] >> setting->setting_config;
}

static inline void write(cv::FileStorage& fs, const std::string&, const SaveConfig::Setting& setting_config)
{
    fs << "{";
    fs << "save_ng" << setting_config.save_ng;
    fs << "save_ngthumb" << setting_config.save_ngthumb;
    fs << "save_ok" << setting_config.save_ok;
    fs << "save_okthumb" << setting_config.save_okthumb;
    fs << "open_sizelimit" << setting_config.open_sizelimit;
    fs << "}";
}
static inline void read(const cv::FileNode& node, SaveConfig::Setting& setting_config, const SaveConfig::Setting& default_value = SaveConfig::Setting())
{
    if (node.empty())
        setting_config = default_value;
    else
    {
        node["save_ng"] >> setting_config.save_ng;
        node["save_ngthumb"] >> setting_config.save_ngthumb;
        node["save_ok"] >> setting_config.save_ok;
        node["save_okthumb"] >> setting_config.save_okthumb;
        node["open_sizelimit"] >> setting_config.open_sizelimit;
    }
}
