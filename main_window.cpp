#include "main_window.h"
#include "ui_main_window.h"
#include "camera_config_dialog.h"
#include "reading_code_config.h"
#include "save_config_dialog.h"
#include "about.h"
#include "position_calibrate.h"
#include <QLabel>
#include <QStatusBar>
#include <QLineEdit>
#include <QDateTime>
#include <QString>
#include <QTimer>
#include <QObject>
#include <QColor>
#include <QMessageBox>
#include <ssvision/ssvision>
#include "baojitai.h"
#include "product.h"
#include <QComboBox>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QStorageInfo>
#include "communication.h"
#include "plc_config_dialog.h"
#include "location_config.h"
#include "frame_dialog.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QMetaProperty>
#include <QObjectList>
#include <QFileDialog>
#include "halcon_tools.h"
#include "material_product_dialog.h"
#include <QtSql/qsql.h>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtCore>
#include "xlsxdocument.h"
#include "xlsxformat.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include <QtXlsx>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer_(this)
{
    ui->setupUi(this);
    location_result_updated_ = false;
    reading_code_result_updated_ = false;
    check_frame_result_updated_ = false;

    //ui->checkBox_repair_mode->setEnabled(false);

    QDesktopWidget* desktopWidget = QApplication::desktop();
    //获取可用桌面大小
    QRect deskRect = desktopWidget->availableGeometry();
//    this->setGeometry(QRect &deskRect);
//    this->setWindowState(Qt::WindowFullScreen);
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);

    ui->label_location_result->setText("");
    ui->label_reading_code_result->setText("");
    ui->label_check_frame_result->setText("");
    ui->toolButton_reset->hide();
    //ui->lineEdit_current_product->setEnabled(false);
    //ui->lineEdit_current_product->setStyleSheet(QStringLiteral(" QLineEdit{ color: black };background-color:rgba(255,255,255,255)"));

	ProductManager* product_manager = ProductManager::instance();
	vector<string> product_name_list = product_manager->product_name_list();
	foreach(string product_name, product_name_list)
	{
        ui->comboBox_product_list->addItem(product_name.c_str());
        ui->switch_model->addItem(product_name.c_str());
	}    

    statusBar()->setStyleSheet(QStringLiteral("QStatusBar::item{border: 0px}"));

    QString status_bar_item_style_sheet = QStringLiteral(" QLineEdit{ color: white };background-color:rgba(255,255,255,0)");
    QLineEdit *lineEdit = new QLineEdit;
    lineEdit->setMaximumSize(76,24);
    lineEdit->setMinimumSize(76,24);
    lineEdit->setStyleSheet(status_bar_item_style_sheet);
    lineEdit->setText(QStringLiteral("人员登录"));
	lineEdit->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    statusBar()->addWidget(lineEdit);
    lineEdit->setReadOnly(true);

//    QLineEdit *lineEdit2 = new QLineEdit;
//    lineEdit2->setMaximumSize(76,24);
//    lineEdit2->setStyleSheet(status_bar_item_style_sheet);
//    lineEdit2->setText(QStringLiteral("系统状态"));
//	lineEdit2->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
//    statusBar()->addWidget(lineEdit2);
//    lineEdit2->setReadOnly(true);

    QLineEdit *lineEdit3 = new QLineEdit;
    lineEdit3->setMaximumSize(76,24);
    lineEdit3->setMinimumSize(76,24);
    lineEdit3->setStyleSheet(status_bar_item_style_sheet);
    lineEdit3->setText(QStringLiteral("数据端口"));
	lineEdit3->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    statusBar()->addWidget(lineEdit3);
    lineEdit3->setReadOnly(true);

    //数据端口信号灯
    reading_code_serial_port_status_lineedit = new QLineEdit;
    reading_code_serial_port_status_lineedit->setMaximumSize(10,24);
    statusBar()->addWidget(reading_code_serial_port_status_lineedit);
    reading_code_serial_port_status_lineedit->setReadOnly(true);

    reading_code_serial_port_status_lineedit2 = new QLineEdit;
    reading_code_serial_port_status_lineedit2->setMaximumSize(10,24);
	reading_code_serial_port_status_lineedit2->setStyleSheet(QStringLiteral(" QLineEdit{ color: white }"));
    statusBar()->addWidget(reading_code_serial_port_status_lineedit2);
    reading_code_serial_port_status_lineedit2->setReadOnly(true);

    reading_code_serial_port_status_lineedit3= new QLineEdit;
    reading_code_serial_port_status_lineedit3->setMaximumSize(10,24);
    reading_code_serial_port_status_lineedit3->setStyleSheet(QStringLiteral(" QLineEdit{ color: white }"));
    statusBar()->addWidget(reading_code_serial_port_status_lineedit3);
    reading_code_serial_port_status_lineedit3->setReadOnly(true);

    fid_cmc_socket_status_lineedit = new QLineEdit;
    fid_cmc_socket_status_lineedit->setMaximumSize(10,24);
    fid_cmc_socket_status_lineedit->setStyleSheet(QStringLiteral(" QLineEdit{ color: white }"));
    statusBar()->addWidget(fid_cmc_socket_status_lineedit);
    fid_cmc_socket_status_lineedit->setReadOnly(true);

//	QLineEdit* plc_lineedit = new QLineEdit;
//	plc_lineedit->setMaximumSize(42, 24);
//    plc_lineedit->setStyleSheet(status_bar_item_style_sheet);
//	plc_lineedit->setText(QStringLiteral("PLC"));
//	plc_lineedit->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
//	statusBar()->addWidget(plc_lineedit);
//	plc_lineedit->setReadOnly(true);
	plc_status_lineedit = new QLineEdit;
//	plc_status_lineedit->setMaximumSize(10, 24);
//    plc_status_lineedit->setStyleSheet(status_bar_item_style_sheet);
	plc_status_lineedit->setText(QStringLiteral("PLC"));
	plc_status_lineedit->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	plc_status_lineedit->setStyleSheet(QStringLiteral(" QLineEdit{ color: white }"));
	statusBar()->addWidget(plc_status_lineedit);
	plc_status_lineedit->setReadOnly(true);

//	QLineEdit* robotic_status_label = new QLineEdit;
//	robotic_status_label->setMaximumSize(58, 24);
//    robotic_status_label->setStyleSheet(status_bar_item_style_sheet);
//	robotic_status_label->setText(QStringLiteral("机械臂"));
//	robotic_status_label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
//	statusBar()->addWidget(robotic_status_label);
//	robotic_status_label->setReadOnly(true);

	robotic_status_lineEdit = new QLineEdit;
//	robotic_status_lineEdit->setMaximumSize(10, 24);
    robotic_status_lineEdit->setText(QStringLiteral("机械臂"));
	robotic_status_lineEdit->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	robotic_status_lineEdit->setStyleSheet(" QLineEdit{ color: white }");
	statusBar()->addWidget(robotic_status_lineEdit);
	robotic_status_lineEdit->setReadOnly(true);

    //相机状态区
//    QLineEdit *lineEdit6 = new QLineEdit;
//    lineEdit6->setMaximumSize(76,24);
//    lineEdit6->setStyleSheet(status_bar_item_style_sheet);
//    lineEdit6->setText(QStringLiteral("读码相机"));
//	lineEdit6->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
//    statusBar()->addWidget(lineEdit6);
//    lineEdit6->setReadOnly(true);
    qr_camera_status_lineedit = new QLineEdit;
//    qr_camera_status_lineedit->setMaximumSize(10,24);
    qr_camera_status_lineedit->setText(QStringLiteral("读码相机"));
	qr_camera_status_lineedit->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    statusBar()->addWidget(qr_camera_status_lineedit);
    qr_camera_status_lineedit->setReadOnly(true);

//    QLineEdit *lineEdit7 = new QLineEdit;
//    lineEdit7->setMaximumSize(76,24);
//    lineEdit7->setStyleSheet(status_bar_item_style_sheet);
//    lineEdit7->setText(QStringLiteral("定位相机"));
//	lineEdit7->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
//    statusBar()->addWidget(lineEdit7);
//    lineEdit7->setReadOnly(true);
    pos_camera_status_lineedit = new QLineEdit;
//    pos_camera_status_lineedit->setMaximumSize(10,24);
    pos_camera_status_lineedit->setText(QStringLiteral("定位相机"));
	pos_camera_status_lineedit->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    statusBar()->addWidget(pos_camera_status_lineedit);
    pos_camera_status_lineedit->setReadOnly(true);
//    QLineEdit *lineEdit8 = new QLineEdit;
//    lineEdit8->setMaximumSize(76,24);
//    lineEdit8->setStyleSheet(status_bar_item_style_sheet);
//    lineEdit8->setText(QStringLiteral("支架相机"));
//	lineEdit8->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
//    statusBar()->addWidget(lineEdit8);
//    lineEdit8->setReadOnly(true);
    frame_camera_status_lineedit = new QLineEdit;
//    frame_camera_status_lineedit->setMaximumSize(10,24);
    frame_camera_status_lineedit->setText(QStringLiteral("支架相机"));
	frame_camera_status_lineedit->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    statusBar()->addWidget(frame_camera_status_lineedit);
    frame_camera_status_lineedit->setReadOnly(true);
    //

//    QLineEdit *lineEdit9 = new QLineEdit;
//    lineEdit9->setMaximumSize(76,24);
//    lineEdit9->setStyleSheet(status_bar_item_style_sheet);
//    lineEdit9->setText(QStringLiteral("触发状态"));
//	lineEdit9->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
//    statusBar()->addWidget(lineEdit9);
//    lineEdit9->setReadOnly(true);

//    QLineEdit *lineEdit10 = new QLineEdit;
//    lineEdit10->setMaximumSize(76,24);
//    lineEdit10->setStyleSheet(status_bar_item_style_sheet);
//    lineEdit10->setText(QStringLiteral("运行状态"));
//	lineEdit10->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
//    statusBar()->addWidget(lineEdit10);
//    lineEdit10->setReadOnly(true);

    running_status_lineEdit = new QLineEdit;
//    running_status_lineEdit->setMaximumSize(10, 24);
    running_status_lineEdit->setStyleSheet(" QLineEdit{ color: white }");
    running_status_lineEdit->setText(QStringLiteral("运行状态"));
	running_status_lineEdit->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    statusBar()->addWidget(running_status_lineEdit);
    running_status_lineEdit->setReadOnly(true);

//    QLineEdit *lineEdit11 = new QLineEdit;
//    lineEdit11->setMaximumSize(76,24);
//    lineEdit11->setStyleSheet(status_bar_item_style_sheet);
//    lineEdit11->setText(QStringLiteral("上游设备"));
//    lineEdit11->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
//    statusBar()->addWidget(lineEdit11);
//    lineEdit11->setReadOnly(true);

    advanced_device_count_label = new QLabel;
