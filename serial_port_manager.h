#ifndef SERIALPORTMANAGER_H
#define SERIALPORTMANAGER_H

#include <ssvision/ssvision>

using namespace ssvision;

class SerialPortManager
{
public:
    static SerialPortManager* instance();

private:
    SerialPortManager();

public:
    void set_config_dir_path(string dir_path);
    SerialPort* create_serial_port(const string& config_file_name);
    void save_serial_port_config(SerialPort* sp, const string& config_file_name);

private:
    string config_dir_path_;
};

#endif // SERIALPORTMANAGER_H
