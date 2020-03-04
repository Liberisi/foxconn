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

	QLineEdit* plc_lineedit = new QLineEdit;
	plc_lineedit->setMaximumSize(42, 24);
    plc_lineedit->setStyleSheet(status_bar_item_style_sheet);
	plc_lineedit->setText(QStringLiteral("PLC"));
	plc_lineedit->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	statusBar()->addWidget(plc_lineedit);
	plc_lineedit->setReadOnly(true);
	plc_status_lineedit = new QLineEdit;
	plc_status_lineedit->setMaximumSize(10, 24);
	plc_status_lineedit->setStyleSheet(QStringLiteral(" QLineEdit{ color: white }"));
	statusBar()->addWidget(plc_status_lineedit);
	plc_status_lineedit->setReadOnly(true);

	QLineEdit* robotic_status_label = new QLineEdit;
	robotic_status_label->setMaximumSize(58, 24);
    robotic_status_label->setStyleSheet(status_bar_item_style_sheet);
	robotic_status_label->setText(QStringLiteral("机械臂"));
	robotic_status_label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	statusBar()->addWidget(robotic_status_label);
	robotic_status_label->setReadOnly(true);

	robotic_status_lineEdit = new QLineEdit;
	robotic_status_lineEdit->setMaximumSize(10, 24);
	robotic_status_lineEdit->setStyleSheet(" QLineEdit{ color: white }");
	statusBar()->addWidget(robotic_status_lineEdit);
	robotic_status_lineEdit->setReadOnly(true);

    //相机状态区
    QLineEdit *lineEdit6 = new QLineEdit;
    lineEdit6->setMaximumSize(76,24);
    lineEdit6->setStyleSheet(status_bar_item_style_sheet);
    lineEdit6->setText(QStringLiteral("读码相机"));
	lineEdit6->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    statusBar()->addWidget(lineEdit6);
    lineEdit6->setReadOnly(true);
    qr_camera_status_lineedit = new QLineEdit;
    qr_camera_status_lineedit->setMaximumSize(10,24);
    statusBar()->addWidget(qr_camera_status_lineedit);
    qr_camera_status_lineedit->setReadOnly(true);

    QLineEdit *lineEdit7 = new QLineEdit;
    lineEdit7->setMaximumSize(76,24);
    lineEdit7->setStyleSheet(status_bar_item_style_sheet);
    lineEdit7->setText(QStringLiteral("定位相机"));
	lineEdit7->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    statusBar()->addWidget(lineEdit7);
    lineEdit7->setReadOnly(true);
    pos_camera_status_lineedit = new QLineEdit;
    pos_camera_status_lineedit->setMaximumSize(10,24);
    statusBar()->addWidget(pos_camera_status_lineedit);
    pos_camera_status_lineedit->setReadOnly(true);
    QLineEdit *lineEdit8 = new QLineEdit;
    lineEdit8->setMaximumSize(76,24);
    lineEdit8->setStyleSheet(status_bar_item_style_sheet);
    lineEdit8->setText(QStringLiteral("支架相机"));
	lineEdit8->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    statusBar()->addWidget(lineEdit8);
    lineEdit8->setReadOnly(true);
    frame_camera_status_lineedit = new QLineEdit;
    frame_camera_status_lineedit->setMaximumSize(10,24);
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

    QLineEdit *lineEdit10 = new QLineEdit;
    lineEdit10->setMaximumSize(76,24);
    lineEdit10->setStyleSheet(status_bar_item_style_sheet);
    lineEdit10->setText(QStringLiteral("运行状态"));
	lineEdit10->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    statusBar()->addWidget(lineEdit10);
    lineEdit10->setReadOnly(true);

    running_status_lineEdit = new QLineEdit;
    running_status_lineEdit->setMaximumSize(10, 24);
    running_status_lineEdit->setStyleSheet(" QLineEdit{ color: white }");
    statusBar()->addWidget(running_status_lineEdit);
    running_status_lineEdit->setReadOnly(true);

    QLineEdit *lineEdit11 = new QLineEdit;
    lineEdit11->setMaximumSize(76,24);
    lineEdit11->setStyleSheet(status_bar_item_style_sheet);
    lineEdit11->setText(QStringLiteral("上游设备"));
    lineEdit11->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    statusBar()->addWidget(lineEdit11);
    lineEdit11->setReadOnly(true);

    advanced_device_count_label = new QLabel;
    advanced_device_count_label->setMaximumSize(22, 24);
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

    ui->spinBox_x_offset->setValue(baojitai->robotic_x_offset());
    ui->spinBox_y_offset->setValue(baojitai->robotic_y_offset());
    ui->spinBox_rz_offset->setValue(baojitai->robotic_rz_offset());

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

void MainWindow::on_spinBox_x_offset_valueChanged(int arg1)
{
    Baojitai::instance()->set_robotic_x_offset(arg1);
}

void MainWindow::on_spinBox_y_offset_valueChanged(int arg1)
{
    Baojitai::instance()->set_robotic_y_offset(arg1);
}

void MainWindow::on_spinBox_rz_offset_valueChanged(int arg1)
{
    Baojitai::instance()->set_robotic_rz_offset(arg1);
}

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
