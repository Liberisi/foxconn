#include "reading_code_config.h"
#include "ui_reading_code_config.h"
#include <QMessageBox>
#include <QFileDialog>
#include <ssvision/ssvision>
#include "baojitai.h"
#include "halcon_tools.h"
#include <QTextCodec>
#include <QString>

ReadingCodeConfigDialog::ReadingCodeConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReadingCodeConfigDialog)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());

    reading_code_duration_ = 0;

    ui->label_result->setText("");
    ui->widget_image->set_halcon_widget_delegate(this);

    QComboBox* serial_box_combobox[3];
    serial_box_combobox[0] = ui->comboBox_serial_port_1;
    serial_box_combobox[1] = ui->comboBox_serial_port_2;
    serial_box_combobox[2] = ui->comboBox_serial_port_3;

    QComboBox* baud_rate_combobox[3];
    baud_rate_combobox[0] = ui->comboBox_baud_rate_1;
    baud_rate_combobox[1] = ui->comboBox_baud_rate_2;
    baud_rate_combobox[2] = ui->comboBox_baud_rate_3;

    QComboBox* character_bits_combobox[3];
    character_bits_combobox[0] = ui->comboBox_character_bits_1;
    character_bits_combobox[1] = ui->comboBox_character_bits_2;
    character_bits_combobox[2] = ui->comboBox_character_bits_3;

    Baojitai* baojitai = Baojitai::instance();
    vector<string> serial_port_name_list = ssvision::QtSerialPort::serial_port_list();
    vector<int> baud_rate_list = ssvision::QtSerialPort::baud_rate_list();
    vector<int> character_bits_list = ssvision::QtSerialPort::character_bits_list();
    for (int i = 0; i < 3; ++i)
    {
        QComboBox* combobox_serial_port = serial_box_combobox[i];
        QComboBox* combobox_baud_rate = baud_rate_combobox[i];
        QComboBox* combobox_character_bits = character_bits_combobox[i];
        foreach(string port_name, serial_port_name_list)
            combobox_serial_port->addItem(port_name.c_str());
        foreach (int baud_rate, baud_rate_list)
            combobox_baud_rate->addItem(std::to_string(baud_rate).c_str());
        foreach (int bits, character_bits_list) {
            combobox_character_bits->addItem(std::to_string(bits).c_str());
        }

        SerialPort* sp = NULL;
        switch(i)
        {
        case 0:
            sp = baojitai->serial_port_sending_code();
            break;
        case 1:
            sp = baojitai->serial_port_repair_mode();
            break;
        case 2:
            sp = baojitai->serial_port_read_fid();
            break;
        }

        string port_name_ui = "COM1";
        int baud_rate_ui = 9600;
        int bits_ui = 8;
        if (sp)
        {
            port_name_ui = sp->port_name();
            baud_rate_ui = sp->baud_rate();
            bits_ui = sp->character_bits();
        }

        vector<string>::iterator port_name_iter = std::find(serial_port_name_list.begin(), serial_port_name_list.end(), port_name_ui);
        if (port_name_iter != serial_port_name_list.end())
            combobox_serial_port->setCurrentIndex(port_name_iter - serial_port_name_list.begin());

        vector<int>::iterator baud_rate_iter = std::find(baud_rate_list.begin(), baud_rate_list.end(), baud_rate_ui);
        if (baud_rate_iter != baud_rate_list.end())
        {
            int idx = baud_rate_iter - baud_rate_list.begin();
            combobox_baud_rate->setCurrentIndex(idx);
        }
        vector<int>::iterator bits_iter = std::find(character_bits_list.begin(), character_bits_list.end(), bits_ui);
        if (bits_iter != character_bits_list.end())
            combobox_character_bits->setCurrentIndex(bits_iter - character_bits_list.begin());
    }

    Product* product = baojitai->current_product();
    if (product)
    {
        Product::DataCodeParam param = product->data_code_param();
        if (param.product_bar_code_type)
        {
            ui->radioButton_product_bar_code->toggle();
            vector<string> bar_code_names = halcontools::all_bar_code_names();
            foreach(string bar_code_name, bar_code_names)
                ui->comboBox_product_code_type->addItem(bar_code_name.c_str());
        }
        else if (param.product_mat_code_type)
        {
            ui->radioButton_product_mat_code->toggle();
            vector<string> code_2d_names = halcontools::all_2d_code_names();
            foreach (string code_2d_name, code_2d_names)
                ui->comboBox_product_code_type->addItem(code_2d_name.c_str());
        }
        ui->lineEdit_board_code_prefix->setText(param.board_code_prefix().c_str());

        Product::VisionParam param1 = product->vision_param();
        ui->spinBox_read_code_exposure_time->setValue(param1.read_code_exposure_time);
    }



    vector<string> bar_code_names = halcontools::all_bar_code_names();
    foreach(string bar_code_name, bar_code_names)
        ui->comboBox_bar_code_type->addItem(bar_code_name.c_str());

    int sn_msleep_time = baojitai->msleep_time_.sn_msleep_time();
    int tid_msleep_time = baojitai->msleep_time_.tid_msleep_time();
    int fid_singleslot_time = baojitai->msleep_time_.fid_singleslot_time();
    ui->spinBox_sn_send_cmc_msleep_time->setValue(sn_msleep_time);
    ui->spinBox_TID_send_cmc_msleep_time->setValue(tid_msleep_time);
    ui->spinBox_wait_last_fid_max_time->setValue(fid_singleslot_time);

    connect(baojitai, SIGNAL(signal_product_change(Product*)), this, SLOT(on_product_change_signal(Product*)), Qt::QueuedConnection);
    connect(baojitai, SIGNAL(signal_camera_buffer_updated(Camera*)), this, SLOT(on_camera_buffer_changed(Camera*)), Qt::QueuedConnection);
    connect(baojitai, SIGNAL(signal_serial_port_read(SerialPort*,QString)), this, SLOT(on_serial_port_read_signal(SerialPort*,QString)));
    on_product_change_signal(baojitai->current_product());
}

