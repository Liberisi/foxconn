#include "item_information_center.h"
#include <QDebug>
#include "baojitai.h"

ItemInformationCenter* ItemInformationCenter::instance()  //继承
{
    static ItemInformationCenter* item_information = NULL;
    if (item_information == NULL)
    {
        item_information = new ItemInformationCenter;
    }
    return item_information;
}


//
//void ItemInformationCenter::initServerSignals()   //初始化信号槽
//{
//    connect(&m_server, SIGNAL(newConnection()), this, SLOT(onServerNewConnection()));


//}
//bool ItemInformationCenter::startServer(int port)         //启动服务器
//{

//    if(m_server.listen(QHostAddress::AnyIPv4,port)       //只监听IPV4的所有客户端
//    {
////        ui->targetLabel->show();
////        ui->targetObject->show();
////        ui->localPort->setText(QString("%1").arg(m_server.serverPort()));

//        return true;
//    }
//    else
//       return false;

//}

//void ItemInformationCenter::onServerNewConnection()
//{
//    qDebug() << "onNewConnection";
//    QTcpSocket* tcp = m_server.nextPendingConnection();     //获取新的客户端信息

//    QString info=tcp->peerAddress().toString()+":"+QString("%1").arg(tcp->peerPort());
//    //ui->targetObject->addItem(info);
//    QMessageBox::information(this,"提示",QString("新的客户端连入:%1").arg(info),QMessageBox::Ok);

//    tcp->setObjectName(info);       //设置名称,方便查找

//    connect(tcp, SIGNAL(connected()), this, SLOT(onServerConnected()));
//    connect(tcp, SIGNAL(disconnected()), this, SLOT(onServerDisconnected()));
//    connect(tcp, SIGNAL(readyRead()), this, SLOT(onServerDataReady()));
//    connect(tcp, SIGNAL(bytesWritten(qint64)), this, SLOT(onServerBytesWritten(qint64)));

//}
//void ItemInformationCenter::onServerConnected()
//{

//}
//void ItemInformationCenter::onServerDisconnected()
//{
//    QTcpSocket* tcp = dynamic_cast<QTcpSocket*>(sender());

//    if( tcp != NULL )       //从连接对象中移除掉
//    {
//        qDebug() << "onServerDisconnected";
//        qDebug() << "Local Address:" << tcp->peerAddress();
//        qDebug() << "Local Port:" << tcp->peerPort();


//        QString info=tcp->peerAddress().toString()+":"+QString("%1").arg(tcp->peerPort());

//        QMessageBox::information(this,"提示",QString("客户端断开连接:%1").arg(info),QMessageBox::Ok);

//        int index = ui-> targetObject ->findText(info);
//        if(index>=0)
//        ui->targetObject->removeItem(index);
//    }

//}
//void ItemInformationCenter::onServerDataReady()
//{
//    QTcpSocket* tcp = dynamic_cast<QTcpSocket*>(sender());

//    if(tcp->peerAddress().toString()!=targetAddr || tcp->peerPort()!=targetPort  )
//    {
//        targetAddr = tcp->peerAddress().toString();
//        targetPort = tcp->peerPort();

//        ui->recvEdit->insertPlainText("[接受来自"+ targetAddr+":"+QString("%1").arg(targetPort)+"]:\r\n");

//    }

//    ui->recvEdit->moveCursor(QTextCursor::End);

////    if(ui->hexRecv->isChecked())        //十六进制接收？
////    {
////          QByteArray data =  tcp->readAll();


////          for(int i=0;i<data.length();i++)
////          {

////              ui->recvEdit->insertPlainText(QString("%1 ").arg((unsigned char)data[i],2,16,QChar('0')).toUpper());

////          }
////          ui->recvEdit->insertPlainText("\r\n");
////    }
////    else
//            QString message = tcp->readLine();
//			out_log << message.toStdString() << endl;
////            on_item_message(socket, message);
//            if (message.length() > 0 && message[0] == '@')
//            {
//                on_item_message(socket, message);
//				out_log << message.toStdString() << endl;
//            }
////        ui->recvEdit->insertPlainText(QString::fromLocal8Bit(tcp->readAll())+"\r\n");


