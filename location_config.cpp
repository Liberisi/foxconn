#include "location_config.h"
#include "ui_location_config.h"
#include <ssvision/ssvision>
#include "baojitai.h"
#include <QFileDialog>
#include <QString>
#include <QTextCodec>
#include <QMessageBox>
#include "halcon_tools.h"

LocationConfigDialog::LocationConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Imageparameter)
{
    ui->setupUi(this);
    ui->image_widget->set_halcon_widget_delegate(this);
	found_ = false;

    Product* product = Baojitai::instance()->current_product();
    if (product)
    {
        Product::VisionParam param = product->vision_param();
        ui->lineEdit_drop_z->setText(to_string(param.delta_z_put).c_str());
        ui->lineEdit_grap_z->setText(to_string(param.delta_z).c_str());
        ui->lineEdit_l1->setText(to_string(param.l1).c_str());
        ui->lineEdit_l2->setText(to_string(param.l2).c_str());
        ui->lineEdit_size_var->setText(to_string(param.xl1).c_str());
        //待保存至每个产品

    }

    Baojitai* baojitai = Baojitai::instance();
    ui->spinBox_x_offset->setValue(baojitai->robotic_x_offset());
    ui->spinBox_y_offset->setValue(baojitai->robotic_y_offset());
    ui->spinBox_z_offset->setValue(baojitai->robotic_rz_offset());

    connect(Baojitai::instance(), SIGNAL(signal_camera_buffer_updated(Camera*)), this, SLOT(on_camera_buffer_changed(Camera*)), Qt::QueuedConnection);
    connect(Baojitai::instance(), SIGNAL(signal_robotic_command(RoboticTCPServer*,QString)), this, SLOT(on_robotic_command(RoboticTCPServer*,QString)));
}

LocationConfigDialog::~LocationConfigDialog()
{
    delete ui;
}

void LocationConfigDialog::on_paint(HalconWidget *, HWindow &halcon_window)
{
    if (!halcon_window.IsHandleValid())
        return;
    if (halcon_image_.IsInitialized())
    {
        halcon_window.SetPart(0, 0, (Hlong)halcon_image_.Height(), (Hlong)halcon_image_.Width());
        halcon_window.DispImage(halcon_image_);
        halcon_window.SetLineWidth(10);
        halcon_window.SetRgb(128, 128, 128);
        halcon_window.DispCross(
                    halcon_image_.Height() * 0.5,
                    halcon_image_.Width() * 0.5,
                    halcon_image_.Height() * 0.9,
                    0
                    );
    }
	if (found_)
	{
        halcontools::draw_rect(halcon_window, x_, y_, phi_, l1_, l2_, halcontools::kHalconColorRed, 1, false);
        float x1 = x_ + l1_ * cos(phi_);
        float y1 = y_ - l1_ * sin(phi_);
        float x2 = x_ - l1_ * cos(phi_);
        float y2 = y_ + l1_ * sin(phi_);
        halcontools::draw_line(halcon_window, x1, y1, x2, y2, halcontools::kHalconColorBlue);
        float pi_2 = 3.14159f * 0.5;
        float x3 = x_ + l2_ * cos(pi_2 + phi_);
        float y3 = y_ - l2_ * sin(pi_2 + phi_);
        float x4 = x_ - l2_ * cos(pi_2 + phi_);
        float y4 = y_ + l2_ * sin(pi_2 + phi_);
        halcontools::draw_line(halcon_window, x3, y3, x4, y4, halcontools::kHalconColorBlue);

        HHomMat2D mat = Baojitai::instance()->image_to_robotic_matrix();
        halcontools::transform_point(mat, x3, y3, x3, y3);
        halcontools::transform_point(mat, x4, y4, x4, y4);
        float dx = x1 - x2;
        float dy = y1 - y2;
        float width_mm = sqrt(dx * dx + dy * dy);
        dx = x3 - x4;
        dy = y3 - y4;
        float height_mm = sqrt(dx * dx + dy * dy);
    }
}

