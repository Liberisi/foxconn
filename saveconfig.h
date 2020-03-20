#ifndef SAVECONFIG_H
#define SAVECONFIG_H

#include <string>

using namespace std;

class SaveConfig
{
public:
    typedef struct
    {
    bool save_ng;
    bool save_ngthumb;
    bool save_ok;
    bool save_okthumb;
    bool open_sizelimit;
    }Setting;

public:
    SaveConfig(string name) : name_(name){}
    ~SaveConfig(){}

    string name() {return name_;}
    void load_config(const string& config_path);
    void save_config(const string& config_path);

public:

    Setting setting_config;

private:
    string name_;
};
#endif // SAVECONFIG_H
