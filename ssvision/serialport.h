#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <string>
#include <map>

using namespace std;

namespace ssvision {

class SerialPort;
class SerialPortDelegate
{
public:
    virtual void on_serial_port_open(SerialPort* serial_port) = NULL;
    virtual void on_serial_port_close(SerialPort* serial_port) = NULL;
    virtual void on_serial_port_read(SerialPort* serial_port, const char* data, int size) = NULL;
};

class SerialPort
{
public:
    typedef enum {
        kBaudRate_1200,
        kBaudRate_2400,
        kBaudRate_4800,
        kBaudRate_9600,
        kBaudRate_19200,
        kBaudRate_38400,
        kBaudRate_57600,
        kBaudRate_115200,
        kBaudRateUnknown,
    } BaudRate;
    typedef enum {
        kCharacterBits_5,
        kCharacterBits_6,
        kCharacterBits_7,
        kCharacterBits_8,
        kCharacterBitsUnknown,
    } CharacterBits;
    typedef enum {
        kParityNoParity,
        kParityEvenParity,
        kParityOddParity,
        kParitySpaceParity,
        kParityMarkParity,
        kParityUnknown,
    } Parity;

protected:
    SerialPort(string port_name);
public:
    virtual ~SerialPort(){}

public:
    string port_name(){ return port_name_;}

	// 弱引用，用户自己管理 delegate
    void set_delegate(SerialPortDelegate* serial_port_delegate);
    
    virtual bool set_baud_rate(int baud_rate);
    int baud_rate(){return baud_rate_;} // 关闭返回 0
    virtual bool set_character_bits(int character_bits);
    int character_bits() {return character_bits_;}// 关闭返回 0
    virtual bool set_parity(Parity parity);
    Parity parity();// 关闭返回 unknown

    virtual bool open(){return false;}
    virtual bool is_open(){ return false; }
    virtual void close(){}
    virtual int writeline(const char*, int){ return 0; }
    virtual int read(const char*,int){return 0;}
//    bool open(BaudRate baud_rate, CharacterBits character_bits, Parity parity);
//    void close();
//    virtual bool sync_send(void* data, int length);
//    void set_receive_callback(SerialPortReceiveCallback callback);

private:
    SerialPort(){}

protected:
    string port_name_;
    int baud_rate_;
    int character_bits_;
    Parity parity_;
    SerialPortDelegate* serial_port_delegate_;
};

}

#endif // SERIALPORT_H