//    advanced_device_count_label->setMaximumSize(22, 24);
    advanced_device_count_label->setText(QStringLiteral("上游设备"));
    advanced_device_count_label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    advanced_device_count_label->setStyleSheet(" QLabel{ color: white }");
    statusBar()->addWidget(advanced_device_count_label);
    advanced_device_count_label->setText("0");
    //advanced_device_count_label->setReadOnly(true);

//    QLineEdit *lineEdit11 = new QLineEdit;
//    lineEdit11->setMaximumSize(45,24);
//    lineEdit11->setStyleSheet(" QLineEdit{ color: white }");
//    lineEdit11->setText(QStringLiteral("[对象]"));
//    statusBar()->addWidget(lineEdit11);
//    lineEdit11->setReadOnly(true);
//    QLineEdit *lineEdit12 = new QLineEdit;
//    lineEdit12->setMaximumSize(80,24);
//    lineEdit12->setStyleSheet(" QLineEdit{ color: white }");
//    lineEdit12->setText(QStringLiteral("[报表：正常]"));
//    statusBar()->addWidget(lineEdit12);
//    lineEdit12->setReadOnly(true);

    //QLineEdit *lineEdit13 = new QLineEdit;
    //lineEdit13->setMaximumSize(55,24);
    //lineEdit13->setStyleSheet(" QLineEdit{ color: white }");
    //lineEdit13->setText(QStringLiteral("时间监控")) ;
    //statusBar()->addWidget(lineEdit13);
    //lineEdit13->setReadOnly(true);

    QWidget* spacer = new QWidget;
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	statusBar()->addWidget(spacer);

    currentTimeLabel = new QLabel;
    currentTimeLabel->setMaximumSize(180,24);
    currentTimeLabel->setStyleSheet(" QLabel{ color: white }");
    statusBar()->addWidget(currentTimeLabel);

    connect(&timer_,SIGNAL(timeout()),this,SLOT(timeUpdate()));
    timer_.start(1000);

    ui->widget_image_location->set_halcon_widget_delegate(this);
    ui->widget_reading_code->set_halcon_widget_delegate(this);
    ui->widget_image_check_frame->set_halcon_widget_delegate(this);

    Baojitai* baojitai = Baojitai::instance();
	baojitai->set_plc_act_utl(&plc_utltype_);
    connect(baojitai, SIGNAL(signal_serial_port_status_change(SerialPort*)), this, SLOT(on_serial_port_status_signal(SerialPort*)), Qt::QueuedConnection);
    connect(baojitai, SIGNAL(signal_product_change(Product*)), this, SLOT(on_prodoct_change_signal(Product*)), Qt::QueuedConnection);
    connect(baojitai, SIGNAL(signal_robotic_status_change(RoboticTCPServer*)), this, SLOT(on_robotic_status_change_signal(RoboticTCPServer*)), Qt::QueuedConnection);
    connect(baojitai, SIGNAL(signal_plc_status_change()), this, SLOT(on_plc_status_change_signal()), Qt::QueuedConnection);
    connect(baojitai, SIGNAL(signal_camera_status_change(Camera*)), this, SLOT(on_camera_status_change_signal(Camera*)), Qt::QueuedConnection);
    connect(baojitai, SIGNAL(signal_camera_buffer_updated(Camera*)), this, SLOT(on_camera_buffer_changed(Camera*)), Qt::QueuedConnection);
    connect(baojitai, SIGNAL(signal_running_status_change()), this, SLOT(on_running_status_change()), Qt::QueuedConnection);
    connect(baojitai, SIGNAL(signal_advanced_device_count_change()), this, SLOT(on_advanced_device_count_change()), Qt::QueuedConnection);
    connect(baojitai, SIGNAL(signal_location_finish()), this, SLOT(on_location_finish()), Qt::QueuedConnection);
    connect(baojitai, SIGNAL(signal_reading_code_finish()), this, SLOT(on_reading_code_finish()), Qt::QueuedConnection);
    connect(baojitai, SIGNAL(signal_check_frame_finish()), this, SLOT(on_check_frame_finish()), Qt::QueuedConnection);
    connect(baojitai, SIGNAL(signal_product_arrive()), this, SLOT(on_signal_product_arrive()), Qt::QueuedConnection);
    connect(baojitai, SIGNAL(signal_product_info(QString)), this, SLOT(on_signal_product_info(QString)), Qt::QueuedConnection);
    connect(baojitai, SIGNAL(signal_plc_repair_mode_change()), this, SLOT(on_signal_plc_repair_mode_change()), Qt::QueuedConnection);
    connect(baojitai, SIGNAL(signal_plc_reset()), this, SLOT(on_signal_plc_reset()), Qt::QueuedConnection);
    connect(baojitai, SIGNAL(signal_fid_cmc_socket_status_change()), this, SLOT(on_fid_cmc_socket_status_change()), Qt::QueuedConnection);
    connect(baojitai, SIGNAL(signal_tid_ng(QString,QString)), this, SLOT(on_signal_tid_ng(QString,QString)), Qt::QueuedConnection);
    connect(baojitai, SIGNAL(signal_sn_ng(QString,QString,QString)), this, SLOT(on_signal_sn_ng(QString,QString,QString)), Qt::QueuedConnection);
    connect(baojitai, SIGNAL(signal_fid_ng(QString,QString)), this, SLOT(on_signal_fid_ng(QString,QString)), Qt::QueuedConnection);
    connect(baojitai, SIGNAL(signal_location_ng()), this, SLOT(on_signal_location_ng()), Qt::QueuedConnection);

	// 刷新相机状态
    on_camera_status_change_signal(baojitai->camera_reading_code());
    on_camera_status_change_signal(baojitai->camera_location());
    on_camera_status_change_signal(baojitai->camera_check_frame());
	// 刷新串口状态
	on_serial_port_status_signal(NULL);
    // 刷新机械臂状态
    on_robotic_status_change_signal(baojitai->robotic_tcp_server());
    // 刷新当前产品
    on_prodoct_change_signal(baojitai->current_product());
	// 打开PLC
	baojitai->open_plc_act_utl();
    // 刷新设备运行状态
    on_running_status_change();
    // fid cmc 连接状态
    on_fid_cmc_socket_status_change();
    // 站线信息
    ui->label_select_scan_dir->setText(baojitai->scan_dir().c_str());
    ui->lineEdit_line_name->setText(baojitai->line_name().c_str());
    ui->lineEdit_station_name->setText(baojitai->station_name().c_str());
    ui->lineEdit_station_id->setText(baojitai->station_id().c_str());

//    RoboticTCPServer* robotic_server = baojitai->robotic_tcp_server();
//    if (robotic_server)
//        ui->label_robotic_port->setText(to_string(robotic_server->listening_port()).c_str());
//    ItemInformationCenter* item_center = baojitai->item_center();
//    if (item_center)
//        ui->label_advanced_device_port->setText(to_string(item_center->listening_port()).c_str());

    QPalette pal(ui->pos_visual_angle->palette());
    pal.setColor(QPalette::Background, Qt::green);
    ui->pos_visual_angle->setAutoFillBackground(true);
    ui->pos_visual_angle->setPalette(pal);

    ui->stackedWidget->setCurrentIndex(0);
    ui->listView_info->setModel(&info_list_item_model_);
    ui->tableView_ng->setModel(&ng_list_item_model_);
    ui->tableView_ng->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableView_advance_product_ng->setModel(&advanced_device_ng_item_model_);


    //QsqDatabase db = QsqlDatabase::addDatabase("SQLITE");
    //db.setDatabaseName("item.db");
    //if(!db.open())
    //{
    //       //错误处理
    //}
    //static QSqlQueryModel *model = new QSqlQueryModel(ui->tableView_advance_product_ng);
    //model->setQuery(QString("select * from table;"));
    //model->setHeaderData(0,Qt::Horizontal,QObject::tr("编号"));
    //model->setHeaderData(1,Qt::Horizontal,QObject::tr("TID"));
    //model->setHeaderData(2,Qt::Horizontal,QObject::tr("NG"));
    //model->setHeaderData(3,Qt::Horizontal,QObject::tr("REASON"));
    //model->setHeaderData(4,Qt::Horizontal,QObject::tr("STATION"));
    //model->setHeaderData(5,Qt::Horizontal,QObject::tr("DATATIME"));
    //ui->tableView_advance_product_ng->setModel(model);
    //db->close();

}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::resetUI(QWidget *pWidget)
//{
//    if(!pWidget){
//        return;
//    }
//    QDesktopWidget* desktopWidget = QApplication::desktop();
//    //获取可用桌面大小
//    QRect deskRect = desktopWidget->availableGeometry();
//    // 如果分辨率已经在1920及以上，则不需要进行处理
//    if(deskRect.width() >1920){
//        return;
//    }
//    //仅使用x比例，否则窗口会变形
//    float scale = deskRect.width() / 1920.0;
//    QObjectList lst = pWidget->children();
//    QPoint pt(0,0);
//    for(auto l : lst)
//    {
//        auto MainWindow = qobject_cast<QWidget*>(l);
//        if(MainWindow)
//        {
//            pt = MainWindow->pos();

//            MainWindow->move(QPoint(pt.x() * scale, pt.y() * scale));
//            MainWindow->resize(MainWindow->width() * scale, MainWindow->height() * scale);

//            QFont font;
//            int nIndex = MainWindow->metaObject()->indexOfProperty("font");
//            auto propertyFont = MainWindow->metaObject()->property(nIndex);

//            QVariant var =  propertyFont.read(MainWindow);
//            if(var.canConvert(QMetaType::QFont))
//            {
//                font = var.value<QFont>();

//                font.setPointSizeF(font.pointSizeF() * scale);
//                propertyFont.write(MainWindow,QVariant::fromValue(font));
//            }

//            QPixmap pixmap;
//            nIndex = MainWindow->metaObject()->indexOfProperty("pixmap");
//            auto pixmapProp = MainWindow->metaObject()->property(nIndex);

//            var = pixmapProp.read(MainWindow);
//            if(var.canConvert(QMetaType::QPixmap))
//            {
//                pixmap = var.value<QPixmap>();
//                if(!pixmap.isNull())
//                {
//                    QSize sizePixmap(pixmap.size().width() * scale, pixmap.size().height() * scale);

//                    pixmap =  pixmap.scaled(sizePixmap);
//                    pixmapProp.write(MainWindow,QVariant::fromValue(pixmap));
//                }
//            }
//        }
//    }

