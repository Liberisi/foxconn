#include "robotictcpserver.h"
#include <QAbstractSocket>

namespace ssvision{

//获取全部地址
QList<QHostAddress> RoboticTCPServer::all_address()
{
    return QNetworkInterface().allAddresses();
}

RoboticTCPServer::RoboticTCPServer()
{
    robotic_socket_ = NULL;
    delegate_ = NULL;
    connect(&tcp_server_,&QTcpServer::newConnection,this,&RoboticTCPServer::newConnect_slot);
}

RoboticTCPServer::~RoboticTCPServer()
{
    disconnect(&tcp_server_, 0, 0, 0);
}
bool RoboticTCPServer::robotic_connected()
{
    return this->robotic_socket_;
}

void RoboticTCPServer::kick_robotic()
{
    if(robotic_socket_)
    {
    robotic_socket_->close();
    delete robotic_socket_;
    robotic_socket_ = NULL;
    }
}

bool RoboticTCPServer::send_command(const char *data, int size)
{
    if (robotic_socket_ && data && size > 0)
    {
        robotic_socket_->write(data, size);
    }
    else
        return false;
}

void RoboticTCPServer::set_delegate(RoboticTCPServerDelegate* delegate)
{
    delegate_ = delegate;
}

bool RoboticTCPServer::listening(int port)
{
    if (!tcp_server_.isListening())
    {
        tcp_server_.listen(QHostAddress::Any, port );
    }
    return tcp_server_.isListening();
}

int RoboticTCPServer::listening_port()
{
    return tcp_server_.serverPort();
}

//关闭
void RoboticTCPServer::close()
{
    tcp_server_.close();
}



QString RoboticTCPServer::getIpAddress() const
{
    return QNetworkInterface().allAddresses().at(1).toString();
}

//
//void RoboticTCPServer::write(QString data)
//{
//    for(int i  = 0;i< tcpClientVec.size();i++)
//    {
//        tcpClientVec[i]->write(data.toUtf8().data());
//    }
//}

void RoboticTCPServer::write(QString ip,int port,QString data)
{
        if(robotic_socket_->peerAddress().toString().split("::ffff:")[1]
                ==ip&&robotic_socket_->peerPort() == port)
        {
            robotic_socket_->write(data.toUtf8().data());
            robotic_socket_->flush();
            return;
        }
}


void RoboticTCPServer::newConnect_slot()
{
//    一个新客户端的连接
    if (robotic_socket_)
    {
        robotic_socket_->close();
        delete robotic_socket_;
        robotic_socket_ = NULL;
    }
    robotic_socket_ = tcp_server_.nextPendingConnection();
    //新连接的客户端的 Ip 和 port
    //emit newConnectIPportInfo_signal(
    //            robotic_socket_->peerAddress().toString()
    //            .split("::ffff:")[1],
    //            robotic_socket_->peerPort());

    //tcpClientVec.append(robotic_socket_);

    connect(robotic_socket_,&QTcpSocket::readyRead,this,&RoboticTCPServer::readData_slot);
    connect(robotic_socket_,&QTcpSocket::disconnected,this,&RoboticTCPServer::disConnect_slot);

    if (delegate_)
        delegate_->on_robotic_connected(this);
}

void RoboticTCPServer::disConnect_slot()
{
	if (robotic_socket_->state() ==
		QAbstractSocket::UnconnectedState)
	{
		robotic_socket_->deleteLater();
		robotic_socket_ = NULL;
		emit disConnect_signal();
		if (delegate_)
			delegate_->on_robotic_disconnected(this);
	}
}


void RoboticTCPServer::readData_slot()
{
    QString buffer = robotic_socket_->readAll();
    emit readData_signal(buffer);
    if (delegate_)
        delegate_->on_robotic_command(this, (void*)buffer.toStdString().c_str(), buffer.toStdString().length());
}
}