ReadingCodeConfigDialog::~ReadingCodeConfigDialog()
{
    delete ui;
}

void ReadingCodeConfigDialog::on_paint(HalconWidget *widget, HWindow &halcon_window)
{
    if (!halcon_window.IsHandleValid())
        return;
	if (halcon_image_.IsInitialized())
	{
		halcon_window.SetPart(0, 0, (Hlong)halcon_image_.Height(), (Hlong)halcon_image_.Width());
		halcon_window.DispImage(halcon_image_);
    }
    if (reading_code_duration_ > 0)
    {
        string time_str = to_string(reading_code_duration_);
        //halcon_window.DispText(time_str.c_str(), "window", "top", "left", "green", HTuple(), HTuple());
    }
    foreach (HRegion region, bar_code_regions_)
	{
        halcontools::draw_region(halcon_window, region, halcontools::kHalconColorGreen, 1, false);
	}
    foreach (HXLD xld, mat_code_xlds_)
	{
        halcontools::draw_xld(halcon_window, xld, halcontools::kHalconColorRed, 1, false);
	}

}

void ReadingCodeConfigDialog::on_connect_btn_clicked()
{
    string port_name_ui;
    int baud_rate_ui;
    int character_bits_ui;

    if (ui->comboBox_serial_selection->currentIndex() == 0)
    {
        port_name_ui = ui->comboBox_serial_port_1->currentText().toStdString();
        baud_rate_ui = ui->comboBox_baud_rate_1->currentText().toInt();
        character_bits_ui = ui->comboBox_character_bits_1->currentText().toInt();
    }
    else if (ui->comboBox_serial_selection->currentIndex() == 1)
    {
        port_name_ui = ui->comboBox_serial_port_2->currentText().toStdString();
        baud_rate_ui = ui->comboBox_baud_rate_2->currentText().toInt();
        character_bits_ui = ui->comboBox_character_bits_2->currentText().toInt();
    }
    else if (ui->comboBox_serial_selection->currentIndex() == 2)
    {
        port_name_ui = ui->comboBox_serial_port_3->currentText().toStdString();
        baud_rate_ui = ui->comboBox_baud_rate_3->currentText().toInt();
        character_bits_ui = ui->comboBox_character_bits_3->currentText().toInt();
    }

    if (port_name_ui.length() == 0)
    {
        QMessageBox::warning(this, QStringLiteral("设备异常"), QStringLiteral("无法创建串口设备"), QMessageBox::StandardButton::Ok);
        return;
    }

    Baojitai* baojitai = Baojitai::instance();
    SerialPort* old_serial_ports[3];
    old_serial_ports[0] = baojitai->serial_port_sending_code();
	old_serial_ports[1] = baojitai->serial_port_read_fid();
    old_serial_ports[2] = baojitai->serial_port_repair_mode();
    for (int i = 0; i < sizeof(old_serial_ports)/sizeof(old_serial_ports[0]); ++i)
    {
        SerialPort* serial_port = old_serial_ports[i];
        if (serial_port && serial_port->port_name().compare(port_name_ui) == 0)
        {
            serial_port->close();
        }
    }

    SerialPort* serial_port = new QtSerialPort(port_name_ui);
    if (serial_port)
    {
        serial_port->set_baud_rate(baud_rate_ui);
        serial_port->set_character_bits(character_bits_ui);
        serial_port->set_parity(ssvision::SerialPort::kParityNoParity);
    }
    else
    {
        QMessageBox::warning(this, QStringLiteral("设备异常"), QStringLiteral("无法创建串口设备"), QMessageBox::StandardButton::Ok);
        return;
    }

    if (ui->comboBox_serial_selection->currentIndex() == 0)
    {
        baojitai->set_serial_port_sending_code(serial_port);
    }
    else if (ui->comboBox_serial_selection->currentIndex() == 1)
    {
        baojitai->set_serial_port_repair_mode(serial_port);
    }
    else if (ui->comboBox_serial_selection->currentIndex() == 2)
    { 
        baojitai->set_serial_port_reading_fid(serial_port);
    }

    if (serial_port->is_open() || serial_port->open())
        QMessageBox::information(this, QStringLiteral("串口提示"), QStringLiteral("串口已经打开"), QMessageBox::StandardButton::Ok);
    else
        QMessageBox::warning(this, QStringLiteral("串口提示"), QStringLiteral("串口打开失败"), QMessageBox::StandardButton::Ok);
}

