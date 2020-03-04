#include "fid_cmc_socket.h"

FidCMCCommandParser::FidCMCCommandParser()
{
    data_size_ = 0;
    memset(buffer_, 0, sizeof(buffer_)/sizeof(buffer_[0]));
}

int FidCMCCommandParser::empty_buffer_size()
{
    int buffer_size = sizeof(buffer_)/sizeof(buffer_[0]);
    return buffer_size - data_size_;
}

void FidCMCCommandParser::push_data(const char* data, int length)
{
    int buffer_size = sizeof(buffer_)/sizeof(buffer_[0]);
    int push_count = 0;
    for (int i = data_size_; i < buffer_size; ++i)
    {
        if (push_count < length)
        {
            buffer_[i] = data[push_count++];
        }
        else
            break;
    }
    data_size_ += push_count;
}

string FidCMCCommandParser::shift_fid()
{
    bool find_return = false;
    unsigned int fid_length = 0;
    for(int i = 0; i < data_size_; ++i)
    {
        if (buffer_[i] == '\r')
        {
            find_return = true;
            break;
        }
        fid_length++;
    }

    if (find_return)
    {
        string fid;
        //qDebug() << to_string(fid_length).c_str() << endl;
        if (fid_length == 8 && buffer_[0] == 0x1B && buffer_[1] == 0x07)
        {
            for (unsigned int i = fid_length - 6; i < fid_length; ++i)
            {
                fid.push_back(buffer_[i]);
            }
        }

        // 以防出现连续的 '\r'
        int next_fid_start = fid_length + 1;
        for (int i = next_fid_start; i < data_size_; ++i)
        {
            if (buffer_[i] == '\r')
                next_fid_start++;
            else
                break;
        }
        int move_count = 0;
        for (int i = next_fid_start; i < data_size_; ++i)
        {
            buffer_[move_count++] = buffer_[i];
        }
        data_size_ = move_count;
        return fid;
    }
    else
        return "";
}

// --------------------------------------------------------------------------------------------

FidCMCSocket::FidCMCSocket()
{
    delegate_ = NULL;
    connect(&tcp_socket_, SIGNAL(readyRead()), this, SLOT(on_socket_read()));
    connect(&tcp_socket_, SIGNAL(connected()), this, SLOT(on_socket_connected()));
    connect(&tcp_socket_, SIGNAL(disconnected()), this, SLOT(on_socket_disconnected()));
}

void FidCMCSocket::set_delegate(FidCMCSocketDelegate* delegate)
{
    delegate_ = delegate;
}

bool FidCMCSocket::is_connected()
{
    QAbstractSocket::SocketState state = tcp_socket_.state();
    if (state == QAbstractSocket::ConnectedState)
        return true;
    else
        return false;
}

void FidCMCSocket::connect_host(QString ip, int port)
{
    tcp_socket_.abort();
    tcp_socket_.connectToHost(ip, port);
}

void FidCMCSocket::clear_cmc_screen()
{
    if (is_connected())
    {
        char msg[2];
        msg[0] = 0x1b;
        msg[1] = 0x60;
        tcp_socket_.write(msg, 2);
    }
}

void FidCMCSocket::on_socket_read()
{
    QByteArray bytes = tcp_socket_.readAll();
    if (delegate_)
        delegate_->on_fid_cmc_socket_read_bytes(bytes);

    //cmd_parser_.push_data(bytes.data(), bytes.length());
    char* data = bytes.data();
    int size = bytes.length();
    int left_size = size;
    do
    {
        int buffer_size = cmd_parser_.empty_buffer_size();
        if (buffer_size == 0)
            break;
        int push_size = left_size < buffer_size ? left_size : buffer_size;
        cmd_parser_.push_data(data, push_size);
        left_size -= push_size;
        string fid = cmd_parser_.shift_fid();
        while (fid.length() > 0)
        {
            if (delegate_)
                delegate_->on_fid_cmc_socket_read_fid(fid);
            fid = cmd_parser_.shift_fid();
        }
    } while (left_size > 0);
}

void FidCMCSocket::on_socket_error()
{
   // QByteArray bytes = tcp_socket_.readAll();
    qDebug() << "socket error" << endl;
}

void FidCMCSocket::on_socket_connected()
{
    if (delegate_)
        delegate_->on_fid_cmc_socket_connected(this);
}

void FidCMCSocket::on_socket_disconnected()
{
    if (delegate_)
        delegate_->on_fid_cmc_socket_disconnected(this);
}
