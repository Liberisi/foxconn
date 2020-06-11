#include "item_information_center.h"
#include <QDebug>
#include "baojitai.h"
#include "qthread.h"
#include <QSqlQuery>
#include <QSqlError>


ItemInformationCenter* ItemInformationCenter::instance()  //继承
{
    static ItemInformationCenter* item_information = NULL;
    if (item_information == NULL)
    {
        item_information = new ItemInformationCenter;
    }
    return item_information;
}



ItemInformationCenter::ItemInformationCenter() //初始化
{
    delegate_ = NULL;
    connect(&tcp_server_, SIGNAL(newConnection()), this, SLOT(on_socket_connect()));
}

void ItemInformationCenter::set_delegate(ItemInformationCenterDelegate *delegate) //断开
{
    delegate_ = delegate;
}

void ItemInformationCenter::listening(int port)  //侦听
{
    if (!tcp_server_.isListening())
    {
        tcp_server_.listen(QHostAddress::Any, port);
    }
}

bool ItemInformationCenter::is_listening() //侦听中
{
    return tcp_server_.isListening();
}
int ItemInformationCenter::listening_port()
{
    return tcp_server_.serverPort();
}
vector<string> ItemInformationCenter::connected_device_ip_list() //连接设备ip地址
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


void ItemInformationCenter::on_socket_connect()  //隧道连接
{
    QTcpSocket* socket = tcp_server_.nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(on_socket_read()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(on_socket_disconnect()));
    //    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(onServerBytesWritten(qint64)));
    sockets_.push_back(socket);
    string ip_str = socket->peerAddress().toString().toStdString();
    if (delegate_)
        delegate_->on_advanced_device_connect(this, ip_str);
}
void ItemInformationCenter::on_socket_disconnect()   //隧道断开
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


void ItemInformationCenter::on_socket_read()
{


	QTcpSocket* socket = dynamic_cast<QTcpSocket*>(sender());
	QString message = QString::fromLocal8Bit(socket->readAll());
	on_item_message(socket, message);

}

void ItemInformationCenter::on_item_message(QTcpSocket* socket, QString& message) //信息
{
//    if (message.length() == 0)
//        return;
//    if (message[0] != '@')
//        return;

    // 消息格式
    // @条码_ok_工站_datatime\r
    // @条码_ng_原因_工站_datatime\r

    char file_name[128];
    memset(file_name, 0, 128);
    sprintf(file_name, "server.log");
    std::ofstream out_log(file_name);
    out_log << message.toStdString() << endl;
    QStringList str_list = message.split('_');


    QString item_name;
    if (str_list.length() > 0)
    {
        item_name = str_list[0];
        out_log << item_name.toStdString() << endl;
        if (item_name.length() > 1)
        {
            item_name = item_name.right(item_name.length()-1);
        }
    }

    // 1 ng
    // 0 ok
    // -
    QString ng_str;
    int ng_type = -1;
    if (str_list.length() > 1)
    {
        ng_str = str_list[1];
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
        bool repair_mode = Baojitai::instance()->is_repair_mode();
        if (repair_mode = false)
        {
            string response_item_name = item_name.toStdString()+ "autoNG\r\n";
            out_log << response_item_name << endl;
            socket->write(response_item_name.c_str(), response_item_name.length());
        }
        else
        {
            string response_item_name = item_name.toStdString()+ "manualNG\r\n";
            socket->write(response_item_name.c_str(), response_item_name.length());
        }
    }

    //工站
    //贴标机和锁螺丝机
    QString station;
    if (str_list.length() > 1)
    {
        station = str_list[3];
    }

    //日期
    QString datatime;
    if (str_list.length() > 1)
    {
        datatime = str_list[4];
        if (datatime.length() > 1)
        {
            datatime = datatime.left(item_name.length()-2);
        }
    }
    add_item(item_name.toStdString(), ng_str.toStdString()  , ng_reason.toStdString(), station.toStdString(), datatime.toStdString());

    QString loginfo;
    loginfo.sprintf("%p",QThread::currentThread());
    out_log << loginfo.toStdString() << endl;
}

