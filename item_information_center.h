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

#include <string>
#include <fstream>
#include <sstream>


using namespace std;

class ItemInformationCenter;
class ItemInformationCenterDelegate
{
public:
    virtual void on_advanced_device_connect(ItemInformationCenter* item_info_center, const string& ip_str) = NULL;
    virtual void on_advanced_device_disconnect(ItemInformationCenter* item_info_center, const string& ip_str) = NULL;
    virtual void on_advanced_device_item_information(const string& name, bool is_ng, const string& ng_reason, const string &station, const string &datatime) = NULL;
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
    void add_item(const string& id_str, const string& ng_str, const string &ng_code, const string& ng_reason, const string& station, const string &datatime);
    void remove_item(const string& id_str);
    void get_all_item_id(vector<string> &items);
    bool get_item(const string& id_str, string& is_ng, string &ng_code, string& ng_reason , string &station, string &datatime);
    void set_item(string& id_str, string& is_ng, string &ng_code, string& ng_reason, string& station, string &datatime);
    bool contrast_item(const string &id_str, string& id);

protected:
    //void on_item_message(QTcpSocket* socket, QString& message);

    signals:
    void signal_item_message(QTcpSocket* socket, QString message);


public slots:
 //   void onServerNewConnection();
 //   void onServerConnected();
 //   void onServerDisconnected();
 //   void onServerDataReady();
 //   void onServerBytesWritten(qint64 bytes);

    void on_socket_connect();
    void on_socket_disconnect();
    void on_socket_read();

    void on_signal_item_message(QTcpSocket* socket, QString message);

private:
    QSqlDatabase db_;

signals:

     void signal_query_updated();

protected:

     QTcpServer tcp_server_;
     vector<QTcpSocket*> sockets_;
     ItemInformationCenterDelegate* delegate_;
     QTcpServer currentClient;
     
     QTcpServer m_server;
         QString targetAddr;
         int targetPort;

private:
    void startConnect(bool ison);

    bool startServer(int port);
};

//QTcpSocket m_client;
//QTcpServer m_server;


//QString targetAddr;
//int targetPort;

//public:
//explicit Widget(QWidget *parent = 0);
//~Widget();
//private slots:
//void on_btn_switch_clicked();
//void on_tcpMode_currentIndexChanged(int index);
//void on_btn_send_clicked();             //发送按钮
//void on_betn_clear_clicked();           //清空按钮


////客户端槽函数
////    void onClientConnected();
////    void onClientDisconnected();
////    void onClientDataReady();
////    void onClientBytesWritten(qint64 bytes);
////    void onClientErr(QAbstractSocket::SocketError socketError);
////服务器槽函数
//void onServerNewConnection();
//void onServerConnected();
//void onServerDisconnected();
//void onServerDataReady();
//void onServerBytesWritten(qint64 bytes);

//private:
//void startConnect(bool ison);


////    void initClientSignals();   //初始化客户端信号槽
////    bool startClient();         //启动客户端


//void initServerSignals();   //初始化客户端信号槽
//bool startServer();     //启动服务器

//Ui::Widget *ui;
#endif // ITEMINFORMATION_H
