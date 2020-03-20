#include "item_information_center.h"
#include <QDebug>

ItemInformationCenter* ItemInformationCenter::instance()
{
    static ItemInformationCenter* item_information = NULL;
    if (item_information == NULL)
    {
        item_information = new ItemInformationCenter;
    }
    return item_information;
}

ItemInformationCenter::ItemInformationCenter()
{
    delegate_ = NULL;
    connect(&tcp_server_, SIGNAL(newConnection()), this, SLOT(on_socket_connect()));
}

void ItemInformationCenter::set_delegate(ItemInformationCenterDelegate *delegate)
{
    delegate_ = delegate;
}

void ItemInformationCenter::listening(int port)
{
    if (!tcp_server_.isListening())
    {
        tcp_server_.listen(QHostAddress::Any, port);
    }
}

bool ItemInformationCenter::is_listening()
{
    return tcp_server_.isListening();
}
int ItemInformationCenter::listening_port()
{
    return tcp_server_.serverPort();
}
vector<string> ItemInformationCenter::connected_device_ip_list()
{
    vector<string> ip_list;
    vector<QTcpSocket*>::iterator iter = sockets_.begin();
    while(iter != sockets_.end())
    {
        QTcpSocket* socket = *iter;
        if (socket->state() == QAbstractSocket::ConnectedState)
        {
            string ip_str = socket->peerAddress().toString().toStdString();
            ip_list.push_back(ip_str);
        }
        iter++;
    }
    return ip_list;
}
void ItemInformationCenter::on_socket_connect()
{
    QTcpSocket* socket = tcp_server_.nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(on_socket_read()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(on_socket_disconnect()));
    sockets_.push_back(socket);
    string ip_str = socket->peerAddress().toString().toStdString();
    if (delegate_)
        delegate_->on_advanced_device_connect(this, ip_str);
}
void ItemInformationCenter::on_socket_disconnect()
{
    vector<QTcpSocket*>::iterator iter = sockets_.begin();
    while(iter != sockets_.end())
    {
        QTcpSocket* socket = *iter;
        if (socket->state() == QAbstractSocket::UnconnectedState)
        {
            disconnect(socket, SIGNAL(readyRead()), this, SLOT(on_socket_read()));
            disconnect(socket, SIGNAL(disconnected()), this, SLOT(on_socket_disconnect()));
            socket->deleteLater();
            iter = sockets_.erase(iter);
            string ip_str = socket->peerAddress().toString().toStdString();
            if (delegate_)
                delegate_->on_advanced_device_disconnect(this, ip_str);
        }
        else
        {
            iter++;
        }
    }
}
void ItemInformationCenter::on_item_message(QTcpSocket* socket, QString& message)
{
    if (message.length() == 0)
        return;
    if (message[0] != '@')
        return;

    // 消息格式
    // @条码_ok
    // @条码_ng_原因

    QStringList str_list = message.split('_');
    QString item_name;
    if (str_list.length() > 0)
    {
        item_name = str_list[0];
        if (item_name.length() > 1)
        {
            item_name = item_name.right(item_name.length()-1);
        }
    }

    // 1 ng
    // 0 ok
    // -1
    int ng_type = -1;
    if (str_list.length() > 1)
    {
        QString ng_str = str_list[1];
        if (ng_str.compare("ok", Qt::CaseInsensitive) == 0)
        {
            ng_type = 0;
        }
        else if (ng_str.compare("ng", Qt::CaseInsensitive) == 0)
        {
            ng_type = 1;
        }
    }

    QString ng_reason;
    if (ng_type == 1 && str_list.length() > 2)
    {
        ng_reason = str_list[2];
    }

    if (item_name.length() > 0 && ng_type != -1)
    {
        string response_item_name = item_name.toStdString() + "\r\n";
        socket->write(response_item_name.c_str(), response_item_name.length());
        add_item(item_name.toStdString(), ng_type == 1, ng_reason.toStdString());
    }
}

void ItemInformationCenter::on_socket_read()
{
    vector<QTcpSocket*>::iterator iter = sockets_.begin();
    while(iter != sockets_.end())
    {
        QTcpSocket* socket = *iter;
        while (socket->canReadLine())
        {
            QString message = socket->readLine();
            if (message.length() > 0 && message[0] == '@')
            {
                on_item_message(socket, message);
            }
        }
        iter++;
    }
}
void ItemInformationCenter::open(const string db_path)
{
    const QString driver("QSQLITE");
    if(QSqlDatabase::isDriverAvailable(driver))
    {
        db_ = QSqlDatabase::addDatabase(driver);
        db_.setDatabaseName(db_path.c_str());
        db_.open();
        QSqlQuery query("CREATE TABLE product (id TEXT PRIMARY KEY, ng BOOL, reason TEXT)");
        if(!query.isActive())
            qWarning() << "ERROR: " << query.lastError().text();
    }
}
void ItemInformationCenter::add_item(const string& id_str, bool is_ng, const string& ng_reason)
{
    QSqlQuery query;
    string command = "INSERT INTO product (id, ng, reason) VALUES (";
    command += "\'"+id_str+"\'," + (is_ng ? "1" : "0") + ",\'" + ng_reason + "\'" + ")";
    if(!query.exec(command.c_str()))
    {
        set_item(id_str, is_ng, ng_reason);
    }
}
void ItemInformationCenter::remove_item(const string& id_str)
{
    QSqlQuery query;
    string command = "DELETE FROM product WHERE id = ";
    command += "\'" + id_str + "\'";
    query.exec(command.c_str());
}
bool ItemInformationCenter::get_item(const string& id_str, bool* is_ng, string& ng_reason)
{
    QSqlQuery query;
    string command = "SELECT ng , reason FROM product WHERE id = ";
    command += "\'" + id_str + "\'";
    query.prepare(command.c_str());
    if(!query.exec())
    {
        return false;
    }
    else
    {
        while(query.next())
        {
            if (is_ng)
            {
                *is_ng = query.value(0).toBool();
            }
            ng_reason = query.value(1).toString().toStdString();
        }
        return true;
    }
}
void ItemInformationCenter::set_item(const string& id_str, bool is_ng, const string& ng_reason)
{
    QSqlQuery query;
    string command = "UPDATE product set ";
    command += "ng = " + (is_ng ? string("1") : string("0")) + ", ";
    command += "reason = '" + ng_reason + "' ";
    command += "WHERE id = ";
    command += "\'" + id_str + "\'";
    query.exec(command.c_str());
}