//    pWidget->resize(pWidget->width() * scale, pWidget->height() * scale);
//}

//float MainWindow::getScale()
//{
//    QDesktopWidget* desktopWidget = QApplication::desktop();
//    //获取可用桌面大小
//    QRect deskRect = desktopWidget->availableGeometry();

//    return deskRect.width() / 1920.0;
//}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (Baojitai::instance()->is_running())
    {
        QMessageBox::warning(this, QStringLiteral("检测系统正在运行"), QStringLiteral("请先点击停止按钮"), QMessageBox::StandardButton::Ok);
        event->ignore();
        return;
    }
    on_pushButton_export_ng_table_clicked();
}

void MainWindow::on_toolButton_3_windowIconTextChanged(const QString &iconText)
{

}

void MainWindow::on_help_btn_clicked()
{
   About about;
   about.exec();
}

void MainWindow::on_pro_btn_clicked()
{
    Baojitai* baojitai = Baojitai::instance();
    if (baojitai->is_running())
    {
        QMessageBox::warning(this, QStringLiteral("设备正在运行"), QStringLiteral("请先点击Stop按钮"), QMessageBox::StandardButton::Ok);
        return;
    }

    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_sty_btn_clicked()
{
    Baojitai* baojitai = Baojitai::instance();
    if (baojitai->is_running())
    {
        QMessageBox::warning(this, QStringLiteral("设备正在运行"), QStringLiteral("请先点击Stop按钮"), QMessageBox::StandardButton::Ok);
        return;
    }

    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_main_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_Pc_btn_clicked()
{
    PositionCalibrate pos_calibrate;
    pos_calibrate.exec();
}

void MainWindow::on_cam_btn_clicked()
{
    CameraConfigDialog camera_config_dialog;
    camera_config_dialog.exec();
}

void MainWindow::on_qr_btn_clicked()
{
    ReadingCodeConfigDialog qrconfig;
    connect(&qrconfig, SIGNAL(SignalSerialPort(const string&)), this, SLOT(on_serial_sinal(const string&)));
    qrconfig.exec();
    disconnect(&qrconfig, SIGNAL(SignalSerialPort(const string&)), this, SLOT(on_serial_sinal(const string&)));
}

void MainWindow::on_sav_btn_clicked()
{
    SaveConfigDialog config_save;
    config_save.exec();
}

void MainWindow::on_label_2_linkActivated(const QString &link)
{

}

void MainWindow::timeUpdate()
{
    QDateTime CurrentTime= QDateTime::currentDateTime();

    QString Timestr=CurrentTime.toString( QStringLiteral(" yyyy/MM/dd hh:mm:ss ")); //设置显示的格式

    currentTimeLabel->setText(Timestr);

    Baojitai* baojitai = Baojitai::instance();
    ui->checkBox_close_location->setChecked(baojitai->is_close_location());
    ui->checkBox_close_tid->setChecked(baojitai->is_close_tid());
    ui->checkBox_close_sn->setChecked(baojitai->is_close_sn());
    ui->checkBox_close_fid->setChecked(baojitai->is_close_fid());
}

void MainWindow::on_camera_reading_code_buffer_changed()
{
    const unsigned char* image_buffer = NULL;
    int width, height;
    Baojitai::instance()->camera_reading_code_buffer(&image_buffer, &width, &height);
    if (image_buffer)
    {
        HImage img("byte", width, height, (void*)image_buffer);
        image_reading_code_ = img.CopyImage();
        reading_code_result_updated_ = false;
        ui->widget_reading_code->update();
    }
}

void MainWindow::on_camera_location_buffer_changed()
{
    const unsigned char* image_buffer = NULL;
    int width, height;
    Baojitai::instance()->camera_location_buffer(&image_buffer, &width, &height);
    if (image_buffer)
    {
        HImage img("byte", width, height, (void*)image_buffer);
        image_location_ = img.CopyImage();
        location_result_updated_ = false;
        ui->widget_image_location->update();
        ui->label_location_result->setText("");
    }
}

void MainWindow::on_camera_check_frame_buffer_changed()
{
    const unsigned char* image_buffer = NULL;
    int width, height;
    Baojitai::instance()->camera_check_frame_buffer(&image_buffer, &width, &height);
    if (image_buffer)
    {
        HImage img("byte", width, height, (void*)image_buffer);
        image_check_frame_ = img.CopyImage();
        ui->widget_image_check_frame->update();
    }
}

void MainWindow::draw_camera_reading_code(HWindow& window)
{
    if (!window.IsHandleValid())
        return;

    if (image_reading_code_.IsInitialized())
    {
        window.SetPart(0, 0, (Hlong)image_reading_code_.Height(), (Hlong)image_reading_code_.Width());
        window.DispImage(image_reading_code_);
    }

    if (reading_code_result_updated_)
    {
		if (board_bar_code_region_.IsInitialized())
			halcontools::draw_region(window, board_bar_code_region_, halcontools::kHalconColorGreen, 1, false);
		if (product_bar_code_region_.IsInitialized())
			halcontools::draw_region(window, product_bar_code_region_, halcontools::kHalconColorRed, 1, false);
		if (product_mat_code_xld_.IsInitialized())
			halcontools::draw_xld(window, product_mat_code_xld_, halcontools::kHalconColorRed, 1, false);
    }
}

void MainWindow::draw_camera_location(HWindow& window)
{
    if (!window.IsHandleValid())
        return;

    if (image_location_.IsInitialized())
    {
        window.SetPart(0, 0, (Hlong)image_location_.Height(), (Hlong)image_location_.Width());
        window.DispImage(image_location_);
    }

    if (location_result_updated_)
    {
        if (location_result_.find_rect)
        {
            int width = image_location_.Width();
            int height = image_location_.Height();
            if (location_result_.x < width &&
                    location_result_.y < height &&
                    location_result_.l1 * 2 < width &&
                    location_result_.l2 * 2 < height)
            {
                float x = location_result_.x;
                float y = location_result_.y;
                float phi = location_result_.phi;
                float l1 = location_result_.l1;
                float l2 = location_result_.l2;
                halcontools::draw_rect(window, x, y, phi, l1, l2, halcontools::kHalconColorRed, 1, false);
                float x1 = x + l1 * cos(phi);
                float y1 = y - l1 * sin(phi);
                float x2 = x - l1 * cos(phi);
                float y2 = y + l1 * sin(phi);
                halcontools::draw_line(window, x1, y1, x2, y2, halcontools::kHalconColorBlue);
                float pi_2 = 3.14159f * 0.5;
                float x3 = x + l2 * cos(pi_2 + phi);
                float y3 = y - l2 * sin(pi_2 + phi);
                float x4 = x - l2 * cos(pi_2 + phi);
                float y4 = y + l2 * sin(pi_2 + phi);
                halcontools::draw_line(window, x3, y3, x4, y4, halcontools::kHalconColorBlue);
            }
        }
        else
        {
//            halcontools::draw_cross(window,
//                                    (Hlong)image_location_.Height() *0.5,
//                                    (Hlong)image_location_.Width() * 0.5,
//                                    300,
//                                    halcontools::kHalconColorRed,
//                                    45,
//                                    10);
        }
    }
}
void MainWindow::draw_camera_check_frame(HWindow& window)
{
    if (!window.IsHandleValid())
        return;

    if (image_check_frame_.IsInitialized())
    {
        window.SetPart(0, 0, (Hlong)image_check_frame_.Height(), (Hlong)image_check_frame_.Width());
        window.DispImage(image_check_frame_);
    }

    if (check_frame_result_updated_)
    {
        FrameParam param = Baojitai::instance()->frame_param_;

        int x = param.x();
        int y = param.y();
        int w = param.w();
        int h = param.h();

        if (check_frame_result_.is_disk_ok)
        {
            halcontools::draw_rect(window, x + w * 0.5, y + h * 0.5, 0, w * 0.5, h * 0.5, halcontools::kHalconColorGreen, 1, false);
        }
        else
        {
            halcontools::draw_rect(window, x + w * 0.5, y + h * 0.5, 0, w * 0.5, h * 0.5, halcontools::kHalconColorRed, 1, false);
        }

        int lx = param.lx();
        int ly = param.ly();
        int lw = param.lw();
        int lh = param.lh();
        if (check_frame_result_.is_found_left)
        {
            halcontools::draw_rect(window, lx, ly, 0, lw, lh, halcontools::kHalconColorRed, 1, false);
            //halcontools::draw_region(window, check_frame_result_.left_white_region, halcontools::kHalconColorRed, 1, true);
        }
        else
        {
            halcontools::draw_rect(window, lx, ly, 0, lw, lh, halcontools::kHalconColorGreen, 1, false);
        }

        int rx = param.rx();
        int ry = param.ry();
        int rw = param.rw();
        int rh = param.rh();
        if (check_frame_result_.is_found_right)
        {
            halcontools::draw_rect(window, rx, ry, 0, rw, rh, halcontools::kHalconColorRed, 1, false);
            //halcontools::draw_region(window, check_frame_result_.right_white_region, halcontools::kHalconColorRed, 1, true);
        }
        else
        {
            halcontools::draw_rect(window, rx, ry, 0, rw, rh, halcontools::kHalconColorGreen, 1, false);
        }
    }
}

void MainWindow::on_camera_buffer_changed(Camera* camera)
{
    if (!camera)
        return;
    Baojitai* baojitai = Baojitai::instance();
    if (camera == baojitai->camera_location())
    {
        on_camera_location_buffer_changed();
    }
    else if (camera == baojitai->camera_reading_code())
    {
        on_camera_reading_code_buffer_changed();
    }
    else if (camera == baojitai->camera_check_frame())
    {
        on_camera_check_frame_buffer_changed();\
    }
}

void MainWindow::on_location_finish()
{
    Baojitai::instance()->location_result(location_result_);
    location_result_updated_ = true;
    ui->widget_image_location->update();
    if (location_result_.success)
        ui->label_location_result->setText(QStringLiteral("定位成功"));
    else
        ui->label_location_result->setText(QStringLiteral("定位失败"));
}

void MainWindow::on_reading_code_finish()
{
    bool success;
	Baojitai::instance()->reading_code_result(success, tid_, sn_, board_bar_code_region_, product_bar_code_region_, product_mat_code_xld_);
    reading_code_result_updated_ = true;
    ui->widget_reading_code->update();
}

void MainWindow::on_check_frame_finish()
{
    Baojitai::instance()->check_frame_result(check_frame_result_);
    check_frame_result_updated_ = true;
    ui->widget_image_check_frame->update();

}

void MainWindow::on_camera_status_change_signal(Camera* camera)
{
    Baojitai* baojitai = Baojitai::instance();
    if (camera == baojitai->camera_reading_code())
    {
        if(camera && camera->is_open())
            qr_camera_status_lineedit->setStyleSheet("background-color: rgb(0, 255, 0);");
        else
            qr_camera_status_lineedit->setStyleSheet("background-color: rgb(255,0, 0);");
    }
    
	if (camera == baojitai->camera_location())
    {
        if(camera && camera->is_open())
            pos_camera_status_lineedit->setStyleSheet("background-color: rgb(0, 255, 0);");
        else
            pos_camera_status_lineedit->setStyleSheet("background-color: rgb(255,0, 0);");
    }
    
	if (camera == baojitai->camera_check_frame())
    {
        if(camera && camera->is_open())
            frame_camera_status_lineedit->setStyleSheet("background-color: rgb(0, 255, 0);");
        else
            frame_camera_status_lineedit->setStyleSheet("background-color: rgb(255,0, 0);");
    }
}

void MainWindow::on_robotic_status_change_signal(RoboticTCPServer* robotic_tcp_server)
{
    if (robotic_tcp_server && robotic_tcp_server->robotic_connected())
    {
        // 状态栏显示 机械臂已连接
//		robotic_status_lineEdit->setText(QStringLiteral("[机械手已连接]"));
		robotic_status_lineEdit->setStyleSheet("background-color: rgb(0, 255, 0);");
    }
    else
    {
        // 状态栏显示 机械臂断开连接
//		robotic_status_lineEdit->setText(QStringLiteral("[机械手断开连接]"));
		robotic_status_lineEdit->setStyleSheet("background-color: rgb(255, 0, 0);");
    }
}

void MainWindow::on_plc_status_change_signal()
{
	Baojitai* baojitai = Baojitai::instance();
	if (baojitai)
	{
		if (baojitai->plc_act_utl())
		{
			plc_status_lineedit->setStyleSheet("background-color: rgb(0, 255, 0);");
		}
		else
		{
			plc_status_lineedit->setStyleSheet("background-color: rgb(255, 0, 0);");
		}
	}
}

void MainWindow::on_advanced_device_count_change()
{
    Baojitai* baojitai = Baojitai::instance();
    if (baojitai)
    {
        vector<string> ip_list = baojitai->advanced_device_ip_list();
        QString text;
        text.sprintf("%d", ip_list.size());
        this->advanced_device_count_label->setText(text);
    }
}

void MainWindow::on_fid_cmc_socket_status_change()
{
    Baojitai* baojitai = Baojitai::instance();
    if (baojitai->is_fid_cmc_socket_connected())
        fid_cmc_socket_status_lineedit->setStyleSheet("background-color: rgb(0, 255, 0);");
    else
        fid_cmc_socket_status_lineedit->setStyleSheet("background-color: rgb(255, 0, 0);");
}

void MainWindow::on_serial_sinal(const string& device_name)
{
//    ssvision::SerialPortManager* manager = ssvision::SerialPortManager::instance();
//    ssvision::SerialPort* serial_port = manager->serialport(device_name);
//    if (!serial_port)
//    {
//        QMessageBox::warning(this, "v", device_name.c_str(), QMessageBox::StandardButton::Ok);
//        return;
//    }
//    if (device_name.compare(baojitai_temp::kSerialPortNameReadingCode) == 0)
//    {
//        if (serial_port->is_open())
//        {
//             reading_code_serial_port_status_lineedit->setStyleSheet("background-color: rgb(0, 255, 0);");
//        }
//        else
//        {
//            reading_code_serial_port_status_lineedit->setStyleSheet("background-color: rgb(255, 0, 0);");
//        }
//    }
}


void MainWindow::on_serial_port_status_signal(ssvision::SerialPort*)
{
	Baojitai* baojitai = Baojitai::instance();

    SerialPort* sp = baojitai->serial_port_sending_code();
    if (sp && sp->is_open())
        reading_code_serial_port_status_lineedit->setStyleSheet("background-color: rgb(0, 255, 0);");
    else
        reading_code_serial_port_status_lineedit->setStyleSheet("background-color: rgb(255, 0, 0);");

	sp = baojitai->serial_port_read_fid();
    if (sp && sp->is_open())
        reading_code_serial_port_status_lineedit2->setStyleSheet("background-color: rgb(0, 255, 0);");
    else
        reading_code_serial_port_status_lineedit2->setStyleSheet("background-color: rgb(255, 0, 0);");
	
    sp = baojitai->serial_port_repair_mode();
    if (sp && sp->is_open())
        reading_code_serial_port_status_lineedit3->setStyleSheet("background-color: rgb(0, 255, 0);");
    else
        reading_code_serial_port_status_lineedit3->setStyleSheet("background-color: rgb(255, 0, 0);");
}

void MainWindow::on_signal_plc_reset()
{
    info_list_item_model_.clear();
    QStandardItem* item = new QStandardItem("plc reset");
    info_list_item_model_.appendRow(item);
}

void MainWindow::on_signal_plc_repair_mode_change()
{
    bool repair_mode = Baojitai::instance()->is_repair_mode();
    ui->label_repair_mode->setText(repair_mode ? QStringLiteral("返修模式") : QStringLiteral("正常模式"));
}

void MainWindow::on_running_status_change()
{
    Baojitai* baojitai = Baojitai::instance();
    if (baojitai->is_running())
    {
        running_status_lineEdit->setStyleSheet("background-color: rgb(0, 255, 0);");
        ui->toolButton_start->setEnabled(false);
        ui->toolButton_stop->setEnabled(true);
        //ui->checkBox_repair_mode->setEnabled(false);
    }
    else
    {
        running_status_lineEdit->setStyleSheet("background-color: rgb(255, 0, 0);");
        ui->toolButton_start->setEnabled(true);
        ui->toolButton_stop->setEnabled(false);
        //ui->checkBox_repair_mode->setEnabled(true);
    }
}

void MainWindow::on_toolButton_change_product_clicked()
{
    Baojitai* baojitai = Baojitai::instance();
    if (baojitai->is_running())
    {
        QMessageBox::warning(this, QStringLiteral("设备正在运行"), QStringLiteral("请先点击Stop按钮"), QMessageBox::StandardButton::Ok);
        return;
    }

	QString product_model = ui->comboBox_product_list->currentText();
	if (product_model.length() == 0)
	{
        QMessageBox::warning(this, QStringLiteral("未知产品型号"), QStringLiteral("请先创建产品"), QMessageBox::StandardButton::Ok);
		return;
	}
	else
	{
        Product *current_product = Baojitai::instance()->current_product();
        if (current_product && !current_product->is_saved())
        {
            QMessageBox msgBox;
            msgBox.setText(QStringLiteral("当前产品设置未保存"));
            msgBox.setInformativeText(QStringLiteral("请选择是否保存当前产品设置"));
            msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Save);
            int ret = msgBox.exec();
            switch (ret) {
            case QMessageBox::Save:
            {
                string product_config_path = ProductManager::instance()->product_config_path(current_product->name());
                current_product->save_config(product_config_path);
            }
                break;
            case QMessageBox::Discard:
            {
                                         // 用户选择不保存
            }
                break;
            case QMessageBox::Cancel:
            {
                                        // 用户选择取消
                                        return;
            }
                break;
            default:
                // should never be reached
                break;
            }
        }
		
        Product* product = ProductManager::instance()->create_product(product_model.toStdString());
        Baojitai::instance()->set_current_product(product);
	}
}

void MainWindow::on_toolButton_change_clicked()
{
    QString product_model = ui->switch_model->currentText();
    if (product_model.length() == 0)
    {
        QMessageBox::warning(this, QStringLiteral("未知产品型号"), QStringLiteral("请先创建产品"), QMessageBox::StandardButton::Ok);
        return;
    }
    else
    {
        Product *current_product = Baojitai::instance()->current_product();
        if (current_product&& !current_product->is_saved())
        {
            QMessageBox msgBox;
            msgBox.setText(QStringLiteral("当前产品设置未保存"));
            msgBox.setInformativeText(QStringLiteral("请选择是否保存当前产品设置"));
            msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Save);
            int ret = msgBox.exec();
            switch (ret) {
            case QMessageBox::Save:
            {
                string product_config_path = ProductManager::instance()->product_config_path(current_product->name());
                current_product->save_config(product_config_path);
            }
                break;
            case QMessageBox::Discard:
            {
                // 用户选择不保存
            }
                break;
            case QMessageBox::Cancel:
            {
                // 用户选择取消切换产品
                return;
            }
                break;
            }
        }

        Product* new_product = ProductManager::instance()->create_product(product_model.toStdString());
        Baojitai::instance()->set_current_product(new_product);
    }
}