void ReadingCodeConfigDialog::on_senddata_btn_clicked()
{
    ssvision::SerialPort* serial_port = nullptr;
    if (ui->comboBox_serial_selection->currentIndex() == 0)
    {
        serial_port = Baojitai::instance()->serial_port_sending_code();
    }
    else if (ui->comboBox_serial_selection->currentIndex() == 1)
    {
        serial_port = Baojitai::instance()->serial_port_repair_mode();
    }
    else
    {
		serial_port = Baojitai::instance()->serial_port_read_fid();
    }
    if (serial_port && serial_port->is_open())
    {
        string message = ui->lineEdit_message->text().toStdString();
        serial_port->writeline(message.c_str(), (int)message.length());
    }
    else
    {
        QMessageBox::information(this, QStringLiteral("串口提示"), QStringLiteral("请先打开串口"), QMessageBox::StandardButton::Ok);
    }
}

void ReadingCodeConfigDialog::on_serial_port_read_signal(SerialPort* serial_port, QString message)
{
    Baojitai* baojitai = Baojitai::instance();
    if (serial_port = baojitai->serial_port_sending_code())
       { ui->label_recv_com1->setText(message); }
	else if (serial_port = baojitai->serial_port_repair_mode())
       { ui->label_recv_com2->setText(message); }
	else if (serial_port = baojitai->serial_port_read_fid())
       { ui->label_recv_com3->setText(message); }
}

void ReadingCodeConfigDialog::on_toolButton_3_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("open image file"), "./", tr("Image files(*.jpg *.png *.bmp *.tif);;All files (*.*)"));
     if (!filename.isNull())
//     { //用户选择了文件
//      QTextCodec *code = QTextCodec::codecForName("gb18030");//处理中文字符
//      ReadImage(&Image, code->fromUnicode(filename).data());
//      HTuple  img_width, img_height;
//      GetImageSize(Image, &img_width, &img_height);
//      SetPart(hv_WindowHandle, 0, 0, img_height - 1, img_width - 1);
//      DispObj(Image, hv_WindowHandle);
//     }
//     else
//     {

