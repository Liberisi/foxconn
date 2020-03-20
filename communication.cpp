#include "communication.h"
#include "ui_communication.h"
#include "baojitai.h"
#include <QString>
#include <QTextCodec>

Communication::Communication(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Communication)
{
    ui->setupUi(this);

    setFixedSize(this->width(), this->height());

    socket = new QTcpSocket();
    QList<QHostAddress> all_address  = RoboticTCPServer::all_address();
    foreach(QHostAddress address, all_address)
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
        {
            if(address.toString().contains("127.0.")) continue;
            ui->comboBox_ip->addItem(address.toString());
        }
    }

    Baojitai* baojitai = Baojitai::instance();
    connect(baojitai, SIGNAL(signal_fid_cmc_socket_status_change()), SLOT(on_cmc_socket_status_change()), Qt::QueuedConnection);

    RoboticTCPServer* tcp_server = baojitai->robotic_tcp_server();
    if (tcp_server)
    {
        string robotic_port = to_string(tcp_server->listening_port());
        ui->label_robotic_port->setText(robotic_port.c_str());
    }

    ItemInformationCenter* item_center = baojitai->item_center();
    if (item_center)
    {
        string item_center_port = to_string(item_center->listening_port());
        ui->label_advance_device_port->setText(item_center_port.c_str());
    }

    string ip_add = "127.0.0.1";
    int port = 0;
    baojitai->read_fid_cmc_ip_port(ip_add, port);
    ui->lineEdit_CMC_ip->setText(ip_add.c_str());
    ui->lineEdit_CMC_port->setText(to_string(port).c_str());
}

Communication::~Communication()
{
    delete this->socket;
    delete ui;
}

void Communication::on_cmc_socket_status_change()
{
    Baojitai* baojitai = Baojitai::instance();
    if (baojitai->is_fid_cmc_socket_connected())
    {
        ui->label_cmc_socket_connect_status->setText(QStringLiteral("已连接"));
    }
    else
    {
        ui->label_cmc_socket_connect_status->setText(QStringLiteral("未连接"));
    }
}

//void Communication::on_connect_btn_clicked()
//{
//    RoboticTCPServer* robotic_tcp_server  = Baojitai::instance()->robotic_tcp_server();
//    int port;
//    if (robotic_tcp_server && robotic_tcp_server->listen(&port))
//    {
//        ui->lineEdit_port->setText(to_string(port).c_str());
//    }
//    if(ui->btn_lisening->text() == tr("监听"))
//        {
//            QString IP;
//            int port;

//            //获取IP地址
//            IP = ui->lineEdit_ip->text();
//            //获取端口号
//            port = ui->lineEdit_port->text().toInt();

//            //取消已有的连接
//            socket->abort();
//            //连接服务器
//            socket->connectToHost(IP, port);

//            //等待连接成功
//            if(!socket->waitForConnected(30000))
//            {
//                qDebug() << "Connection failed!";
//                return;
//            }
//            qDebug() << "Connect successfully!";

//            //发送按键使能
//            ui->send_btn->setEnabled(true);
//            //修改按键文字
//            ui->btn_lisening->setText("中断监听");
//        }
//        else
//        {
//            //断开连接
//            socket->disconnectFromHost();
//            //修改按键文字
//            ui->btn_lisening->setText("监听");
//            ui->send_btn->setEnabled(false);
//        }
//}

//void Communication::on_send_btn_clicked()
//{
//    RoboticTCPServer* robotic_tcp_server  = Baojitai::instance()->robotic_tcp_server();
//    if (robotic_tcp_server)
//    {
//        robotic_tcp_server->send_command(ui->textEdit_send->toPlainText().toLatin1(),ui->textEdit_send->toPlainText().length());
//    }
//}

void Communication::Read_Data()
{
    RoboticTCPServer* robotic_tcp_server  = Baojitai::instance()->robotic_tcp_server();
    if (robotic_tcp_server)
    {
        //ui->textEdit_recv->setText("robotic_tcp_server");
    }
//    RoboticTCPServer* robotic_tcp_server = Baojitai::instance()->robotic_tcp_server();
//        QString str = ui->textEdit_recv->toPlainText();
//        str+=tr(robotic_tcp_server);
//        //刷新显示
//        ui->textEdit_recv->setText(str);
}

//void Communication::socket_Disconnected()
//{
//    //发送按键失能
//    ui->send_btn->setEnabled(false);
//    //修改按键文字
//    ui->btn_lisening->setText("连接");
//    qDebug() << "Disconnected!";
//}

//void Communication::on_btn_lisening_clicked()
//{

//}

void Communication::on_btn_lisening_clicked()
{
//    RoboticTCPServer* robotic_tcp_server  = Baojitai::instance()->robotic_tcp_server();
//    int port;
//    if (robotic_tcp_server && robotic_tcp_server->listen(&port))
//    {
//        ui->lineEdit_port->setText(to_string(port).c_str());
//    }
}

void Communication::on_comboBox_ip_currentIndexChanged(int index)
{
    ui->textEdit->setText(ui->comboBox_ip->itemText(index));
}

void Communication::on_pushButton_clicked()
{

}

void Communication::on_pushButton_CMC_connect_clicked()
{
    QString ip_add = ui->lineEdit_CMC_ip->text();
    int cmc_port = ui->lineEdit_CMC_port->text().toInt();
    Baojitai* baojitai = Baojitai::instance();
    baojitai->save_fid_cmc_ip_port(ip_add.toStdString(), cmc_port);
    baojitai->connect_fid_cmc_tcp_server(ip_add.toStdString(), cmc_port);
}