void MainWindow::on_paint(HalconWidget *halconwidget, HWindow &halcon_window)
{
    if (halconwidget == ui->widget_image_location)
        draw_camera_location(halcon_window);
    else if (halconwidget == ui->widget_image_check_frame)
        draw_camera_check_frame(halcon_window);
    else if (halconwidget == ui->widget_reading_code)
        draw_camera_reading_code(halcon_window);
}

void MainWindow::on_prodoct_change_signal(Product *product)
{
    if (!product)
        return;
    string product_model = product->name();
    ui->switch_model->clear();
    ui->comboBox_product_list->clear();
    foreach(string product_name, ProductManager::instance()->product_name_list())
    {
        ui->comboBox_product_list->addItem(product_name.c_str());
        ui->switch_model->addItem(product_name.c_str());
    }
    ui->switch_model->setCurrentText(product_model.c_str());
    ui->comboBox_product_list->setCurrentText(product_model.c_str());
    ui->lineEdit_current->setText(product_model.c_str());
    ui->label_current_product->setText((product_model.c_str()));
}

void MainWindow::on_toolButton_create_clicked()
{
    string product_model = ui->lineEdit_create->text().toStdString();
    if (product_model.length() == 0)
    {
        QMessageBox::warning(this, QStringLiteral("未知产品型号"), QStringLiteral("请输入产品型号"), QMessageBox::StandardButton::Ok);
        return;
    }
    else
    {
        bool product_exist = false;
        foreach(string exist_product_name, ProductManager::instance()->product_name_list())
        {
            if(product_model.compare(exist_product_name) == 0)
            {
                product_exist = true;
                break;
            }
        }

        if (product_exist)
        {
            QMessageBox::warning(this,"", QStringLiteral("已有该型号"), QMessageBox::StandardButton::Ok);
        }
        else
        {
            Baojitai* baojitai = Baojitai::instance();
            Product *product = new Product(product_model);
            string product_config_path = ProductManager::instance()->product_config_path(product->name());
            Product* current_product = baojitai->current_product();
            if (current_product)
            {
                product->set_code_param(current_product->data_code_param());
                product->set_metric_param(current_product->metric_param());
                product->set_vision_param(current_product->vision_param());
            }
            product->save_config(product_config_path);
            baojitai->set_current_product(product);
            QMessageBox::warning(this,"", QStringLiteral("创建成功"), QMessageBox::StandardButton::Ok);
            ui->lineEdit_create->setText("");
        }
    }
}

