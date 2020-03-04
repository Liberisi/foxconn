#include "serialport.h"
#include "logger.h"

namespace ssvision {

SerialPort::SerialPort(string port_name):serial_port_delegate_(nullptr)
{
    port_name_ = port_name;
    baud_rate_ = 0;
    character_bits_ = 0;
    parity_ = SerialPort::kParityNoParity;
}

void SerialPort::set_delegate(SerialPortDelegate* serial_port_delegate)
{
    serial_port_delegate_ = serial_port_delegate;
}

bool SerialPort::set_baud_rate(int baud_rate)
{
       baud_rate_ = baud_rate;
       return true;
}

bool SerialPort::set_character_bits(int character_bits)
{
    character_bits_ = character_bits;
    return true;
}

bool SerialPort::set_parity(Parity parity)
{
    parity_ = parity;
    return true;
}

}
