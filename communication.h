#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class Communication;
}

class Communication : public QDialog
{
    Q_OBJECT

public:
    explicit Communication(QWidget *parent = 0);
    ~Communication();

public slots:
    void on_cmc_socket_status_change();

private slots:
//    void on_connect_btn_clicked();
    void Read_Data();
    //void on_send_btn_clicked();
    void on_btn_lisening_clicked();

    void on_comboBox_ip_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_pushButton_CMC_connect_clicked();

private:
    Ui::Communication *ui;

    QTcpSocket *socket;
};

#endif // COMMUNICATION_H