void MainWindow::on_toolButton_del_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(QStringLiteral("警告"));
    msgBox.setText(QStringLiteral("确定要删除当前产品"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Yes:
    {
        Baojitai* baojitai = Baojitai::instance();
        Product* current_product = baojitai->current_product();
        if (current_product)
        {
            ProductManager* product_manager = ProductManager::instance();
            product_manager->remove_product(current_product->name());
            vector<string> product_name_list = product_manager->product_name_list();
            if (product_name_list.size() > 0)
            {
                Product* product = product_manager->create_product(product_name_list[0]);
                baojitai->set_current_product(product);
            }
            else
                baojitai->set_current_product(NULL);
        }
    }
        break;
    case QMessageBox::No:
    {
        return;
    }
        break;
    }
}

void MainWindow::on_toolButton_start_clicked()
{
//    bool repair_mode = ui->checkBox_repair_mode->isChecked();
//    if (repair_mode)
//    {
//        int ret = QMessageBox::information(this, QStringLiteral("返修模式"),
//                                       QStringLiteral("是否进入返修模式?"),
//                                       QMessageBox::Ok
//                                       | QMessageBox::Cancel,
//                                       QMessageBox::Cancel);
//        if (ret != QMessageBox::Ok)
//        {
//            return;
//        }
//    }

    Baojitai* baojitai = Baojitai::instance();
    bool repair_mode = baojitai->is_repair_mode();
    if (repair_mode)
    {
        SerialPort* sp = baojitai->serial_port_repair_mode();
        if (!sp)
            QMessageBox::information(this, QStringLiteral("返修串口设备未连接"),
                                           QStringLiteral("先打开返修串口设备"),
                                           QMessageBox::Ok);
    }
    else
    {
        SerialPort* sp = baojitai->serial_port_sending_code();
        if (!sp)
            QMessageBox::information(this, QStringLiteral("串口设备未连接"),
                                           QStringLiteral("先打开串口设备"),
                                           QMessageBox::Ok);
    }

    //主界面启动槽
    //baojitai->set_repair_mode(repair_mode);
    baojitai->start();
    ui->toolButton_start->setEnabled(false);
    ui->toolButton_stop->setEnabled(false);

    //ui->checkBox_repair_mode->setEnabled(false);

}

void MainWindow::on_toolButton_stop_clicked()
{
    //主界面停止槽
    Baojitai::instance()->stop();
    ui->toolButton_start->setEnabled(false);
    ui->toolButton_stop->setEnabled(false);
    //ui->checkBox_repair_mode->setEnabled(false);
}

void MainWindow::on_toolButton_reset_clicked()
{
//    主界面复位槽
}

void MainWindow::on_commun_btn_clicked()
{
    Communication comunication;
    comunication.exec();
}

void MainWindow::on_plc_btn_clicked()
{
    //plc_utltype_.SetActLogicalStationNumber(2);
    //plc_utltype_.SetActPassword("");

    ////plc_utltype_->isHidden();
    //qDebug()<<"myactive";
    ////通讯线路打开
    //int iRet = plc_utltype_.Open();
    //qDebug("return:%x",iRet);

    PLCConfigDialog plc_config_dlg;
    plc_config_dlg.set_plc_act_utl_type(&plc_utltype_);
    plc_config_dlg.exec();
}


void MainWindow::on_Imparam_btn_clicked()
{
    LocationConfigDialog imageparameter;
    imageparameter.exec();
}

void MainWindow::on_frame_btn_clicked()
{
    Frame_Dialog frame_Dialog;
    frame_Dialog.exec();
}

void MainWindow::on_signal_product_arrive()
{
    info_list_item_model_.clear();
}

void MainWindow::on_signal_product_info(QString info)
{
    QStandardItem* item = new QStandardItem(info);
    info_list_item_model_.appendRow(item);
}

void MainWindow::on_signal_location_ng()
{
    QTime time = QTime::currentTime();
    QString time_str = time.toString("HH:mm:ss");
    QStandardItem* item_time = new QStandardItem(time_str);
    QStandardItem* item_location_ng = new QStandardItem("location ng");
    QStandardItem* item_tid = new QStandardItem("");
    QStandardItem* item_sn = new QStandardItem("");
    QStandardItem* item_reason = new QStandardItem("image");

    QList<QStandardItem*> row;
    row.append(item_time);
    row.append(item_location_ng);
    row.append(item_tid);
    row.append(item_sn);
    row.append(item_reason);
    ng_list_item_model_.insertRow(0, row);
    ui->label_ng_table_export_path->setText("");
    if (ng_list_item_model_.rowCount() % 20 == 0)
    {
        on_pushButton_export_ng_table_clicked();
    }
}

void MainWindow::on_signal_tid_ng(QString tid, QString reason)
{
    QTime time = QTime::currentTime();
    QString time_str = time.toString("HH:mm:ss");
    QStandardItem* item_time = new QStandardItem(time_str);
    QStandardItem* item_tid_ng = new QStandardItem("tid ng");
    QStandardItem* item_tid = new QStandardItem(tid);
    QStandardItem* item_sn = new QStandardItem("");
    QStandardItem* item_reason = new QStandardItem(reason);

    QList<QStandardItem*> row;
    row.append(item_time);
    row.append(item_tid_ng);
    row.append(item_tid);
    row.append(item_sn);
    row.append(item_reason);
    ng_list_item_model_.insertRow(0, row);
    ui->label_ng_table_export_path->setText("");
    if (ng_list_item_model_.rowCount() % 20 == 0)
    {
        on_pushButton_export_ng_table_clicked();
    }
}

void MainWindow::on_signal_sn_ng(QString sn, QString reason, QString tid)
{
    QTime time = QTime::currentTime();
    QString time_str = time.toString("HH:mm:ss");
    QStandardItem* item_time = new QStandardItem(time_str);
    QStandardItem* item_sn_ng = new QStandardItem("sn ng");
    QStandardItem* item_tid = new QStandardItem(tid);
    QStandardItem* item_sn = new QStandardItem(sn);
    QStandardItem* item_reason = new QStandardItem(reason);

    QList<QStandardItem*> row;
    row.append(item_time);
    row.append(item_sn_ng);
    row.append(item_tid);
    row.append(item_sn);
    row.append(item_reason);
    ng_list_item_model_.insertRow(0, row);
    ui->label_ng_table_export_path->setText("");
    if (ng_list_item_model_.rowCount() % 20 == 0)
    {
        on_pushButton_export_ng_table_clicked();
    }
}

void MainWindow::on_signal_fid_ng(QString fid, QString reason)
{
    QTime time = QTime::currentTime();
    QString time_str = time.toString("HH:mm:ss");
    QStandardItem* item_time = new QStandardItem(time_str);
    QStandardItem* item_fid_ng = new QStandardItem("fid ng");
    QStandardItem* item_blank = new QStandardItem("");
    QStandardItem* item_fid = new QStandardItem(fid);
    QStandardItem* item_reason = new QStandardItem(reason);

    QList<QStandardItem*> row;
    row.append(item_time);
    row.append(item_fid_ng);
    row.append(item_blank);
    row.append(item_fid);
    row.append(item_reason);
    ng_list_item_model_.insertRow(0, row);
    ui->label_ng_table_export_path->setText("");
    if (ng_list_item_model_.rowCount() % 20 == 0)
    {
        on_pushButton_export_ng_table_clicked();
    }
}

void MainWindow::on_toolButton_9_clicked()
{
    // ui->listView_info->add
//    Baojitai* baojitai = Baojitai::instance();
//    string data = "12";
//    baojitai->on_read_fid_data(data.c_str(), data.length());
//    data = "12";
//    baojitai->on_read_fid_data(data.c_str(), data.length());
//    data = "34\r";
//    baojitai->on_read_fid_data(data.c_str(), data.length());
//    data = "TC12345\r";
//    baojitai->on_read_fid_data(data.c_str(), data.length());
//    data = "3\r\rTB8904\r";
//    baojitai->on_read_fid_data(data.c_str(), data.length());
//    data = "12345\r5678\r879\r89";
//    baojitai->on_read_fid_data(data.c_str(), data.length());

    //baojitai->test_emit_tid_ng("unknwon", "xx");
//    baojitai->test_emit_tid_ng("TF0023", "CMC");
//    baojitai->test_emit_sn_ng("validsnxxxx9999y7", "cmc", "ft2030");

}

//void MainWindow::on_spinBox_x_offset_valueChanged(int arg1)
//{
//    Baojitai::instance()->set_robotic_x_offset(arg1);
//}

//void MainWindow::on_spinBox_y_offset_valueChanged(int arg1)
//{
//    Baojitai::instance()->set_robotic_y_offset(arg1);
//}

//void MainWindow::on_spinBox_rz_offset_valueChanged(int arg1)
//{
//    Baojitai::instance()->set_robotic_rz_offset(arg1);
//}

void MainWindow::on_toolButton_send_undo_0_clicked()
{
    Baojitai* baojitai = Baojitai::instance();
    if (baojitai->is_running())
    {
        baojitai->on_user_send_undo();
    }
    else
    {
        QMessageBox::information(this, QStringLiteral("发送失败"),
                                       QStringLiteral("先点击开始按钮"),
                                       QMessageBox::Ok);
    }
}

void MainWindow::on_checkBox_close_location_toggled(bool checked)
{
    Baojitai::instance()->set_close_location(checked);
}

void MainWindow::on_checkBox_close_tid_toggled(bool checked)
{
    Baojitai::instance()->set_close_tid(checked);
}

void MainWindow::on_checkBox_close_sn_toggled(bool checked)
{
    Baojitai::instance()->set_close_sn(checked);
}

void MainWindow::on_checkBox_close_fid_toggled(bool checked)
{
    Baojitai::instance()->set_close_fid(checked);
}

void MainWindow::on_pushButton_send_AAAAAA_clicked()
{
    Baojitai* baojitai = Baojitai::instance();
    if (baojitai->is_running())
    {
        baojitai->on_user_send_AAAAAA();
    }
    else
    {
        QMessageBox::information(this, QStringLiteral("发送失败"),
                                       QStringLiteral("先点击开始按钮"),
                                       QMessageBox::Ok);
    }
}