void ItemInformationCenter::open(const string db_path)
{
    char file_name[128];
    memset(file_name, 0, 128);
    sprintf(file_name, "opendb.log");
    std::ofstream out_log(file_name);
    QString loginfo;
    loginfo.sprintf("%p",QThread::currentThread());
    out_log << loginfo.toStdString() << endl;

    const QString driver("QSQLITE");
    if(QSqlDatabase::isDriverAvailable(driver))
    {
        db_ = QSqlDatabase::addDatabase(driver);
        db_.setDatabaseName(db_path.c_str());
        db_.open();
        QSqlQuery query("CREATE TABLE product (id TEXT PRIMARY KEY, ng TEXT, reason TEXT, station TEXT, datatime TEXT)");
        if(!query.isActive())
            qWarning() << "ERROR: " << query.lastError().text();
    }
}


void ItemInformationCenter::add_item(string &id_str, string &ng_str, string &ng_reason, string &station, string &datatime) //sql增加
{
    char file_name[128];
    memset(file_name, 0, 128);
    sprintf(file_name, "add_item.log");
    std::ofstream out_log(file_name);

//    QString str = QString("insert into product(num, name, score) values('%1', '%2', '%3')").arg(num).arg(namestr).arg(score);
//    query.prepare("INSERT INTO product VALUES (id_str, is_ng, ng_reason, station, datatime)");
//    query.bindValue("id_str",id_str.c_str());
//    query.bindValue("is_ng",ng_str.c_str());
//    query.bindValue("ng_reason",ng_reason.c_str());
//    query.bindValue("station",station.c_str());
//    query.bindValue("datatime",datatime.c_str());


    QSqlQuery query = QSqlQuery(db_);
    string command = "INSERT INTO product (id, ng, reason, station, datatime) VALUES (";
    command += "\'"+id_str+"\',\'" + ng_str + "\',\'" + ng_reason +"\',\'" + station + "\',\'" + datatime + "\'"+ ")";
    query.prepare(command.c_str());
    out_log << command << endl;

    if(!query.exec(command.c_str()))
    {
        out_log << "invoke set_item" << endl;
		set_item(id_str, ng_str, ng_reason, station, datatime);
    }
    else
    {
        out_log << "insert success" << endl;
    }
}

void ItemInformationCenter::get_all_item_id(vector<string> &items)
{
    QSqlQuery query = QSqlQuery(db_);
    string command = "SELECT * FROM product";
    query.prepare(command.c_str());
    if(!query.exec())
    {
        return;
    }
    else
    {
        while(query.next())
        {
            string id_str = query.value(0).toString().toStdString();
            items.push_back(id_str);
        }
    }
}

void ItemInformationCenter::remove_item(const string& id_str) //sql移除
{
    QSqlQuery query = QSqlQuery(db_);
    string command = "DELETE FROM product WHERE id = ";
    command += "\'" + id_str + "\'";
    query.exec(command.c_str());
}
bool ItemInformationCenter::get_item(const string& id_str, string& is_ng, string& ng_reason , string& station, string &datatime) //查询
{
    QSqlQuery query = QSqlQuery(db_);
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
//            if (is_ng)
//            {
//                *is_ng = query.value(0).toBool();
//            }
            is_ng = query.value(0).toString().toStdString();
            ng_reason = query.value(1).toString().toStdString();
            station = query.value(2).toString().toStdString();
            datatime = query.value(3).toString().toStdString();
        }
        return true;
    }
}

bool ItemInformationCenter::contrast_item(const string& id_str)
{
    QSqlQuery query = QSqlQuery(db_);
    string command = "SELECT ng , reason FROM product WHERE id = ";
    command += "\'" + id_str + "\'";
    query.prepare(command.c_str());
    if(!query.exec())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void ItemInformationCenter::set_item(string &id_str, string &is_ng, string &ng_reason, string &station, string &datatime) //修改
{
    char file_name[128];
    memset(file_name, 0, 128);
    sprintf(file_name, "set_item.log");
    std::ofstream out_log(file_name);
    out_log << id_str << endl;
    out_log << ng_reason<< endl;
    out_log << station << endl;
    out_log << datatime << endl;

    QSqlQuery query = QSqlQuery(db_);
    string command = "UPDATE product set ";
    command += "ng = '" + is_ng  + "', ";
    command += "reason = '" + ng_reason + "', ";
    command += "station = '" + station + "',";
    command += "datatime = '" + datatime + "',";
    command += "WHERE id = ";
    command += "\'" + id_str + "\'";

    out_log << command << endl;

    query.exec(command.c_str());
}