//     }
//    QString fileName = QFileDialog::getOpenFileName(this,
//        tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.bmp *.tif)"));
//    if (fileName.length() > 0)
    {
        QTextCodec *code = QTextCodec::codecForName("gb18030");//处理中文字符
        halcon_image_.ReadImage(code->fromUnicode(filename).data());
        bar_codes_.clear();
        bar_code_regions_.clear();
        reading_code_duration_ = 0;
        ui->widget_image->update();
        ui->label_result->setText("");
    }
}

void ReadingCodeConfigDialog::on_toolButton_reading_code_clicked()
{
	if (!halcon_image_.IsInitialized())
		return;

    bar_codes_.clear();
    bar_code_regions_.clear();
    int bar_code_duration;
    halcontools::read_bar_code(halcon_image_, "Code 128", bar_codes_, bar_code_regions_, bar_code_duration);

    mat_code_xlds_.clear();
    mat_codes_.clear();
    int mat_code_duration;
    halcontools::read_2d_code_special(halcon_image_, ssvision::k2DCodeDataMatrixECC200, mat_codes_, mat_code_xlds_, mat_code_duration);

    reading_code_duration_ = bar_code_duration + mat_code_duration;

    ui->widget_image->update();

    QString result = "[";
    for (int i = 0; i < bar_codes_.size(); ++i)
    {
        string code = bar_codes_[i];
        if (i > 0)
            result += ", ";
        result += code.c_str();
    }
    result += "] ";

    result += "[";
    for (int i = 0; i < mat_codes_.size(); ++i)
    {
        string code = mat_codes_[i];
        if (i > 0)
            result += ", ";
        result += code.c_str();
    }
    result += "] ";

    result += " cost ";
    result += ::to_string(reading_code_duration_).c_str();
    result += "ms";
    ui->label_result->setText(result);
}

void ReadingCodeConfigDialog::on_product_change_signal(Product *product)
{
    if (!product)
        return;
    string product_model = product->name();
    ui->lineEdit_currentmodel->setText(product_model.c_str());

    Product::DataCodeParam param = product->data_code_param();
	ui->checkBox_barcode->setChecked(param.use_board_code);
	ui->spinBox_bar_code_length->setValue(param.board_code_length);
    ui->checkBox_mat_code->setChecked(param.use_product_code);
    ui->spinBox_mat_code_length->setValue(param.product_code_length);
}

void ReadingCodeConfigDialog::on_toolButton_capture_clicked()
{
    Camera* camera = Baojitai::instance()->camera_reading_code();
    if (camera && camera->is_open())
        camera->trigger();
}

void ReadingCodeConfigDialog::on_camera_buffer_changed(Camera* camera)
{
    if (camera == Baojitai::instance()->camera_reading_code())
    {
        const unsigned char* image_buffer = NULL;
        int width, height;
        Baojitai::instance()->camera_reading_code_buffer(&image_buffer, &width, &height);
        if (image_buffer)
        {
            HImage img("byte", width, height, (void*)image_buffer);
			halcon_image_ = img.CopyImage();
			ui->widget_image->update();
        }
    }
}

void ReadingCodeConfigDialog::on_toolButton_save_serial_config_clicked()
{
    Baojitai* baojitai = Baojitai::instance();

    SerialPort* sp = baojitai->serial_port_sending_code();
    if (sp && sp->is_open())
        baojitai->save_serial_port_sending_code_config();

	sp = baojitai->serial_port_read_fid();
    if (sp && sp->is_open())
        baojitai->save_serial_port_check_frame_config();

    sp = baojitai->serial_port_repair_mode();
    if (sp && sp->is_open())
        baojitai->save_serial_port_repair_mode_config();
}