void MainWindow::on_checkBox_offline_toggled(bool checked)
{
    Baojitai::instance()->set_offline_mode(checked);
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    //Baojitai::instance()->set_receive_send_fid(checked);
}

void MainWindow::on_pushButton_save_line_station_info_clicked()
{
    string scan_dir = ui->label_select_scan_dir->text().toStdString();
    if (scan_dir.length() == 0)
    {
        QMessageBox::information(this, QStringLiteral("保存失败"),
                                       QStringLiteral("请先选择扫描目录"),
                                       QMessageBox::Ok);
        return;
    }
    string line_name = ui->lineEdit_line_name->text().toStdString();
    string station_name = ui->lineEdit_station_name->text().toStdString();
    string station_id = ui->lineEdit_station_id->text().toStdString();
    Baojitai::instance()->save_line_station_info(scan_dir, line_name, station_name, station_id);
}

void MainWindow::on_pushButton_clear_ng_table_clicked()
{
    this->ng_list_item_model_.clear();
}

void MainWindow::on_pushButton_export_ng_table_clicked()
{
    QDateTime datetime = QDateTime::currentDateTime();
    QDate date = datetime.date();
    int year = date.year();
    int month = date.month();
    int day = date.day();
    // 20190931
    QString yyyyMMdd = QString().sprintf("%04d%02d%02d", year, month, day);
    QTime time = datetime.time();
    int hour = time.hour();
    int minute = time.minute();
    int second = time.second();
    QString hhmmss = QString().sprintf("%02d%02d%02d", hour, minute, second);

    string file_name = (yyyyMMdd + "_" + hhmmss + "_ng.csv").toStdString();
    string file_path = Baojitai::instance()->date_file_path(datetime, file_name);
    ofstream file_stream(file_path);
    int count = ng_list_item_model_.rowCount();
    for (int i = 0; i < count; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            if (j != 0)
                file_stream << ",";
            file_stream << ng_list_item_model_.data(ng_list_item_model_.index(i, j)).toString().toStdString();
        }
        file_stream << endl;
    }

    ui->label_ng_table_export_path->setText(file_path.c_str());
}

void MainWindow::on_pushButton_select_scan_dir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    ".", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->label_select_scan_dir->setText(dir);
}

void MainWindow::on_timer_scan_dir()
{
    QString scan_dir = ui->label_select_scan_dir->text();
    QDir src_dir(scan_dir);
    QFileInfoList list = src_dir.entryInfoList();
    QString lxk_path;
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        QString suffix = fileInfo.suffix();
        if (suffix.compare("LXK", Qt::CaseInsensitive) == 0)
        {
            lxk_path = fileInfo.filePath();
            break;
        }
    }

    if (lxk_path.length() == 0)
    {
        QMessageBox::information(this, QStringLiteral("扫码换机种失败"),
                                       QStringLiteral("没有获取到正确的 LXK 文件"),
                                       QMessageBox::Ok);
        return;
    }

    ifstream lxk_file(lxk_path.toStdString());
    int line_no = 5;
    int read_line = 0;
    string line;
    while (getline(lxk_file, line))
    {
        if (++read_line == line_no - 1)
            break;
    }
    string material_line;
    getline(lxk_file, material_line);
    if (material_line.length() == 0)
    {
        QMessageBox::information(this, QStringLiteral("扫码换机种失败"),
                                       QStringLiteral("没有获取到正确的物料号"),
                                       QMessageBox::Ok);
        return;
    }

    qDebug() << material_line.c_str() << endl;

    Baojitai* baojitai = Baojitai::instance();
    string product;
    if (baojitai->material_exists(material_line, product))
    {
        Product* new_product = ProductManager::instance()->create_product(product);
        Baojitai::instance()->set_current_product(new_product);
        QMessageBox::information(this, QStringLiteral("新机种"),
                                       product.c_str(),
                                       QMessageBox::Ok);
    }
    else
    {
        MaterialProductDialog dialog;
        dialog.set_material(material_line);
        int ret = dialog.exec();
        product = dialog.get_product();
        if (ret == QDialog::Accepted && product.length() > 0)
        {
            Baojitai* baojitai = Baojitai::instance();
            Product* new_product = ProductManager::instance()->create_product(product);
            baojitai->set_current_product(new_product);
            baojitai->insert_material_product(material_line, product);
            QMessageBox::information(this, QStringLiteral("新机种"),
                                           product.c_str(),
                                           QMessageBox::Ok);
        }
    }
}

void MainWindow::on_lineEdit_scan_tid_returnPressed()
{
    QString tid = ui->lineEdit_scan_tid->text();
    if (tid.length() == 0)
        return;
    QString scan_dir = ui->label_select_scan_dir->text();
    if (scan_dir.length() == 0)
    {
        QMessageBox::information(this, QStringLiteral("扫码换机种失败"),
                                       QStringLiteral("先选择扫描文件夹，再扫码"),
                                       QMessageBox::Ok);
        return;
    }

//    QDir dir(scan_dir);
//    QStringList filter; //过滤器
//    filter.append("*");
//    QDirIterator it(scan_dir, filter, QDir::Files, QDirIterator::Subdirectories);
//    while(it.hasNext())
//    {
//        dir.remove(it.next());
//    }

    QString scn_path = ui->label_select_scan_dir->text() + "/" + tid + ".scn";
    ofstream scn_file(scn_path.toStdString());
    scn_file << tid.toStdString() << endl;
    scn_file << ui->lineEdit_line_name->text().toStdString() << endl;
    scn_file << ui->lineEdit_station_name->text().toStdString() << endl;
    scn_file << ui->lineEdit_station_id->text().toStdString() << endl;

    QTimer::singleShot(2000, this, SLOT(on_timer_scan_dir()));
}

//void PositionCalibrate::on_tableview_selection_changed(QItemSelection selected, QItemSelection deselected)
//{
//    ui->tableView->selectionModel()->select(selected, QItemSelectionModel::Select | QItemSelectionModel::Rows);
//    ui->tableView->selectionModel()->select(deselected, QItemSelectionModel::Deselect | QItemSelectionModel::Rows);
//    ui->tableView_2->selectionModel()->select(selected, QItemSelectionModel::Select | QItemSelectionModel::Rows);
//    ui->tableView_2->selectionModel()->select(deselected, QItemSelectionModel::Deselect | QItemSelectionModel::Rows);
//    ui->image_window->update();
//}