void LocationConfigDialog::on_toolButton_choose_image_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("open image file"), "./", tr("Image files(*.jpg *.png *.bmp *.tif);;All files (*.*)"));
     if (!filename.isNull())
    {
        QTextCodec *code = QTextCodec::codecForName("gb18030");//处理中文字符
        halcon_image_.ReadImage(code->fromUnicode(filename).data());
		found_ = false;
        ui->image_widget->update();
    }
}

void LocationConfigDialog::on_toolButton_extract_clicked()
{
	if (!halcon_image_.IsInitialized())
		return;

//    for (int row = 152; row < 500; row++)
//    {
//        for (int col = 765; col < 1662; ++col)
//        {
//            //unsigned char* byte = img_data + row * width + col;
//            //*byte = 255;
//            halcon_image_.SetGrayval(row, col, 255);
//        }
//    }

//    for (int row = 1354; row < 1652; row++)
//    {
//        for (int col = 569; col < 1357; col++)
//        {
//            //unsigned char* byte = img_data + row * width + col;
//            //*byte = 255;
//            halcon_image_.SetGrayval(row, col, 255);
//        }
//    }

    int black_threshold = ui->spinBox_black_region_threshold->text().toInt();
    halcontools::extract_rect(halcon_image_, &x_, &y_, &phi_, &l1_, &l2_, &found_, black_threshold);
    int width = halcon_image_.Width();
    int height = halcon_image_.Height();

//    if (found_ && (l1_ * 2 < width *0.2 || l1_ * 2 > width*0.9 || l2_ * 2 < height * 0.2 || l2_ * 2 > height * 0.9 ))
//    {
//        found_ = false;
//    }

	if (found_)
    {
        //halcontools::draw_rect(halcon_window, x_, y_, phi_, l1_, l2_, halcontools::kHalconColorRed, 1, false);
        float x1 = x_ + l1_ * cos(phi_);
        float y1 = y_ - l1_ * sin(phi_);
        float x2 = x_ - l1_ * cos(phi_);
        float y2 = y_ + l1_ * sin(phi_);
        //halcontools::draw_line(halcon_window, x1, y1, x2, y2, halcontools::kHalconColorBlue);
        float pi_2 = 3.14159f * 0.5;
        float x3 = x_ + l2_ * cos(pi_2 + phi_);
        float y3 = y_ - l2_ * sin(pi_2 + phi_);
        float x4 = x_ - l2_ * cos(pi_2 + phi_);
        float y4 = y_ + l2_ * sin(pi_2 + phi_);
        //halcontools::draw_line(halcon_window, x3, y3, x4, y4, halcontools::kHalconColorBlue);

        HHomMat2D mat = Baojitai::instance()->image_to_robotic_matrix();
        halcontools::transform_point(mat, x1, y1, x1, y1);
        halcontools::transform_point(mat, x2, y2, x2, y2);
        halcontools::transform_point(mat, x3, y3, x3, y3);
        halcontools::transform_point(mat, x4, y4, x4, y4);
        float dx = x1 - x2;
        float dy = y1 - y2;
        float width_mm = sqrt(dx * dx + dy * dy);
        dx = x3 - x4;
        dy = y3 - y4;
        float height_mm = sqrt(dx * dx + dy * dy);

        QString size_str;
        size_str.sprintf("[%0.2f, %0.2f]", width_mm, height_mm);
        ui->label_size->setText(size_str);
        ui->image_widget->update();
    }
}

