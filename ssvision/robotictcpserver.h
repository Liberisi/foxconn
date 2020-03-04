#ifndef ROBOTICTCPSERVER_H
#define ROBOTICTCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>

/**

 */

namespace ssvision{

class RoboticTCPServer;
class RoboticTCPServerDelegate
{
public:
    virtual void on_robotic_connected(RoboticTCPServer* robotic_tcp_server) = NULL;
    virtual void on_robotic_disconnected(RoboticTCPServer* robotic_tcp_server) = NULL;
    virtual void on_robotic_command(RoboticTCPServer* robotic_tcp_server, void* data, int size) = NULL;
//    virtual void on_robotic_command_send(RoboticTCPServer* robotic_tcp_server, int command, void* data) = NULL;
};

class RoboticTCPServer : public QObject
{
public:
    Q_OBJECT

public:
    static QList<QHostAddress> all_address();

    RoboticTCPServer();
    ~RoboticTCPServer();
    bool robotic_connected();
    //bool command(int command, void* data);
    bool send_command(const char *data, int size);
    void set_delegate(RoboticTCPServerDelegate* delegate);
    bool listening(int port);
    int listening_port();
    void kick_robotic();

protected:
    void close();



    QString getIpAddress()const;

    void write(QString data);

    void write(QString ip,int port,QString data);

signals:

    void readData_signal(QString);
    void disConnect_signal();
    void newConnectIPportInfo_signal(QString ip,int port);

public slots:

    void newConnect_slot();
    void disConnect_slot();
    void readData_slot();

private:
    QTcpServer tcp_server_;
    QTcpSocket* robotic_socket_;
    RoboticTCPServerDelegate* delegate_;
};

}

#endif // ROBOTICTCPSERVER_H