void MainWindow::on_toolButton_information_xlsx_clicked()
{
//    QXlsx::Document xlsx("数据采集表.xlsx");/*打开一个book1的文件*/
//    //第一排
////    QXlsx::Format format1;/*设置该单元的样式*/
////    format1.setFontColor(QColor(Qt::black));/*文字为黑色*/
////    //    format1.setPatternBackgroundColor(QColor(152,251,152));/*背景颜色*/
////    format1.setFontSize(16);/*设置字体大小*/
////    format1.setHorizontalAlignment(QXlsx::Format::AlignHCenter);/*横向居中*/
////    //    format1.setBorderStyle(QXlsx::Format::BorderDashDotDot);/*边框样式*/
////    xlsx.write("A1:I1", "设备信息采集表!", format1);/*写入文字，应该刚才设置的样式*/
////    //    QXlsx::Format format2;/
////    //    format2.setFontBold(true);/*设置加粗*/
////    //    format2.setFontColor(QColor(Qt::red));/*文字为黑色*/
////    ////    format1.setPatternBackgroundColor(QColor(152,251,152));/*背景颜色*/
////    //    format2.setFontSize(11);/*设置字体大小*/
////    //    format2.setHorizontalAlignment(QXlsx::Format::AlignHCenter);/*横向居中*/
////    ////    format2.setBorderStyle(QXlsx::Format::BorderDashDotDot);/*边框样式*/
////    //    xlsx.write("L1", "PLC实际使用地址", format2);/*写入文字，应该刚才设置的样式*/

//        //第二排
////    QXlsx::Format format3;/*重新设置另一个单元的样式*/
////    format3.setFontBold(true);/*设置加粗*/
////    //    format2.setFontUnderline(QXlsx::Format::FontUnderlineDouble);/*下双划线*/
////    //    format2.setFillPattern(QXlsx::Format::PatternLightUp);/*填充方式*/
////    format3.setFontSize(14);/*设置字体大小*/
////    format3.setHorizontalAlignment(QXlsx::Format::AlignHCenter);/*横向居中*/
////    xlsx.write("A2", "序號", format3);/*写入文字，应该刚才设置的样式*/
////    xlsx.write("B2:C2", "項目", format3);
////    xlsx.write("D2", "單位", format3);/*写入文字，应该刚才设置的样式*/
////    xlsx.write("E2", "PLC地址分配", format3);
////    xlsx.write("F2", "PLC數據類型", format3);/*写入文字，应该刚才设置的样式*/
////    xlsx.write("G2", "統計週期", format3);
////    xlsx.write("H2", "更新頻率", format3);/*写入文字，应该刚才设置的样式*/
////    xlsx.write("I2", "可讀寫性", format3);

//        //第三排
////    QXlsx::Format format4;/*设置该单元的样式*/
////    format4.setFontColor(QColor(Qt::red));/*文字为红色*/
////    format4.setFontSize(12);
////    format4.setHorizontalAlignment(QXlsx::Format::AlignHCenter);/*横向居中*/
//    QXlsx::Format format5;
//    format5.setFontColor(QColor(Qt::black));/*文字为黑色*/
//    format5.setFontSize(12);
//    format5.setHorizontalAlignment(QXlsx::Format::AlignHCenter);/*横向居中*/
////    xlsx.write("A3", "1", format4);
////    xlsx.write("B3:C3", "設備ID", format4);
////    xlsx.write("D3", "/", format5);/*写入文字，应该刚才设置的样式*/
////    xlsx.write("E3", "D5000-D5003", format5);
////    xlsx.write("F3", "/", format5);/*写入文字，应该刚才设置的样式*/
////    xlsx.write("G3", "/", format5);
////    xlsx.write("H3", "每班一次", format5);/*写入文字，应该刚才设置的样式*/
////    xlsx.write("I3", "讀寫", format5);
////    xlsx.write("J3", "设置，开机清零时间", format5);

//        //第四排
////    xlsx.write("A4", "2", format4);
////    xlsx.write("B4:C4", "設備白班開班時間", format4);
//    int day_hour_value;
//    int day_minute_value;
//	plc_utl_->GetDevice("D5004", day_hour_value);
//	plc_utl_->GetDevice("D5005", day_minute_value);
//	xlsx.write("D4", (day_hour_value + string("H ") + day_minute_value + string("MIN ")).c_str(), format5);/*写入文字，应该刚才设置的样式*/
//    xlsx.write("E4", "D5004-D5005", format5);
////    xlsx.write("F4", "/", format5);/*写入文字，应该刚才设置的样式*/
////    xlsx.write("G4", "/", format5);
////    xlsx.write("H4", "每班一次", format5);/*写入文字，应该刚才设置的样式*/
////    xlsx.write("I4", "讀寫", format5);
////    xlsx.write("J4", "设置，开机清零时间", format5);

//        //第五排
////    xlsx.write("A5", "3", format4);
////    xlsx.write("B5:C5", "設備晚班開班時間", format4);
//    int night_hour_value;
//    int night_minute_value;
//	plc_utl_->GetDevice("D5006", night_hour_value);
//	plc_utl_->GetDevice("D5007", night_minute_value);
//	xlsx.write("D5", (night_hour_value + string("H") + night_minute_value + string("MIN")).c_str(), format5);/*写入文字，应该刚才设置的样式*/
////    xlsx.write("E5", "D5000-D5003", format5);
////    xlsx.write("F5", "/", format5);/*写入文字，应该刚才设置的样式*/
////    xlsx.write("G5", "/", format5);
////    xlsx.write("H5", "每班一次", format5);/*写入文字，应该刚才设置的样式*/
////    xlsx.write("I5", "讀寫", format5);
////    xlsx.write("J5", "设置，开机清零时间", format5);

//    //第六排
////    xlsx.write("A6", "3", format4);
////    xlsx.write("B6:C6", "設備狀態(1待機、2工作、3報警等)", format4);
//    int status;
//	plc_utl_->GetDevice("D5010", status);
//    switch (status)
//    {
//    case 1 :
//        xlsx.write("D6","待機", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 2 :
//        xlsx.write("D6","工作", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 3 :
//        xlsx.write("D6","報警", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    }
////    xlsx.write("E6", "D5010", format5);
////    xlsx.write("F6", "16位", format5);/*写入文字，应该刚才设置的样式*/
////    xlsx.write("G6", "實時", format5);
////    xlsx.write("H6", "實時", format5);/*写入文字，应该刚才设置的样式*/
////    xlsx.write("I6", "只讀", format5);

//    //第七排
//    int currunt_code;
//	plc_utl_->GetDevice("D5011", currunt_code);
//    switch (status)
//    {
//    case 110 :
//        xlsx.write("D7","视觉定位反馈超时(M20，M21)", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 111 :
//        xlsx.write("D7","视觉扫TID反馈超时(M60)", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 112 :
//        xlsx.write("D7","视觉没set M63", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 122 :
//        xlsx.write("D7","安全门被打开", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 225 :
//        xlsx.write("D7","急停被按下", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 271 :
//        xlsx.write("D7","掉真空报警", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 275 :
//        xlsx.write("D7","FID刷卡失败，设备已暂停，请处理！", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 31 :
//        xlsx.write("D7","机器人报警", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 43 :
//        xlsx.write("D7","皮带异常", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 51 :
//        xlsx.write("D7","支架转盘拍照NG", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 53 :
//        xlsx.write("D7","支架挡杆拍照NG", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 601 :
//        xlsx.write("D7","支架异常总数", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 380 :
//        xlsx.write("D7","支架上有产品，请清理", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 381 :
//        xlsx.write("D7","支架转盘偏位", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 382 :
//        xlsx.write("D7","支架背靠未到位", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 653 :
//        xlsx.write("D7","流水板气缸上限傳感器異常或流水板卡阻", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 654 :
//        xlsx.write("D7","機器人放料完成信號異常", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 658 :
//        xlsx.write("D7","升降機進料口傳感器X15異常", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 659 :
//        xlsx.write("D7","升降线极限位傳感器X16異常", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 660 :
//        xlsx.write("D7","机器人原点信号异常或流水板卡阻", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 661 :
//        xlsx.write("D7","機器人放料完成信號異常", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 662 :
//        xlsx.write("D7","检测气缸1收回到位信号異常", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 663 :
//        xlsx.write("D7","检测气缸2收回到位信号X11異常", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 664 :
//        xlsx.write("D7","检测气缸1伸出位傳感器X6", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 665 :
//        xlsx.write("D7","气缸2伸出傳感器X10異常", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 670 :
//        xlsx.write("D7","M670升降机正装气缸伸出异常", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 671 :
//        xlsx.write("D7","M671升降机正装气缸缩回异常", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 672 :
//        xlsx.write("D7","M672升降机倒装气缸伸出异常", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 673 :
//        xlsx.write("D7","M673升降机倒装气缸缩回异常", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 674 :
//        xlsx.write("D7","M674卡泡棉气缸伸出异常", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 675 :
//        xlsx.write("D7","M675卡泡棉气缸缩回异常", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 676 :
//        xlsx.write("D7","M676初始化条件不足", format5);/*写入文字，应该刚才设置的样式*/
//        break;
//    case 677 :
//        xlsx.write("D7","M677感应器X16异常", format5);/*写入文字，应该刚才设置的样式*/
//        break;

//    //第七排
//    int Cycle_Time;
//	plc_utl_->GetDevice("D5021", Cycle_Time);
//	xlsx.write("D8", (Cycle_Time + string("S")).c_str(), format5);/*写入文字，应该刚才设置的样式*/

//    //第八排
//    int production_quantity;
//	plc_utl_->GetDevice("D5022", production_quantity);
//	xlsx.write("D9", (production_quantity + string("個")).c_str(), format5);/*写入文字，应该刚才设置的样式*/

//    //第九排
//    int ng_number;
//	plc_utl_->GetDevice("D5024", ng_number);
//	xlsx.write("D10", (ng_number + string("個")).c_str(), format5);

//    //第十排
//	int yield_rate;
//	plc_utl_->GetDevice("D5026", yield_rate);
//	xlsx.write("D11", (yield_rate + string("%")).c_str(), format5);

//    //第十一排
//    int running_time;
//	plc_utl_->GetDevice("D5030", running_time);
//	xlsx.write("D12", (running_time + string("分钟")).c_str(), format5);

//    //第十二排
//    int change_product;
//	plc_utl_->GetDevice("D5031", change_product);
//	xlsx.write("D13", (change_product + string("次")).c_str(), format5);

//    //第十三排
//    int change_product_used_time;
//	plc_utl_->GetDevice("D5032", change_product_used_time);
//	xlsx.write("D14", (change_product_used_time + string("S")).c_str(), format5);

//    //第十四排
//	int sleep;
//	plc_utl_->GetDevice("D5034", sleep);
//	xlsx.write("D15", (sleep + string("S")).c_str(), format5);

//    //第十五排
//    int bug;
//	plc_utl_->GetDevice("D5036", bug);
//	xlsx.write("D16", (bug + string("S")).c_str(), format5);

//    //第十六排
//    int wait;
//	plc_utl_->GetDevice("D5038", wait);
//	xlsx.write("D17", (wait + string("S")).c_str(), format5);

//    //第十七排
//    int block;
//	plc_utl_->GetDevice("D5040", block);
//	xlsx.write("D18", (block + string("S")).c_str(), format5);

//    //第十八排
//    int in_running_rate;
//	plc_utl_->GetDevice("D5046", in_running_rate);
//	xlsx.write("D19", (in_running_rate + string("%")).c_str(), format5);

//    //第十九排
//    int all_ng_numbers;
//    int pozition;
//    int tid;
//    int sn;
//    int tid_cmc;
//    int sn_cmc;
//    int fid_cmc;
//    int advance_product;
//	plc_utl_->GetDevice("D5100", pozition);
//	plc_utl_->GetDevice("D5102", tid);
//	plc_utl_->GetDevice("D5106", sn);
//	plc_utl_->GetDevice("D5108", tid_cmc);
//	plc_utl_->GetDevice("D5110", sn_cmc);
//	plc_utl_->GetDevice("D5112", fid_cmc);
//	plc_utl_->GetDevice("D5104", advance_product);
//	xlsx.write("D24", (pozition + string("個")).c_str(), format5);
//	xlsx.write("D25", (tid + string("個")).c_str(), format5);
//       xlsx.write("D26",(sn+string("個")).c_str(), format5);
//        xlsx.write("D28",(tid_cmc+string("個")).c_str(), format5);
//         xlsx.write("D29",(sn_cmc+string("個")).c_str(), format5);
//         xlsx.write("D20",(fid_cmc+string("個")).c_str(), format5);
//         xlsx.write("D27",(advance_product+string("個")).c_str(), format5);

//    all_ng_numbers = pozition + tid + sn + tid_cmc + sn_cmc + fid_cmc + advance_product;
//    xlsx.write("D31",(all_ng_numbers+string("個")).c_str(), format5);

//    //第二十排
//    int shengjiaangji_maintain;
//	plc_utl_->GetDevice("D5160", shengjiaangji_maintain);
//    xlsx.write("D32",(shengjiaangji_maintain+string("天")).c_str(), format5);
//	int jixieshou_maintain;
//	plc_utl_->GetDevice("D5161", jixieshou_maintain);
//	xlsx.write("D33", (jixieshou_maintain + string("天")).c_str(), format5);
//	int haimian_maintain;
//	plc_utl_->GetDevice("D5162", haimian_maintain);
//	xlsx.write("D34", (haimian_maintain + string("天")).c_str(), format5);
//	int yunxingyixiang_maintain;
//	plc_utl_->GetDevice("D5163", yunxingyixiang_maintain);
//	xlsx.write("D35", (yunxingyixiang_maintain + string("天")).c_str(), format5);
//	int pidai_maintain;
//	plc_utl_->GetDevice("D5164", pidai_maintain);
//	xlsx.write("D36", (pidai_maintain + string("天")).c_str(), format5);
//	int diangui_maintain;
//	plc_utl_->GetDevice("D5165", diangui_maintain);
//	xlsx.write("D37", (diangui_maintain + string("天")).c_str(), format5);
//	int qiguan_maintain;
//	plc_utl_->GetDevice("D5166", qiguan_maintain);
//	xlsx.write("D38", (qiguan_maintain + string("天")).c_str(), format5);
//	int fengshan_maintain;
//	plc_utl_->GetDevice("D5167", fengshan_maintain);
//	xlsx.write("D39", (fengshan_maintain + string("天")).c_str(), format5);
//	int maintain9;
//	plc_utl_->GetDevice("D5168", maintain9);
//	xlsx.write("D40", (maintain9 + string("天")).c_str(), format5);
//	int maintain10;
//	plc_utl_->GetDevice("D5169", maintain10);
//	xlsx.write("D41", (maintain10 + string("天")).c_str(), format5);

//    //第二十一项
//	int pozition_no_rec_num;
//	int pozition_no_rec_time;
//	plc_utl_->GetDevice("D5400", pozition_no_rec_num);
//	plc_utl_->GetDevice("D5600", pozition_no_rec_time);
////    xlsx.write("D25",pozition_no_rec_num+"次", format5);
////    xlsx.write("D26",pozition_no_rec_time+"S", format5);

//	int tid_no_rec_num;
//	int tid_no_rec_time;
//	plc_utl_->GetDevice("D5402", tid_no_rec_num);
//	plc_utl_->GetDevice("D5602", tid_no_rec_time);
////    xlsx.write("D25",tid_no_rec_num+"次", format5);
////    xlsx.write("D26",tid_no_rec_time+"S", format5);

//	int m63_not_set_num;
//	int m63_not_set_time;
//	plc_utl_->GetDevice("D5404", m63_not_set_num);
//	plc_utl_->GetDevice("D5604", m63_not_set_time);
////    xlsx.write("D25",m63_not_set_num+"次", format5);
////    xlsx.write("D26",m63_not_set_time+"S", format5);

//	int door_open_num;
//	int door_open_time;
//	plc_utl_->GetDevice("D5406", door_open_num);
//	plc_utl_->GetDevice("D5606", door_open_time);
////    xlsx.write("D25",door_open_num+"次", format5);
////    xlsx.write("D26",door_open_time+"S", format5);

//	int crash_stop_num;
//	int crash_stop_time;
//	plc_utl_->GetDevice("D5408", crash_stop_num);
//	plc_utl_->GetDevice("D5608", crash_stop_time);
////    xlsx.write("D25",crash_stop_num+"次", format5);
////    xlsx.write("D26",crash_stop_time+"S", format5);

//	int vacuum_num;
//	int vacuum_time;
//	plc_utl_->GetDevice("D5410", vacuum_num);
//	plc_utl_->GetDevice("D5610", vacuum_time);
////    xlsx.write("D25",vacuum_num+"次", format5);
////    xlsx.write("D26",vacuum_time+"S", format5);

//	int fid_failed_num;
//	int fid_failed_time;
//	plc_utl_->GetDevice("D5412", fid_failed_num);
//	plc_utl_->GetDevice("D5612", fid_failed_time);
////    xlsx.write("D25",fid_failed_num+"次", format5);
////    xlsx.write("D26",fid_failed_time+"S", format5);

//	int robot_warning_num;
//	int robot_warning_time;
//	plc_utl_->GetDevice("D5414", robot_warning_num);
//	plc_utl_->GetDevice("D5614", robot_warning_time);
////    xlsx.write("D25",robot_warning_num+"次", format5);
////    xlsx.write("D26",robot_warning_time+"S", format5);

//	int conveyer_belt_num;
//	int conveyer_belt_time;
//	plc_utl_->GetDevice("D5416", conveyer_belt_num);
//	plc_utl_->GetDevice("D5616", conveyer_belt_time);
////    xlsx.write("D25",conveyer_belt_num+"次", format5);
////    xlsx.write("D26",conveyer_belt_time+"S", format5);

//	int frame_disk_num;
//	int frame_disk_time;
//	plc_utl_->GetDevice("D5418", frame_disk_num);
//	plc_utl_->GetDevice("D5618", frame_disk_time);
////    xlsx.write("D25",frame_disk_num+"次", format5);
////    xlsx.write("D26",frame_disk_time+"S", format5);

//	int frame_hand_num;
//	int frame_hand_time;
//	plc_utl_->GetDevice("D5420", frame_hand_num);
//	plc_utl_->GetDevice("D5620", frame_hand_time);
////    xlsx.write("D25",frame_hand_num+"次", format5);
////    xlsx.write("D26",frame_hand_time+"S", format5);

//	int frame_ng_num;
//	int frame_ng_time;
//	plc_utl_->GetDevice("D5422", frame_ng_num);
//	plc_utl_->GetDevice("D5622", frame_ng_time);
////    xlsx.write("D25",frame_ng_num+"次", format5);
////    xlsx.write("D26",frame_ng_time+"S", format5);

//	int frame_product_ng_num;
//	int frame_product_ng_time;
//	plc_utl_->GetDevice("D5424", frame_product_ng_num);
//	plc_utl_->GetDevice("D5624", frame_product_ng_time);
////    xlsx.write("D25",frame_product_ng_num+"次", format5);
////    xlsx.write("D26",frame_product_ng_time+"S", format5);

//	int D5426;
//	int D5626;
//	plc_utl_->GetDevice("D5426", D5426);
//	plc_utl_->GetDevice("D5626", D5626);


//	int D5428;
//	int D5628;
//	plc_utl_->GetDevice("D5400", D5428);
//	plc_utl_->GetDevice("D5600", D5628);
////    xlsx.write("D25",pozition_no_rec_num+"次", format5);
////    xlsx.write("D26",pozition_no_rec_time+"S", format5);

//	int D5430;
//	int D5630;
//	plc_utl_->GetDevice("D5430", D5430);
//	plc_utl_->GetDevice("D5630", D5630);


//	int D5432;
//	int D5632;
//	plc_utl_->GetDevice("D5432", D5432);
//	plc_utl_->GetDevice("D5632", D5632);

//	int D5434;
//	int D5634;
//	plc_utl_->GetDevice("D5434", D5434);
//	plc_utl_->GetDevice("D5634", D5634);

//	int D5436;
//	int D5636;
//	plc_utl_->GetDevice("D5436", D5436);
//	plc_utl_->GetDevice("D5636", D5636);

//	int D5438;
//	int D5638;
//	plc_utl_->GetDevice("D5438", D5438);
//	plc_utl_->GetDevice("D5638", D5638);

//	int D5440;
//	int D5640;
//	plc_utl_->GetDevice("D5440", D5440);
//	plc_utl_->GetDevice("D5640", D5640);

//	int D5442;
//	int D5642;
//	plc_utl_->GetDevice("D5442", D5442);
//	plc_utl_->GetDevice("D5642", D5642);

//	int D5444;
//	int D5644;
//	plc_utl_->GetDevice("D5444", D5444);
//	plc_utl_->GetDevice("D5644", D5644);

//	int D5446;
//	int D5646;
//	plc_utl_->GetDevice("D5446", D5446);
//	plc_utl_->GetDevice("D5646", D5646);

//	int D5448;
//	int D5648;
//	plc_utl_->GetDevice("D5448", D5448);
//	plc_utl_->GetDevice("D5648", D5648);

//	int D5450;
//	int D5650;
//	plc_utl_->GetDevice("D5450", D5450);
//	plc_utl_->GetDevice("D5650", D5650);

//	int D5452;
//	int D5652;
//	plc_utl_->GetDevice("D5452", D5452);
//	plc_utl_->GetDevice("D5652", D5652);

//	int D5454;
//	int D5654;
//	plc_utl_->GetDevice("D5454", D5454);
//	plc_utl_->GetDevice("D5654", D5654);

//	int D5456;
//	int D5656;
//	plc_utl_->GetDevice("D5456", D5456);
//	plc_utl_->GetDevice("D5656", D5656);

//	int D5458;
//	int D5658;
//	plc_utl_->GetDevice("D5458", D5458);
//	plc_utl_->GetDevice("D5658", D5658);

//	int D5460;
//	int D5660;
//	plc_utl_->GetDevice("D5460", D5460);
//	plc_utl_->GetDevice("D5660", D5660);

//	int D5462;
//	int D5662;
//	plc_utl_->GetDevice("D5462", D5462);
//	plc_utl_->GetDevice("D5662", D5662);

//    int D5464;
//    int D5664;
//	plc_utl_->GetDevice("D5464", D5464);
//	plc_utl_->GetDevice("D5664", D5664);

//    xlsx.write("D25",pozition_no_rec_num+tid_no_rec_num+m63_not_set_num+"次", format5);
//    xlsx.write("D26",pozition_no_rec_time+tid_no_rec_time+m63_not_set_time+"S", format5);
//    }

//    QXlsx::Document xlsx2("equipment_information_collection.xlsx");/*复制book1到book2*/
//    xlsx2.saveAs("equipment_information_collection.xlsx");
}

