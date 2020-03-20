#include "msleepsetting.h"

#include <string>
#include <fstream>
#include <sstream>

using namespace std;

MsleepSetting::MsleepSetting()
{

}


void MsleepSetting::read_param(const string& path)
{
    ifstream file(path);
    if (!file.is_open())
        return;

    string line;

    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> tid_msleep_time_;
    }
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> sn_msleep_time_;
    }
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> fid_singleslot_time_;
    }
}

void MsleepSetting::write_param(const string& path)
{
    ofstream file(path);
    file << tid_msleep_time_ << endl
         << sn_msleep_time_ << endl
         << fid_singleslot_time_ << endl;
}

void MsleepSetting::set_tid_msleep_time(int tid_msleep_time)
{
    tid_msleep_time_ = tid_msleep_time;
}
void MsleepSetting::set_sn_msleep_time(int sn_msleep_time)
{
    sn_msleep_time_ = sn_msleep_time;
}
void MsleepSetting::set_fid_singleslot_time(int fid_singleslot_time)
{
    fid_singleslot_time_ = fid_singleslot_time;
}
