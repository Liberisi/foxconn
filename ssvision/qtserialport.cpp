#include "qtserialport.h"
#include <QDebug>
#include <QSerialPortInfo>
#include "logger.h"

namespace ssvision {

	vector<string> QtSerialPort::serial_port_list()
	{
		vector<string> list;
		foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
		{
			list.push_back(info.portName().toStdString());
		}
		return list;
	}

	vector<int> QtSerialPort::baud_rate_list()
	{
		vector<int> list;
		for (int i = 0; i < SerialPort::kBaudRateUnknown; ++i)
		{
			switch (i) {
			case SerialPort::kBaudRate_1200:
				list.push_back(1200);
				break;
			case SerialPort::kBaudRate_9600:
				list.push_back(9600);
				break;
			case SerialPort::kBaudRate_19200:
				list.push_back(19200);
				break;
			case SerialPort::kBaudRate_115200:
				list.push_back(115200);
				break;
			default:
				break;
			}
		}
		return list;
	}

	vector<int> QtSerialPort::character_bits_list()
	{
		vector<int> list;
		for (int i = 0; i < SerialPort::kCharacterBitsUnknown; ++i)
		{
			switch (i) {
			case SerialPort::kCharacterBits_5:
				list.push_back(5);
				break;
			case SerialPort::kCharacterBits_6:
				list.push_back(6);
				break;
			case SerialPort::kCharacterBits_7:
				list.push_back(7);
				break;
			case SerialPort::kCharacterBits_8:
				list.push_back(8);
				break;
			default:
				break;
			}
		}
		return list;
	}

	QtSerialPort::QtSerialPort(string port_name) :SerialPort(port_name)
	{
		qt_serial_port_.setPortName(port_name.c_str());
		connect(&qt_serial_port_, &QSerialPort::readyRead, this, &QtSerialPort::readyRead_slot);
	}

	QtSerialPort::~QtSerialPort()
	{
		close();
	}

	bool QtSerialPort::set_baud_rate(int baud_rate)
	{
		SerialPort::set_baud_rate(baud_rate);
		qt_serial_port_.setBaudRate(baud_rate);
		return true;
	}

	bool QtSerialPort::set_character_bits(int character_bits)
	{
		SerialPort::set_character_bits(character_bits);
		switch (character_bits)
		{
		case 5:
			return qt_serial_port_.setDataBits(QSerialPort::Data5);
		case 6:
			return qt_serial_port_.setDataBits(QSerialPort::Data6);
		case 7:
			return qt_serial_port_.setDataBits(QSerialPort::Data7);
		case 8:
			return qt_serial_port_.setDataBits(QSerialPort::Data8);
		}
		return false;
	}

	bool QtSerialPort::set_parity(Parity parity)
	{
		switch (parity) {
		case SerialPort::kParityEvenParity:
			return qt_serial_port_.setParity(QSerialPort::EvenParity);
		case SerialPort::kParityOddParity:
			return qt_serial_port_.setParity(QSerialPort::OddParity);
		case SerialPort::kParitySpaceParity:
			return qt_serial_port_.setParity(QSerialPort::SpaceParity);
		case SerialPort::kParityMarkParity:
			return qt_serial_port_.setParity(QSerialPort::MarkParity);
		case SerialPort::kParityNoParity:
		default:
			return qt_serial_port_.setParity(QSerialPort::NoParity);
		}
	}

	bool QtSerialPort::open()
	{
		if (qt_serial_port_.isOpen())
			return true;
		bool success = qt_serial_port_.open(QIODevice::ReadWrite);
		if (success && serial_port_delegate_)
			serial_port_delegate_->on_serial_port_open(this);
		return success;
	}

	bool QtSerialPort::is_open()
	{
		return qt_serial_port_.isOpen();
	}

	void QtSerialPort::close()
	{
		if (qt_serial_port_.isOpen())
		{
			qt_serial_port_.close();
			if (serial_port_delegate_)
				serial_port_delegate_->on_serial_port_close(this);
		}
	}

	int QtSerialPort::writeline(const char* data, int length)
	{
		string message(data, length);
		message += "\r";
		return qt_serial_port_.write(message.c_str(), message.length());
	}

	void QtSerialPort::readyRead_slot()
	{
        QByteArray bytes = qt_serial_port_.readAll();
        QString message = bytes;
        qDebug() << "读串口: "<< message << endl;
        while (bytes.length() > 0)
		{
			if (serial_port_delegate_)
			{
				serial_port_delegate_->on_serial_port_read(this,
                    bytes.data(),
                    bytes.length());
			}
            bytes = qt_serial_port_.readAll();
		}
	}

}