void MainWindow::reload_advanced_device_ng_table()
{
    advanced_device_ng_item_model_.clear();

    ItemInformationCenter* ng_item_info = ItemInformationCenter::instance();
    if (ng_item_info)
    {
        vector<string> items_id;
        ng_item_info->get_all_item_id(items_id);
        for (size_t i = 0; i < items_id.size(); ++i)
        {
            string id_str = items_id[i];
            bool is_ng;
            string ng_reason;
            string station;
            string time;
            bool find = ng_item_info->get_item(id_str, &is_ng, ng_reason, station, time);
            if (find)
            {
                QStandardItem* item_id = new QStandardItem(id_str.c_str());
                string ng_str = is_ng ? "ng" : "ok";
                QStandardItem* item_ng = new QStandardItem(ng_str.c_str());
                QStandardItem* item_station = new QStandardItem(station.c_str());
                QStandardItem* item_ng_reason = new QStandardItem(ng_reason.c_str());
                QStandardItem* item_time = new QStandardItem(time.c_str());
                QList<QStandardItem*> row;
                row.append(item_id);
                row.append(item_ng);
                row.append(item_station);
                row.append(item_ng_reason);
                row.append(item_time);
                advanced_device_ng_item_model_.appendRow(row);
            }
        }
    }
}

void MainWindow::on_pushButton_refresh_advance_ng_list_clicked()
{
    reload_advanced_device_ng_table();
}

void MainWindow::on_toolButton_romove_advance_product_ng_clicked()
{
    QList<int> removeRows;
    vector<string> remove_id;

    foreach(QModelIndex index, ui->tableView_advance_product_ng->selectionModel()->selectedIndexes()) {
        if(!removeRows.contains(index.row())) {
            removeRows.append(index.row());
        }
    }

    qSort(removeRows);
    int countRow = removeRows.count();
    for (int i = 0; i < countRow; ++i)
    {
        QStandardItem* item = advanced_device_ng_item_model_.item(removeRows.at(i));
        string id_str = item->text().toStdString();
        remove_id.push_back(id_str);
    }

    ItemInformationCenter* ng_item_info = ItemInformationCenter::instance();
    for( int i = countRow; i > 0; i--)
    {
        advanced_device_ng_item_model_.removeRow( removeRows.at(i-1), QModelIndex());
        ng_item_info->remove_item(remove_id[i-1]);
    }
}
