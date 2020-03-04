#include "serial_port_manager.h"

#include <fstream>
#include <sstream>
#include <QDir>
#include <QFileInfo>

SerialPortManager* SerialPortManager::instance()
{
    static SerialPortManager* serial_port_manager = NULL;
    if (!serial_port_manager)
    {
        serial_port_manager = new SerialPortManager();
    }
    return serial_port_manager;
}

SerialPortManager::SerialPortManager()
{

}

void SerialPortManager::set_config_dir_path(string dir_path)
{
    config_dir_path_ = dir_path;
}

SerialPort* SerialPortManager::create_serial_port(const string& config_file_name)
{
    QString config_file_path = QDir::cleanPath(QString(config_dir_path_.c_str()) + QDir::separator() + config_file_name.c_str());
    QFileInfo file_info(config_file_path);
    if (file_info.exists())
    {
        string port_name;
        int baud_rate = 0;
        int character_bits = 0;
        ifstream config_file(config_file_path.toStdString());
        string line;
        if (getline(config_file, line))
        {
            stringstream ss(line);
            ss >> port_name;
        }
        if (getline(config_file, line))
        {
            stringstream ss(line);
            ss >> baud_rate;
        }
        if (getline(config_file, line))
        {
            stringstream ss(line);
            ss >> character_bits;
        }
        if (port_name.length() > 0)
        {
            QtSerialPort* serial_port = new QtSerialPort(port_name);
            serial_port->set_baud_rate(baud_rate);
            serial_port->set_character_bits(character_bits);
            return serial_port;
        }
    }
    return NULL;
}

void SerialPortManager::save_serial_port_config(SerialPort* sp, const string& config_file_name)
{
    if (!sp || config_file_name.length() == 0)
        return;
    QString config_file_path = QDir::cleanPath(QString(config_dir_path_.c_str()) + QDir::separator() + config_file_name.c_str());
    if (sp->port_name().length() > 0)
    {
        ofstream config_file(config_file_path.toStdString());
        config_file << sp->port_name() << endl
                    << sp->baud_rate() << endl
                    << sp->character_bits() << endl;

    }
}