void LocationConfigDialog::on_pushButton_save_image_clicked()
{
    if (!halcon_image_.IsInitialized())
    {
        //QMessageBox::warning(this, QStringLiteral("图片为空"), QStringLiteral("请先拍照或者选择图片"), QMessageBox::StandardButton::Ok);
        return;
    }

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

void LocationConfigDialog::on_robotic_command(RoboticTCPServer* robotic_tcp_server, QString command)
{
    if (command.toStdString().compare("t") != 0 &&
            command.toStdString().compare("T") != 0 &&
            command.toStdString().compare("s") != 0 &&
            command.toStdString().compare("S") != 0)
        return;

    Baojitai* baojitai = Baojitai::instance();
    Product* product = baojitai->current_product();
    if (found_ && product)
    {
        Product::VisionParam param = product->vision_param();
        float x = x_;
        float y = y_;
        halcontools::transform_point(baojitai->image_to_robotic_matrix(), x, y, x, y);
        float dz = param.delta_z;
        float r = phi_;
        float s = param.delta_z_put;
        baojitai->send_product_information_to_robotic(x, y, dz, r, s);
    }
}

void LocationConfigDialog::on_toolButton_save_product_param_clicked()
{
    Product* current_product = Baojitai::instance()->current_product();
    if (!current_product)
    {
        QMessageBox::warning(this, QStringLiteral("未知产品型号"), QStringLiteral("请先创建选择产品"), QMessageBox::StandardButton::Ok);
        return;
    }

    int grab_z = ui->lineEdit_grap_z->text().toInt();
    int drop_z = ui->lineEdit_drop_z->text().toInt();

    ui->lineEdit_grap_z->setText(to_string(grab_z).c_str());
    ui->lineEdit_drop_z->setText(to_string(drop_z).c_str());

    if (grab_z < 5 || grab_z > 1000 || drop_z < 5 || drop_z > 1000)
    {
        QMessageBox::warning(this, QStringLiteral("Z Out of range"), QStringLiteral("5 ~ 400"), QMessageBox::StandardButton::Ok);
        return;
    }

    int l1 = ui->lineEdit_l1->text().toInt();
    int l2 = ui->lineEdit_l2->text().toInt();
    if (l1 < 100 || l1 > 800 || l2 < 100 || l2 > 800)
    {
        QMessageBox::warning(this, QStringLiteral("L Out of range"), QStringLiteral("100 ~ 800"), QMessageBox::StandardButton::Ok);
        return;
    }

    int size_var = ui->lineEdit_size_var->text().toInt();

    Product::VisionParam param = current_product->vision_param();
    param.delta_z = grab_z;
    param.delta_z_put = drop_z;
    param.l1 = l1;
    param.l2 = l2;
    param.xl1 = size_var;
    current_product->set_vision_param(param);
    current_product->save_config(ProductManager::instance()->product_config_path(current_product->name()));

    QMessageBox::warning(this, QStringLiteral("Success"), QStringLiteral("Saved"), QMessageBox::StandardButton::Ok);
}

void LocationConfigDialog::on_toolButton_clicked()
{
    Camera* camera = Baojitai::instance()->camera_location();
    if (camera && camera->is_open() && !camera->is_grabbing())
        camera->trigger();
}

void LocationConfigDialog::on_camera_buffer_changed(Camera* camera)
{
    if (camera == Baojitai::instance()->camera_location())
    {
        const unsigned char* image_buffer = NULL;
        int width, height;
        Baojitai::instance()->camera_location_buffer(&image_buffer, &width, &height);
        if (image_buffer)
        {
            HImage img("byte", width, height, (void*)image_buffer);
            halcon_image_ = img.CopyImage();
            ui->image_widget->update();
        }
    }
}

void LocationConfigDialog::on_pushButton_save_result_image_clicked()
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
            halcontools::write_location_image_ng(image, found_, x_, y_, phi_, l1_, l2_, "unknown", filename.toStdString());
        }
    }
}

void LocationConfigDialog::on_spinBox_x_offset_valueChanged(int arg1)
{
    Baojitai::instance()->set_robotic_x_offset(arg1);
}

void LocationConfigDialog::on_spinBox_y_offset_valueChanged(int arg1)
{
    Baojitai::instance()->set_robotic_y_offset(arg1);
}

void LocationConfigDialog::on_spinBox_z_offset_valueChanged(int arg1)
{
    Baojitai::instance()->set_robotic_rz_offset(arg1);
}
