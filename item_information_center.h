#ifndef ITEMINFORMATION_H
#define ITEMINFORMATION_H

#include <string>
#include <vector>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QTcpServer>
#include <QTcpSocket>

using namespace std;

class ItemInformationCenter;
class ItemInformationCenterDelegate
{
public:
    virtual void on_advanced_device_connect(ItemInformationCenter* item_info_center, const string& ip_str) = NULL;
    virtual void on_advanced_device_disconnect(ItemInformationCenter* item_info_center, const string& ip_str) = NULL;
    virtual void on_advanced_device_item_information(const string& name, bool is_ng, const string& ng_reason) = NULL;
};

class ItemInformationCenter : public QObject
{
public:
    Q_OBJECT

public:
    static ItemInformationCenter* instance();

private:
    ItemInformationCenter();

public:
    void set_delegate(ItemInformationCenterDelegate* delegate);
    void listening(int port);
    bool is_listening();
    int listening_port();
    vector<string>  connected_device_ip_list();

    void open(const string db_path);
    // is_ng 为 true 表示 NG
    void add_item(const string& id_str, bool is_ng, const string& ng_reason);
    void remove_item(const string& id_str);
    bool get_item(const string& id_str, bool* is_ng, string& ng_reason);
    void set_item(const string& id_str, bool is_ng, const string& ng_reason);

protected:
    void on_item_message(QTcpSocket* socket, QString& message);

public slots:

    void on_socket_connect();
    void on_socket_disconnect();
    void on_socket_read();

protected:
     QSqlDatabase db_;
     QTcpServer tcp_server_;
     vector<QTcpSocket*> sockets_;
     ItemInformationCenterDelegate* delegate_;
};

#endif // ITEMINFORMATION_H
