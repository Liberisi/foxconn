#ifndef MSLEEPSETTING_H
#define MSLEEPSETTING_H

#include<string>

using namespace std;
class MsleepSetting
{
public:
    MsleepSetting();

    void read_param(const string& path);
    void write_param(const string& path);

    void set_tid_msleep_time(int tid_msleep_time);
    void set_sn_msleep_time(int sn_msleep_time);
    void set_fid_singleslot_time(int fid_singleslot_time);

    int tid_msleep_time() {return tid_msleep_time_;}
    int sn_msleep_time() {return sn_msleep_time_;}
    int fid_singleslot_time() {return fid_singleslot_time_;}

private:
    int tid_msleep_time_;
    int sn_msleep_time_;
    int fid_singleslot_time_;

};
#endif // MSLEEPSETTING_H
