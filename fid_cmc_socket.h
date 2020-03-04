#ifndef FRIDCMCTCPCLIENT_H
#define FRIDCMCTCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <string>

using namespace std;

class FidCMCSocket;
class FidCMCSocketDelegate
{
public:
    virtual void on_fid_cmc_socket_connected(FidCMCSocket* cmc_client) = NULL;
    virtual void on_fid_cmc_socket_disconnected(FidCMCSocket* cmc_client) = NULL;
    virtual void on_fid_cmc_socket_read_bytes(const QByteArray& bytes) = NULL;
    virtual void on_fid_cmc_socket_read_fid(const string fid) = NULL;
};

class FidCMCCommandParser
{
public:
    FidCMCCommandParser();

    // 剩余buffer空间
    int empty_buffer_size();
    // 如果 length 大于剩余buffer空间，则多余数据会被丢弃
    void push_data(const char* data, int length);
    string shift_fid();

private:
    int data_size_;
    char buffer_[128];
};

class FidCMCSocket : public QObject
{
public:
    Q_OBJECT

public:
    FidCMCSocket();
    void set_delegate(FidCMCSocketDelegate* delegate);
    void connect_host(QString ip, int port);
    bool is_connected();
    void clear_cmc_screen();

public slots:
    void on_socket_read();
    void on_socket_connected();
    void on_socket_disconnected();
    void on_socket_error();

private:
    QTcpSocket tcp_socket_;
    FidCMCSocketDelegate* delegate_;
    FidCMCCommandParser cmd_parser_;
};

#endif // FRIDCMCTCPCLIENT_H
