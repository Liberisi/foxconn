/**
 * 读到3个0
 * 发第一个码, 发送完之后，需要读取plc第一个1，如果timeout则再次发送。然后再次读取plc第一个1，如果timeout则再次发送。再次发送次数可配置。
 *
 * 读完码，发送给
 *
 * 1 正常模式
 *
 * 2 离线模式（视觉不管, 关机）
 *
 * 3 返修模式 （每次都从plc读取上传哪几个码)
 *
 * 4 手动模式
 *
 * 三个 D 地址
 * 定位NG
 * 条码超视野
 * 条码NG
 * 二维码超视野
 * 二维码NG
 * 支架NG
 *
 * 二维码的 长度， 起始字符串
 *
 * 图片保存，
 * 磁盘快满的时候从前往后删除
  */

#ifndef QTSERIALPORT_H
#define QTSERIALPORT_H

#include "serialport.h"
#include <string>
#include <vector>
#include <QSerialPort>

using namespace std;

namespace ssvision {

class QtSerialPort : public QObject, public SerialPort
{
//public:
//    Q_OBJECT

public:
    static vector<string> serial_port_list();
    static vector<int> baud_rate_list();
    static vector<int> character_bits_list();

    virtual bool set_baud_rate(int baud_rate);
    // always return true
    virtual bool set_character_bits(int character_bits);
    // always return true
    virtual bool set_parity(Parity parity);

    virtual bool open();
    virtual bool is_open();
	virtual void close();

    virtual int writeline(const char* data, int length);

public:
    QtSerialPort(string port_name);
    virtual ~QtSerialPort();

//signals:
    //void readyRead(QString);

private:
    QSerialPort qt_serial_port_;

    void readyRead_slot();
};

}

#endif // QTSERIALPORT_H