void ReadingCodeConfigDialog::on_toolButton_save_clicked()
{
    int tid_msleep_time =ui->spinBox_TID_send_cmc_msleep_time->text().toInt();
    int sn_msleep_time = ui->spinBox_sn_send_cmc_msleep_time->text().toInt();
    int fid_singleslot_time = ui->spinBox_wait_last_fid_max_time->text().toInt();

    Baojitai *baojitai = Baojitai::instance();
    baojitai->msleep_time_.set_tid_msleep_time(tid_msleep_time);
    baojitai->msleep_time_.set_sn_msleep_time(sn_msleep_time);
    baojitai->msleep_time_.set_fid_singleslot_time(fid_singleslot_time);
    baojitai->save_msleep_time();

    Product* product = Baojitai::instance()->current_product();
	if (!product)
		return;

    Product::VisionParam param1 = product->vision_param();
    int read_code_exposure_time = ui->spinBox_read_code_exposure_time->text().toInt();
    param1.read_code_exposure_time = read_code_exposure_time;
    product->set_vision_param(param1);


    Product::DataCodeParam param = product->data_code_param();
    param.use_product_code = ui->checkBox_mat_code->isChecked();
    param.product_code_length = ui->spinBox_mat_code_length->text().toInt();
    if (ui->radioButton_product_mat_code->isChecked())
    {
        param.product_bar_code_type = NULL;
        string mat_code_type = ui->comboBox_product_code_type->currentText().toStdString();
        if (mat_code_type.compare(ssvision::k2DCodeDataMatrixECC200) == 0)
            param.product_mat_code_type = ssvision::k2DCodeDataMatrixECC200;
    }
    else if (ui->radioButton_product_bar_code->isChecked())
    {
        param.product_mat_code_type = NULL;
        string bar_code_type = ui->comboBox_product_code_type->currentText().toStdString();
        if (bar_code_type.compare(ssvision::kBarCodeCode128) == 0)
            param.product_bar_code_type = ssvision::kBarCodeCode128;
    }

	param.use_board_code = ui->checkBox_barcode->isChecked();
	param.board_code_length = ui->spinBox_bar_code_length->text().toInt();
    string bar_code_type = ui->comboBox_bar_code_type->currentText().toStdString();
    if (bar_code_type.compare(ssvision::kBarCodeCode128) == 0)
		param.board_bar_code_type = ssvision::kBarCodeCode128;

    string board_code_prefix = ui->lineEdit_board_code_prefix->text().toStdString();
	param.set_board_code_prefix(board_code_prefix);
    product->set_code_param(param);
    product->save_config(ProductManager::instance()->product_config_path(product->name()));
}

void ReadingCodeConfigDialog::on_pushButton_save_image_clicked()
{
    if (!halcon_image_.IsInitialized())
        return;

    QString filename = QFileDialog::getSaveFileName(this,
           tr("Save Image"),
           "",
           tr("*.bmp;;")); //选择路径
    if(filename.isEmpty())
    {
           return;
    }
    else
    {
        halcontools::write_image(halcon_image_, filename.toStdString());
    }
}

void ReadingCodeConfigDialog::on_radioButton_product_mat_code_toggled(bool checked)
{
    ui->comboBox_product_code_type->clear();
    vector<string> code_2d_names = halcontools::all_2d_code_names();
    foreach (string code_2d_name, code_2d_names)
        ui->comboBox_product_code_type->addItem(code_2d_name.c_str());
}

void ReadingCodeConfigDialog::on_radioButton_product_bar_code_toggled(bool checked)
{
    ui->comboBox_product_code_type->clear();
    vector<string> bar_code_names = halcontools::all_bar_code_names();
    foreach(string bar_code_name, bar_code_names)
        ui->comboBox_product_code_type->addItem(bar_code_name.c_str());
}

void ReadingCodeConfigDialog::on_pushButton_save_result_image_clicked()
{
    if (halcon_image_.IsInitialized())
    {
        QString filename = QFileDialog::getSaveFileName(this,
               tr("Save Image"),
               "",
               tr("*.jpg;;")); //选择路径
        if(!filename.isEmpty())
        {
            cv::Mat image = halcontools::HImageToIplImage(halcon_image_);
            string tid, sn;

            bool draw_1 = false;
            HRegion region_1;
            if (bar_code_regions_.size() > 0)
            {
                draw_1 = true;
                region_1 = bar_code_regions_[0];
                tid = bar_codes_[0];
            }
            bool draw_xld = false;
            HXLD xld;
            if (mat_code_xlds_.size() > 0)
            {
                draw_xld = true;
                xld = mat_code_xlds_[0];
                sn = mat_codes_[0];
            }

            halcontools::write_reading_code_image_ng(image,
                                                 draw_1, region_1,
                                                 false, HRegion(),
                                                 draw_xld, xld,
                                                 tid, sn,
                                                 filename.toStdString());
        }
    }
}