//}
//void ItemInformationCenter::onServerBytesWritten(qint64 bytes)
//{
//    qDebug() << "onBytesWritten:" << bytes;


//    ui->sendLenLabel->setText(QString("%1").arg(ui->sendLenLabel->text().toInt()+bytes));

//}
//
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

void ItemInformationCenter::onServerBytesWritten(QString bytes)
{
//    bool repair_mode = Baojitai::instance()->is_repair_mode();
//    if (repair_mode = false)
//    {
//       string response_item_name = item_name.toStdString()+ "autoNG\r\n";
//        socket->write(response_item_name.c_str(), response_item_name.length());
//    }
//    else
//    {
//        string response_item_name = item_name.toStdString()+ "manualNG\r\n";
//        socket->write(response_item_name.c_str(), response_item_name.length());
//    }

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
	char file_name[128];
	memset(file_name, 0, 128);
	sprintf(file_name, "server_read.log");
	std::ofstream out_log(file_name);

	QTcpSocket* socket = dynamic_cast<QTcpSocket*>(sender());
	QString message = QString::fromLocal8Bit(socket->readAll());
	on_item_message(socket, message);

	//    if(tcp->peerAddress().toString()!=targetAddr || tcp->peerPort()!=targetPort  )
	//    {
	//        targetAddr = tcp->peerAddress().toString();
	//        targetPort = tcp->peerPort();
//    vector<QTcpSocket*>::iterator iter = sockets_.begin();
//    while(iter != sockets_.end())
//    {
//        QTcpSocket* socket = *iter;
//		
//        while (socket->canReadLine())
//        {
//
//            QString message = QString::fromLocal8Bit(socket->readLine());
//			out_log << message.toStdString() << endl;
////            on_item_message(socket, message);
//            if (message.length() > 0 && message[0] == '@')
//            {
//                on_item_message(socket, message);
//				out_log << message.toStdString() << endl;
//            }
////            /*socket->write("autoNG\r\n")*/;
//            
//            out_log << message.toStdString() << endl;
//        }
//        iter++;
//    }
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
            datatime = item_name.left(item_name.length()-2);
        }
    }
    add_item(item_name.toStdString(), ng_type == 1 , ng_reason.toStdString(), station.toStdString(), datatime.toStdString());
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
void ItemInformationCenter::add_item(const string& id_str, bool is_ng, const string& ng_reason, const string& station, const string &datatime) //sql增加
{
    QSqlQuery query;
    string command = "INSERT INTO product (id, ng, reason，station) VALUES (";
    command += "\'"+id_str+"\'," + (is_ng ? "1" : "0") + ",\'" + ng_reason + station + ",\'" + datatime +"\'" + ")";
    if(!query.exec(command.c_str()))
    {
        set_item(id_str, is_ng, ng_reason, station, datatime);
    }
}
void ItemInformationCenter::get_all_item_id(vector<string> &items)
{
    QSqlQuery query;
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
    QSqlQuery query;
    string command = "DELETE FROM product WHERE id = ";
    command += "\'" + id_str + "\'";
    query.exec(command.c_str());
}
bool ItemInformationCenter::get_item(const string& id_str, bool* is_ng, string& ng_reason , string& station, string &datatime) //查询
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
            station = query.value(2).toString().toStdString();
            datatime = query.value(3).toString().toStdString();
        }
        return true;
    }
}
void ItemInformationCenter::set_item(const string& id_str, bool is_ng, const string& ng_reason, const string &station, const string &datatime) //修改
{
    QSqlQuery query;
    string command = "UPDATE product set ";
    command += "ng = " + (is_ng ? string("1") : string("0")) + ", ";
    command += "reason = '" + ng_reason + "' ";
    command += "WHERE id = ";
    command += "\'" + station + "\'";
    command += "\'" + id_str + "\'";
    command += "'" + datatime + "'";
    query.exec(command.c_str());
}

